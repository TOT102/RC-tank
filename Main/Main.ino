#include "config.h"
#include <SBUS.h>
#include <limits.h>
#include "CytronMotorDriver.h"
 
int chanel[4];
int n;

SBUS sbus(Serial);

CytronMD motor1(PWM_PWM, 3, 4);  // PWM 1 = Pin 3 1 M1A, DIR 1 = Pin 5 1 M1B.
CytronMD motor2(PWM_PWM, 5, 6); // PWM 2 = Pin 4 1 M2A, DIR 2 = Pin 6 1 M2B.
CytronMD motor3(PWM_PWM, 7, 8); // PWM 2 = Pin 4 2 M2A, DIR 2 = Pin 6 2 M2B.
CytronMD motor4(PWM_PWM, 9, 10);// PWM 2 = Pin 4 2 M2A, DIR 2 = Pin 6 2 M2B.
 
void setup() {
  // put your setup code here, to run once:
  sbus.begin();
  
  motor1.setSpeed(0);
  motor2.setSpeed(0);  
  motor3.setSpeed(0);
  motor4.setSpeed(0);
}
ISR(TIMER2_COMPA_vect)
{
  sbus.process();
}

static int minChannel = INT_MAX;
static int maxChannel = INT_MIN;

// Scale the S.BUS channel values into the range [0, 255] for use as LED brightness values.
int getChannel(int channel) {
  int value = sbus.getChannel(channel);

  if (value < minChannel) {
    minChannel = value;
  }
  if (value > maxChannel) {
    maxChannel = value;
  }

  float result = value;

  result -= minChannel;
  result /= (maxChannel - minChannel);
  result *= 255;

  return (int)result;
}

void readChanels(){
  if (n <= 4){
    chanel[n] = getChannel(n);
    n++;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  readChanels();
  if (sbus.getChannel(4) > 1200){
    motor1.setSpeed(255);
    motor2.setSpeed(255);  
    motor3.setSpeed(255);
    motor4.setSpeed(255);
  }
  else {
    motor1.setSpeed(0);
    motor2.setSpeed(0);  
    motor3.setSpeed(0);
    motor4.setSpeed(0);
  }
  if (sbus.getChannel(3) > 1200){
    motor1.setSpeed(0);
    motor2.setSpeed(0);  
    motor3.setSpeed(255);
    motor4.setSpeed(255); 
  }
  else {
    motor1.setSpeed(0);
    motor2.setSpeed(0);  
    motor3.setSpeed(0);
    motor4.setSpeed(0);
  }
  if (sbus.getChannel(3) < 500){
    motor1.setSpeed(255);
    motor2.setSpeed(255);  
    motor3.setSpeed(-255);
    motor4.setSpeed(-255); 
  }
  else {
    motor1.setSpeed(0);
    motor2.setSpeed(0);  
    motor3.setSpeed(0);
    motor4.setSpeed(0);
  }
}