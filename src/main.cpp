#include "../include/interface.h"
Motors tank(3, 0, .97, 1.0, 5, 2.8);
Servos arm(0, BKND::P2D(0, 315), BKND::P2D(90, 1365));
Servos claw(1, BKND::P2D(0, 0), BKND::P2D(90, 1000));
Sensors<BKND::sensors::type::Analog> startlight(1);
PathFind navigate(tank.m_pass);
Sensors<BKND::sensors::type::Analog> ground(0);
void Wait(float seconds) {
  tank.Brake();
  msleep(seconds * 1000);
}
int main() {
  BKND::Thread VELOCITY([]() { BKND::motors::Velocity(tank.m_pass); });
  BKND::Thread TIMER([]() { BKND::misc::Timer(); });
  TIMER.Run();
  VELOCITY.Run();

  return 0;
}
