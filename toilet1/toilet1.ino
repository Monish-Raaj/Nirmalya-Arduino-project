const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
int FloatSensor=9;int led1=13,statled=12;
int count=0,cn,usecount=0;
long int time_init=0,t;
int valvepin = 8;
#include<NewPing.h>
NewPing sonar(pingPin,echoPin);
int flag=0;
int buttonState = 1,noflo=0;
int pb=0;
  
byte sensorInterrupt = 0;  // 0 = digital pin 2
byte sensorPin       = 2;

// The hall-effect flow sensor outputs approximately 4.5 pulses per second per
// litre/minute of flow.
float calibrationFactor = 4.5;

volatile byte pulseCount;  

float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

unsigned long oldTime;


void setup() { pinMode(statled, OUTPUT);pinMode (led1, OUTPUT); 
  Serial.begin(9600); // Starting Serial Terminal
   pinMode(valvepin, OUTPUT);
   digitalWrite(valvepin, LOW);
  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;noflo=0;
pinMode(FloatSensor, INPUT_PULLUP); 
  // The Hall-effect sensor is connected to pin 2 which uses interrupt 0.
  // Configured to trigger on a FALLING state change (transition from HIGH
  // state to LOW state)
  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
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
  { digitalWrite(statled, HIGH); 
    if(flag==0)
     time_init=millis();flag=1;cn=0;
    Serial.print(time_init);Serial.println("Milliseconds Initial");}
   else
    {cn++;
     if(cn==3 && flag==1)
      {digitalWrite(statled, LOW);
        Serial.print(millis());
        Serial.println(" Milliseconds Current ");
     t=millis()-time_init;
     Serial.print(t);
     Serial.println(" Milliseconds Difference");
     delay(200);
     time_init=0;
     flag=0;}
    }
    if(t>5000)
    {flush();     
      usecount++;
     Serial.println(t);
     Serial.println("----FLUSH-----");

    }
    if(usecount>3)
    {usecount=0;
   // fullwash();
    Serial.println("-----FULL WASH-----");
    }
    if(flag==1&&(millis()-time_init)>(60000))
    {//warn
     Serial.println("------WARN-----");
     }
    t=0;
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
buttonState = digitalRead(FloatSensor); 
  if (!(buttonState == HIGH) )
  { 
    digitalWrite(led1, LOW);
    Serial.println( "WATER LEVEL - HIGH"); 
  } 
  else 
  { 
    digitalWrite(led1,HIGH);
    Serial.println( "WATER LEVEL - LOW" ); 
  } 


if(pb==1)
{Serial.println("-----------------------------------------------------PIPE BLOCKAGE------------------------------------------");
  digitalWrite(led1, HIGH);}

  
  if((millis() - oldTime) > 100)    // Only process counters once per second
  { 
   
   
   
   
   
   }
  delay(500);
}
void pulseCounter()
{
 
  pulseCount++;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
void flush()
{  digitalWrite(valvepin,HIGH);

int con=8;
while(con--)
{

buttonState = digitalRead(FloatSensor); 
 if ((buttonState == HIGH) )
  { 
    digitalWrite(led1, HIGH);
    Serial.println( "WATER LEVEL - LOW"); 
  } 
 // Disable the interrupt while calculating flow rate and sending the value to
    // the host
    detachInterrupt(sensorInterrupt);
       
    // Because this loop may not complete in exactly 1 second intervals we calculate
    // the number of milliseconds that have passed since the last execution and use
    // that to scale the output. We also apply the calibrationFactor to scale the output
    // based on the number of pulses per second per units of measure (litres/minute in
    // this case) coming from the sensor.
    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
    if(flowRate==0)
    noflo++;
else noflo=0;

   if(noflo>3  && buttonState==LOW)
  { Serial.println("-----------------------------------------------------PIPE BLOCKAGE------------------------------------------");
  digitalWrite(led1, HIGH);
  pb=1;}
  else
  {pb=0;
   digitalWrite(led1, LOW);}
    // Note the time this processing pass was executed. Note that because we've
    // disabled interrupts the millis() function won't actually be incrementing right
    // at this point, but it will still return the value it was set to just before
    // interrupts went away.
    oldTime = millis();
    
    // Divide the flow rate in litres/minute by 60 to determine how many litres have
    // passed through the sensor in this 1 second interval, then multiply by 1000 to
    // convert to millilitres.
    flowMilliLitres = (flowRate / 60) * 1000;
    
    // Add the millilitres passed in this second to the cumulative total
    totalMilliLitres += flowMilliLitres;
      
    unsigned int frac;
    
    // Print the flow rate for this second in litres / minute
  Serial.print("Flow rate: ");
    Serial.print(int(flowRate));  // Print the integer part of the variable
    Serial.print("L/min");
    Serial.println("\t");       // Print tab space

    // Print the cumulative total of litres flowed since starting
    Serial.print("Output Liquid Quantity: ");        
    Serial.print(totalMilliLitres);
    Serial.println("mL"); 
    Serial.print("\t");       // Print tab space
  Serial.print(totalMilliLitres/1000);
  Serial.println("L");
  //if(flowRate==0)
   //Serial.println(" ----PIPELINE FAULT---- ");

    

    // Reset the pulse counter so we can start incrementing again
    pulseCount = 0;

    // Enable the interrupt again now that we've finished sending output
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  
  delay(1000);




}



    


  digitalWrite(valvepin, LOW);
  
}
