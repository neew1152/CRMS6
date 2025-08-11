void Checkline() // ถ้าออกเส้นเองจะโดนปรับฟาว 30 วิ
{
  // เช็คไม่ให้หุ่นออกเส้น (คิดง่ายๆอย่าคิดเยอะ)
  while(true)
  {
    ReadAnalog();
    if(L > 2000 && R > 2000)
    {
      holonomic(40,90,0);
      delay(500);
      return false;
    }
    else if(R > 2000)
    {
      holonomic(40,180,0);
      delay(500);
      return false;
    }
    else if(L > 2000)
    {
      holonomic(40,0,0);
      delay(500);
      return false;
    }
    else if(C > 2000)
    {
      holonomic(40,270,0);
      delay(600);
      return false;
    }
    else 
    {
      return false;
    }
  }
}
void CheckGoalyellow()
{
  if (huskylens.updateBlocks() && huskylens.blockSize[2]) // สีเหลือง
  {

  }
}
void CheckGoalbule()
{
  if (huskylens.updateBlocks() && huskylens.blockSize[3]) // สีน้ำเงิน
  {
    while(true)
    {

    }
  }
}