#pragma once
#include "basic.h"
namespace sensors {
bool dgtl::Value(int port) { return KIPR::digital(port); }

float nlg::Value(int port) { return (float)KIPR::analog(port) / 4095; }
int nlg::Raw(int port) { return KIPR::analog(port); }

void accel::Calibrate() {
  KIPR::accel_calibrate();
  Update();
}
float accel::Magnitude() {
  Update();
  return Value.Magnitude();
}
float accel::Pitch() {
  Update();
  return Value.Pitch();
}
float accel::Yaw() {
  Update();
  return Value.Yaw();
}
void accel::Update() {
  Value.X = KIPR::accel_x();
  Value.Y = KIPR::accel_y();
  Value.Z = KIPR::accel_z();
}

void gyro::Calibrate() { KIPR::gyro_calibrate(); }
float gyro::Magnitude() {
  Update();
  return Value.Magnitude();
}
float gyro::Pitch() {
  Update();
  return Value.Pitch();
}
float gyro::Yaw() {
  Update();
  return Value.Yaw();
}
void gyro::Update() {
  Value.X = KIPR::gyro_x();
  Value.Y = KIPR::gyro_y();
  Value.Z = KIPR::gyro_z();
}

void mag::Calibrate() {
  // magneto_calibrate();
}
float mag::Magnitude() {
  Update();
  return Value.Magnitude();
}
float mag::Pitch() {
  Update();
  return Value.Pitch();
}
float mag::Yaw() {
  Update();
  return Value.Yaw();
}
void mag::Update() {
  Value.X = KIPR::magneto_x();
  Value.Y = KIPR::magneto_y();
  Value.Z = KIPR::magneto_z();
}

int bttry::Power() { return KIPR::power_level() * 100; }
bool bttry::Critical() { return Power() < 33; }
} // namespace sensors
