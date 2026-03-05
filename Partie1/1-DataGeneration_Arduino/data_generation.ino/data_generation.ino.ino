#include <Arduino_LSM9DS1.h>  // Library used to access the IMU (accelerometer + gyroscope)


// ============================================================================
// CONFIGURATION PARAMETERS
// ============================================================================

// Number of samples collected for each vibration sequence.
// This value must match the one used later in the Python training script.
const int numSamples = 100;

// Time interval between two measurements.
// 20 milliseconds corresponds approximately to a sampling frequency of 50 Hz.
const int sampleDelay = 20;


// ============================================================================
// GLOBAL VARIABLES
// ============================================================================

// Counter used to track how many samples have been collected
// in the current vibration sequence.
int samplesRead = 0;


// ============================================================================
// SETUP : executed once when the board starts
// ============================================================================
void setup() {

  // Start serial communication with the computer
  Serial.begin(9600);

  // Wait until the serial port is ready
  while (!Serial);

  // Initialize the IMU sensor
  // If initialization fails, stop the program
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  // Print the CSV header
  // This line defines the columns for the data file
  Serial.println("aX,aY,aZ,gX,gY,gZ");
}


// ============================================================================
// LOOP : runs continuously after setup
// ============================================================================
void loop() {

  // Variables used to temporarily store IMU measurements
  float aX, aY, aZ;   // acceleration values on X, Y, Z axes
  float gX, gY, gZ;   // angular velocity values from the gyroscope

  // Acquire a complete data window (numSamples measurements)
  while (samplesRead < numSamples) {

    // Check if new data is available from both sensors
    if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {

      // Read acceleration data
      IMU.readAcceleration(aX, aY, aZ);

      // Read gyroscope data
      IMU.readGyroscope(gX, gY, gZ);

      // Increase the sample counter
      samplesRead++;

      // --------------------------------------------------------------------
      // Send the sensor data to the computer in CSV format
      // --------------------------------------------------------------------

      Serial.print(aX, 3);
      Serial.print(',');

      Serial.print(aY, 3);
      Serial.print(',');

      Serial.print(aZ, 3);
      Serial.print(',');

      Serial.print(gX, 3);
      Serial.print(',');

      Serial.print(gY, 3);
      Serial.print(',');

      Serial.println(gZ, 3);

      // Small delay to control the sampling frequency
      delay(sampleDelay);
    }
  }

  // Print an empty line to separate vibration sequences
  Serial.println();

  // Reset the counter to start capturing a new vibration sequence
  samplesRead = 0;
}


/*
============================================================================
ADDITIONAL INFORMATION
============================================================================

1. DATA FORMAT

   The transmitted data follows the CSV format with the columns:

   aX,aY,aZ,gX,gY,gZ

   These correspond to the three axes of the accelerometer
   and the three axes of the gyroscope.

2. MEASUREMENT UNITS

   Acceleration : expressed in G (gravitational acceleration)
   Gyroscope    : expressed in degrees per second (deg/s)

3. DATASET STRUCTURE

   One vibration sequence corresponds to 100 lines of measurements.

   Example:

   aX,aY,aZ,gX,gY,gZ
   0.01,0.98,-0.02,0.12,0.03,-0.02
   ...
   (100 lines)

   An empty line is printed after each sequence to separate
   different vibration recordings.

4. DATASET CREATION

   The captured data should be stored in separate CSV files
   depending on the vibration type:

      weak.csv
      strong.csv
      vibration_idle.csv

   These files will then be used in Python to train
   the vibration classification model.

*/