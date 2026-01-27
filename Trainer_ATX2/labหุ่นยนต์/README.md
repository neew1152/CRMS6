# 0301 lab01glcd.ino
### 📌 คู่มือการใช้งานคำสั่ง `glcd()`
**รูปแบบคำสั่ง:** `glcd(uchar _x, uchar _y ,char *p,...)`
| พารามิเตอร์ | คำอธิบาย |
| :--- | :--- |
| **`x`** | บรรทัด (0 - 15) |
| **`y`** | ตัวอักษร (0 - 24) |
| **`*p`** | ข้อความที่ต้องการแสดง |
**ตัวระบุรูปแบบ (Format Specifiers):**
* `%d` : เลขจำนวนเต็ม -32,768 ถึง 32,767
* `%h` : เลขฐานสิบหก
* `%b` : เลขฐานสอง
* `%!` : แสดงตัวเลขจำนวนเต็มในช่วง -2,147,483,648 ถึง 2,147,483,647
* `%f` : ทศนิยม 3 หลัก
### 📄 โค้ดหลัก
```cpp
#include <ATX2.h>
int x = 99; // ของจริงเป็นค่าเซ็นเซอร์
void setup() {
XIO(); // Extended Input/Output
OK();
beep();
glcdMode(3); // หมุนกลับหัว
glcdClear();
glcd(1, 2, "Value = %d ", x); // แสดงค่า x
glcd(3, 2, "Knob = %d ", knob(0, 180)); // แสดงค่า knob
}
void loop() {
// ว่างเปล่า
}
```
---
# 0302 lab02fd.ino
### 📄 โค้ดหลัก
```cpp
#include <ATX2.h>
void setup() {
XIO(); // Extended Input/Output
OK();
beep();
glcdMode(3); // หมุนกลับหัว
glcdClear();
}
void loop() {
fd2(20, 40); // เดินหน้า M1 M2
delay(2000); // หน่วงเวลา 2 วินาที
ao(); // ปิดการทำงานมอเตอร์ทั้งหมด
while(1); // หยุดคอย (Infinite loop)
}
```
---
# 0303 lab03sensor
### 📄 Tab: `lab03sensor` (เวอร์ชั่นแรก)
```cpp
#include <ATX2.h>
void setup() {
XIO(); // Extended Input/Output
OK();
beep();
glcdMode(3); // หมุนกลับหัว
glcdClear();
}
void loop() {
glcd(1, 2, "A0 = %d ", analog(0)); // แสดงค่า analog(0)
}
```
### ➕ New Tab: `function` (สร้างแท็บใหม่สำหรับฟังก์ชัน)
```cpp
void showA() {
glcd(0, 2, "A0 = %d ", analog(0));
glcd(2, 2, "A2 = %d ", analog(2));
glcd(4, 2, "A5 = %d ", analog(5));
glcd(5, 2, "A7 = %d ", analog(7));
}
```
### 📄 Tab: `lab03sensor` (แก้ไขไฟล์หลักเพื่อเรียกใช้ฟังก์ชัน)
```cpp
#include <ATX2.h>
void setup() {
XIO(); // Extended Input/Output
OK();
beep();
glcdMode(3); // หมุนกลับหัว
glcdClear();
}
void loop() {
showA(); // เรียกใช้ฟังก์ชันจากแท็บ function
}
```
---
# 0303 lab04function (New File)
### 📄 File: `lab04function.ino` (สร้างไฟล์ใหม่)
```cpp
#include <ATX2.h>
// ค่าอ้างอิง (Black + White) / 2
int Ref_LL = 562;
int Ref_RR = 602;
int Ref_L = 562;
int Ref_R = 602;
// กำหนดตัวแปรเก็บค่าเซ็นเซอร์
int LL = analog(0);
int RL = analog(7);
int L = analog(2);
int R = analog(5);
void setup() {
XIO(); // Extended Input/Output
OK();
glcdMode(3); // หมุนกลับหัว
glcdClear();
beep();
fd_c();
// track_CL(30);
}
void loop() {
// ว่างเปล่า
}
// ฟังก์ชันเดินหน้าจนกว่าจะเจอเส้น (Forward until line)
void fd_c() {
while(1) { // วนลูป
if (analog(0) < Ref_LL) { // ถ้า A0 < ค่าอ้างอิง (เจอสีดำ)
break; // ออกจากลูป
}
fd(30); // ถ้ายังไม่เจอให้เดินหน้าต่อ
}
ao(); delay(1000); // หยุดมอเตอร์และหน่วงเวลา
}
// ฟังก์ชันเดินตามเส้น (Track line)
void trackline(int speed) {
L = analog(2); // อัปเดตค่าเซ็นเซอร์ซ้าย
R = analog(5); // อัปเดตค่าเซ็นเซอร์ขวา
if (L > Ref_L && R > Ref_R) { // L & R ขาว
fd(speed);
} else if (L < Ref_L && R > Ref_R) { // L ดำ & R ขาว
sl(speed);
} else if (L > Ref_L && R < Ref_R) { // L ขาว & R ดำ
sr(speed);
}
}
// ฟังก์ชันเดินตามเส้นจนกว่าจะเจอเส้นตัด
void track_CL(int speed1) {
while(1) {
if (analog(0) < Ref_LL) { // ถ้า A0 < Ref_LL (เจอสีดำ)
break; // ออกจากลูป
}
trackline(speed1); // เรียกใช้ฟังก์ชันเดินตามเส้น
}
ao(); delay(1000); // หยุดมอเตอร์
}
```
---
# 0304 crossturn
### ➕ New Tab: `turn` (สร้างแท็บใหม่ต่อจากโปรเจกต์เดิม)
```cpp
// ฟังก์ชันข้ามเส้นตัด (Cross)
void cross(int time) {
fd(30);
delay(time);
ao(); delay(100);
}
// ฟังก์ชันเลี้ยวขวา 90 องศา (Turn Right 90)
void R90() {
sr(30);
delay(200); ao(); // หมุนและหน่วงเวลาจน A3 พ้นเส้นดำ
R = analog(3); // เก็บค่าเซ็นเซอร์
while(R > Ref_R) { // วนลูปตราบที่ R ยังเป็นสีขาว (> Ref_R)
sr(30); // หมุนขวาต่อ
R = analog(3); // อัปเดตค่าเซ็นเซอร์
}
ao(); delay(200); // หยุดมอเตอร์
}
```

