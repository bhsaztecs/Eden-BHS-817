#include "../include/declarations.h"
namespace BKND {
namespace pathFind {
void AthenaDecision(float p_deltal, float p_deltar, pass p_vals) {
  DBUG if (BKND::MarginOfError(fabs(p_deltal), fabs(p_deltar), p_vals.margin) &&
           (p_deltal != p_deltar)) {
    BKND::pathFind::AngularPathfind(p_deltal, p_deltar, p_vals);
    return;
  }
  if (BKND::MarginOfError(p_deltal, p_deltar, p_vals.margin)) {
    BKND::pathFind::LinearPathfind(p_deltal, p_deltar);
    return;
  }
  BKND::pathFind::DynamicPathfind(p_deltal, p_deltar);
}
void AngularPathfind(float p_deltal, float p_deltar, pass p_vals) {
  DBUG float wheelangle = (fabs(p_deltal) + fabs(p_deltar)) / 2;
  float orientationoffset = wheelangle / p_vals.turnrate;

  BKND::G_Position.m_Orientation += orientationoffset;
}

void LinearPathfind(float p_deltal, float p_deltar) {
  DBUG float distance = BKND::DTIW((p_deltal + p_deltar) / 2);
  BKND::P2D delta(distance * cos(BKND::G_Position.m_Orientation),
                  distance * sin(BKND::G_Position.m_Orientation));

  BKND::G_Position.m_X += delta.m_X;
  BKND::G_Position.m_Y += delta.m_Y;
}

void DynamicPathfind(float p_deltal, float p_deltar) {
  DBUG float curvature = (p_deltal + p_deltar) / (p_deltal - p_deltar);
  float distancetraveled = (p_deltal + p_deltar) / 2;
  float theta = distancetraveled / fabs(curvature);
  BKND::P2D changeinposition(fabs(curvature) * cos(theta),
                             fabs(curvature) * sin(theta));

  BKND::G_Position += changeinposition;
  BKND::G_Position.m_Orientation += theta;
}
void Face(float p_deg, float p_time, pass p_vals) {
  DBUG BKND::worldSpace originalposition = BKND::G_Position;
  BKND::worldSpace origin;
  BKND::G_Position = origin;
  float deltaorientation = BKND::Rad(p_deg) - BKND::G_Position.m_Orientation;
  float wheelangle = BKND::Deg(deltaorientation * (p_vals.turnrate / 2));
  BKND::motors::Rotation(wheelangle, -wheelangle, p_time, p_vals);
  BKND::G_Position += originalposition;
}
void GoTo(BKND::P2D p_goal, float p_time, pass p_vals) {
  DBUG BKND::worldSpace originalposition = BKND::G_Position;
  BKND::worldSpace origin;
  BKND::G_Position = origin;
  BKND::P2D deltaposition(p_goal - BKND::G_Position);
  Face(deltaposition.Angle(), (p_time * deltaposition.Angle()), p_vals);

  BKND::motors::Brake(p_vals);
  msleep(10);

  BKND::motors::Distance(deltaposition.Magnitude(), deltaposition.Magnitude(),
                         p_time * deltaposition.Magnitude(), p_vals);
  BKND::G_Position += originalposition;
}
} // namespace pathFind
} // namespace BKND
