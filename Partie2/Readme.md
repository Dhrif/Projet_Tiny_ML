# Embedded Component Classification with Arduino & Edge Impulse

## Project Presentation

### Overview

This project demonstrates how to build an **embedded computer vision system** capable of recognizing electronic components using an **Arduino Nano 33 BLE Sense** and the **OV7670 camera module**.

The system uses **Edge Impulse** to train a lightweight machine learning model that can classify images captured by the camera directly on the microcontroller.

Once trained, the model is deployed to the Arduino board, allowing **real-time classification of components**.

The predictions are also sent through **Serial communication**, which can be connected to **Node-RED** for visualization or further processing.

---

### Objectives

The main objectives of this project are:

- Capture images using an **OV7670 camera**
- Train an **image classification model** using **Edge Impulse**
- Deploy the model to an **embedded system**
- Perform **real-time inference on Arduino**
- Send classification results to **Node-RED**

---

### Components Used

Hardware:

- **Arduino Nano 33 BLE Sense**
- **OV7670 Camera Module**
- **Electronic components for classification**
  - DHT11 Sensor
  - LED
- USB cable

Software:

- **Arduino IDE / Arduino CLI**
- **Edge Impulse Studio**
- **Node-RED**
- **Edge Impulse CLI tools**

---

### Dataset

The dataset used to train the model contains **92 images** divided into three classes:

| Class | Images |
|------|------|
| DHT11 | 31 |
| LED | 29 |
| Background | 27 |

All images were captured using the **camera connected to the Arduino board** through the Edge Impulse data acquisition interface.

Images were resized to:
## Installation and Usage Guide

### Step 1: Edge Impulse Configuration
1. Follow the instructions in [`1-EdgeImpulse/instructions.md`](1-EdgeImpulse/instructions.md)
2. Create an **Edge Impulse account** if you do not already have one.
3. Access or import the project using the provided **Edge Impulse project link**.
4. Collect training data for each component class using the connected camera.

---

### Step 2: Arduino Programming
1. Install the **Edge Impulse Arduino library** (see [`doc/documentation.md`](doc/documentation.md)).
2. Open the Arduino sketch:  
   [`2-ArduinoCamera/arduino_camera_classification/arduino_camera_classification.ino`](2-ArduinoCamera/arduino_camera_classification/arduino_camera_classification.ino)
3. Upload the program to the **Arduino Nano 33 BLE Sense**.
4. Verify the **Serial connection** with a baud rate of **115200**.

---

### Step 3: Node-RED Configuration
1. Install **Node-RED** and the **Node-RED Dashboard module**.
2. Import the flow from:  
   [`3-NodeRED/flows.json`](3-NodeRED/flows.json)
3. Configure the **Serial port** in the **Serial In** node (select the correct COM port).
4. Access the dashboard at:

