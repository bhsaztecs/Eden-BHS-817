#include "../include/declarations.h"
namespace BKND {
namespace pathFind {
void AthenaDecision(float p_deltal, float p_deltar, pass Vals) {
  if (BKND::MarginOfError(fabs(p_deltal), fabs(p_deltar), Vals.margin) &&
      (p_deltal != p_deltar)) {
    BKND::pathFind::AngularPathfind(p_deltal, p_deltar, Vals);
    return;
  }
  if (BKND::MarginOfError(p_deltal, p_deltar, Vals.margin)) {
    BKND::pathFind::LinearPathfind(p_deltal, p_deltar);
    return;
  }
  BKND::pathFind::DynamicPathfind(p_deltal, p_deltar);
  return;
}
void AngularPathfind(float p_deltal, float p_deltar, pass Vals) {
  float Wa = (fabs(p_deltal) + fabs(p_deltar)) / 2;
  float Ooffset = Wa / Vals.turnrate;

  BKND::Position.m_O += Ooffset;
}

void LinearPathfind(float p_deltal, float p_deltar) {
  float Distance = BKND::DTIW((p_deltal + p_deltar) / 2);
  BKND::P2D delta(Distance * cos(BKND::Position.m_O),
                  Distance * sin(BKND::Position.m_O));

  BKND::Position.m_X += delta.m_X;
  BKND::Position.m_Y += delta.m_Y;
}

void DynamicPathfind(float p_deltal, float p_deltar) {
  float c = (p_deltal + p_deltar) / (p_deltal - p_deltar);
  float a = (p_deltal + p_deltar) / 2;
  float theta = a / fabs(c);
  BKND::P2D prime(fabs(c) * cos(theta), fabs(c) * sin(theta));

  BKND::Position += prime;
  BKND::Position.m_O += theta;
}
void Face(float p_deg, float p_time, pass Vals) {
  BKND::worldSpace temp = BKND::Position;
  BKND::worldSpace zero;
  BKND::Position = zero;
  float DeltaO = BKND::Rad(p_deg) - BKND::Position.m_O;
  float WheelAngle = BKND::Deg(DeltaO * (Vals.turnrate / 2));
  BKND::motors::Rotation(WheelAngle, -WheelAngle, p_time, Vals);
  BKND::Position += temp;
}
void GoTo(BKND::P2D p_goal, float p_time, pass Vals) {
  BKND::worldSpace temp = BKND::Position;
  BKND::worldSpace zero;
  BKND::Position = zero;
  BKND::P2D delta(p_goal - BKND::Position);
  Face(delta.Angle(), (p_time * delta.Angle()), Vals);

  BKND::motors::Brake(Vals);
  KIPR::msleep(10);

  BKND::motors::Distance(delta.Magnitude(), delta.Magnitude(),
                         p_time * delta.Magnitude(), Vals);
  BKND::Position += temp;
}
} // namespace pathFind
} // namespace BKND
