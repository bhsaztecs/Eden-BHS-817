#pragma once
#include "basic.h"

class Motors {
public:
  int m_LeftPort, m_RightPort;
  float m_LeftCompensator, m_RightCompensator, m_TimeCompensator;
  float m_LeftSpeed = 0, m_RightSpeed = 0;
  void NormalizeMultipliers(float p_lcompensator, float p_rcompensator) {
    float l_maximizer = 1;
    if (m_LeftCompensator > m_RightCompensator) {
      l_maximizer = 1 / m_LeftCompensator;
    } else {
      l_maximizer = 1 / m_RightCompensator;
    }

    m_RightCompensator = m_RightCompensator * l_maximizer;
    m_LeftCompensator = m_LeftCompensator * l_maximizer;
    m_TimeCompensator = l_maximizer;
  }

  Motors(int p_leftport, int p_rightport, float p_lcompensator,
         float p_rcompensator) {
    m_LeftPort = p_leftport;
    m_RightPort = p_rightport;
    NormalizeMultipliers(p_lcompensator, p_rcompensator);
    Clear();
  }
  void Clear() { BKND::motors::ClearMotorRotations(m_LeftPort, m_RightPort); }
  void Velocity() {
    BKND::motors::Velocity(m_LeftPort, m_RightPort, m_LeftSpeed, m_RightSpeed);
  }
  void Speed(float p_leftgoalpercent, float p_rightgoalpercent,
             float p_timeinseconds) {
    BKND::motors::Speed(p_leftgoalpercent, p_rightgoalpercent, p_timeinseconds,
                        m_LeftPort, m_RightPort, m_LeftCompensator,
                        m_RightCompensator, m_TimeCompensator);
  }
  void Rotation(float p_leftgoaldegrees, float p_rightgoaldegrees,
                float p_timeinseconds) {
    BKND::motors::Rotation(
        p_leftgoaldegrees, p_rightgoaldegrees, p_timeinseconds, m_LeftPort,
        m_RightPort, m_LeftCompensator, m_RightCompensator, m_TimeCompensator);
  }
  void Distance(float p_leftgoalinches, float p_rightgoalinches,
                float p_timeinseconds) {
    BKND::motors::Distance(p_leftgoalinches, p_rightgoalinches, p_timeinseconds,
                           m_LeftPort, m_RightPort, m_LeftCompensator,
                           m_RightCompensator, m_TimeCompensator);
  }
  void Accelerate(float p_leftgoalpercent, float p_rightgoalpercent,
                  float p_timeinseconds) {
    BKND::motors::Accelerate(p_leftgoalpercent, p_rightgoalpercent,
                             p_timeinseconds, m_LeftPort, m_RightPort,
                             m_LeftSpeed, m_RightSpeed, m_LeftCompensator,
                             m_RightCompensator, m_TimeCompensator);
  }
  void Brake() { BKND::motors::Brake(m_LeftPort, m_RightPort); }
};
class Servos {
  float lerp(float p_a, float p_b, float p_t) {
    return p_a + (p_b - p_a) * p_t;
  }

public:
  int port;
  BKND::P2D Minimum, Maximum;

  Servos(int p_port, BKND::P2D p_min, BKND::P2D p_max) {}
  void Set(float p_angle) { BKND::servos::Set(port, p_angle); }
  void Change(float p_angle) { BKND::servos::Change(port, p_angle); }
  void GoTo(float p_angle, float p_time) {
    BKND::servos::Move(port, p_angle, p_time);
  }
  float Angle() { return BKND::TTDA(KIPR::get_servo_position(port)); }
};

template <BKND::sensors::type> class Sensors {
public:
  int Port;

  Sensors(int p_port) : Port(p_port) {}
};

template <> class Sensors<BKND::sensors::type::Analog> {
public:
  int Port;

  Sensors(int p_port) : Port(p_port) {}
  float Value() { return BKND::sensors::nlg::Value(Port); }
};
template <> class Sensors<BKND::sensors::type::Digital> {
public:
  int Port;

  Sensors(int p_port) : Port(p_port) {}
  bool Value() { return BKND::sensors::dgtl::Value(Port); }
};

class PathFind {
public:
  float Margin;
  Motors Read;
  float TurnRate;
  PathFind(float p_margin, float p_turnrate, Motors p_readfrom)
      : Read(p_readfrom) {
    Margin = p_margin;
    TurnRate = p_turnrate;
  }
  void GoTo(BKND::P2D p_goal, float p_time) {
    BKND::pathFind::GoTo(p_goal, p_time, TurnRate, Read.m_LeftPort,
                         Read.m_RightPort, Read.m_LeftCompensator,
                         Read.m_RightCompensator, Read.m_TimeCompensator);
  }
  void Face(float p_goal, float p_time) {
    BKND::pathFind::Face(p_goal, p_time, TurnRate, Read.m_LeftPort,
                         Read.m_RightPort, Read.m_LeftCompensator,
                         Read.m_RightCompensator, Read.m_TimeCompensator);
  }
};
