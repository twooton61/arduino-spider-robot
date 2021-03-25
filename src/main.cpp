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

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  110  // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  625  // this is the 'maximum' pulse length count (out of 4096)

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

static const int MAX_SERVOS = 12;
volatile int current_angles[MAX_SERVOS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
volatile int target_angles[MAX_SERVOS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

int signal_joint = 0;
int last_servo_tick = 0;
int last_keyboard_read_tick = 0;

const int SERVO_TICK = 20;
const int DEGREES_PER_TICK = 20;

int angleToPulse(int ang)
{
  return map(ang, 0, 180, SERVOMIN, SERVOMAX);  // map angle of 0 to 180 to Servo min and Servo max
}

void set_deg(int servo, int deg)
{
  target_angles[servo] = deg;
}

void set_all(int deg)
{
  for (int i = 0; i < MAX_SERVOS; i++) {
    set_deg(i, deg);
  }
}


inline void low_base()
{
  set_deg(FRONT_RIGHT_KNEE, 45);
  set_deg(FRONT_LEFT_KNEE, 135);
  set_deg(BACK_LEFT_KNEE, 45);
  set_deg(BACK_RIGHT_KNEE, 135);

  set_deg(FRONT_RIGHT_ANKLE, 45);
  set_deg(FRONT_LEFT_ANKLE, 135);
  set_deg(BACK_LEFT_ANKLE, 45);
  set_deg(BACK_RIGHT_ANKLE, 135);
}

inline void mid_base()
{
  set_deg(FRONT_RIGHT_KNEE, 67);
  set_deg(FRONT_LEFT_KNEE, 112);
  set_deg(BACK_LEFT_KNEE, 67);
  set_deg(BACK_RIGHT_KNEE, 112);

  set_deg(FRONT_RIGHT_ANKLE, 67);
  set_deg(FRONT_LEFT_ANKLE, 112);
  set_deg(BACK_LEFT_ANKLE, 67);
  set_deg(BACK_RIGHT_ANKLE, 112);
}

inline void high_base()
{
  set_deg(FRONT_RIGHT_KNEE, 90);
  set_deg(FRONT_LEFT_KNEE, 90);
  set_deg(BACK_LEFT_KNEE, 90);
  set_deg(BACK_RIGHT_KNEE, 90);

  set_deg(FRONT_RIGHT_ANKLE, 90);
  set_deg(FRONT_LEFT_ANKLE, 90);
  set_deg(BACK_LEFT_ANKLE, 90);
  set_deg(BACK_RIGHT_ANKLE, 90);
}

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

  low_base();
}

const int DEFAULT_KEYBOARD_CODE = -1;
int keyboard_code = DEFAULT_KEYBOARD_CODE;

void loop()
{
  const int latest_millies =  millis();
  if (latest_millies > (last_servo_tick + SERVO_TICK)) {
    last_servo_tick = latest_millies;

    for (int servo_index = 0; servo_index < MAX_SERVOS; servo_index++) {
      if (current_angles[servo_index] != target_angles[servo_index]) {
        Serial.print("Servo: ");
        Serial.print(servo_index);
        Serial.print(" , current: ");
        Serial.print(current_angles[servo_index]);
        Serial.print(" , target: ");
        Serial.print(target_angles[servo_index]);
        // current_angles[servo_index] += SERVO_TICK;
        current_angles[servo_index] = target_angles[servo_index];
        if (current_angles[servo_index] > target_angles[servo_index]) {
          current_angles[servo_index] = target_angles[servo_index];
        }

        Serial.print(" , new: ");
        Serial.println(current_angles[servo_index]);
      }

      pwm.setPWM(servo_index, 0, angleToPulse(target_angles[servo_index]));
    }
  }

  if (latest_millies > (last_keyboard_read_tick + 1000)) {
    Serial.println("keyboard tick");
    last_keyboard_read_tick = latest_millies;
    int potential_keyboard_code = Serial.read();
    if (potential_keyboard_code != DEFAULT_KEYBOARD_CODE) {
      keyboard_code = potential_keyboard_code;
    }

    Serial.print("received:");
    Serial.println(keyboard_code, DEC);

    switch (keyboard_code) {
      // 2, low base
      case 50:
        low_base();
        break;
      // 5, tippy toe
      case 53:
        mid_base();
        break;
      // 8, tippy toe
      case 56:
        high_base();
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
  }
}

