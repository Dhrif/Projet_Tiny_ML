
## Important Notes

- The camera must be powered using **3.3V only**.
- Keep wires **short (<10 cm)** to reduce signal noise.
- VSYNC, HREF, and PCLK signals are required for proper frame synchronization.
- The OV7670 camera does **not contain internal memory**, meaning the Arduino reads pixels directly in real time.

---

# Edge Impulse Library Installation

## Step 1 – Download the Model Library

1. Open the Edge Impulse project  
   (link available in `1-EdgeImpulse/link_to_edge_impulse.md`)

2. Navigate to:
Deployment → Arduino Library

3. Select:
Arduino Nano 33 BLE Sense

4. Enable:
EON Compiler


5. Click **Build**

6. Download the generated **.zip library**

---

## Step 2 – Install the Library in Arduino IDE

1. Open **Arduino IDE**
2. Go to:
Sketch → Include Library → Add .ZIP Library


3. Select the downloaded `.zip`
4. Click **Open**

Arduino will automatically install the Edge Impulse library.

---

## Step 3 – Verify Installation

Check that the library appears in:
Sketch → Include Library

---

# Arduino Inference Program

The Arduino sketch performs the following tasks:

1. Initialize the **OV7670 camera**
2. Capture an image frame
3. Resize the image to **64×64 pixels**
4. Run the **Edge Impulse model**
5. Send classification results via **Serial communication**

---

## Output Format

The Arduino program sends predictions as a **JSON message**

This format allows **Node-RED to easily parse the data**.

---

## Uploading the Arduino Code

1. Open the sketch:
2-ArduinoCamera/arduino_camera_classification.ino


2. Select the board:
Tools → Board → Arduino Nano 33 BLE Sense


3. Select the correct serial port.

4. Click **Upload**.

---

# Node-RED Configuration

Node-RED is used to **visualize the classification results in real time**.

---

## Installing Node-RED

node --version && npm --version
npm install -g node-red
node-red

open : http://127.0.0.1:1880/
## Installing the Dashboard

1. Open **Node-RED**
2. Go to **Menu → Manage palette**
3. Search for:
node-red-dashboard



4. Click **Install** to install the package.

---

## Importing the Flow

The Node-RED flow is available in:
3-NodeRED/flows.json


To import it:

1. Open **Node-RED**
2. Go to **Menu → Import**
3. Select or paste the content of `flows.json`
4. Click **Import**
5. Click **Deploy**

---

## Serial Node Configuration

Open the **Serial In** node and configure the following parameters:

| Parameter | Value |
|----------|------|
| Port | Arduino COM port |
| Baud rate | 115200 |
| Data bits | 8 |
| Stop bits | 1 |
| Parity | None |

---

## Access the Dashboard

Open the following URL in your browser:

To import it:

1. Open **Node-RED**
2. Go to **Menu → Import**
3. Select or paste the content of `flows.json`
4. Click **Import**
5. Click **Deploy**

---

## Serial Node Configuration

Open the **Serial In** node and configure the following parameters:

| Parameter | Value |
|----------|------|
| Port | Arduino COM port |
| Baud rate | 115200 |
| Data bits | 8 |
| Stop bits | 1 |
| Parity | None |

---

## Access the Dashboard

Open the following URL in your browser:
http://localhost:1880/ui


The dashboard displays:

- detected component
- prediction probability
- detection counters
- system status

---

# Project Summary

This project successfully integrates:

- **OV7670 camera** with **Arduino Nano 33 BLE Sense**
- **Edge Impulse TinyML model**
- **Embedded real-time inference**
- **Node-RED visualization dashboard**

The system demonstrates how **machine learning can be deployed on microcontrollers for real-time electronic component classification**.






