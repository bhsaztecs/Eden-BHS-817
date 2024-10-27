#pragma once
#include "basic.h"
namespace servos {
using namespace BKND;
using namespace BKND::servos;
using namespace KIPR;
void Set(int port, float Angle) { DLOG set_servo_position(port, DTTA(Angle)); }
void Change(int port, float changeInAngle) {
  DLOG int curA = TTDA(get_servo_position(port));
  int posA = curA + changeInAngle;

  Set(port, posA);
}
void Move(int port, float Angle, float timeInSeconds) {
  DLOG int curAng = get_servo_position(port);
  Angle = DTTA(Angle);
  int it = Angle - curAng;
  if (it > 0) {
    for (int a = curAng; a < Angle; a += 10) {
      Set(port, TTDA(a));
      msleep(abs(timeInSeconds / it) * 10 * 1000);
    }
  } else {
    for (int a = curAng; a > Angle; a -= 10) {
      Set(port, TTDA(a));
      msleep(abs(timeInSeconds / it) * 10 * 1000);
    }
  }
}
} // namespace servos
