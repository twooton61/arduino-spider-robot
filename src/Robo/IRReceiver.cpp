#include <Arduino.h>
#include <Robo/IRReceiver.h>
#include <Helpers.h>

namespace Robo {
IRReceiver::IRReceiver(Brain& robo_brain, const int pin) :
  AbstractPart(robo_brain, "IR Receiver"),
  m_pin(pin),
  m_ir_receiver(pin)
{
}

void IRReceiver::setup()
{
  m_ir_receiver.enableIRIn();
  m_ir_receiver.blink13(true);
}

bool IRReceiver::detect_signal()
{
  return m_ir_receiver.decode(&m_ir_receiver_results);
}

IRReceiver::IRCode IRReceiver::get_ir_code()
{
  IRCode ir_code = m_ir_receiver_results.value;
  IRCode ir_code_to_consider = 0;

  const bool is_holding_button = ir_code == 4294967295;
  if (is_holding_button) {
    ir_code_to_consider = m_last_ir_code;
  }
  else {
    ir_code_to_consider = ir_code;
    m_last_ir_code = ir_code;
  }

  Serial.print("IR code: ");
  Serial.print(String(ir_code));
  Serial.print(" IR to consider: ");
  Serial.println(String(ir_code_to_consider));

  return ir_code_to_consider;
}

boolean IRReceiver::is_left_code(const IRCode ir_code) const
{
  switch (ir_code) {
    case 2351064443UL:
    case 16716015UL:
      Serial.println("left pressed");

      return true;
      break;
  }

  return false;
}

boolean IRReceiver::is_right_code(const IRCode ir_code) const
{
  switch (ir_code) {
    case 16734885UL:
      Serial.println("right pressed");

      return true;
      break;
  }

  return false;
}

boolean IRReceiver::is_up_code(const IRCode ir_code) const
{
  switch (ir_code) {
    case 16718055UL:
      Serial.println("up pressed");

      return true;
      break;
  }

  return false;
}

boolean IRReceiver::is_down_code(const IRCode ir_code) const
{
  switch (ir_code) {
    case 16730805UL:
      Serial.println("down pressed");

      return true;
      break;
  }

  return false;
}

boolean IRReceiver::is_button_1_code(const IRCode ir_code) const
{
  switch (ir_code) {
    case 16726215UL:
      Serial.println("button 1");

      return true;
      break;
  }

  return false;
}

void IRReceiver::resume()
{
  m_ir_receiver.resume();
}
}  // namespace Robo
