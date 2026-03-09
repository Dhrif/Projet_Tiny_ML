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

  ## Quick Start

### Getting started with Vibration Classification (PARTIE 1)

1. Generate training data using the Arduino sketch `data_generation.ino`
2. Collect IMU vibration data and label the dataset
3. Train the machine learning model using the Jupyter notebook `training_vibrations.ipynb`
4. Export the trained model to **TensorFlow Lite (.tflite)**
5. Deploy the model on the Arduino using `inference_vibrations.ino`
6. Run real-time inference and observe the results via the Serial Monitor

---

### Getting started with Electronic Component Classification (PARTIE 2)

1. Open the Edge Impulse project (link available in `1-EdgeImpulse/link_to_edge_impulse.md`)
2. Upload and label images of electronic components (LED, resistor, sensor, etc.)
3. Train the image classification model in Edge Impulse
4. Export the model for **Arduino Nano 33 BLE**
5. Connect the **OV7670 camera module** to the Arduino
6. Upload `arduino_camera_classification.ino` to perform real-time inference
7. Send classification results to **Node-RED**
8. Import `flows.json` and start the **Node-RED dashboard** to visualize component counts
   

---

## License and Contribution

This project was developed in an **educational context** for teaching **Embedded Artificial Intelligence (TinyML)**.  
The repository is intended for learning purposes and experimentation with machine learning on embedded systems.

Contributions are welcome through:
- **Pull requests**
- **Issue reports**
- Suggestions for improvements or optimizations

If you would like to contribute, please feel free to open an issue or submit a pull request on this GitHub repository.

**Technologies used:**

- Arduino
- Edge Impulse
- TensorFlow Lite
- Node-RED
- Python

---

## Support and Troubleshooting

If you encounter issues while running the project, consider checking the following points:

- Ensure that all required **Arduino libraries** are correctly installed.
- Verify the **hardware connections** (sensors, camera, and board wiring).
- Make sure the **Edge Impulse model** is properly exported and integrated into the Arduino project.
- Confirm that **Node-RED is running correctly** and that the flow (`flows.json`) has been properly imported.
- Check the **Serial Monitor output** for debugging messages.

If the problem persists, you can open an **issue on the GitHub repository** describing:
- the problem encountered
- the hardware configuration
- the error messages displayed

This will help identify and resolve the issue more quickly.


