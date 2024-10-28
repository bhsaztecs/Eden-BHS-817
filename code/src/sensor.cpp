#include "../include/declarations.h"

namespace BKND {
namespace sensors {
namespace dgtl {
bool Value(int p_port) { return KIPR::digital(p_port); }
} // namespace dgtl
namespace nlg {
float Value(int p_port) { return (float)KIPR::analog(p_port) / 4095; }
int Raw(int p_port) { return KIPR::analog(p_port); }
} // namespace nlg
namespace accel {
BKND::P3D Value;
void Calibrate() {
  KIPR::accel_calibrate();
  BKND::sensors::accel::Update();
}
float Magnitude() {
  BKND::sensors::accel::Update();
  return Value.Magnitude();
}
float Pitch() {
  BKND::sensors::accel::Update();
  return Value.Pitch();
}
float Yaw() {
  BKND::sensors::accel::Update();
  return Value.Yaw();
}
void Update() {
  Value.m_X = KIPR::accel_x();
  Value.m_Y = KIPR::accel_y();
  Value.m_Z = KIPR::accel_z();
}
} // namespace accel
namespace gyro {
BKND::P3D Value;
void Calibrate() { KIPR::gyro_calibrate(); }
float Magnitude() {
  BKND::sensors::gyro::Update();
  return Value.Magnitude();
}
float Pitch() {
  BKND::sensors::gyro::Update();
  return Value.Pitch();
}
float Yaw() {
  BKND::sensors::gyro::Update();
  return Value.Yaw();
}
void Update() {
  Value.m_X = KIPR::gyro_x();
  Value.m_Y = KIPR::gyro_y();
  Value.m_Z = KIPR::gyro_z();
}
} // namespace gyro
namespace mag {
BKND::P3D Value;
void Calibrate() {
  // magneto_calibrate();
}
float Magnitude() {
  BKND::sensors::mag::Update();
  return Value.Magnitude();
}
float Pitch() {
  BKND::sensors::mag::Update();
  return Value.Pitch();
}
float Yaw() {
  BKND::sensors::mag::Update();
  return Value.Yaw();
}
void Update() {
  Value.m_X = KIPR::magneto_x();
  Value.m_Y = KIPR::magneto_y();
  Value.m_Z = KIPR::magneto_z();
}
} // namespace mag
namespace bttry {
int Power() { return KIPR::power_level() * 100; }
bool Critical() { return Power() < 33; }
} // namespace bttry
} // namespace sensors
} // namespace BKND
