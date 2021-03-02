#ifndef ROBO_IRRECEIVER_H_
#define ROBO_IRRECEIVER_H_

#include <Arduino.h>
#include <Robo/AbstractPart.h>
#include <IRremote.h>
#include <Helpers.h>

namespace Robo {
class IRReceiver : public AbstractPart
{
  DISABLE_COPY_AND_ASSIGN(IRReceiver)
public:
  typedef unsigned long IRCode;

  IRReceiver(Brain& robo_brain, const int pin);

  void setup() override;
  bool detect_signal();
  IRCode get_ir_code();
  boolean is_holding_code(const IRCode ir_code);
  boolean is_left_code(const IRCode ir_code) const;
  boolean is_right_code(const IRCode ir_code) const;
  boolean is_up_code(const IRCode ir_code) const;
  boolean is_down_code(const IRCode ir_code) const;
  boolean is_button_1_code(const IRCode ir_code) const;
  void resume();

private:
  const int m_pin = 0;
  IRrecv m_ir_receiver;
  decode_results m_ir_receiver_results;
  IRCode m_last_ir_code = 0;
};
}  // namespace Robo

#endif  // ROBO_IRRECEIVER_H_
