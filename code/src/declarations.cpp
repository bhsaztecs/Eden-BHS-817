#include "../include/declarations.h"
namespace BKND {
string PrettyTime(int p_ms) {
  int min, sec;
  int totalms = p_ms;
  min = totalms / (60 * 1000);
  totalms %= 60 * 1000;
  sec = totalms / 1000;
  totalms %= 1000;

  // Convert totalms to float and then to string to handle decimals
  std::string msStr = std::to_string(totalms / 1000.0f);

  // Remove trailing zeros
  size_t found = msStr.find_last_not_of('0');
  if ((found != std::string::npos) && (found != msStr.size() - 1)) {
    msStr = msStr.substr(0, found + 1);
  }

  return std::to_string(min) + ":" + std::to_string(sec) + msStr.substr(1);
}

float Rad(float p_degrees) { return p_degrees * 0.01745329251; }
float Deg(float p_radians) { return p_radians * 57.2957795131; }
float mm(float p_inches) { return p_inches * 25.4; }
float inch(float p_mm) { return p_mm / 25.4; }

/*
 * ATBC();
 * A to B for the C
 * A = degrees
 * B = ticks
 * C = wheels
 * Degrees to Ticks for the Wheels
 */
int DTTW(float p_degrees) { return p_degrees * 5.55; }

float TTDW(int p_ticks) { return p_ticks / 5.55; }

float DTIW(float p_degrees) { return 1.5 * Rad(p_degrees); }

float ITDW(float p_inches) { return Deg(1.5 / p_inches); }

float TTIW(int p_ticks) { return p_ticks / 206.49999936; }

int ITTW(float p_inches) { return p_inches * 206.49999936; }
/***********************/
int DTTA(float p_degrees) { return (-12.2222 * p_degrees) + 1450; }

float TTDA(int p_tics) { return (-0.081818 * p_tics) + 118.636; }

int DTTC(float p_degrees) { return (12.05 * p_degrees) + 723.5; }

float TTDC(int p_tics) { return (0.082 * p_tics) - 60; }

P2D::P2D(float x, float y) {
  this->m_X = x;
  this->m_Y = y;
}
float P2D::Magnitude() {
  return std::sqrt(std::pow(m_X, 2) + std::pow(m_Y, 2));
}
float P2D::Angle() { return Deg(std::atan2(m_Y, m_X)); }
P2D P2D::operator-(const P2D &p_other) {
  return P2D(this->m_X - p_other.m_X, this->m_Y - p_other.m_Y);
}
P2D P2D::operator+(const P2D &p_other) {
  return P2D(this->m_X + p_other.m_X, this->m_Y + p_other.m_Y);
}
void P2D::operator=(const P2D &p_other) {
  this->m_X = p_other.m_X;
  this->m_Y = p_other.m_Y;
}
bool P2D::operator==(const P2D &p_other) {
  return (this->m_X == p_other.m_X) && (this->m_Y == p_other.m_Y);
}
void P2D::operator+=(const P2D &p_other) {
  P2D temp(this->m_X + p_other.m_X, this->m_Y + p_other.m_Y);
  this->m_X = temp.m_X;
  this->m_Y = temp.m_Y;
}
void P2D::operator-=(const P2D &p_other) {
  P2D temp(this->m_X - p_other.m_X, this->m_Y - p_other.m_Y);
  this->m_X = temp.m_X;
  this->m_Y = temp.m_Y;
}

P3D::P3D(float p_x, float p_y, float p_z) {
  this->m_X = p_x;
  this->m_Y = p_y;
  this->m_Z = p_z;
}
float P3D::Magnitude() {
  return std::sqrt(std::pow(m_X, 2) + std::pow(m_Y, 2) + std::pow(m_Z, 2));
}
float P3D::Pitch() { return Deg(std::atan(m_Y / m_Z)); }
float P3D::Yaw() { return Deg(std::atan(m_X / m_Z)); }
P3D P3D::operator-(const P3D &p_other) {
  return P3D(this->m_X - p_other.m_X, this->m_Y - p_other.m_Y,
             this->m_Z - p_other.m_Z);
}
P3D P3D::operator+(const P3D &p_other) {
  return P3D(this->m_X + p_other.m_X, this->m_Y + p_other.m_Y,
             this->m_Z + p_other.m_Z);
}
void P3D::operator=(const P3D &p_other) {
  this->m_X = p_other.m_X;
  this->m_Y = p_other.m_Y;
  this->m_Z = p_other.m_Z;
}
bool P3D::operator==(const P3D &p_other) {
  return (this->m_X == p_other.m_X) && (this->m_Y == p_other.m_Y) &&
         (this->m_Z == p_other.m_Z);
}
void P3D::operator+=(const P3D &p_other) {
  P3D temp(this->m_X + p_other.m_X, this->m_Y + p_other.m_Y,
           this->m_Z + p_other.m_Z);
  this->m_X = temp.m_X;
  this->m_Y = temp.m_Y;
  this->m_Z = temp.m_Z;
}
void P3D::operator-=(const P3D &p_other) {
  P3D temp(this->m_X - p_other.m_X, this->m_Y - p_other.m_Y,
           this->m_Z - p_other.m_Z);
  this->m_X = temp.m_X;
  this->m_Y = temp.m_Y;
  this->m_Z = temp.m_Z;
}

worldSpace::worldSpace(float p_x, float p_y, float p_r, float p_o) {
  this->m_O = p_o;
  this->m_X = p_x;
  this->m_Y = p_y;
  this->m_Radius = p_r;
  Obstacles.push_back(this);
}

bool worldSpace::operator==(const worldSpace &p_other) {
  return (this->m_X == p_other.m_X) && (this->m_Y == p_other.m_Y);
}
bool worldSpace::operator!=(const worldSpace &p_other) {
  return (this->m_X != p_other.m_X) || (this->m_Y != p_other.m_Y);
}
worldSpace worldSpace::operator-(const P2D &p_other) {
  return worldSpace(this->m_X - p_other.m_X, this->m_Y - p_other.m_Y);
}
worldSpace worldSpace::operator+(const P2D &p_other) {
  return worldSpace(this->m_X + p_other.m_X, this->m_Y + p_other.m_Y);
}
void worldSpace::operator+=(const P2D &p_other) {
  P2D temp(this->m_X + p_other.m_X, this->m_Y + p_other.m_Y);
  this->m_X = temp.m_X;
  this->m_Y = temp.m_Y;
}
void worldSpace::operator-=(const P2D &p_other) {
  P2D temp(this->m_X - p_other.m_X, this->m_Y - p_other.m_Y);
  this->m_X = temp.m_X;
  this->m_Y = temp.m_Y;
}
worldSpace worldSpace::operator=(const worldSpace &p_other) { return p_other; }

float Interpolate(float p_timepercent, float p_delta) {
  return (std::pow(p_timepercent, 2.16) /
          (std::pow(p_timepercent, 2.16) +
           (std::pow((1 - p_timepercent), 2.16)))) *
         p_delta;
}

Thread::Thread(
    void (*p_func)()) { // create a new thread with a function as a parameter
  thread_create(p_func);
}
void Thread::Run() { // start the thread
  thread_start(m_Thethread);
}
void Thread::Kill() { // end the thread
  thread_destroy(m_Thethread);
}
} // namespace BKND
