# Industrial Internet of Things – Position Monitoring System

##  Aim

To design and implement a real-time IoT-based system that monitors the position and orientation of an object using accelerometer and gyroscope sensors, displays the data on an OLED screen, and transmits it to the cloud using ThingSpeak.

---

##  Problem Statement

In many industrial environments, understanding how an object moves or changes its orientation is critical. This system is designed to observe these changes in real time using a simulated setup that collects accelerometer and gyroscope data and displays it both locally and remotely.

---

##  Scope of the Solution

- Monitor motion and orientation using MPU6050 (accelerometer + gyroscope).
- Display the sensor values on an OLED screen in real-time.
- Upload sensor readings to the cloud using Wi-Fi and ThingSpeak.
- Simulate the entire setup using Wokwi online simulator.

---

##  Required Components

###  Simulated Hardware (via Wokwi)
- ESP32 Development Board
- MPU6050 Accelerometer + Gyroscope Module
- OLED Display (128x64 I2C)

###  Software
- Wokwi Online Simulator

###  Cloud Platform
- ThingSpeak

###  Libraries Used
- `Wire.h`
- `Adafruit_MPU6050.h`
- `Adafruit_Sensor.h`
- `Adafruit_SSD1306.h`
- `Adafruit_GFX.h`
- `WiFi.h`
- `ThingSpeak.h`

---

##  Flowchart (Logic Steps)

1. Start
2. Initialize Serial Monitor
3. Initialize OLED Display
4. Initialize MPU6050 Sensor
5. Connect to WiFi  
   - If connection fails, halt and show error
6. Initialize ThingSpeak connection
7. Begin loop:
   - Read accelerometer and gyroscope values
   - Display values on OLED
   - Upload values to ThingSpeak
   - Wait for 20 seconds
   - Repeat loop

---

##  ThingSpeak Channel Configuration

| Field No. | Label              |
|-----------|--------------------|
| Field 1   | Accelerometer X    |
| Field 2   | Accelerometer Y    |
| Field 3   | Accelerometer Z    |
| Field 4   | Gyroscope X        |
| Field 5   | Gyroscope Y        |
| Field 6   | Gyroscope Z        |

 https://thingspeak.mathworks.com/channels/3004286

---

##  Wokwi Simulation

 https://wokwi.com/projects/435754657634787329

---

##  Video Demonstration

 https://drive.google.com/file/d/1oi1nDqLZAsC7DeRmHi-lXmsIfr0ga6dn/view?usp=sharing

---

##  Summary

This project offers an elegant simulation of an Industrial IoT system that monitors object movement and orientation in real time. It combines sensor data collection, live display, and cloud connectivity through a streamlined approach, all powered within a virtual environment using Wokwi. The system is simple, effective, and ready for real-world extension.

---
