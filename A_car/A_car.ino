#include <SoftwareSerial.h>
#include <Wire.h>

#define MAX_STRING 128
// The maximum received command length from an Android system over the bluetooth

/*
 * Connections Between HC-06 and Arduino ---
 * HC-06    Arduino
 * TX       RX/Pin10
 * RX       TX/Pin11
 */

SoftwareSerial BTSerial(10,11);     // HC06 <-> Arduino RX/TX

byte cmd[MAX_STRING];               // var: Received command from Android
int cmd_len = 0;                    // var: Received command length record
int mode = 0;                       // var: Mode for motor action

int IN1=4;                          // var: Motor A driver 1
int IN2=5;                          // var: Motor A driver 2
int IN3=6;                          // var: Motor B driver 1
int IN4=7;                          // var: Motor B driver 2

void forward(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void backward(){
  digitalWrite(IN2,HIGH);
  digitalWrite(IN1,LOW);
  digitalWrite(IN4,HIGH);
  digitalWrite(IN3,LOW);
}

void turnleft(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}

void turnright(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void stay(){
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
}

void setup(){
    for (int i=4; i<=7; i++)
        pinMode(i,OUTPUT);          // Init: Motor control driver pins
    for (int i=4; i<=7; i++)
        digitalWrite(i,OUTPUT);

    Serial.begin(9600);             // Init: Arduino <-> Computer Baud Rate
    BTSerial.begin(38400);           // Init: HC-06 <-> Arduino Baud Rate
    pinMode(13, OUTPUT);            // Init: Bluetooth Signal LED
}

void loop(){
    char str[MAX_STRING];           // var: String to be recieved
    int cmd_tmp_size;               // var: Command size waiting to be read.
    int i;                          // var: Reading loop counter
    int tick = 0;                   // var: 

    while ( tick < MAX_STRING ){
        cmd_tmp_size = BTSerial.available();        // Get the size of commands waiting to be read
        if ( cmd_tmp_size > 0 ){                    // If there are commands waiting
            for ( i=0; i < cmd_tmp_size; i++ ){     // For each command character waiting
                cmd[(cmd_len++)%MAX_STRING] = char(BTSerial.read());
                                                    // Read command character and save it into cmd
            }
        }
        else {
            tick++;
        }
    }

    if (cmd_len){                   // If cmd have content
        sprintf(str,"%s",cmd);      // Convert cmd to string, and print formatted string to str
        Serial.println(str[0]);     // Print str by Serial
        cmd[0] = '\0';              // Clean cmd
        if(str[0]=='0')             // Switch modes
          mode = 0;
        else if(str[0]=='u')
          mode = 1;
        else if(str[0]=='d')
          mode = 2;
        else if(str[0]=='l')
          mode = 3;
        else if(str[0]=='r')
          mode = 4;
        else
          mode = -1;
    }
    cmd_len = 0;                    // Reset cmd's length record
    
    if(mode == 1){                  // Switch mode actions
      digitalWrite(13,HIGH);
      forward();
    }
    else if(mode == 2){
      digitalWrite(13,HIGH);
      backward();
    }
    else if(mode == 3){
      digitalWrite(13,HIGH);
      turnleft();
    }
    else if(mode == 4){
      digitalWrite(13,HIGH);
      turnright();
    }
    else{
      digitalWrite(13, LOW);
      stay();
    }
}
