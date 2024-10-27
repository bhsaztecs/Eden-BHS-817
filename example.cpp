#include "code/include/interface.h"
Motors tank(0 /*left port*/, 3 /*right port*/, 1.0 /*left motor multiplier*/,
            1.0 /*right motor multiplier*/);
Servos arm(0 /*port*/, BKND::P2D(-45 /*degrees*/, 125 /*tics*/) /*minimum*/,
           BKND::P2D(45, 2047) /*maximum*/);
Servos claw(1, BKND::P2D(0, 0), BKND::P2D(90, 1020));
Sensors<BKND::sensors::type::Analog> /*sensor type*/
    startlight(0 /*port*/);
PathFind
    navigate(5 /*margin of error (lower is more precise, higher is faster*/,
             2.8, /*turnrate*/
             tank /*what wheels to read from*/);

void Wait(float seconds) {
  tank.Brake();
  KIPR::msleep(seconds * 1000);
}
void update() {
  while (true) { // indefinitely
    Wait(0.5);   // delay
    std::cout << BKND::TTDA(arm.Angle()) << std::endl;
  }
}

int main() {
  if (true /*tournament mode*/) {
    BKND::misc::waitforlight(startlight.m_Port);
    KIPR::shut_down_in(119);
  }
  BKND::Thread UPDATE(update);
  UPDATE.Run();
  Wait(1);
  tank.Accelerate(100 /*left goal*/, 100 /*right goal*/,
                  5 /*tics per second per second*/);
  tank.Accelerate(0, 0, 5);
  Wait(1);
  return 0;
}
