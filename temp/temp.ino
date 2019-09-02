const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
int count=0,cn,usecount=0;
long int time_init=0,t;
#include<NewPing.h>
NewPing sonar(pingPin,echoPin);
int flag=0;
void setup() { pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600); // Starting Serial Terminal
}

void loop() {
  long duration, inches, cm;
  pinMode(echoPin, OUTPUT);
//  delayMicroseconds(2);
  //
// digitalWrite(echoPin, HIGH);
//delayMicroseconds(10);
digitalWrite(echoPin, LOW);
 pinMode(echoPin, INPUT);
  duration = sonar.ping();

  //inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  //Serial.print(inches);
  //Serial.print("in, ");
  if(cm!=0 && cm<70 )
  { digitalWrite(LED_BUILTIN, HIGH); 
    if(flag==0)
     time_init=millis();flag=1;cn=0;
    Serial.print(time_init);Serial.println("Milliseconds Initial");}
   else
    {cn++;
     if(cn==3 && flag==1)
      {digitalWrite(LED_BUILTIN, LOW);
        Serial.print(millis());
        Serial.println(" Milliseconds Current ");
     t=millis()-time_init;
     Serial.print(t);
     Serial.println(" Milliseconds Difference");
     time_init=0;
     flag=0;}
    }
    if(t>120000)
    {//flush()      usecount++;
     Serial.println(t);
     Serial.println("flush");

    }
    if(usecount>19)
    {usecount=0;
   // fullwash();
    Serial.println("full wash");
    }
    if(flag==1&&(millis()-time_init)>(150000))
    {//warn
     Serial.println("warn");
     }

    t=0;




  Serial.print(cm);
  Serial.print("cm");

  Serial.println();
  delay(500);
}


long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
