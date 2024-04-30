#pragma once
#include "Basic.h"

void servos::Set(float armAngle, float clawAngle = TTDC(get_servo_position(ClawServo))) {
  DLOG
    set_servo_position(ArmServo, DTTA(armAngle));
  set_servo_position(ClawServo, DTTC(clawAngle));
}
void servos::Change(float changeInArmAngle, float changeInClawAngle = 0) {
  DLOG
    int curA = TTDA(get_servo_position(ArmServo));
  int curC = TTDC(get_servo_position(ClawServo));
  int posA = curA + changeInArmAngle;
  int posC = curC + changeInClawAngle;

  servos::Set(posA, posC);
}
void servos::Move(float armAngle, float timeInSeconds) {
  DLOG
    int curAng = get_servo_position(ArmServo);
  armAngle = DTTA(armAngle);
  int it = armAngle - curAng;
  if ( it > 0 ) {
    for ( int a = curAng; a < armAngle; a += 10 ) {
      Set(TTDA(a));
      Wait(abs(timeInSeconds / it) * 10);
    }
  }
  else {
    for ( int a = curAng; a > armAngle; a -= 10 ) {
      Set(TTDA(a));
      Wait(abs(timeInSeconds / it) * 10);
    }
  }
}