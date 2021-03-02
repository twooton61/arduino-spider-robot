/*
   Server Robot
   Author: twooton
   Email: tcwooton@gmail.com
   Description: Simple Robot
*/

#include <Arduino.h>
#include <Helpers.h>
#include <Robo/Brain.h>
#include <Robo/IRReceiver.h>
#include <Robo/Servo.h>

Robo::Brain robo_brain;

Robo::Servo robo_servo_front_left_hip(robo_brain, DIGITAL_IO_PIN(9), 90, Robo::Servo::ANGLE_SHRINKS_TO_STRAIGHTEN);
Robo::Servo robo_servo_front_right_hip(robo_brain, DIGITAL_IO_PIN(11), 90, Robo::Servo::ANGLE_GROWS_TO_STRAIGHTEN);
Robo::Servo robo_servo_back_left_hip(robo_brain, DIGITAL_IO_PIN(10), 90, Robo::Servo::ANGLE_GROWS_TO_STRAIGHTEN);
Robo::Servo robo_servo_back_right_hip(robo_brain, DIGITAL_IO_PIN(12), 90, Robo::Servo::ANGLE_SHRINKS_TO_STRAIGHTEN);

Robo::Servo robo_servo_front_left_knee(robo_brain, DIGITAL_IO_PIN(8), 90, Robo::Servo::ANGLE_SHRINKS_TO_STRAIGHTEN);
Robo::Servo robo_servo_front_right_knee(robo_brain, DIGITAL_IO_PIN(7), 0, Robo::Servo::ANGLE_GROWS_TO_STRAIGHTEN);
Robo::Servo robo_servo_back_left_knee(robo_brain, DIGITAL_IO_PIN(6), 0, Robo::Servo::ANGLE_GROWS_TO_STRAIGHTEN);
Robo::Servo robo_servo_back_right_knee(robo_brain, DIGITAL_IO_PIN(5), 90, Robo::Servo::ANGLE_SHRINKS_TO_STRAIGHTEN);
const int HIP_MODE = 0;
const int KNEE_MODE = 1;

int current_mode = HIP_MODE;

Robo::IRReceiver robo_ir_receiver(robo_brain, DIGITAL_IO_PIN(4));

namespace spider
{
inline void idle()
{
  delay(300);
}

inline void hips_flat()
{
  robo_servo_front_right_hip.flat();
  robo_servo_front_left_hip.flat();

  robo_servo_back_left_hip.flat();
  robo_servo_back_right_hip.flat();
}

inline void hips_base()
{
  robo_servo_front_right_hip.base();
  robo_servo_front_left_hip.base();
  robo_servo_back_left_hip.base();
  robo_servo_back_right_hip.base();
}

inline void hips_straight()
{
  robo_servo_front_right_hip.straight();
  robo_servo_front_left_hip.straight();
  robo_servo_back_left_hip.straight();
  robo_servo_back_right_hip.straight();
}

inline void knees_flat()
{
  robo_servo_front_right_knee.flat();
  robo_servo_front_left_knee.flat();

  robo_servo_back_left_knee.flat();
  robo_servo_back_right_knee.flat();
}

inline void knees_base() {
  robo_servo_front_right_knee.base();
  robo_servo_front_left_knee.base();

  robo_servo_back_left_knee.base();
  robo_servo_back_right_knee.base();
}

inline void knees_straight()
{
  robo_servo_front_right_knee.straight();
  robo_servo_front_left_knee.straight();

  robo_servo_back_left_knee.straight();
  robo_servo_back_right_knee.straight();
}

inline void walk()
{
  hips_base();
  knees_flat();
  delay(500);

  robo_servo_front_left_knee.straight();
  idle();
  robo_servo_front_right_knee.straight();
  idle();
}
}  // namespace spider

void setup()
{
  Serial.begin(9600);

  Serial.println("setup");

  pinMode(LED_BUILTIN , OUTPUT);

  robo_brain.setup();
}


static const int TICK_INTERVAL = 300;
unsigned long last_tick = 0;

void loop()
{
  if (millis() < last_tick + TICK_INTERVAL){
    return;
  }
  last_tick += TICK_INTERVAL;

  Serial.println(current_mode == HIP_MODE ? "hips" : "knees");

  Robo::IRReceiver::IRCode ir_code = 0;
  if (robo_ir_receiver.detect_signal()) {
    ir_code = robo_ir_receiver.get_ir_code();

    switch ( ir_code ){
      // all hips
      case 0xFFA25D:
      Serial.println("CH-");
      spider::hips_flat();
      delay(1000);
      break;
      case 0xFF629D:
      Serial.println("CH");
      spider::hips_base();
      delay(1000);
      break;
      case 0xFFE21D:
      Serial.println("CH+");
      spider::hips_straight();
      delay(1000);
      break;

      // all knees
      case 0xFF22DD:
      Serial.println("|<<");
      spider::knees_flat();
      delay(1000);
      break;
      case 0xFF02FD:
      Serial.println(">>|");
      spider::knees_base();
      delay(1000);
      break;
      case 0xFFC23D:
      Serial.println(">||");
      spider::knees_straight();
      delay(1000);

      break;
      case 0xFFE01F:
      Serial.println("-");
      current_mode = HIP_MODE;
      break;
      case 0xFFA857:
      Serial.println("+");
      current_mode = KNEE_MODE;
      break;
      case 0xFF906F:
      Serial.println("EQ");
      spider::walk();
      break;

      // front left
      case 0xFF6897:
      Serial.println("0");
      current_mode == HIP_MODE ? robo_servo_front_left_hip.flat() : robo_servo_front_left_knee.flat();
      break;
      case 0xFF9867:
      Serial.println("100+");
      current_mode == HIP_MODE ? robo_servo_front_left_hip.base() : robo_servo_front_left_knee.base();
      break;
      case 0xFFB04F:
      Serial.println("200+");
      current_mode == HIP_MODE ? robo_servo_front_left_hip.straight() : robo_servo_front_left_knee.straight();
      break;

      // front right
      case 0xFF30CF:
      Serial.println("1");
      current_mode == HIP_MODE ? robo_servo_front_right_hip.flat() : robo_servo_front_right_knee.flat();
      break;
      case 0xFF18E7:
      Serial.println("2");
      current_mode == HIP_MODE ? robo_servo_front_right_hip.base() : robo_servo_front_right_knee.base();
      break;
      case 0xFF7A85:
      Serial.println("3");
      current_mode == HIP_MODE ? robo_servo_front_right_hip.straight() : robo_servo_front_right_knee.straight();
      break;
      case 0xFF10EF:

      // back left
      Serial.println("4");
      current_mode == HIP_MODE ? robo_servo_back_left_hip.flat() : robo_servo_back_left_knee.flat();
      break;
      case 0xFF38C7:
      Serial.println("5");
      current_mode == HIP_MODE ? robo_servo_back_left_hip.base() : robo_servo_back_left_knee.base();
      break;
      case 0xFF5AA5:
      Serial.println("6");
      current_mode == HIP_MODE ? robo_servo_back_left_hip.straight() : robo_servo_back_left_knee.straight();
      break;

      // back right
      case 0xFF42BD:
      Serial.println("7");
     current_mode == HIP_MODE ? robo_servo_back_right_hip.flat() : robo_servo_back_right_knee.flat();
      break;
      case 0xFF4AB5:
      Serial.println("8");
      current_mode == HIP_MODE ? robo_servo_back_right_hip.base() : robo_servo_back_right_knee.base();
      break;
      case 0xFF52AD:
      Serial.println("9");
      current_mode == HIP_MODE ? robo_servo_back_right_hip.straight() : robo_servo_back_right_knee.straight();
      break;
    }

    Serial.println("IR CODE:");
    Serial.println(ir_code);

    robo_ir_receiver.resume();
  }
}
