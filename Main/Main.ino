// Integration of PWM erceiver support
#include "config.h"
#include <limits.h>
#include <CytronMotorDriver.h>
#include <PWMreceiver.h>
#include <Servo.h>

int pinNumbers[] = { A0, A1, A2, A3 };
size_t numPins = sizeof(pinNumbers) / sizeof(pinNumbers[0]);

Servo servo;
PWMReceiver receiver(pinNumbers, numPins);
CytronMD motor1(PWM_PWM, M1A, M1B);  
CytronMD motor2(PWM_PWM, M2A, M2B);  

void setup() {
  Serial.begin(9600);

  servo.attach(SERVO_PIN);
  motor1.setSpeed(0);
  motor2.setSpeed(0);
}

void loop() {
  // polling:
  receiver.readData();

  servo.write(receiver.getChannel(0));

  if (receiver.getChannel(1) > 60) {
    //forward
    motor1.setSpeed(255);
    motor2.setSpeed(255);
  } else if (receiver.getChannel(1) < 40) {
    //backward
    motor1.setSpeed(-255);
    motor2.setSpeed(-255);
  }
  if (receiver.getChannel(2) > 60) {
    //clockwise
    motor1.setSpeed(-255);
    motor2.setSpeed(255);
  } else if (receiver.getChannel(2) < 40) {
    //counter clockwise
    motor1.setSpeed(255);
    motor2.setSpeed(-255);
  }
}
