/*
 * Pellet Dispenser sketch to be uploaded to arduino with adafruit motor shield (v2)
 * connect the red and blue wires of the stepper motor to "m4" on the motor shield
 * connect the green and black wires to "m4" of the motor shield 
 * connect the red wires of the break beam to either 3.3v or 5v power supply
 * connect the black wires of the break beam to ground
 * connect the white wire of the breakb beam to pin 11
 */

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);

bool rot = true;
int disp = 0;
char command;
void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  AFMS.begin();  // create with the default frequency 1.6KHz
  myMotor->setSpeed(10);  // 10 rpm   
  pinMode(11, INPUT); // pin to read breakbeam
  digitalWrite(11, HIGH); //turn on pullup resistor 
}

void loop() {
  if (Serial.available()){
    command = Serial.read();
    Serial.println(command);
  } 
  if (command == '1') {
    if(rot == false){
      myMotor->step(25, FORWARD, SINGLE);
      delay(100);
    }
    else if(rot == true){
      myMotor->step(25, BACKWARD, SINGLE);
      delay(100);
    }
    command = 'n';
  }
  else if (command == '0'){
    Serial.write(command);
    command = 'n';
  } 
  if (!digitalRead(11)){
    disp++;
    if(disp == 5){
      disp = 0;
      rot = !rot;
    }
    delay(100);
  }
}

