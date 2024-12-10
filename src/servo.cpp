#include "../include/declarations.h"
namespace BKND {
namespace servos {
void Set(int p_port, float p_angle) {
  DBUG set_servo_position(p_port, BKND::DTTA(p_angle));
}
void Change(int p_port, float p_changeinangle) {
  DBUG int currentangle = BKND::TTDA(get_servo_position(p_port));
  int newangle = currentangle + p_changeinangle;

  Set(p_port, newangle);
}
void Move(int p_port, float p_angle, float p_timeinseconds) {
  DBUG int currentangle = get_servo_position(p_port);
  p_angle = BKND::DTTA(p_angle);
  int iterator = p_angle - currentangle;
  if (iterator > 0) {
    for (int interpolatedangle = currentangle; interpolatedangle < p_angle;
         interpolatedangle += 10) {
      Set(p_port, BKND::TTDA(interpolatedangle));
      msleep(fabs(p_timeinseconds / iterator) * 10 * 1000);
    }
  } else {
    for (int interpolatedangle = currentangle; interpolatedangle > p_angle;
         interpolatedangle -= 10) {
      Set(p_port, BKND::TTDA(interpolatedangle));
      msleep(fabs(p_timeinseconds / iterator) * 10 * 1000);
    }
  }
}
} // namespace servos
} // namespace BKND
