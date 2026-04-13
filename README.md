# 🌼 Animatronic Flower Garden

An interactive Robotics project where flowers react to environmental light using sensors, actuators and embedded control systems.

---

## 📌 Project Description
The Animatronic Flower Garden is a kinetic sculpture consisting of multiple robotic flowers that respond dynamically to environmental stimuli such as light, wind, and human presence.

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
- 🌼 4x SG90 servos → control petal motion
- 🔄 Stepper motor (28BYJ-48) → controls stem sway

---

## 🌼 Mechanical Design

Each flower includes:

- 4x Petal blades (servo-driven)
- Linkage rods connecting servo → petals
- Central hub (bloom mechanism)
- Spur gear system for stem motion
- Base housing for electronics

→ Designed for **3D printing and modular assembly** 

---

## ⚙️ Current Progress
- ✅ Servo-controlled petal opening/closing
- ✅ Light-based blooming behavior
- ✅ Multi-servo synchronization
- ✅ Smooth motion (easing)

---

## 🔌 Hardware Components

### Electronics
- Arduino Nano (1 per flower)
- SG90 Micro Servos (×4 per flower)
- 28BYJ-48 Stepper Motor + Driver
- LDR (light sensor)
- PIR Motion Sensor
- Microphone module

### Power
- 5V external power supply (recommended for stability)

### Mechanical / Structural
- 3D printed petals, hub, base, linkage system
- 3mm rods (pivot joints)
- Screws, nuts, washers

---

## 💻 Software Design

### Key Features
- Sensor polling (light, motion, sound)
- State machine-based behavior system
- Smooth servo motion using incremental stepping
- Reactive behaviors based on thresholds

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