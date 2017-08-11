#include "Wire.h"
#include "I2Cdev.h"
#include "ADXL345.h"
#include <SoftwareSerial.h>

ADXL345 acc;

int16_t ax, ay, az;

#define OUTPUT_READABLE_ACCELGYRO
#define LED_PIN 13
bool blinkState = false;

SoftwareSerial BTSerial(10, 11);

void setup() {
    Wire.begin();
    BTSerial.begin(38400);

    Serial.begin(9600);
    Serial.println("Initializing I2C devices...");
    acc.initialize();

    Serial.println("Testing device connections...");
    Serial.println(acc.testConnection() ? "ADXL345 connection successful" : "ADXL345 connection failed");
    pinMode(LED_PIN, OUTPUT);    
}

void loop() {
    // read raw accel measurements from device
    acc.getAcceleration(&ax, &ay, &az);

    // display tab-separated accel x/y/z values
    Serial.print("accel:\t");
    Serial.print(ax); Serial.print("\t");
    Serial.print(ay); Serial.print("\t");
    Serial.println(az);


    if (ay>150) {
      Serial.print("for");
      Serial.print("\t");
      BTSerial.write('u');
    }
    else if (ay<-150) {
      Serial.print("back");
      Serial.print("\t");
      BTSerial.write('d');
    }
    /*else {
      Serial.print("no_x");
      Serial.print("\t");
      BTSerial.write('0');
    }*/
    else if (ax>150) {
      Serial.print("right");
      Serial.print("\t");
      BTSerial.write('r');
    }
    else if (ax<-150) {
      Serial.print("left");
      Serial.print("\t");.'.=0                            \ \\
      BTSerial.write('l');
    }
    else {
      Serial.print("no_y");
      Serial.print("\t");
      BTSerial.write('0');
    }
    Serial.println("\n");

    #ifdef OUTPUT_BINARY_ACCELGYRO
        Serial.write((uint8_t)(ax >> 8)); Serial.write((uint8_t)(ax & 0xFF));
        Serial.write((uint8_t)(ay >> 8)); Serial.write((uint8_t)(ay & 0xFF));
        Serial.write((uint8_t)(az >> 8)); Serial.write((uint8_t)(az & 0xFF));
    #endif

    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
}
