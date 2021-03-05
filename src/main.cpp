/*
  Server Robot
  Author: twooton
  Email: tcwooton@gmail.com
  Description: Spider Robot
*/

#include <Arduino.h>
#include <Helpers.h>
#include <Robo/Brain.h>
#include <Robo/IRReceiver.h>
#include <Robo/Servo.h>
#include <Robo/ServoShield.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>


// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  125  // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575  // this is the 'maximum' pulse length count (out of 4096)

// You can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. It's not precise!

void setup()
{
  Serial.begin(9600);

  Serial.println("setup");

  pwm.begin();
  pwm.setPWMFreq(60);
}

int angleToPulse(int ang){
  return map(ang, 0, 180, SERVOMIN, SERVOMAX);  // map angle of 0 to 180 to Servo min and Servo max
}

void loop()
{
  pwm.setPWM(0, 0, angleToPulse(0));

  delay(1000);

  pwm.setPWM(0, 0, angleToPulse(180));

  delay(1000);
}

