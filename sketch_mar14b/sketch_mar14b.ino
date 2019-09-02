const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
int count=0,cn,usecount=0;
long int time_init=0,t;
#include<NewPing.h>
NewPing sonar(pingPin,echoPin,10);
int flag=0;
void setup() { pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600); // Starting Serial Terminal
}

void loop() {
  long duration, inches, cm;
  delay(50);
  cm=sonar.ping_cm();
  Serial.print(cm);
   Serial.print("cm");

  Serial.println();
}
