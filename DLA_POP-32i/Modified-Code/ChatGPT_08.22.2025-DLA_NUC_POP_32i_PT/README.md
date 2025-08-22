# What’s Happening with the IMU & Robot Rotation

### 1. Why does the degree freeze?

<img width="1536" height="1024" alt="image" src="https://github.com/user-attachments/assets/4aad8b7f-e67e-41d2-b758-51475a7e261b" />

* Imagine your robot has a “compass” inside (the IMU) that tells it which way it is pointing.
* The robot’s brain is trying to turn it to a target angle by comparing its current direction to the target.
* But the compass goes from **0° to 360°** and then jumps back to 0°.
* If the robot is near that jump (like 359° → 0°), it gets confused and thinks it’s far from the target, so it keeps spinning — that’s why it looks frozen.

---

### 2. Why is it not the same result or the same successful direction even though it is the same code?

* Each time `calibrate_IMU()` is called, `zeroYaw()` sets the **current heading as 0°**.
* Depending on the robot’s orientation at that exact moment, the “zero reference” shifts.
* Therefore, the robot behaves differently in each run: only the direction aligned with the temporary zero heading works correctly.

---

### 3. Every time `zeroYaw()` is done it resets the IMU, but why is there only one successful direction?

* `zeroYaw()` defines **the current physical orientation of the robot as the IMU’s 0° reference**.
* All other directions are measured relative to this temporary zero.
* Since the control logic only reacts correctly when `pvYaw` matches the temporary zero, **only one direction appears successful**, and the others seem frozen or spin endlessly.

---

### 4. Why does leaving the robot for a long time and then testing change the successful direction?

* MEMS IMUs have **gyro drift and magnetometer biases** that change over time due to temperature, vibrations, or electrical noise.
* Each time you start the robot and zero the IMU, the “0° reference” might shift slightly because the IMU reading is not perfectly stable.
* This explains why the “working direction” changes over hours or between tests.

---

### ✅ Summary

* The root cause is **repeated or poorly timed zeroing of the IMU combined with wrap-around issues in yaw comparison**.
* Fixes include:

  1. Zero the IMU **only once** at startup when the robot faces a known reference.
  2. Normalize yaw to **0–360°**.
  3. Use **angle difference calculations** (`angleError`) to handle wrap-around smoothly.
  4. Improve packet reading to avoid frozen `pvYaw`.
