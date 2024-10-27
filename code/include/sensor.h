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
  Value.X = accel_x();
  Value.Y = accel_y();
  Value.Z = accel_z();
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
  Value.X = gyro_x();
  Value.Y = gyro_y();
  Value.Z = gyro_z();
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
  Value.X = magneto_x();
  Value.Y = magneto_y();
  Value.Z = magneto_z();
}
} // namespace mag
namespace bttry {
using namespace BKND::sensors::bttry;
int Power() { return power_level() * 100; }
bool Critical() { return Power() < 33; }
} // namespace bttry
} // namespace sensors
