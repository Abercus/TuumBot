
#ifndef RTX_MAINBOARD_H
#define RTX_MAINBOARD_H

#include "RTX485.hpp"

namespace rtx { namespace hal {

  class MainBoard : public RTX485::Device {
  private:
    bool m_ballSensorState;

  public:
    MainBoard();

    void init(RTX485::WriteHandle wHandle, RTX485::SignalService sigRegister);
    void signal(RTX485::Message);

    void senseBall();
    void chargeCoil();
    void releaseCoil();

    bool getBallSensorState();
  };

}}

#endif // RTX_MAINBOARD_H
