#pragma once
#include "Basic.h"
void AthenaDecision(float deltaL, float deltaR) {
	DLOG
		if ( MarginOfError(abs(deltaL), abs(deltaR), AthenaMargin) && (deltaL != deltaR) ) {
			AngularPathfind(deltaL, deltaR);
			return;
		}
	if ( MarginOfError(deltaL, deltaR, AthenaMargin) ) {
		LinearPathfind(deltaL, deltaR);
		return;
	}
	DynamicPathfind(deltaL, deltaR);
	return;
}

void AngularPathfind(float deltaL, float deltaR) {
	DLOG
		float Wa = (abs(deltaL) + abs(deltaR)) / 2;
	float Ooffset = Wa / TurnRate;

	Position.O += Ooffset;
}

void LinearPathfind(float deltaL, float deltaR) {
	DLOG
		float Distance = DTIW((deltaL + deltaR) / 2);
	P2D delta(Distance * cos(Position.O), Distance * sin(Position.O));

	Position.X += delta.X;
	Position.Y += delta.Y;
}

void DynamicPathfind(float deltaL, float deltaR) {
	DLOG
		float c = (deltaL + deltaR) / (deltaL - deltaR);
	float a = (deltaL + deltaR) / 2;
	float theta = a / abs(c);
	P2D prime(abs(c) * cos(theta), abs(c) * sin(theta));

	Position += prime;
	Position.O += theta;
}

void pathFind::Face(float deg, float time) {
	DLOG
		worldSpace temp = Position;
	worldSpace zero;
	Position = zero;
	float DeltaO = Rad(deg) - Position.O;
	float WheelAngle = Deg(DeltaO * (TurnRate / 2));
	motors::Rotation(WheelAngle, -WheelAngle, time);
	Position += temp;
}
void pathFind::GoTo(float x, float y, float time) {
	DLOG
		worldSpace temp = Position;
	worldSpace zero;
	Position = zero;
	P2D delta(x - Position.X, y - Position.Y);
	Face(delta.Angle(), (time * delta.Angle()));

	motors::Brake();
	Wait(0.1);

	motors::Distance(delta.Magnitude(), delta.Magnitude(), time * delta.Magnitude());
	Position += temp;
}
void pathFind::GoTo(P2D goal, float time) {
	DLOG
		worldSpace temp = Position;
	worldSpace zero;
	Position = zero;
	P2D delta(goal - Position);
	Face(delta.Angle(), (time * delta.Angle()));

	motors::Brake();
	Wait(0.1);

	motors::Distance(delta.Magnitude(), delta.Magnitude(), time * delta.Magnitude());
	Position += temp;
}