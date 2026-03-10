# Edge Impulse Project Reproduction Guide

This document explains how to reproduce the Edge Impulse part of the project step by step, from connecting the hardware to training and testing the model.

---

# 1. Hardware Preparation

Before starting the Edge Impulse workflow, the **Arduino Nano 33 BLE Sense** must be prepared and connected.

## Flash the Board with Arduino CLI

The board must first be flashed using **Arduino CLI**.

Steps:

1. Install **Arduino CLI** if it is not already installed.
2. Navigate to the project directory containing the firmware for the board.
3. Flash the board using the firmware located in:
arduino_nano_33_ble_sense/

This firmware allows the board to communicate with Edge Impulse and stream camera data.

---

# 2. Connect the Board to Edge Impulse

1. Create or log in to your **Edge Impulse account**  
   https://studio.edgeimpulse.com

2. Create a **new project**.

3. Open a **terminal / shell**.

4. Run the following command to connect the board to the Edge Impulse project:

```bash
edge-impulse-daemon --clean
```

This command detects the connected device and links it to your Edge Impulse project.

Once the board is connected, you can start collecting data.

# 3. Data Acquisition

In the **Data Acquisition** section of Edge Impulse, there are two ways to add images:

- **Upload images** that were captured manually.
- **Capture images directly from the camera** connected to the board.

For this project, the **second method (live acquisition from the camera)** was used.  
This approach provided more reliable results during the inference stage on the embedded device.

### Selected Components

The dataset was created using the electronic components available during the experiment:

- **DHT11 sensor**
- **LED**
- **Background (no component)**

Each captured image was manually labeled according to the component visible in the frame.

### Dataset Composition

The dataset contains **92 images in total**, distributed as follows:

| Class | Number of Images |
|------|------|
| DHT11 | 31 |
| LED | 29 |
| Background | 27 |

These images were captured using the camera connected to the Arduino board.

---

# 4. Create Impulse

In the **Create Impulse** step, the image processing and machine learning pipeline was defined.

### Image Resolution

All images were resized to:
64 × 64 pixels


The detailed justification for choosing this resolution is explained in **documentation.md**.

### Pipeline Architecture

The following pipeline configuration was used:

#### Preprocessing Block

- **Block:** Image  
- **Purpose:**
  - Resize images
  - Normalize visual data

#### Learning Block

- **Block:** Classification  
- **Purpose:**
  - Perform image category recognition.

---

# 5. Feature Extraction

Navigate to:
Impulse Design → Image


in the Edge Impulse interface.

The following parameter was modified:

- **Color Depth:** Grayscale

Using grayscale images reduces memory usage and improves compatibility with embedded devices.

### Steps

1. Click **Save parameters**
2. Click **Generate Features**

---

# 6. Model Training

For the training phase, most of the **default parameters provided by Edge Impulse** were kept.

The only modification was:

- **Training cycles (epochs): 80**

Increasing the number of epochs allows the model to learn more effectively while keeping the training time reasonable.

Training results, including metrics and confusion matrices, are available in the following directory:
screenshots/


---

# 7. Live Classification Test

After training the model, Edge Impulse provides a **Live Classification** tool to test the model in real time.

### Steps

1. Go to **Live Classification**
2. Capture an image using the connected camera
3. Observe the predicted class and probability

Example outputs and screenshots of the classification results are available in:
screenshots/


---

## 8. Observations

### General Observations

The Edge Impulse workflow provides a clear and structured pipeline for building embedded machine learning models.  
From data acquisition to model training and live testing, the platform simplifies the process of developing an image classification system suitable for microcontrollers.

Using live data acquisition with the camera allowed the dataset to closely match the real conditions in which the model is later used during inference on the embedded device.

### Model Performance

During training, the model achieved an **accuracy of 100%** on the validation dataset.

While this result indicates that the model fits the current dataset very well, it is important to note that the dataset is relatively small and contains controlled conditions.  
Therefore, additional data collected under different lighting conditions, angles, and backgrounds could further improve the robustness and generalization of the model.

---



