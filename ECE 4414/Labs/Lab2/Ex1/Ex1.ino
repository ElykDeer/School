void setup()
{
  Serial.begin(115200);
}

void loop()
{
  float val;
  long x;
  x = millis();
  val = abs(3 * sin(2 * 3.141592654 * x / 1000));
  delay(1);
  Serial.println(val);
}