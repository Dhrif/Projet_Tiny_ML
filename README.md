# TinyML Project – Vibration & Electronic Component Classification

## Overview

This project demonstrates the use of **Tiny Machine Learning (TinyML)** on embedded systems using the **Arduino Nano 33 BLE**.

The project is divided into two main parts:

1. **Vibration classification** using IMU sensor data and a TensorFlow Lite model.
2. **Electronic component classification and counting** using image recognition with Edge Impulse and a camera module.

The objective is to implement a complete embedded AI workflow:
- Data collection
- Model training
- Model deployment
- Real-time inference on a microcontroller.

---

# Repository Structure
Voici la **partie “Repository Structure” corrigée**, où j’ai **enlevé les `...`** et gardé uniquement les dossiers et fichiers principaux. Tu peux **remplacer directement cette section dans ton README**.

TinyML_project/
│
├── README.md
│
├── PARTIE_1_ClassificationVibrations/
│   ├── README.md
│   ├── 1-DataGeneration_Arduino/
│   │   └── data_generation.ino
│   │
│   ├── 2-Training/
│   │   ├── dataset/
│   │   ├── notebooks/
│   │   │   └── training_vibrations.ipynb
│   │   └── models/
│   │
│   ├── 3-Inference_Arduino/
│   │   └── inference_vibrations.ino
│   │
│   └── doc/
│       └── documentation.md
│
└── PARTIE_2_ClassificationComposants/
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
