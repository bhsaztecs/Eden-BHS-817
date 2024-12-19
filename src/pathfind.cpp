#include "../include/declarations.h"
namespace BKND {
namespace pathFind {
void AthenaDecision(float p_deltal, float p_deltar, pass p_vals) {
  if (BKND::MarginOfError(p_deltal, p_deltar, p_vals.margin)) {
    BKND::pathFind::LinearPathfind(p_deltal, p_deltar, p_vals);
    return;
  }
  if (BKND::MarginOfError(fabs(p_deltal), fabs(p_deltar), p_vals.margin)) {
    BKND::pathFind::AngularPathfind(p_deltal, p_deltar, p_vals);
    return;
  }
  BKND::pathFind::DynamicPathfind(p_deltal, p_deltar);
}
void AngularPathfind(float p_deltal, float p_deltar, pass p_vals) {
  float wheelangle = (fabs(p_deltal) + fabs(p_deltar)) / 2;
  float orientationoffset = wheelangle / (p_vals.turnrate * 1.32); // WHYYYYYYY

  BKND::G_Position.m_Orientation += BKND::Deg(orientationoffset);
}

void LinearPathfind(float p_deltal, float p_deltar, pass p_vals) {
  float distance = (p_deltal + p_deltar) / 2;
  BKND::P2D delta(distance * cos(BKND::Rad(BKND::G_Position.m_Orientation)),
                  distance * sin(BKND::Rad(BKND::G_Position.m_Orientation)));

  BKND::G_Position.m_X += delta.m_X;
  BKND::G_Position.m_Y += delta.m_Y;
}

void DynamicPathfind(float p_deltal, float p_deltar) {
  float curvature = (p_deltal + p_deltar) / (p_deltal - p_deltar);
  float distancetraveled = (p_deltal + p_deltar) / 2;
  float theta = distancetraveled / fabs(curvature);
  BKND::P2D changeinposition(fabs(curvature) * cos(theta),
                             fabs(curvature) * sin(theta));

  BKND::G_Position += changeinposition;
  BKND::G_Position.m_Orientation += BKND::Deg(theta);
}
void Face(float p_deg, float p_time, pass p_vals) {
  DBUG;
  float wheelangle =
      (p_deg - BKND::G_Position.m_Orientation) * (p_vals.turnrate);
  BKND::motors::Rotation(-wheelangle, wheelangle, p_time, p_vals);
}
void GoTo(BKND::P2D p_goal, float p_time, pass p_vals) {
  DBUG;
  BKND::P2D delta = (p_goal - BKND::G_Position);
  float ftime = (delta.Angle() / delta.Angle() + delta.Magnitude()) * p_time;
  float dtime =
      (delta.Magnitude() / delta.Angle() + delta.Magnitude()) * p_time;

  Face(delta.Angle(), p_time / 2, p_vals);
  BKND::motors::Brake(p_vals);
  msleep(10);
  BKND::motors::Distance(delta.Magnitude(), delta.Magnitude(), p_time / 2,
                         p_vals);
}
} // namespace pathFind
} // namespace BKND
