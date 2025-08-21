void Checkline()  // ถ้าออกเส้นเองจะโดนปรับฟาว 30 วิ
{
  // เช็คไม่ให้หุ่นออกเส้น (คิดง่ายๆอย่าคิดเยอะ)
  ReadAnalog();
  if (B > 2000) {
    //holonomic(0, 0, 0);
    //Mode = 2; //เข้าโหมด 2 เพื่อเดินหน้าเเล้วกลับศุ่โหมด 1
    check = 1;
    holonomic(80, 90, 0);
    delay(150);
    return false;
  } else if (R > 2000) {
    //holonomic(0, 0, 0);
    sensor = 2;
    holonomic(80, 180, 0);
    delay(200);
  } else if (L > 2000) {
    //holonomic(0, 0, 0);
    sensor = 1;
    holonomic(80, 0, 0);
    delay(200);
  } else if (C > 2000) {
    //holonomic(0, 0, 0);
    sensor = 3;
    Mode = 1; //เข้าโหมดหนึ่งถอยหลัง timer เเล้ว Slide ค้นหา
    holonomic(90, 270, 0);
    delay(200);
  } 
}
void Checkline_Goalkeeper()
{
  // เช็คไม่ให้หุ่นออกเส้นตอนเป็นผู้รักษาประตู (คิดง่ายๆอย่าคิดเยอะ)
  ReadAnalog();
  if (B > 2000) {
    //holonomic(0, 0, 0);
    holonomic(70, 90, 0);
    delay(10);
  } else if (R > 2000) {
    //holonomic(0, 0, 0);
    sensor = 2;
    holonomic(70, 180, 0);
    delay(200);
  } else if (L > 2000) {
    //holonomic(0, 0, 0);
    sensor = 1;
    holonomic(70, 0, 0);
    delay(200);
  } else if (C > 1000) {
    //holonomic(0, 0, 0);
    holonomic(70, 270, 0);
    delay(200);
  }
}