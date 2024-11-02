#include "../include/interface.h"
#include "../include/declarations.h"

void Motors::NormalizeMultipliers(float p_lcompensator, float p_rcompensator) {
  float l_maximizer = 1;
  if (m_pass.lmm > m_pass.rmm) {
    l_maximizer = 1 / m_pass.lmm;
  } else {
    l_maximizer = 1 / m_pass.rmm;
  }

  m_pass.rmm = m_pass.rmm * l_maximizer;
  m_pass.lmm = m_pass.lmm * l_maximizer;
  m_pass.tmm = l_maximizer;
}

Motors::Motors(int p_leftport, int p_rightport, float p_lcompensator,
               float p_rcompensator, float margin, float turnrate)
    : m_pass(p_leftport, p_rightport, p_lcompensator, p_rcompensator, 1.0f,
             margin, turnrate, m_LeftSpeed, m_RightSpeed) {
  NormalizeMultipliers(p_lcompensator, p_rcompensator);
  Clear();
}
void Motors::Clear() { BKND::motors::ClearMotorRotations(m_pass); }
void Motors::Velocity() { BKND::motors::Velocity(m_pass); }
void Motors::Speed(float p_leftgoalpercent, float p_rightgoalpercent,
                   float p_timeinseconds) {
  BKND::motors::Speed(p_leftgoalpercent, p_rightgoalpercent, p_timeinseconds,
                      m_pass);
}
void Motors::Rotation(float p_leftgoaldegrees, float p_rightgoaldegrees,
                      float p_timeinseconds) {
  BKND::motors::Rotation(p_leftgoaldegrees, p_rightgoaldegrees, p_timeinseconds,
                         m_pass);
}
void Motors::Distance(float p_leftgoalinches, float p_rightgoalinches,
                      float p_timeinseconds) {
  BKND::motors::Distance(p_leftgoalinches, p_rightgoalinches, p_timeinseconds,
                         m_pass);
}
void Motors::Accelerate(float p_leftgoalpercent, float p_rightgoalpercent,
                        float p_timeinseconds) {
  BKND::motors::Accelerate(p_leftgoalpercent, p_rightgoalpercent,
                           p_timeinseconds, m_pass);
}
void Motors::Brake() { BKND::motors::Brake(m_pass); }

Servos::Servos(int p_port, BKND::P2D p_min, BKND::P2D p_max) {}
void Servos::Set(float p_angle) { BKND::servos::Set(m_Port, p_angle); }
void Servos::Change(float p_angle) { BKND::servos::Change(m_Port, p_angle); }
void Servos::GoTo(float p_angle, float p_time) {
  BKND::servos::Move(m_Port, p_angle, p_time);
}
float Servos::Angle() { return BKND::TTDA(get_servo_position(m_Port)); }

Sensors<BKND::sensors::type::Analog>::Sensors(int p_port) : m_Port(p_port) {}
float Sensors<BKND::sensors::type::Analog>::Value() {
  return BKND::sensors::nlg::Value(m_Port);
}

Sensors<BKND::sensors::type::Digital>::Sensors(int p_port) : m_Port(p_port) {}
bool Sensors<BKND::sensors::type::Digital>::Value() {
  return BKND::sensors::dgtl::Value(m_Port);
}

PathFind::PathFind(BKND::pass motorstoread) : m_Read(motorstoread) {}
void PathFind::GoTo(BKND::P2D p_goal, float p_time) {
  BKND::pathFind::GoTo(p_goal, p_time, m_Read);
}
void PathFind::Face(float p_goal, float p_time) {
  BKND::pathFind::Face(p_goal, p_time, m_Read);
}
