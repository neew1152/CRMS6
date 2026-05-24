# Overview Differences

Based on the provided code files, the second set of code (`Simplified`) is a heavily refactored, modernized, and stabilized version of the first set (`OEM`). The modifications suggest the robot was experiencing hardware lockups (specifically I2C crashes), motor stalling, and erratic movements, which the new code aims to fix.

Here are the primary technical differences broken down by category:

### 1. RTOS Concurrency and Safety (Crucial Difference)
*   **I2C Mutex Protection:** The `OEM` code runs FreeRTOS tasks (`liftLoop`, `sonarLoop`, `switchGripperLoop`) on different cores. Because both the sensors (VL53L0X) and the motor driver appear to use the I2C bus (`Wire`), concurrent access in the `OEM` code would cause the ESP32 to crash. The `Simplified` code introduces `i2cMutex = xSemaphoreCreateRecursiveMutex();`. Every single I2C read/write and motor command in the `Simplified` code is safely wrapped in this mutex to prevent bus collisions.
*   **Volatile Variables:** The `Simplified` code properly declares variables shared between FreeRTOS tasks and the main loop (like `Ultrasonic_Enable`, `Last_Distance`) as `volatile`. The `OEM` code did not, which can lead to unpredictable behavior due to compiler optimization.
*   **Task Management:** The `OEM` code creates tasks and constantly suspends/resumes them (`vTaskSuspend`/`vTaskResume`). The `Simplified` code leaves the tasks running but uses software flags (like `Ultrasonic_Enable = 1`) to control execution flow, which is much safer and less prone to RTOS deadlocks.

### 2. Sensor Architecture
*   **IR Line Sensors (8 vs. 4):**
    *   The `OEM` code relies on an 8-channel analog line sensor array (`adcRead(0)` to `7`).
    *   The `Simplified` code removes half of these, using only a 4-channel array (`adcRead(0)` to `3`).
    *   The `OEM` code dynamically calculates Min/Max values via a `calibrateMinMax()` function. The `Simplified` code uses hardcoded `IR_Min` and `IR_Max` arrays, speeding up boot time but requiring manual tuning.
*   **Ultrasonic Sensor:**
    *   The `OEM` code's `pulseIn` function has no timeout. If the echo pin misses a signal, the entire FreeRTOS task freezes forever.
    *   The `Simplified` code adds a strict timeout: `pulseIn(ECHO_PIN, HIGH, 5000)`. If it doesn't get a reading within 5ms, it moves on, preventing system lockups.

### 3. Lift and Arm Mechanics
*   **Motor Stall Protection (Lift PID):** 
    *   The `OEM` lift PID loop will drive the motor forever if it doesn't reach its target. If a can is jammed, the motor will burn out.
    *   The `Simplified` code introduces a sophisticated **timeout mechanism** (`stopped_due_to_timeout`). If the encoder count doesn't change by at least 5 ticks within 500ms, it cuts power to the lift motor (`motorWrite(3, 0)`) to prevent stalling and burning out the hardware.
*   **Simplified Kinematics:** 
    *   The `OEM` code contains a highly complex, dedicated RTOS task just for swapping cans between the left and right grippers (`switchGripperLoop`). It also features a `shakeGripper()` function that violently shakes the servos back and forth to force cans to drop.
    *   The `Simplified` code completely deletes the shake logic and the gripper-switching task. It replaces them with cleaner, sequential state functions (`BalanceArm`, `StableCAN`, `DropPosition`) which suggests the physical hardware was upgraded or realigned to not require "shaking."

### 4. Movement and Control Theory (PID)
*   **Drastic PID Tuning Changes:** The control system for driving straight has been completely retuned.
    *   `OEM` KD (Derivative) values were very low: `Kp = 3.5`, **`Kd = 1.0`**.
    *   `Simplified` KD values are massively increased: `Kp = 2.8`, **`Kd = 15.0`** (and `17.0` for backward movement).
    *   *Technical Impact:* The `OEM` robot likely wobbled or oscillated back and forth while driving. The high KD in the `Simplified` code acts as a heavy dampener, making the robot drive much stiffer and straighter.
*   **Line Alignment (`SetFront` / `SetBack`):**
    *   The `OEM` code featured complex, multi-stage loops to align to a line, involving hard-coded pivot turns (`motorWrite(50, 50, 0, 0)`).
    *   The `Simplified` code removes all the complex pivoting. It just reads the 4 sensors and applies a simple reverse speed (`-12`) to the wheel that crosses the line first until both are perfectly aligned.
*   **Turning Consolidation:** The `OEM` code had dozens of turning functions (Pivot turns, Swing turns, `LL`, `RR`, `TL`, `TR`). The `Simplified` code deletes almost all of them, relying entirely on one highly refined `SpinDegree` function using the IMU (`angleRead(YAW)`).

### Summary
The `OEM` code is a classic "student/prototype" codebase: messy, overly complex physical compensations (like shaking the servos), and lacking hardware safety. 

The `Simplified` code is production-ready. It features RTOS thread safety (Mutexes), motor stall protection, non-blocking sensor reads, optimized PID dampening, and streamlined kinematics.

# Hardware Terminology Differences

When transitioning from the **OEM** to the **Simplified** code, the author made several specific changes to the **hardware terminology and component naming conventions**. The Simplified version adopts much more accurate, industry-standard engineering terms, clearing up ambiguity found in the original code.

Here is the breakdown of the hardware terminology differences:

### 1. Distance Sensing Terminology (Acoustic)
*   **OEM Term:** **"Sonar"** (`sonarLoop`, `readSonar()`)
*   **Simplified Term:** **"Ultrasonic"** (`UltrasonicLoop`, `ReadUltrasonic()`)
*   *Hardware Context:* The OEM code used "Sonar" (Sound Navigation and Ranging), which is traditionally associated with underwater acoustics. The Simplified code switches to "Ultrasonic," which is the correct hardware terminology for the standard HC-SR04 or similar air-based acoustic distance sensors used in robotics. 
*   *Pin Changes:* The physical hardware pins were also moved from `27/14` to `13/4`.

### 2. Distance Sensing Terminology (Optical / VL53L0X)
*   **OEM Term:** **"CanDistance" / "IR"** (`readCanDistance()`, and printed to Serial as `"IR: "`)
*   **Simplified Term:** **"Laser"** (`ReadLaser()`, `Laser_Distance`)
*   *Hardware Context:* The robot uses a VL53L0X Time-of-Flight (ToF) sensor to detect objects. The OEM code loosely called this "IR" (Infrared). While technically true (ToF uses an IR VCSEL laser), "IR" in robotics usually implies basic analog proximity sensors. The Simplified code renames this to **"Laser,"** which is much more descriptive of how a ToF sensor actually operates (shooting photons and measuring the time to bounce back).

### 3. Ground / Line Sensing Terminology
*   **OEM Term:** **"Sensor" / "Line"** (`sensor_min`, `line_value`, `readLine()`)
*   **Simplified Term:** **"IR"** (`IR_Data`, `IR_Min`, `ReadIR()`)
*   *Hardware Context:* The OEM code used highly generic terms ("sensor") for the bottom-facing line trackers. The Simplified code reclaims the term **"IR"** (Infrared) for these sensors. This is accurate, as line-tracking arrays (like the TCRT5000) rely on measuring reflected infrared light to distinguish between white and black surfaces. 
*   *Note on ambiguity:* The OEM version called the *distance* sensor "IR", but the Simplified version correctly applies "IR" to the *line* sensors and "Laser" to the distance sensor.

### 4. Hardware Communication Buses
*   **OEM Term:** **`Wire1`** (`Wire1.begin(25, 26)`)
*   **Simplified Term:** **`Wire`** / **`SoftI2C`**
*   *Hardware Context:* The OEM code explicitly forced the I2C communication (for the ToF sensor) onto a secondary hardware bus (`Wire1`) on specific ESP32 pins (25, 26). The Simplified version removes this and falls back on the default I2C bus (`Wire`). It also includes the `<SoftI2C.h>` library, indicating a shift from purely hardware-driven I2C to software-driven (bit-banged) I2C, likely to resolve hardware conflicts or allow for arbitrary pin usage.

### 5. Mechanism and Actuator Spelling/Casing
*   **Channel Mapping:**
    *   **OEM:** Uses misspelled variable names for the servo controller outputs: `chanal_Swing_Left`.
    *   **Simplified:** Corrects this to standard engineering nomenclature: `Channel_Swing_Left`.
*   *Hardware Context:* Simplified upgrades to a highly structured Capitalized_Snake_Case for global hardware states (`IR_Min`, `Swing_Current_Degree`, `Ultrasonic_Drop_Distance`), which is a common standard in embedded C/C++ to denote global hardware variables.

### Summary of Terminology Shift
The OEM code used conversational, beginner-friendly names (e.g., "Sonar", "Line Value", "Can Distance"). 
The Simplified code aligns with standard electromechanical engineering nomenclature (e.g., **"Ultrasonic"** for acoustic time-of-flight, **"Laser"** for optical time-of-flight, and **"IR"** for phototransistor reflectance data).
