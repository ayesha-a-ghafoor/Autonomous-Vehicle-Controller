# Autonomous-Vehicle-Controller
Register-level embedded C firmware for an ATmega328P microcontroller driving an autonomous obstacle-avoiding robotic vehicle.



---



A low-level **Embedded Systems & Robotics** project developed entirely in **register-level Embedded C** for controlling an intelligent autonomous obstacle-avoiding robotic vehicle using the **ATmega328P AVR microcontroller** architecture.

The system demonstrates real-time sensor processing, hardware timer configuration, PWM-based motor control, and complete hardware-software integration through Proteus simulation.

---

# 📌 Project Overview

This project focuses on building a fully autonomous robotic vehicle capable of:

* Detecting nearby obstacles in real time
* Making autonomous steering decisions
* Controlling motor speed and direction dynamically
* Executing firmware directly through AVR register manipulation
* Simulating full hardware circuitry before physical deployment

Unlike traditional Arduino-based implementations, this system was developed using **bare-metal Embedded C** without relying on high-level abstraction libraries.

---

# ⚙️ Core Technical Features

# 🧠 1. Register-Level Firmware Development

### ✔ Bare-Metal Embedded Programming

* Direct interaction with AVR hardware registers
* No Arduino libraries or HAL abstractions used
* Optimized low-level firmware execution

### ✔ Hardware Timer Configuration

Configured:

* 8-bit timers
* 16-bit timers
* Prescalers
* Compare registers

to achieve:

* Precise timing control
* Non-blocking execution cycles
* Stable sensor polling intervals

---

# 📡 2. Sensor Integration Using Input Capture

### ✔ Ultrasonic Distance Sensing

Integrated the **HC-SR04 Ultrasonic Sensor** for obstacle detection and spatial awareness.

### ✔ External Interrupt Handling

Implemented external interrupt routines to:

* Trigger ultrasonic pulses
* Capture returning echo signals
* Process real-time distance measurements

### ✔ Input Capture Unit (ICU)

Used the ATmega328P’s built-in **Input Capture Unit** to measure pulse durations with microsecond-level precision for accurate distance computation.

---

# ⚡ 3. PWM-Based Motor & Steering Control

### ✔ Pulse Width Modulation (PWM)

Generated high-speed PWM signals using hardware timer registers to control:

* Motor speed
* Acceleration
* Deceleration

### ✔ H-Bridge Motor Driver Integration

Interfaced PWM outputs with:

* `L293D`
* `L298N`

H-Bridge drivers for:

* Bidirectional motor control
* Dynamic steering logic
* Synchronized movement operations

---

# 🛠️ Hardware Components & Simulation Environment

| Component               | Description                   |
| ----------------------- | ----------------------------- |
| **Microcontroller**     | ATmega328P (AVR Architecture) |
| **Distance Sensor**     | HC-SR04 Ultrasonic Sensor     |
| **Motor Driver**        | L293D / L298N H-Bridge        |
| **Actuators**           | Dual DC Geared Motors         |
| **Steering System**     | Servo-Based Steering Control  |
| **Simulation Software** | Proteus Design Suite          |

---

# 🔄 System Workflow

1. Ultrasonic sensor continuously scans surroundings
2. Distance values are captured using ICU timing
3. Firmware analyzes obstacle proximity
4. Steering algorithm determines movement direction
5. PWM signals dynamically adjust motor behavior
6. Vehicle autonomously avoids collisions

---

# 🚀 How to Run & Simulate

## 1️⃣ Clone the Repository

```bash
git clone <repository-link>
```

---

## 2️⃣ Compile the Firmware

Open the project inside:

* **Microchip Studio**
* **Atmel Studio**

Compile the source code to generate the `.hex` firmware file.

---

## 3️⃣ Launch the Hardware Simulation

Open the Proteus project file (`.pdsprj`) inside:

* **Proteus Design Suite**

---

## 4️⃣ Load the Firmware

Inside Proteus:

1. Double-click the **ATmega328P** microcontroller
2. Browse and attach the compiled `.hex` file
3. Press the **Run / Play** button

The autonomous robotic vehicle simulation will begin executing in real time.

---

# 📊 Key Embedded Concepts Demonstrated

* Bare-Metal Embedded C Programming
* AVR Register Manipulation
* Hardware Timers & Prescalers
* PWM Signal Generation
* External Interrupt Handling
* Input Capture Unit (ICU)
* Real-Time Sensor Processing
* Autonomous Navigation Logic
* Motor Driver Interfacing
* Hardware-Software Co-Design

---

# 💻 Technologies Used

* Embedded C
* AVR Architecture
* ATmega328P
* Microchip Studio
* Proteus Design Suite
* PWM & Timer Modules
* Ultrasonic Sensor Integration

---

# 🎯 Project Goals

* Build a fully autonomous robotic navigation system
* Demonstrate low-level firmware engineering
* Explore real-time embedded control systems
* Optimize hardware-software interfacing
* Simulate complete robotics workflows before deployment

---

# 👨‍💻 Project Domain

* Embedded Systems
* Robotics
* Firmware Engineering
* Real-Time Systems
* Autonomous Vehicle Control
* AVR Microcontroller Programming

