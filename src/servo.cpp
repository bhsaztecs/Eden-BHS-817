#include "../include/declarations.h"
namespace BKND {
namespace servos {
void Set(int p_port, float p_angle, pointpair p_slope) {
  DBUG;
  set_servo_position(p_port, BKND::lerp(p_slope, p_angle));
}
void Change(int p_port, float p_changeinangle, pointpair p_slope) {
  DBUG;
  int currentangle = BKND::lerp(p_slope, get_servo_position(p_port));
  int newangle = currentangle + p_changeinangle;

  Set(p_port, newangle, p_slope);
}
void Move(int p_port, float p_angle, float p_timeinseconds, pointpair p_slope) {
  DBUG;
  int currentangle = get_servo_position(p_port);
  p_angle = BKND::lerp(p_slope, p_angle);
  int iterator = p_angle - currentangle;
  if (iterator > 0) {
    for (int interpolatedangle = currentangle; interpolatedangle < p_angle;
         interpolatedangle += 10) {
      Set(p_port, interpolatedangle, p_slope);
      msleep(fabs(p_timeinseconds / iterator) * 10 * 1000);
    }
  } else {
    for (int interpolatedangle = currentangle; interpolatedangle > p_angle;
         interpolatedangle -= 10) {
      Set(p_port, interpolatedangle, p_slope);
      msleep(fabs(p_timeinseconds / iterator) * 10 * 1000);
    }
  }
}
} // namespace servos
} // namespace BKND
