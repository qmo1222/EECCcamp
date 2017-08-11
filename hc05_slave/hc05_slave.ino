#include <SoftwareSerial.h>

//slave bluetooth BT22
SoftwareSerial BTSerial(10, 11);

const int led = 13;

void setup() 
{
  Serial.begin(9600);
  BTSerial.begin(38400);
  pinMode(led, OUTPUT);
}
void loop() 
{
  int state;
 if(BTSerial.available())
 { 
    state = BTSerial.read(); // Reads the data from the serial port
    Serial.println(state);
 }
 
 if (state == '1') 
 {
  digitalWrite(led, HIGH); // LED ON
  state = 1;
 }
 else if (state == '0') 
 {
  digitalWrite(led, LOW); // LED ON
  state = 0;
 }
}

