# Understanding Robot Rotation IMU's Issues

### 1. Why does the degree freeze in `ReadMPU()`?

* Dead degrees occur when the IMU yaw crosses the **wrap-around boundary** (`±180°` or `0°/360°`).
* The original code only adjusted **negative angles** (`if (Value < 0) Value += 360`) for display, but the internal logic still used raw `pvYaw`.
* When the yaw goes from `180 → 360` (right turn) or `360 → 180` (left turn), the raw comparison fails, so the robot thinks the yaw hasn’t changed → appearing “frozen.”

---

### 2. Why is it not the same result every time, even with the same code?

* The `calibrate_IMU()` function repeatedly calls `zeroYaw()` in a loop until `pvYaw ≈ 0`.
* The IMU’s “zero” is set **based on whatever heading the robot happens to be facing at that moment**, which can vary slightly each run.
* Consequently, the effective reference direction changes randomly → some runs succeed in one direction, others fail in another.

---

### 3. Why is there only one successful direction after `zeroYaw()`?

* `zeroYaw()` resets the IMU’s current heading to 0°.
* After zeroing, the robot’s navigation logic uses `pvYaw` to determine turns.
* Because the reference is arbitrary (based on the robot’s orientation during zeroing), **only one direction relative to that reference looks correct**, while the other directions appear frozen or rotate incorrectly.

---

### 4. Why does leaving the robot for a long time and then testing change the successful direction?

* MEMS IMUs drift over time due to **temperature, gyro bias, or magnetic interference**.
* Each time you power on and zero the IMU, the “0° reference” shifts slightly because of drift and environmental changes.
* As a result, the previously successful direction may no longer align with the new zero → the robot’s working direction changes unpredictably.

---

### ✅ Key Takeaways

* **Do not repeatedly zero** the IMU; only zero once at a known heading.
* Always **normalize yaw** (`0–360°`) for consistent comparisons.
* Use an **angle difference function** to handle wrap-around when turning.
* Expect some drift in MEMS IMUs; consider calibrating once and using that as a stable reference.
