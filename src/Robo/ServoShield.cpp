#include <Arduino.h>
#include <Robo/ServoShield.h>
#include <Helpers.h>

namespace Robo {
ServoShield::ServoShield(Brain& robo_brain, Adafruit_PWMServoDriver& servo_driver) :
  AbstractPart(robo_brain, String("ServoShield on pin ")),
  m_servo_driver(servo_driver),
  m_twbrbackup(TWBR)  // save I2C bitrate
{
}

void ServoShield::setup()
{
  m_servo_driver.begin();
  m_servo_driver.setPWMFreq(1600);  // This is the maximum PWM frequency


  TWBR = 12;  // upgrade to 400KHz!

  delay(100);
}

void ServoShield::go()
{
    // Drive each PWM in a 'wave'
  for (uint16_t i = 0; i < 4096; i += 8) {
    for (uint8_t pwmnum=0; pwmnum < 16; pwmnum++) {
      m_servo_driver.setPWM(pwmnum, 0, (i + (4096/16)*pwmnum) % 4096);
    }
  }
}
}  // namespace Robo
