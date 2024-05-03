#include "config.h"
#include <SBUS.h>
#include <limits.h>
#include <CytronMotorDriver.h>
#include <Servo.h>

int chanel[4];
int n;

SBUS sbus(Serial);

Servo servo;

CytronMD motor1(PWM_PWM, M1A, M1B);  // PWM 1 = Pin 3 M1A, DIR 1 = Pin 5 M1B.
CytronMD motor2(PWM_PWM, M2A, M2B); // PWM 2 = Pin 4 1 M2A, DIR 2 = Pin 6 1 M2B.

 
void setup() {
  // put your setup code here, to run once:
  servo.attach(SERVO_PIN);
  sbus.begin();
  Serial.begin(9600);
  motor1.setSpeed(0);
  motor2.setSpeed(0);  
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
  Serial.println(sbus.getChannel(4));
  Serial.println(sbus.getChannel(3));

  if (sbus.getChannel(4) > 1200){
    motor1.setSpeed(255);
    motor2.setSpeed(255);  
  }
  else {
    motor1.setSpeed(0);
    motor2.setSpeed(0);  
  }
  if (sbus.getChannel(3) > 1200){
    motor1.setSpeed(0);
    motor2.setSpeed(0);  
  }
  else {
    motor1.setSpeed(0);
    motor2.setSpeed(0);  
  }
  if (sbus.getChannel(3) < 500){
    motor1.setSpeed(255);
    motor2.setSpeed(-255);  
  }
  else {
    motor1.setSpeed(0);
    motor2.setSpeed(0);  
  }
}
