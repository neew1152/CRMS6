# MPU6050 Drift

### 🧭 Why Code Alone Isn't Enough

The MPU6050 provides only:

* **Gyroscope**: Measures angular velocity — but it **drifts over time** due to bias.
* **Accelerometer**: Can correct pitch and roll (gravity), but **not yaw** — gravity has no direction in the yaw plane.

That means:

* **Yaw (heading) has no absolute reference**.
* Your code can guess, filter, or average — but it **can't "anchor"** the yaw to the real world.

So no matter how clever the software is, without **external reference data**, you **will accumulate error**.

### 🛠️ In Summary:

| Goal                    | Can You Do It with Just Code?  | Hardware Needed                     |
| ----------------------- | ------------------------------ | ----------------------------------- |
| Zero yaw at startup     | ✅ Yes                         | None                                |
| Filter/smooth yaw       | ✅ Yes                         | None                                |
| Long-term yaw stability | ❌ No                          | Magnetometer                        |
| Drift elimination       | ❌ No                          | Sensor fusion (code **+** hardware) |

https://inex.co.th/store/manual/POP32i-Sheet230316-re.pdf
