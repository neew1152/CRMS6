void ServoGrip()
{
  servo(1, 50);
}

void ServoPut()
{
  servo(1, 130);
}

void ServoGripUp()
{
  servo(1, 45);
}

void ServoGripDown()
{
  servo(1, 145);
}





void Grip()
{
  ao();
  ServoGrip();
  delay(200);
}

void Put()
{
  ao();
  ServoPut();
  delay(200);
}

void GripUp()
{
  ao();
  ServoGripUp();
  delay(200);
}

void GripDown()
{
  ao();
  ServoGripDown();
  delay(200);
}