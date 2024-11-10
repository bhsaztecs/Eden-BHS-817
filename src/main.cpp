#include "../include/interface.h"
Motors tank(3 /*left port*/, 0 /*right port*/, 1.0 /*left motor multiplier*/,
            1.0 /*right motor multiplier*/, 5 /*margin*/, 2.8 /*turnrate*/);
Servos arm(0 /*port*/, BKND::P2D(-45 /*degrees*/, 125 /*tics*/) /*minimum*/,
           BKND::P2D(45, 2047) /*maximum*/);
Servos claw(1, BKND::P2D(0, 0), BKND::P2D(90, 1020));
Sensors<BKND::sensors::type::Analog> /*sensor type*/
    startlight(0 /*port*/);
PathFind navigate(tank.m_pass /*what wheels to read from*/);
Sensors<BKND::sensors::type::Analog> dist(1);
void Wait(float seconds) {
  tank.Brake();
  msleep(seconds * 1000);
}
float e = 2.71828;
float pi = 3.14159265;
float distance(float x) {
  float stdDev = 4;
  float mean = 4;

  return 0.18 + (1.35 * (1.0 / (stdDev * std::sqrt(2 * pi))) *
                 std::exp(-0.5 * std::pow((x - mean) / stdDev, 2)));
}
int main() {
  if (false /*tournament mode*/) {
    BKND::misc::waitforlight(startlight.m_Port);
    shut_down_in(119)
  }
  BKND::Thread VELOCITY([]() { BKND::motors::Velocity(tank.m_pass); });
  BKND::Thread TIMER([]() { BKND::misc::Timer(); });
  TIMER.Run();
  VELOCITY.Run();
  tank.Accelerate(100, 100, 15);
  tank.Accelerate(0, 0, 15);
  arm.GoTo(45, 1);
  claw.Set(90);
  navigate.GoTo(BKND::P2D(0, 0), 3);
  Wait(1);
  std::cout << "startlight reads " << startlight.Value() << std::endl;
  return 0;
}
