/*
  Server Robot
  Author: twooton
  Email: tcwooton@gmail.com
  Description: Spider Robot
*/

#include <Arduino.h>
#include <Helpers.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>


// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  110  // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  625  // this is the 'maximum' pulse length count (out of 4096)

// You can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. It's not precise!

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

const int FRONT_RIGHT_LEG_STARTING_JOINT = 0;
const int FRONT_RIGHT_HIP = 0;

const int FRONT_LEFT_LEG_STARTING_JOINT = 3;
const int FRONT_LEFT_HIP = 3;

const int BACK_LEFT_LEG_STARTING_JOINT = 6;
const int BACK_LEFT_HIP = 6;

const int BACK_RIGHT_LEG_STARTING_JOINT = 9;
const int BACK_RIGHT_HIP = 9;

const int FRONT_RIGHT_KNEE = 1;
const int FRONT_LEFT_KNEE = 4;
const int BACK_LEFT_KNEE = 7;
const int BACK_RIGHT_KNEE = 10;

const int FRONT_RIGHT_ANKLE = 2;
const int FRONT_LEFT_ANKLE = 5;
const int BACK_LEFT_ANKLE = 8;
const int BACK_RIGHT_ANKLE = 11;

int signal_joint = 0;

void setup()
{
  Serial.begin(9600);

  Serial.println("setup");

  pwm.begin();
  pwm.setPWMFreq(60);

  set_deg(FRONT_RIGHT_HIP, 135);
  set_deg(FRONT_LEFT_HIP, 45);
  set_deg(BACK_LEFT_HIP, 135);
  set_deg(BACK_RIGHT_HIP, 45);
}

const int DEFAULT_BTE = -1;

int bte = DEFAULT_BTE;

void loop()
{
  Serial.println("loop");

  int new_byte = Serial.read();
  if (new_byte != DEFAULT_BTE) {
    bte = new_byte;
  }

  Serial.print("received:");
  Serial.println(bte, DEC);

  switch (bte) {
    // 2, low base
    case 50:
      set_deg(FRONT_RIGHT_KNEE, 45);
      set_deg(FRONT_LEFT_KNEE, 135);
      set_deg(BACK_LEFT_KNEE, 45);
      set_deg(BACK_RIGHT_KNEE, 135);


      set_deg(FRONT_RIGHT_ANKLE, 45);
      set_deg(FRONT_LEFT_ANKLE, 135);
      set_deg(BACK_LEFT_ANKLE, 45);
      set_deg(BACK_RIGHT_ANKLE, 135);
      break;
    // 5, tippy toe
    case 53:
      set_deg(FRONT_RIGHT_KNEE, 67);
      set_deg(FRONT_LEFT_KNEE, 112);
      set_deg(BACK_LEFT_KNEE, 67);
      set_deg(BACK_RIGHT_KNEE, 112);


      set_deg(FRONT_RIGHT_ANKLE, 67);
      set_deg(FRONT_LEFT_ANKLE, 112);
      set_deg(BACK_LEFT_ANKLE, 67);
      set_deg(BACK_RIGHT_ANKLE, 112);
      break;

    // 8, tippy toe
    case 56:
      set_deg(FRONT_RIGHT_KNEE, 90);
      set_deg(FRONT_LEFT_KNEE, 90);
      set_deg(BACK_LEFT_KNEE, 90);
      set_deg(BACK_RIGHT_KNEE, 90);


      set_deg(FRONT_RIGHT_ANKLE, 90);
      set_deg(FRONT_LEFT_ANKLE, 90);
      set_deg(BACK_LEFT_ANKLE, 90);
      set_deg(BACK_RIGHT_ANKLE, 90);
      break;
    // 7, front left leg
    case 55:
      signal_joint = FRONT_LEFT_LEG_STARTING_JOINT;
      break;
    // 9, front right leg
    case 57:
      signal_joint = FRONT_RIGHT_LEG_STARTING_JOINT;
      break;
    // 1, back left
    case 49:
      signal_joint = BACK_LEFT_LEG_STARTING_JOINT;
      break;
    // 3, back right
    case 51:
      signal_joint = BACK_RIGHT_LEG_STARTING_JOINT;
      break;
    // <-
    case 68:
      break;
    // v
    case 66:
      break;
    // ->
    case 67:
      break;
  }


  delay(500);
}

