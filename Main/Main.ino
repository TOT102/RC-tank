// Integration of PWM erceiver support
#include "config.h"
#include <limits.h>
#include "CytronMotorDriver.h"
#include <PWMreceiver.h>

int pinNumbers[] = {A0, A1, A2, A3}; 
size_t numPins = sizeof(pinNumbers) / sizeof(pinNumbers[0]);

PWMReceiver receiver(pinNumbers, numPins);
CytronMD motor1(PWM_PWM, M1A, M1B);  // PWM 1 = Pin 3 M1A, DIR 1 = Pin 5 M1B.
CytronMD motor2(PWM_PWM, M2A, M2B); // PWM 2 = Pin 4 1 M2A, DIR 2 = Pin 6 1 M2B.

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  motor1.setSpeed(0);
  motor2.setSpeed(0);  
}

void loop() {
  // polling:
  receiver.readData();

  if(receiver.getChannel() > 60){
    //forward
  }
  else if(receiver.getChannel() < 40){
    //backward
  }
  if(receiver.getChannel() > 60){
    //clockwise
  }
  else if(receiver.getChannel() < 40){
    //counter clockwise
  }

  

}
