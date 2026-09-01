void Compled_Grip()
{
  GripDown();
  Grip();
  GripUp();
}

void Compled_Put()
{
  GripDown();
  Put();
  GripUp();
}

void Grip()
{
  ao();
  ServoGrip();
  delay(250);
}

void Put()
{
  ao();
  ServoPut();
  delay(250);
}

void GripUp()
{
  ao();
  ServoGripUp();
  delay(250);
}

void GripDown()
{
  ao();
  ServoGripDown();
  delay(250);
}




void ServoGrip()
{
  servo(2, 150);
}

void ServoPut()
{
  servo(2, 50);
}

void ServoGripUp()
{
  servo(1, 75);
}

void ServoGripDown()
{
  servo(1, 0);
}