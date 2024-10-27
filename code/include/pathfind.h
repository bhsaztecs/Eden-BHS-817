#pragma once
#include "basic.h"

namespace pathFind {
using namespace BKND;
using namespace BKND::pathFind;
using namespace KIPR;
void AthenaDecision(float p_deltal, float p_deltar, float p_athenamargin) {
  DLOG if (MarginOfError(abs(p_deltal), abs(p_deltar), p_athenamargin) &&
           (p_deltal != p_deltar)) {
    AngularPathfind(p_deltal, p_deltar);
    return;
  }
  if (MarginOfError(p_deltal, p_deltar, p_athenamargin)) {
    LinearPathfind(p_deltal, p_deltar);
    return;
  }
  DynamicPathfind(p_deltal, p_deltar);
  return;
}
void AngularPathfind(float p_deltal, float p_deltar, float p_turnrate) {
  DLOG float Wa = (fabs(p_deltal) + fabs(p_deltar)) / 2;
  float Ooffset = Wa / p_turnrate;

  Position.O += Ooffset;
}

void LinearPathfind(float p_deltal, float p_deltar) {
  DLOG float Distance = DTIW((p_deltal + p_deltar) / 2);
  P2D delta(Distance * cos(Position.O), Distance * sin(Position.O));

  Position.X += delta.X;
  Position.Y += delta.Y;
}

void DynamicPathfind(float p_deltal, float p_deltar) {
  DLOG float c = (p_deltal + p_deltar) / (p_deltal - p_deltar);
  float a = (p_deltal + p_deltar) / 2;
  float theta = a / fabs(c);
  P2D prime(fabs(c) * cos(theta), fabs(c) * sin(theta));

  Position += prime;
  Position.O += theta;
}
void Face(float p_deg, float p_time, float p_turnrate, int p_leftmotor,
          int p_rightmotor, float p_lmm, float p_rmm, float p_timemultiplier) {
  DLOG worldSpace temp = Position;
  worldSpace zero;
  Position = zero;
  float DeltaO = Rad(p_deg) - Position.O;
  float WheelAngle = Deg(DeltaO * (p_turnrate / 2));
  motors::Rotation(WheelAngle, -WheelAngle, p_time, p_leftmotor, p_rightmotor,
                   p_lmm, p_rmm, p_timemultiplier);
  Position += temp;
}
void GoTo(P2D p_goal, float p_time, float p_turnrate, int p_leftmotor,
          int p_rightmotor, float p_lmm, float p_rmm, float p_timemultiplier) {
  DLOG worldSpace temp = Position;
  worldSpace zero;
  Position = zero;
  P2D delta(p_goal - Position);
  Face(delta.Angle(), (p_time * delta.Angle()), p_turnrate, p_leftmotor,
       p_rightmotor, p_lmm, p_rmm, p_timemultiplier);

  motors::Brake(p_leftmotor, p_rightmotor);
  msleep(10);

  motors::Distance(delta.Magnitude(), delta.Magnitude(),
                   p_time * delta.Magnitude(), p_leftmotor, p_rightmotor, p_lmm,
                   p_rmm, p_timemultiplier);
  Position += temp;
}
} // namespace pathFind
