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
#include <IRremote.h>

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
int last_input_read_tick = 0;

const int SERVO_TICK = 20;
const int DEGREES_PER_TICK = 20;

IRrecv ir_receiver(2);
decode_results ir_receiver_results;
typedef unsigned long IRCode;
IRCode last_ir_code = 0;

int angleToPulse(int ang)
{
  return map(ang, 0, 180, SERVOMIN, SERVOMAX);  // map angle of 0 to 180 to Servo min and Servo max
}

void set_deg(int servo, int deg)
{
  current_angles[servo] = deg;
  pwm.setPWM(servo, 0, angleToPulse(deg));
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

IRCode get_receiver_code()
{
  if (!ir_receiver.decode(&ir_receiver_results)) {
    return 0;
  }

  IRCode ir_code = ir_receiver_results.value;
  IRCode ir_code_to_consider = 0;

  const bool is_holding_button = ir_code == 4294967295;
  if (is_holding_button) {
    ir_code_to_consider = last_ir_code;
  }
  else {
    ir_code_to_consider = ir_code;
    last_ir_code = ir_code;
  }

  Serial.print("IR code: ");
  Serial.print(ir_code);
  Serial.print(" IR to consider: ");
  Serial.println(String(ir_code_to_consider));

  ir_receiver.resume();

  last_ir_code = 0;

  return ir_code_to_consider;
}

void base_hips()
{
  set_deg(FRONT_RIGHT_HIP, 135);
  set_deg(FRONT_LEFT_HIP, 45);
  set_deg(BACK_LEFT_HIP, 135);
  set_deg(BACK_RIGHT_HIP, 45);
}

void setup()
{
  Serial.begin(9600);

  Serial.println("setup");

  ir_receiver.enableIRIn();

  pwm.begin();
  pwm.setPWMFreq(60);

  base_hips();

  low_base();
}

void loop()
{
  const int latest_millies =  millis();

  if (latest_millies > (last_input_read_tick + 1000)) {
    IRCode ir_code = get_receiver_code();

    switch ( ir_code ){
      // all hips
      case 0xFFA25D:
      Serial.println("CH-");
      low_base();
      break;

      case 0xFF629D:
      mid_base();
      break;

      case 0xFFE21D:
      high_base();
      break;

      // all knees
      case 0xFF22DD:
      Serial.println("|<<");
      base_hips();
      break;

      case 0xFF02FD:
      Serial.println(">>|");
      break;

      case 0xFFC23D:
      Serial.println(">||");
      break;

      case 0xFFE01F:
      Serial.println("-");
      break;

      case 0xFFA857:
      Serial.println("+");
      break;

      case 0xFF906F:
      Serial.println("EQ");
      break;

      // front left
      case 0xFF6897:
      Serial.println("0");
      break;

      case 0xFF9867:
      Serial.println("100+");
      break;

      case 0xFFB04F:
      Serial.println("200+");
      break;

      // front right
      case 0xFF30CF:
      Serial.println("1");
      break;

      case 0xFF18E7:
      Serial.println("2");


      set_deg(BACK_RIGHT_KNEE, 180);
      delay(200);
      set_deg(BACK_RIGHT_HIP, 90);
      delay(200);
      set_deg(BACK_RIGHT_KNEE, 135);
      delay(200);

      set_deg(FRONT_RIGHT_KNEE, 0);
      delay(200);
      set_deg(FRONT_RIGHT_HIP, 180);
      delay(200);
      set_deg(FRONT_RIGHT_KNEE, 45);
      delay(200);

      set_deg(BACK_RIGHT_HIP, 45);
      delay(200);
      set_deg(FRONT_RIGHT_HIP, 135);
      delay(200);

      break;

      case 0xFF7A85:
      Serial.println("3");

      break;

      case 0xFF10EF:
      Serial.println("4");
      break;

      case 16726215:
      Serial.println("5");
      break;

      case 0xFF5AA5:
      Serial.println("6");
      break;

      case 0xFF42BD:
      Serial.println("7");
      break;

      case 0xFF4AB5:
      Serial.println("8");
      break;

      case 0xFF52AD:
      Serial.println("9");
      break;
    }
  }
}

