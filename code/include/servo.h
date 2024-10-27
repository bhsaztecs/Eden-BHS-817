#pragma once
#include "basic.h"
namespace servos {
void Set(float armAngle,
         float clawAngle = TTDC(KIPR::get_servo_position(ClawServo))) {
  DLOG KIPR::set_servo_position(ArmServo, DTTA(armAngle));
  KIPR::set_servo_position(ClawServo, DTTC(clawAngle));
}
void Change(float changeInArmAngle, float changeInClawAngle = 0) {
  DLOG int curA = TTDA(KIPR::get_servo_position(ArmServo));
  int curC = TTDC(KIPR::get_servo_position(ClawServo));
  int posA = curA + changeInArmAngle;
  int posC = curC + changeInClawAngle;

  Set(posA, posC);
}
void Move(float armAngle, float timeInSeconds) {
  DLOG int curAng = KIPR::get_servo_position(ArmServo);
  armAngle = DTTA(armAngle);
  int it = armAngle - curAng;
  if (it > 0) {
    for (int a = curAng; a < armAngle; a += 10) {
      Set(TTDA(a));
      Wait(abs(timeInSeconds / it) * 10);
    }
  } else {
    for (int a = curAng; a > armAngle; a -= 10) {
      Set(TTDA(a));
      Wait(abs(timeInSeconds / it) * 10);
    }
  }
}
} // namespace servos
