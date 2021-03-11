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
#define SERVOMIN  110  // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  625  // this is the 'maximum' pulse length count (out of 4096)

// You can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. It's not precise!

void setup()
{
  Serial.begin(9600);

  Serial.println("setup");

  pwm.begin();
  pwm.setPWMFreq(60);
}

int angleToPulse(int ang)
{
  return map(ang, 0, 180, SERVOMIN, SERVOMAX);  // map angle of 0 to 180 to Servo min and Servo max
}

void set_deg(int servo, int deg)
{
  pwm.setPWM(servo, 0, angleToPulse(deg));
}

void set_all(int deg)
{
  for (int i = 0; i < 12; i++) {
    set_deg(i, deg);
  }
}

void loop()
{

  // hips
  set_deg(0, 90);
  set_deg(3, 90);
  set_deg(6, 90);
  set_deg(9, 90);

  // knees
  set_deg(1, 180);
  set_deg(4, 0);
  set_deg(7, 180);
  set_deg(10, 0);

  // ankles
  set_deg(2, 135);
  set_deg(5, 45);
  set_deg(8, 135);
  set_deg(11, 45);

  delay(3000);
}

