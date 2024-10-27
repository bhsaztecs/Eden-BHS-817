#pragma once
#include "basic.h"

namespace pathFind {
using namespace BKND;
using namespace BKND::pathFind;
using namespace KIPR;
void AthenaDecision(float deltaL, float deltaR, float AthenaMargin) {
  DLOG if (MarginOfError(abs(deltaL), abs(deltaR), AthenaMargin) &&
           (deltaL != deltaR)) {
    AngularPathfind(deltaL, deltaR);
    return;
  }
  if (MarginOfError(deltaL, deltaR, AthenaMargin)) {
    LinearPathfind(deltaL, deltaR);
    return;
  }
  DynamicPathfind(deltaL, deltaR);
  return;
}
void AngularPathfind(float deltaL, float deltaR, float TurnRate) {
  DLOG float Wa = (abs(deltaL) + abs(deltaR)) / 2;
  float Ooffset = Wa / TurnRate;

  Position.O += Ooffset;
}

void LinearPathfind(float deltaL, float deltaR) {
  DLOG float Distance = DTIW((deltaL + deltaR) / 2);
  P2D delta(Distance * cos(Position.O), Distance * sin(Position.O));

  Position.X += delta.X;
  Position.Y += delta.Y;
}

void DynamicPathfind(float deltaL, float deltaR) {
  DLOG float c = (deltaL + deltaR) / (deltaL - deltaR);
  float a = (deltaL + deltaR) / 2;
  float theta = a / abs(c);
  P2D prime(abs(c) * cos(theta), abs(c) * sin(theta));

  Position += prime;
  Position.O += theta;
}
void Face(float deg, float time, float TurnRate, int LeftMotor, int RightMotor,
          float LMM, float RMM, float TimeMultiplier) {
  DLOG worldSpace temp = Position;
  worldSpace zero;
  Position = zero;
  float DeltaO = Rad(deg) - Position.O;
  float WheelAngle = Deg(DeltaO * (TurnRate / 2));
  motors::Rotation(WheelAngle, -WheelAngle, time, LeftMotor, RightMotor, LMM,
                   RMM, TimeMultiplier);
  Position += temp;
}
void GoTo(float x, float y, float time, float TurnRate, int LeftMotor,
          int RightMotor, float LMM, float RMM, float TimeMultiplier) {
  DLOG worldSpace temp = Position;
  worldSpace zero;
  Position = zero;
  P2D delta(x - Position.X, y - Position.Y);
  Face(delta.Angle(), (time * delta.Angle()), TurnRate, LeftMotor, RightMotor,
       LMM, RMM, TimeMultiplier);

  motors::Brake(LeftMotor, RightMotor);
  msleep(10);

  motors::Distance(delta.Magnitude(), delta.Magnitude(),
                   time * delta.Magnitude(), LeftMotor, RightMotor, LMM, RMM,
                   TimeMultiplier);
  Position += temp;
}
void GoTo(P2D goal, float time, float TurnRate, int LeftMotor, int RightMotor,
          float LMM, float RMM, float TimeMultiplier) {
  DLOG worldSpace temp = Position;
  worldSpace zero;
  Position = zero;
  P2D delta(goal - Position);
  Face(delta.Angle(), (time * delta.Angle()), TurnRate, LeftMotor, RightMotor,
       LMM, RMM, TimeMultiplier);

  motors::Brake(LeftMotor, RightMotor);
  msleep(10);

  motors::Distance(delta.Magnitude(), delta.Magnitude(),
                   time * delta.Magnitude(), LeftMotor, RightMotor, LMM, RMM,
                   TimeMultiplier);
  Position += temp;
}
} // namespace pathFind
