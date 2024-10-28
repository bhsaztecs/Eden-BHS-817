#pragma once
#include "declarations.h"
class Motors {
public:
  BKND::pass m_pass;
  float m_LeftSpeed, m_RightSpeed;
  void NormalizeMultipliers(float p_lcompensator, float p_rcompensator);

  Motors(int p_leftport, int p_rightport, float p_lcompensator,
         float p_rcompensator, float margin, float turnrate);
  void Clear();
  void Velocity();
  void Speed(float p_leftgoalpercent, float p_rightgoalpercent,
             float p_timeinseconds);
  void Rotation(float p_leftgoaldegrees, float p_rightgoaldegrees,
                float p_timeinseconds);
  void Distance(float p_leftgoalinches, float p_rightgoalinches,
                float p_timeinseconds);
  void Accelerate(float p_leftgoalpercent, float p_rightgoalpercent,
                  float p_timeinseconds);
  void Brake();
};
class Servos {
  float lerp(float p_a, float p_b, float p_t);

public:
  int m_Port;
  BKND::P2D m_Minimum, m_Maximum;
  Servos(int p_port, BKND::P2D p_min, BKND::P2D p_max);
  void Set(float p_angle);
  void Change(float p_angle);
  void GoTo(float p_angle, float p_time);
  float Angle();
};

template <BKND::sensors::type> class Sensors {
public:
  int m_Port;

  Sensors(int p_port);
};

template <> class Sensors<BKND::sensors::type::Analog> {
public:
  int m_Port;

  Sensors(int p_port);
  float Value();
};
template <> class Sensors<BKND::sensors::type::Digital> {
public:
  int m_Port;

  Sensors(int p_port);
  bool Value();
};

class PathFind {
public:
  BKND::pass m_Read;
  PathFind(BKND::pass motorstoread);
  void GoTo(BKND::P2D p_goal, float p_time);
  void Face(float p_goal, float p_time);
};
