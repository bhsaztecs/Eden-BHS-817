#pragma once
#include "Basic.h"
void servos::Set(float armAngle, float clawAngle = TTDC(get_servo_position(ClawServo))) {
	DLOG
        enable_servos();
		set_servo_position(ArmServo, DTTA(armAngle));
	set_servo_position(ClawServo, DTTC(clawAngle));
    disable_servos();
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
	int direction = armAngle - curPos;
    direction = direction/abs(direction);
	for ( float i = curPos; i != armAngle; i += direction ) {
		servos::Set(i);
		msleep(timeInSeconds/10);
	}
}