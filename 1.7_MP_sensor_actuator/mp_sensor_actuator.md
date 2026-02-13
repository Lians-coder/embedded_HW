# 1.7 Miniproject: Sensor and actuator

## Purpose

A simple embedded project that reads an **LDR** and sets an **RGB** pixel color to represent outside brightness.  
Includes a small **state machine** for calibration, error handling, and normal operation.  

### Features

- Reads ambient light using an LDR.  
- Visualizes brightness using an RGB pixel (color gradient).  
- Button-based calibration workflow.  
- Error detection for out-of-range voltages.  
- Simple finite state machine for clear logic.  

### How it works

[KiCad schematic](https://github.com/Lians-coder/embedded_HW/blob/main/1.7_MP_sensor_actuator/miniproject1.7.kicad_sch) for this project.  

The system runs as a state machine:  

| State | Description |
| -- | -- |
| `NEED_CALIB` | White slow blinking - press button to start calibration |
| `NEED_MIN` | Cyan solid - cover LDR and press button to set minimum |
| `NEED_MAX` | Orange solid - expose LDR to max light and press button |
| `SUCCESS_CALIB` | Fast green blinks - calibration successful |
| `REGULAR` | Full color range changes based on brightness |
| `ERROR_ABOVE` | Red slow blinking - voltage above max |
| `ERROR_BELOW` | Blue slow blinking - voltage below min |
| `ERROR_UNKNOWN` | Purple fast blinking - invalid voltage or unknown error |
| `RESET_COMPLETED` | Fast cyan blinks - error recovered |
| `FORCE_CALIB` | Fast blue blinks - force recalibration |

### Code

1. Configuration [file](https://github.com/Lians-coder/embedded_HW/blob/main/1.7_MP_sensor_actuator/platformio.ini) with libs dependencies.  
2. [main.cpp](https://github.com/Lians-coder/embedded_HW/blob/main/1.7_MP_sensor_actuator/main.cpp) - main logic and color function.  
3. States of main logic, button state machine, blinking patterns in [include](https://github.com/Lians-coder/embedded_HW/blob/main/1.7_MP_sensor_actuator/include/).  

### Hardware

- ESP32-S3 DevKitC-1 N16R8  
- LDR  
- NeoPixel (on ESP32 board)  
- Push button  
- Resistors  

### Usage

1. Power on the device.  
2. Follow LED color instructions to calibrate min/max brightness.  
3. After calibration, pixel color changes based on ambient light.  
4. Hold the button to force recalibration if needed.  

### Demo

[Video](https://drive.google.com/file/d/1qO6ksbKZNcdMDNTSpYgZYkxUkulXRs9z/view?usp=sharing), short walkthrough of the whole flow, from setup to failure cases and recovery:  

1. Device boots into NEED_CALIB and walks through setting MIN and MAX brightness.  
2. Normal operation in REGULAR mode (LED color follows ambient light).  
3. Triggering error below min voltage and showing how the system recovers.  
4. Triggering error above max voltage and recovering from that too.  
5. Forcing the calibration process manually with a button hold.  
6. Purposely breaking the settings to enter UNKNOWN ERROR, then recovering back to a working state.  
