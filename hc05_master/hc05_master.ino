#include <SoftwareSerial.h>

//master bluetooth BT10
SoftwareSerial BTSerial(10, 11);

const int ledPin = 13;

void setup() 
{
  Serial.begin(9600);
  BTSerial.begin(38400);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  int state;
 int data = 0;
 if (BTSerial.available())
 { 
    state = BTSerial.read(); // Reads the data from the serial port
 }
 if (Serial.available())
 {
    Serial.println("sending...");
    data = Serial.read();
    Serial.println(data);
    BTSerial.write(data);
 }
}

