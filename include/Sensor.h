#pragma once
#include "Basic.h"
bool dgtl::Value(int port) {
  return digital(port);
}

float nlg::Value(int port) {
  return (float) analog(port) / 4095;
}
int nlg::Raw(int port) {
  return analog(port);
}

void accel::Calibrate() {
  accel_calibrate();
  accel::Update();
}
float accel::Magnitude() {
  accel::Update();
  return Value.Magnitude();
}
float accel::Pitch() {
  accel::Update();
  return Value.Pitch();
}
float accel::Yaw() {
  accel::Update();
  return Value.Yaw();
}
void accel::Update() {
  Value.X = accel_x();
  Value.Y = accel_y();
  Value.Z = accel_z();
}

void gyro::Calibrate() {
  gyro_calibrate();
}
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
  Value.X = gyro_x();
  Value.Y = gyro_y();
  Value.Z = gyro_z();
}

void mag::Calibrate() {
  //magneto_calibrate();
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
  Value.X = magneto_x();
  Value.Y = magneto_y();
  Value.Z = magneto_z();
}

int bttry::Power() {
  return power_level() * 100;
}
bool bttry::Critical() {
  return Power() < 33;
}