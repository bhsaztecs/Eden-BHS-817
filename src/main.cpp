#include "../include/interface.h"
Motors tank(3 /*left port*/, 0 /*right port*/, .97 /*left motor multiplier*/,
            1.0 /*right motor multiplier*/, 5 /*margin*/, 2.8 /*turnrate*/);
Servos arm(0 /*port*/, BKND::P2D(-45 /*degrees*/, 125 /*tics*/) /*minimum*/,
           BKND::P2D(45, 2047) /*maximum*/);
Servos claw(1, BKND::P2D(0, 0), BKND::P2D(90, 1020));
Sensors<BKND::sensors::type::Analog> /*sensor type*/
    startlight(1 /*port*/);
PathFind navigate(tank.m_pass /*what wheels to read from*/);
Sensors<BKND::sensors::type::Analog> ground(0);
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

  while (ground.Value() < 0.92){
        tank.Speed(-100,-20,0.1);
  }
    tank.Speed(-100,-20,1);
  while (ground.Value() < 0.92){
        tank.Speed(-100,20,0.1);
  }
    ao();
    msleep(500);
    tank.Speed(85,100,1.5);
    tank.Speed(100,15,0.88);
    auto t1 = BKND::G_CurrentMS;
  while (ground.Value() < 0.92){
        tank.Speed(50,50,0.1);
  }
    auto t2 = BKND::G_CurrentMS;
    tank.Speed(50,50,(t2-t1)/1000);
    tank.Speed(0,100,1);
    tank.Speed(-50,-50,1);

  return 0;
}
