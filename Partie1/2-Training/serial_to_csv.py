"""
============================================================================
SERIAL → CSV (Arduino IMU) — Project structure compliant
============================================================================

This script records IMU data streamed by Arduino over Serial and saves it
into the project's dataset folder:

PARTIE_1_ClassificationVibrations/2-Training/dataset/

DATA FORMAT EXPECTED (one sample per line):
  aX,aY,aZ,gX,gY,gZ

WINDOW SEPARATION:
- Empty lines are preserved in the output file.
- If your Arduino sketch prints an empty line after each 100 samples,
  then each "window" corresponds to one vibration example.

USAGE (per class):
1) Run the script
2) Enter output file name (e.g., vibration_motor.csv)
3) Let it record ~2 minutes
4) Stop with CTRL+C (or wait end)
5) Repeat for another class (idle, buzzer, ...)

REQUIREMENTS:
  pip install pyserial
"""

import serial
import time
from pathlib import Path

# =============================================================================
# CONFIGURATION (EDIT THESE)
# =============================================================================

SERIAL_PORT = "COM5"     # <-- Change this (Windows: COM5, Linux: /dev/ttyACM0, Mac: /dev/tty.usbmodemXXXX)
BAUD_RATE = 9600      # <-- Must match Arduino Serial.begin(...)
DURATION_SEC = 120       # 2 minutes per vibration type (class)
EXPECTED_COLS = 6        # aX,aY,aZ,gX,gY,gZ

# =============================================================================
# OUTPUT PATH (DO NOT CHANGE IF YOU WANT TO RESPECT THE GIVEN TREE)
# =============================================================================

# Path to: PARTIE_1_ClassificationVibrations/2-Training/dataset/
# This is computed relative to the script location.
SCRIPT_DIR = Path(__file__).resolve().parent
DATASET_DIR = (SCRIPT_DIR / "dataset").resolve()
DATASET_DIR.mkdir(parents=True, exist_ok=True)

# =============================================================================
# MAIN
# =============================================================================

filename = input("CSV file name (e.g., strong.csv): ").strip()
if not filename.endswith(".csv"):
    filename += ".csv"

out_path = DATASET_DIR / filename

print("\n=================================================")
print("[INFO] Serial → CSV recording")
print(f"[INFO] Port      : {SERIAL_PORT}")
print(f"[INFO] Baud rate : {BAUD_RATE}")
print(f"[INFO] Duration  : {DURATION_SEC} s")
print(f"[INFO] Output    : {out_path}")
print("[INFO] Press CTRL+C to stop early.")
print("=================================================\n")

windows_count = 0
samples_in_window = 0
total_samples = 0

with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser, open(out_path, "w", encoding="utf-8") as f:
    # Arduino often resets when serial opens → wait a bit
    time.sleep(2)
    ser.reset_input_buffer()

    # Write CSV header once
    f.write("aX,aY,aZ,gX,gY,gZ\n")

    start = time.time()

    try:
        while time.time() - start < DURATION_SEC:
            raw = ser.readline()
            if not raw:
                continue

            line = raw.decode("utf-8", errors="ignore").strip()

            # -----------------------------
            # 1) Empty line = window separator
            # -----------------------------
            if line == "":
                if samples_in_window > 0:
                    windows_count += 1
                    print(f"[OK] Window #{windows_count} saved ({samples_in_window} samples)")
                    samples_in_window = 0

                # Keep the empty line in the CSV
                f.write("\n")
                continue

            # -----------------------------
            # 2) Ignore Arduino headers / debug text
            # -----------------------------
            if line.startswith("aX,aY,aZ"):
                continue
            if line.startswith("#") or "Started" in line or "IMU" in line:
                continue

            # -----------------------------
            # 3) Validate CSV columns
            # -----------------------------
            parts = line.split(",")
            if len(parts) != EXPECTED_COLS:
                # Ignore malformed lines silently (or print warning if you prefer)
                continue

            # -----------------------------
            # 4) Save valid line
            # -----------------------------
            f.write(line + "\n")
            samples_in_window += 1
            total_samples += 1

    except KeyboardInterrupt:
        print("\n[INFO] Recording stopped by user.")

# If file ended without an empty separator, count the last window
if samples_in_window > 0:
    windows_count += 1
    print(f"[OK] Final window saved ({samples_in_window} samples)")

print("\n=================================================")
print("[DONE] Data acquisition finished.")
print(f"[DONE] File saved to: {out_path}")
print(f"[DONE] Windows (vibrations): {windows_count}")
print(f"[DONE] Total samples saved : {total_samples}")
print("=================================================")