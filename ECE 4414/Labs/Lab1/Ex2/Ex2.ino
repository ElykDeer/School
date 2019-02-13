void setup() {
  Serial.begin(115200);

  unsigned char* portDDRB;

  portDDRB = (unsigned char*) 0x24;
  *portDDRB |= 0x20;
}

// the loop routine runs over and over again forever:
void loop() {
  int led = 13;
  
  digitalWrite(led, HIGH);
  Serial.println("LED ON");
  delay(1000);

  digitalWrite(led, LOW);
  Serial.println("LED OFF");
  delay(1000);
}
