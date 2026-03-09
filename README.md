# TinyML Project – Vibration & Electronic Component Classification

## Table of Contents

- Overview
- Repository Structure
- Hardware Requirements
- Software Requirements
- Quick Start
- Documentation
- License

## Project Overview

This project explores practical applications of **Embedded Artificial Intelligence (TinyML)** on Arduino microcontrollers. It demonstrates how **optimized machine learning models** can be deployed on resource-constrained embedded systems to perform **real-time classification tasks**.

The goal of the project is to design a complete TinyML pipeline including:
- **Data collection**
- **Machine learning model training**
- **Model conversion for microcontrollers**
- **Deployment and real-time inference**

The project is divided into two complementary parts that illustrate different TinyML applications:

- **PART 1 – Vibration Classification**  
  Uses the **IMU sensor integrated in the Arduino Nano 33 BLE** to collect vibration data, train a classification model, and run inference directly on the microcontroller.

- **PART 2 – Electronic Component Classification**  
  Uses **embedded vision** with an **OV7670 camera module** and the **Edge Impulse platform** to recognize different electronic components and send the results to **Node-RED** for counting and visualization.

This project highlights the integration of several key technologies: **Arduino, TensorFlow Lite, Edge Impulse, and Node-RED** to build a complete intelligent embedded system.

---

## Repository Structure

```
TinyML_project/
│
├── README.md
│
├── Partie1/
│   ├── README.md
│   │
│   ├── 1-DataGeneration_Arduino/
│   │   └── data_generation.ino
│   │
│   ├── 2-Training/
│   │   ├── dataset/
│   │   ├── notebooks/
│   │   │   └── training_vibrations.ipynb
|   |   ├── models/
│   │   └── serial_to_csv.py
│   │
│   ├── 3-Inference_Arduino/
│   │   └── inference_vibrations.ino
│   │
│   └── doc/
│       └── documentation.md
│
└── Partie2/
    ├── README.md
    │
    ├── 1-EdgeImpulse/
    │   ├── link_to_edge_impulse.md
    │   └── instructions.md
    │
    ├── 2-ArduinoCamera/
    │   └── arduino_camera_classification.ino
    │
    ├── 3-NodeRED/
    │   ├── flows.json
    │   └── dashboard/
    │
    └── doc/
        └── documentation.md
```
## Hardware Used

The project was implemented using the following hardware components:

- **Arduino Nano 33 BLE**
- **DHT11 temperature and humidity sensor**
- **LED indicator**
- **OV7670 camera module**
- Jumper wires and breadboard

Since electronic components such as resistors and capacitors were not available during the experimentation phase, a **DHT11 sensor and an LED** were used instead to demonstrate the data acquisition and embedded inference workflow.

---

## Software Requirements

- Arduino IDE
- Python
- Jupyter Notebook
- TensorFlow / TensorFlow Lite
- Edge Impulse
- Node-RED



