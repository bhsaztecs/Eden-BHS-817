#pragma once
#include "basic.h"
namespace servos {
using namespace BKND;
using namespace BKND::servos;
using namespace KIPR;
void Set(int p_port, float p_angle) {
  DLOG set_servo_position(p_port, DTTA(p_angle));
}
void Change(int p_port, float p_changeinangle) {
  DLOG int curA = TTDA(get_servo_position(p_port));
  int posA = curA + p_changeinangle;

  Set(p_port, posA);
}
void Move(int p_port, float p_angle, float p_timeinseconds) {
  DLOG int curAng = get_servo_position(p_port);
  p_angle = DTTA(p_angle);
  int it = p_angle - curAng;
  if (it > 0) {
    for (int a = curAng; a < p_angle; a += 10) {
      Set(p_port, TTDA(a));
      msleep(fabs(p_timeinseconds / it) * 10 * 1000);
    }
  } else {
    for (int a = curAng; a > p_angle; a -= 10) {
      Set(p_port, TTDA(a));
      msleep(fabs(p_timeinseconds / it) * 10 * 1000);
    }
  }
}
} // namespace servos
