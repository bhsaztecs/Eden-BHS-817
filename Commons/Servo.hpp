#pragma once
#include "Basic.h"
void servos::Set(float armAngle, float clawAngle = TTDC(get_servo_position(ClawServo))) {
	DLOG
		set_servo_position(ArmServo, DTTA(armAngle));
	set_servo_position(ClawServo, DTTC(clawAngle));
}
void servos::Change(float changeInArmAngle, float changeInClawAngle) {
	DLOG
		int curA = TTDA(get_servo_position(ArmServo));
	int curC = TTDC(get_servo_position(ClawServo));
	int posA = curA + changeInArmAngle;
	int posC = curC + changeInClawAngle;

	servos::Set(posA, posC);
}
void servos::Move(float armAngle, float timeInSeconds) {
	DLOG
		int curPos = TTDA(get_servo_position(ArmServo));
	int distance = armAngle - curPos;
	for ( float i = 0; i < 1; i += 0.01 ) {
		servos::Set(Interpolate(i, distance) + curPos);
		msleep(timeInSeconds / 100);
	}
}
