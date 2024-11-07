#include "../include/interface.h"
Motors tank(3 /*left port*/, 0 /*right port*/, 1.0 /*left motor multiplier*/,
            1.0 /*right motor multiplier*/, 5 /*margin*/, 2.8 /*turnrate*/);
Servos arm(0 /*port*/, BKND::P2D(-45 /*degrees*/, 125 /*tics*/) /*minimum*/,
           BKND::P2D(45, 2047) /*maximum*/);
Servos claw(1, BKND::P2D(0, 0), BKND::P2D(90, 1020));
Sensors<BKND::sensors::type::Analog> /*sensor type*/
    startlight(0 /*port*/);
PathFind navigate(tank.m_pass /*what wheels to read from*/);

void Wait(float seconds) {
  tank.Brake();
  msleep(seconds * 1000);
}

int main() {
  if (false /*tournament mode*/) {
    BKND::misc::waitforlight(startlight.m_Port);
    shut_down_in(119);
  }
  BKND::Thread VELOCITY([]() { BKND::motors::Velocity(tank.m_pass); });
  BKND::Thread TIMER([]() { BKND::misc::Timer(); });
  TIMER.Run();
  VELOCITY.Run();
  Wait(1);
  tank.Accelerate(-100 /*left goal*/, -95 /*right goal*/,
                  5 /*tics per second per second*/);
  tank.Speed(-100, -95, 15);
  tank.Accelerate(0, 0, 5);
  // arm.GoTo(45 /*angle*/, 1 /*time*/);
  // navigate.Face(-180, 2);
  Wait(1);
  std::cout << "hello!" << std::endl;
  return 0;
}
