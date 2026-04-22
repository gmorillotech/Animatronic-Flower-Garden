# 🌼 Animatronic Flower Garden

An interactive Robotics project where flowers react to environmental light, motion, and wind using sensors.

---

## 📌 Project Description
The Animatronic Flower Garden is a kinetic sculpture consisting of three robotic flowers that respond dynamically to environmental stimuli such as light, wind, and human presence.

Each flower operates as an independent embedded system, capable of:
- Opening and closing petals based on light (phototropism)
- Swaying in response to wind or sound
- Recoiling when motion is detected nearby

This project combines **mechanical design, embedded systems, and real-time control** to create lifelike, organic motion.

---

## 👨‍💻 Team
- Denice Garcia  
- Arique Heemal
- George Morillo   

## 🧠 System Architecture

Each flower functions as a **self-contained unit**:

### 🔹 Inputs (Sensors)
- 🌞 LDR (photoresistor) → detects light for blooming
- 👤 PIR motion sensor → triggers recoil behavior
- 🌬️ Microphone → detects wind/sound for sway

### 🔹 Processing
- Arduino Nano processes sensor inputs
- State machine determines behavior:
  - Dormant
  - Blooming
  - Open
  - Recoiling
  - Closing

### 🔹 Outputs (Actuators)
- 🌼 x6 SG90 servos → control petal motion & stem sway

---

## 🌼 Mechanical Design

Each flower includes:

- 4x Petal blades
- Linkage rods connecting central-hub → petals
- Central hub (bloom mechanism)
- Rack and pinion gear system for blooming motion
- Push rod to move flower in swaying motion

→ Designed for **3D printing and modular assembly** 

---

## 🔌 Hardware Components

### Electronics
- x1 Arduino Nano
- x6 SG90 Micro Servos (×2 per flower)
- LDR (light sensor) -> 10kΩ resistor 
- PIR Motion Sensor
- Microphone module

### Power
- 5V external power supply -> Not yet 

### Mechanical / Structural
- 3D printed petals, hubs, linkage systems, gears, pivot rounded bottoms, pivot sockets, push rods, stems 
- Eyeglass pins, servo screws and metal screws, nuts
- Plastic pot, moss and foam

---

## 💻 Software Design

### Key Features

## Light-Responsive Blooming (LDR-Based)
- Flowers automatically open in bright light and close in darkness
- Uses a calibrated LDR + voltage divider circuit for reliable light sensing
- Implements binary threshold + hysteresis logic to prevent flickering or unstable movement

## Motion-Triggered Defensive Recoil (PIR Sensor)
- Detects nearby movement using a PIR motion sensor
- Flowers perform a rapid “recoil” closing behavior when motion is detected
- Includes timed hold and recovery for realistic, responsive interaction

## Sound-Activated Sway (Microphone Sensor)
- Uses a microphone to detect wind-like sound input
- Triggers a temporary swaying motion to simulate environmental interaction
- Filters noise using amplitude-based detection to avoid constant activation

### Example States
- **Dormant** → low light
- **Blooming** → petals opening
- **Open** → reacting to environment
- **Recoiling** → triggered by motion
- **Closing** → low light detected

---

## 🚀 Setup Instructions

1. Clone the repository:
```bash
git clone https://github.com/gmorillotech/Animatronic-Flower-Garden.git
