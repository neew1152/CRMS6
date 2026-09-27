# Overview Differences

Based on a review of the provided codebases, the transition from the **OEM** to the **Simplified** version represents a major refactoring effort. The changes focus heavily on **thread safety (FreeRTOS), hardware protection, code maintainability, and state-machine-based logic**.

Here are the primary technical differences between the two versions:

### 1. FreeRTOS & Thread Safety (Critical Upgrade)
The OEM version relies on multiple FreeRTOS tasks (`liftLoop`, `sonarLoop`, `switchGripperLoop`) but lacks proper resource locking, which can cause I2C bus collisions and data corruption.
*   **I2C Mutexes:** The `Simplified` version introduces `xSemaphoreCreateRecursiveMutex()`. Every time an I2C device (like the ToF sensor or motor driver) is accessed, it is wrapped in `xSemaphoreTakeRecursive(i2cMutex, ...)`. This prevents crashes if two tasks try to use the I2C bus simultaneously.
*   **Volatile Variables:** The `Simplified` version correctly tags variables shared between RTOS threads (like `Last_Distance`, `Ultrasonic_Enable`, `Lift_Target`) with the `volatile` keyword, preventing compiler optimization errors.
*   **Task Management:** Instead of aggressively suspending and resuming the Ultrasonic task (`vTaskSuspend`/`vTaskResume`) which can be unstable in FreeRTOS, the `Simplified` version uses a boolean flag (`if (Ultrasonic_Enable == 1)`) to control whether the sensor pulses or idles. 

### 2. Motor Safety & Lift Stall Detection
The `OEM` lift loop is a basic PID controller that will continuously feed power to the motor if it cannot reach its target, potentially burning out the motor.
*   **Stall Timeout:** The `Simplified` version implements a safety timeout in `LiftLoop`. It checks if the encoder count hasn't changed by at least 5 ticks within 500ms (`millis() - last_change_time > timeout_ms`). If the arm is stuck, it sets `stopped_due_to_timeout = true` and cuts power to the motor (`motorWrite(3, 0)`).

### 3. Arm & Gripper Logic (State Machine Refactoring)
The `OEM` version features highly complex, hardcoded movement sequences with dedicated tasks just for switching the grippers (`switchGripperLoop`).
*   **State-Based Control:** The `Simplified` version removes the `switchGripperLoop` task entirely. It replaces it with a clean `BalanceArm(char position)` function that uses a `switch-case` architecture to move the arms to predefined states ('C'losed, 'O'pen, 'L'eft, 'R'ight, 'S'top, 'W'ide).
*   **Generalized Action Functions:** Massive hardcoded blocks like `placeCan1` and `placeCan2` in OEM are consolidated into scalable `PickCan()` and `DropCan()` functions that accept arguments for which gripper to use and where to drop it.

### 4. Sensor Scope and Implementation
The physical hardware mapping and sensor reading strategies were scaled down and optimized.
*   **Line Sensors:** The `OEM` version expects 8 line sensors (`sensor_min[8]`). The `Simplified` version expects only 4 (`IRLED_Min[4]`).
*   **Ultrasonic Sensor:** The `Simplified` version adds a 5000-microsecond timeout to `pulseIn()`. In the OEM code, `pulseIn` could block the thread indefinitely if the echo pin missed a pulse.
*   **VL53L0X (ToF) Init:** The `OEM` version manually configures VL53L0X registers (budgets, pulse periods) in `setup()`. The `Simplified` version abstracts this (likely handled by an external library now) and strictly focuses on reading the 2-byte distance data safely using the I2C mutex.

### 5. Movement and Navigation Logic
*   **PID Tuning:** The base PD loop for driving forward (`FF`) and backward (`BB`) was detuned slightly for stability. The Proportional (Kp) value was reduced from `3.5` (OEM) to `2.8` (Simplified).
*   **Removal of Open-Loop Turns:** The `OEM` code had separate files with time-based, open-loop turn commands (`LL`, `RR`, `TL`, `TR`—which just fed arbitrary power to motors for a set time). The `Simplified` version removes these entirely, forcing all turns to route through the closed-loop PID `SpinDegree()` function, ensuring much higher accuracy.
*   **Code Consolidation:** Features scattered across `OEM_Func_Move.ino` and `OEM_Func_Spint-Turn.ino` were merged into a single `Simplified_Movement.ino`. Long `if/else` chains checking characters (`select == 'L'`) were modernized into `switch/case` statements.

### Summary
The **OEM** code feels like an iterative, prototype codebase where features were added as needed without a core architecture. The **Simplified** code is a professional refactor. It handles edge cases (motor stalls, blocked ultrasonic sensors, I2C bus collisions), reduces redundant code, and creates a much safer and predictable RTOS environment.

# Hardware Terminology Differences

Based on the provided code, the transition from the **OEM** to the **Simplified** version includes a significant overhaul of how the hardware components are named. 

The developer of the **Simplified** version updated the terminology to be much more accurate to industry-standard robotics hardware, moving away from colloquial or generic names.

Here are the specific hardware terminology differences:

### 1. Acoustic Distance Sensor: "Sonar" vs. "Ultrasonic"
*   **OEM Terminology:** Refers to the acoustic sensor as **"Sonar"** (e.g., `sonarLoop`, `readSonar()`, `sonarTaskHandle`). 
*   **Simplified Terminology:** Correctly identifies the sensor as **"Ultrasonic"** (e.g., `UltrasonicLoop`, `ReadUltrasonic()`, `UltrasonicTaskHandle`).
*   *Note:* While both use sound waves, "Sonar" is typically reserved for underwater acoustics, whereas "Ultrasonic" is the technically correct term for the HC-SR04 style sensors used in terrestrial robotics. Also, the physical pins changed from `27/14` to `13/4`.

### 2. Optical Distance Sensor: "IR/Can" vs. "ToF" (Time-of-Flight)
*   **OEM Terminology:** Refers to the VL53L0X sensor generically as **"IR"** (Infrared) or just names it based on its physical task in the game: **"Can Distance"** (e.g., `readCanDistance()`, `moveToCan0()`).
*   **Simplified Terminology:** Accurately refers to the hardware technology as **"ToF"** or Time-of-Flight (e.g., `ReadToF()`, `ToF_Distance`, `FFToF()`). 

### 3. Floor/Line Sensors: "Sensor/Line" vs. "IRLED"
*   **OEM Terminology:** Uses very generic naming for the downward-facing sensors, calling them **"sensor"** or **"line"** (e.g., `sensor_min`, `line_value`, `readLine()`). It assumes an 8-sensor array.
*   **Simplified Terminology:** Specifies the actual hardware component being read, changing the terminology to **"IRLED"** (Infrared Light Emitting Diode/Receiver) (e.g., `IRLED_Min`, `IRLED_Data`, `ReadIRLED()`). It reduces the array to 4 sensors.

### 4. Arm & Gripper Mechanics: "Switch/Shake" vs. "Balance/State"
*   **OEM Terminology:** Uses highly situational, task-specific verbs for the manipulator hardware, such as **"switchGripper"** and **"shakeGripper"**. 
*   **Simplified Terminology:** Replaces these with structural, kinematic terminology like **"BalanceArm"**, defining the hardware by its mechanical *state* ('C' for Closed, 'O' for Open, 'W' for Wide) rather than a specific sequence of game movements.

### 5. I2C Bus Terminology: "Wire1" vs. "Wire"
*   **OEM Terminology:** Explicitly instantiates an alternate I2C bus using **`Wire1.begin(25, 26)`** and `Wire1.beginTransmission()`.
*   **Simplified Terminology:** Reverts to the standard, default hardware I2C bus terminology **`Wire.begin()`** and relies on a `SoftI2C` library inclusion, indicating a change in how the microcontroller's hardware communication pins are mapped.

### Summary of Naming Conventions
The **OEM** code uses *CamelCase* and names hardware based on **what it interacts with** (e.g., `readCanDistance`, `readLine`). 
The **Simplified** code uses *PascalCase* and names hardware based on **what the component actually is** (e.g., `ReadToF`, `ReadIRLED`).
