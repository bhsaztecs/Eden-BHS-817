#include "../include/declarations.h"
namespace BKND {
namespace servos {
void Set(int p_port, float p_angle) {
  set_servo_position(p_port, BKND::DTTA(p_angle));
}
void Change(int p_port, float p_changeinangle) {
  int curA = BKND::TTDA(get_servo_position(p_port));
  int posA = curA + p_changeinangle;

  Set(p_port, posA);
}
void Move(int p_port, float p_angle, float p_timeinseconds) {
  int curAng = get_servo_position(p_port);
  p_angle = BKND::DTTA(p_angle);
  int it = p_angle - curAng;
  if (it > 0) {
    for (int a = curAng; a < p_angle; a += 10) {
      Set(p_port, BKND::TTDA(a));
      msleep(fabs(p_timeinseconds / it) * 10 * 1000);
    }
  } else {
    for (int a = curAng; a > p_angle; a -= 10) {
      Set(p_port, BKND::TTDA(a));
      msleep(fabs(p_timeinseconds / it) * 10 * 1000);
    }
  }
}
} // namespace servos
} // namespace BKND
