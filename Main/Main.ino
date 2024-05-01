// Integration of PWM erceiver support
#include "config.h"
#include <limits.h>
#include "CytronMotorDriver.h"
 
int chanel[4];
int n;

CytronMD motor1(PWM_PWM, M1A, M1B);  // PWM 1 = Pin 3 M1A, DIR 1 = Pin 5 M1B.
CytronMD motor2(PWM_PWM, M2A, M2B); // PWM 2 = Pin 4 1 M2A, DIR 2 = Pin 6 1 M2B.

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  motor1.setSpeed(0);
  motor2.setSpeed(0);  
}

void loop() {
  // put your main code here, to run repeatedly:
}
