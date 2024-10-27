#pragma once
#include "basic.h"
namespace sensors {
using namespace BKND;
using namespace BKND::sensors;
using namespace KIPR;
namespace dgtl {
bool Value(int p_port) { return digital(p_port); }
} // namespace dgtl
namespace nlg {
float Value(int p_port) { return (float)analog(p_port) / 4095; }
int Raw(int p_port) { return analog(p_port); }
} // namespace nlg
namespace accel {
using namespace BKND::sensors::accel;
void Calibrate() {
  accel_calibrate();
  Update();
}
float Magnitude() {
  Update();
  return Value.Magnitude();
}
float Pitch() {
  Update();
  return Value.Pitch();
}
float Yaw() {
  Update();
  return Value.Yaw();
}
void Update() {
  Value.m_X = accel_x();
  Value.m_Y = accel_y();
  Value.m_Z = accel_z();
}
} // namespace accel
namespace gyro {
using namespace BKND::sensors::gyro;
void Calibrate() { gyro_calibrate(); }
float Magnitude() {
  Update();
  return Value.Magnitude();
}
float Pitch() {
  Update();
  return Value.Pitch();
}
float Yaw() {
  Update();
  return Value.Yaw();
}
void Update() {
  Value.m_X = gyro_x();
  Value.m_Y = gyro_y();
  Value.m_Z = gyro_z();
}
} // namespace gyro
namespace mag {
using namespace BKND::sensors::mag;

void Calibrate() {
  // magneto_calibrate();
}
float Magnitude() {
  Update();
  return Value.Magnitude();
}
float Pitch() {
  Update();
  return Value.Pitch();
}
float Yaw() {
  Update();
  return Value.Yaw();
}
void Update() {
  Value.m_X = magneto_x();
  Value.m_Y = magneto_y();
  Value.m_Z = magneto_z();
}
} // namespace mag
namespace bttry {
using namespace BKND::sensors::bttry;
int Power() { return power_level() * 100; }
bool Critical() { return Power() < 33; }
} // namespace bttry
} // namespace sensors
