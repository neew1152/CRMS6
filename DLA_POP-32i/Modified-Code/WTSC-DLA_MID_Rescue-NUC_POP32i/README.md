# ❓ FAQ

## ทำไมไฟล์วิดีโอดูไม่ได้
> Encode AV1 ใช้ VLC media player หรือ [Google Drive](https://drive.google.com/drive/folders/1qhZoBWKubuwgzbsChi92CIBQ9YKLyMjh)

## ถ้าอัปโหลดไม่สำเร็จจะเกิดอะไรขึ้น
> โค้ดไม่สมบูรณ์และทำให้ Bootloader เสียหาย อาจจะปิดเครื่องแล้วถอดแหล่งจ่ายไฟ รอประมาณ 2 ชั่วโมง ไมโครคอนโทรลเลอร์จะพยายาม Recovery ตัวเอง

## Yaw ของ IMU ไม่เสถียรแก้ไง
> Calibrate_IMU() ควรอยู่นิ่งให้มากที่สุด อาจจะใช้แอร์บับเบิ้ลพันรอบ ๆ IMU เพื่อให้มีการรบกวนน้อยที่สุด ถ้า Yaw ยังคงดริฟท์เยอะเกินไป... ซื้อใหม่

## ทำไมมอเตอร์วิ่งได้ระยะทางไม่เท่ากันเมื่อเวลาผ่านไป
> ความแรงของแบตเตอรี่

## ไมโครคอนโทรลเลอร์รีเซ็ตตัวเองเกิดจากอะไร
> แหล่งจ่ายไฟไม่เสถียร

# 🛒 Store

[INEX ZX-IMU](https://shopee.co.th/INEX-ZX-IMU-%E0%B9%82%E0%B8%A1%E0%B8%94%E0%B8%B9%E0%B8%A5%E0%B8%A7%E0%B8%B1%E0%B8%94%E0%B8%84%E0%B8%A7%E0%B8%B2%E0%B8%A1%E0%B9%80%E0%B8%AD%E0%B8%B5%E0%B8%A2%E0%B8%87%E0%B9%81%E0%B8%A5%E0%B8%B0%E0%B8%97%E0%B8%B4%E0%B8%A8%E0%B8%97%E0%B8%B2%E0%B8%87-Gyro-%E0%B9%80%E0%B8%8B%E0%B8%99%E0%B9%80%E0%B8%8B%E0%B8%AD%E0%B8%A3%E0%B9%8C-sensor-pop32i-i.243707191.28424813969)

[INEX POP-32i](https://inex.co.th/home/product/pop-32i/)

# 📚 Sources

[GitHub](https://github.com/neew1152/)

[Download This Directory](https://download-directory.github.io/?url=https%3A%2F%2Fgithub.com%2Fneew1152%2FCRMS6%2Ftree%2Fmain%2FDLA_POP-32i%2FModified-Code%2FWTSC-DLA_MID_Rescue-NUC_POP32i)
> Rename to "WTSC-DLA_MID_Rescue-NUC_POP32i.zip" > Extract to "WTSC-DLA_MID_Rescue-NUC_POP32i\\"
```cmd
WTSC-DLA_MID_Rescue-NUC_POP32i
    │   Experiment.ino
    │   Main-Motor-Movement.ino
    │   Motor-Movement-Kernel.ino
    │   Operation.ino
    │   README.md
    │   System-Kernel.ino
    │   WTSC-DLA_MID_Rescue-NUC_POP32i.ino
    │
    └───Docs
            PID-Explained.mp4
            POP32i-Sheet230316-re.pdf
            Stable-DLA_MID_Rescue-NUC_POP32i.mp4
```
