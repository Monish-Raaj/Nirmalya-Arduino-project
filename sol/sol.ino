// Code to Open and close an NC valve in 5 seconds gap.
int valvepin = 8;

void setup() {
  pinMode(valvepin, OUTPUT);
}

void loop() {
  //Opens the valve for 5 seconds
  digitalWrite(valvepin, HIGH);
  //delay(500000);
  //Close the valve for 5 seconds
  digitalWrite(valvepin, LOW);
  delay(500);
}
