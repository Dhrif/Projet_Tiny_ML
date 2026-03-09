# PARTIE 1 : Vibration Classification with TinyML

## Overview

This part of the project implements a **real-time vibration classification system** running on an **Arduino Nano 33 BLE** using **TensorFlow Lite for Microcontrollers (TinyML)**.

The system detects and classifies vibrations into three categories:

- **idle** – No vibration (stable condition)
- **weak** – Low-intensity vibration
- **strong** – High-intensity vibration

The classification model is trained using IMU sensor data and then deployed directly on the microcontroller for real-time inference.

---

# System Pipeline

The project follows a **three-step TinyML pipeline**:
dataset/
├── vibration_idle.csv
├── weak.csv
└── strong.csv


---

# 2. Model Training (2-Training)

The training pipeline is implemented in a **Jupyter Notebook** using TensorFlow/Keras.

## Feature Extraction

Instead of using raw time-series signals, the system extracts **statistical features** from each vibration window.

Features are computed from the **acceleration magnitude** and **gyroscope magnitude**


