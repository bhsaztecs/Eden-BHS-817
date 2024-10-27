#pragma once
namespace KIPR {
#include "../kipr/wombat.h"
}
#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
#define DLOG                                                                   \
  if (Debugging) {                                                             \
    auto now = std::chrono::high_resolution_clock::now();                      \
    auto elapsedtime = std::chrono::duration_cast<std::chrono::milliseconds>(  \
        now - program_start_time);                                             \
    std::cout << __PRETTY_FUNCTION__ << " (" << __LINE__                       \
              << ") Time since start: " << PrettyTime(elapsedtime.count())     \
              << std::endl;                                                    \
  }
bool Debugging;

auto program_start_time = std::chrono::high_resolution_clock::now();

namespace BKND {
using namespace KIPR;
class newThread;  // thread functionality
class P2D;        // 2 dimensional coordinate
class P3D;        // 3 dimensional coordinate
class worldSpace; // 2 dimensional coordinate with additional functionality
std::vector<worldSpace *> Obstacles;

long int CurrentMS = 0;

float Deg(float);  /*Convert Radians to Degrees*/
float Rad(float);  /*Convert Degrees to Radians*/
float ITDW(float); /*Convert inches to degrees (for the wheel)*/
float DTIW(float); /*convert degrees to inches (for the wheel)*/
int DTTA(float);   /*convert degrees to ticks (for the arm servo)*/
int DTTC(float);   /*convert degrees to ticks (for the claw servo)*/
int DTTW(float);   /*convert degrees to ticks (for the wheel)*/
int ITTW(float);   /*convert inches to ticks (for the wheel)*/
float TTDA(int);   /*convert ticks to degrees (for the arm servo)*/
float TTDC(int);   /*convert ticks to degrees (for the claw servo)*/
float TTDW(int);   /*convert ticks to degrees (for the wheel)*/
float TTIW(int);   /*convert ticks to inches (for the wheel)*/
float Interpolate(float,
                  float); /*get a smooth transition from point a to point b*/
/* IN {-> Time (from 1 to 0), Delta (from 0 to this number)
 * OUT{-> value returned from the equation.
 */
template <typename A, typename B, typename C>
bool MarginOfError(A, B, C); /*is a close to b?*/
/* IN {-> Check, Goal, Range
 * OUT{-> true/false
 */
template <typename A, typename B, typename C>
bool Clamp(A, B, C); /*Is B within A and C?*/
/* IN {-> Min, Value, Max
 * OUT {-> Min<=Value<=Max
 */
string PrettyTime(int); /*display milliseconds as min:sec.ms*/

class P2D {
public:
  float X;
  float Y;
  P2D(float x = 0, float y = 0) {
    this->X = x;
    this->Y = y;
  }
  float Magnitude() { return std::sqrt(std::pow(X, 2) + std::pow(Y, 2)); }
  float Angle() { return Deg(std::atan2(Y, X)); }
  P2D operator-(const P2D &other) {
    return P2D(this->X - other.X, this->Y - other.Y);
  }
  P2D operator+(const P2D &other) {
    return P2D(this->X + other.X, this->Y + other.Y);
  }
  void operator=(const P2D &other) {
    this->X = other.X;
    this->Y = other.Y;
  }
  bool operator==(const P2D &other) {
    return (this->X == other.X) && (this->Y == other.Y);
  }
  void operator+=(const P2D &other) {
    P2D temp(this->X + other.X, this->Y + other.Y);
    this->X = temp.X;
    this->Y = temp.Y;
  }
  void operator-=(const P2D &other) {
    P2D temp(this->X - other.X, this->Y - other.Y);
    this->X = temp.X;
    this->Y = temp.Y;
  }
};
class P3D {
public:
  float X;
  float Y;
  float Z;
  P3D(float x = 0, float y = 0, float z = 0) {
    this->X = x;
    this->Y = y;
    this->Z = z;
  }
  float Magnitude() {
    return std::sqrt(std::pow(X, 2) + std::pow(Y, 2) + std::pow(Z, 2));
  }
  float Pitch() { return Deg(std::atan(Y / Z)); }
  float Yaw() { return Deg(std::atan(X / Z)); }
  P3D operator-(const P3D &other) {
    return P3D(this->X - other.X, this->Y - other.Y, this->Z - other.Z);
  }
  P3D operator+(const P3D &other) {
    return P3D(this->X + other.X, this->Y + other.Y, this->Z + other.Z);
  }
  void operator=(const P3D &other) {
    this->X = other.X;
    this->Y = other.Y;
    this->Z = other.Z;
  }
  bool operator==(const P3D &other) {
    return (this->X == other.X) && (this->Y == other.Y) && (this->Z == other.Z);
  }
  void operator+=(const P3D &other) {
    P3D temp(this->X + other.X, this->Y + other.Y, this->Z + other.Z);
    this->X = temp.X;
    this->Y = temp.Y;
    this->Z = temp.Z;
  }
  void operator-=(const P3D &other) {
    P3D temp(this->X - other.X, this->Y - other.Y, this->Z - other.Z);
    this->X = temp.X;
    this->Y = temp.Y;
    this->Z = temp.Z;
  }
};
class worldSpace : public P2D {
public:
  float O = 0;
  float Radius = 0;

  worldSpace(float x = 0, float y = 0, float r = 5, float o = 0) {
    this->O = o;
    this->X = x;
    this->Y = y;
    this->Radius = r;
    Obstacles.push_back(this);
  }

  bool operator==(const worldSpace &other) {
    return (this->X == other.X) && (this->Y == other.Y);
  }
  bool operator!=(const worldSpace &other) {
    return (this->X != other.X) || (this->Y != other.Y);
  }
  worldSpace operator-(const P2D &other) {
    return worldSpace(this->X - other.X, this->Y - other.Y);
  }
  worldSpace operator+(const P2D &other) {
    return worldSpace(this->X + other.X, this->Y + other.Y);
  }
  void operator+=(const P2D &other) {
    P2D temp(this->X + other.X, this->Y + other.Y);
    this->X = temp.X;
    this->Y = temp.Y;
  }
  void operator-=(const P2D &other) {
    P2D temp(this->X - other.X, this->Y - other.Y);
    this->X = temp.X;
    this->Y = temp.Y;
  }
  worldSpace operator=(const worldSpace &other) { return other; }
}; // namespace worldSpace:public P2D

namespace misc {
void DefStatus(int); /*
 print a huge block of sensor values (if enabled)
 in: 12bits, i.e. 0xfff, 0b1111_1111_1111
 00: OXY of the bot (print worldspace)
 01: Battery level of the bot
 02: every motor position in ticks
 03: accelerometer values and average
 04: gyroscope values and average
 05: compass angle
 06: motor multiplier values
 07: servo positions in tics
 08: servos enabled?
 09: digital values
 10: analog values
 11: sets debugging on or off
 */
void Timer();    // start a clock that updates a global variable. does not end
void HandsOff(); // starts handsoff/shutdownin
void Status(string);           // overload of DefStatus
void Status(char, char, char); // overload of DefStatus
void Start(bool, int, bool, int, int, float, float,
           float); // initializes variables

namespace buttons {
void Show(bool); // show the buttons on screen?
bool Visible();  // are the buttons on screen?
namespace up {
bool A(); // is a button not pressed
bool B();
bool C();
bool X();
bool Y();
bool Z();
}; // namespace up
namespace down {
bool A(); // is a button pressed
bool B();
bool C();
bool X();
bool Y();
bool Z();
}; // namespace down
namespace pressed {
bool A(); // has a button been clicked
bool B();
bool C();
bool X();
bool Y();
bool Z();
}; // namespace pressed
}; // namespace buttons
}; // namespace misc

namespace pathFind {
void AthenaDecision(float,
                    float); /*Decide which algorithm to use, then uses it.*/
/* IN {-> Change in Left wheel position, Change in Right wheel position
 */
void AngularPathfind(float, float); /*Updates orientation based on inputs*/
void LinearPathfind(float, float);  /*Updates position based on inputs*/
void DynamicPathfind(float, float); /*Updates position and orientation based on
                                       inputs. MAY DIVIDE BY 0*/
void Face(float, float); // face a certain degree heading in given time
void GoTo(float, float,
          float);      // go to an (x,y) coordinate in a given time
void GoTo(P2D, float); // overload
}; // namespace pathFind

namespace sensors {
enum type { Analog, Digital };

namespace dgtl {
bool Value(int); // get the value of a port
}; // namespace dgtl
namespace nlg {
float Value(int); // get the value of a port as a percent of the max
int Raw(int);     // get the raw value of a port
}; // namespace nlg
namespace accel {
P3D Value;
void Calibrate();  // calibrates the accelerometer
float Magnitude(); // gets the magnitude of the vector the accelerometer is
                   // pointing at
float Pitch();     // gets the pitch of the vector
float Yaw();       // gets the yaw of the vector
void Update();     // update the vector's values. (automatically called on
                   // mag,pitch,yaw)
}; // namespace accel
namespace gyro {
P3D Value;
void Calibrate();
float Magnitude();
float Pitch();
float Yaw();
void Update();
}; // namespace gyro
namespace mag {
P3D Value;
void Calibrate();
float Magnitude();
float Pitch();
float Yaw();
void Update();
}; // namespace mag
namespace bttry {
int Power();     // get the power level from 0-100
bool Critical(); // is the battery less than 33% full?
}; // namespace bttry
}; // namespace sensors

namespace servos {
void Set(int, float);    // go to a degree angle in a certain time
void Move(int, float);   // change the degree angle in a certain time
void Change(int, float); // go to a degree angle smoothly in a certain time
}; // namespace servos

namespace motors {
void ClearMotorRotations(int, int); // sets the counter to 0
void Velocity(int, int, float &,
              float &); // updates the global velocity variables, keep it in a
                        // thread. it has no end.
void Speed(float, float, float, int, int, float, float,
           float); // drive at a speed for a time
void Distance(float, float, float, int, int, float, float,
              float); // drive to a distance per wheel in this time
void Rotation(float, float, float, int, int, float, float,
              float); // drive to an angle per wheel in this time
void Accelerate(float, float, float, int, int, float &, float &, float, float,
                float); // interpolate to a speed
void Brake(int, int);   // turn on the brakes
}; // namespace motors

class newThread {
public:
  thread Thread;
  newThread(
      void (*func)()) { // create a new thread with a function as a parameter
    Thread = thread_create(func);
  }
  void Run();  // start the thread
  void Kill(); // end the thread
}; // namespace newThread

float Interpolate(float timePercent, float delta) {
  DLOG return (
      std::pow(timePercent, 2.16) /
      (std::pow(timePercent, 2.16) + (std::pow((1 - timePercent), 2.16)))) *
      delta;
}

float Rad(float degrees) { DLOG return degrees * 0.01745329251; }
float Deg(float radians) { DLOG return radians * 57.2957795131; }
float mm(float inches) { return inches * 25.4; }
float inch(float mm) { return mm / 25.4; }

/*
 * ATBC();
 * A to B for the C
 * A = degrees
 * B = ticks
 * C = wheels
 * Degrees to Ticks for the Wheels
 */
int DTTW(float degrees) { DLOG return degrees * 5.55; }

float TTDW(int ticks) { DLOG return ticks / 5.55; }

float DTIW(float degrees, float radius) { DLOG return radius * Rad(degrees); }

float ITDW(float inches, float radius) { DLOG return Deg(radius / inches); }

float TTIW(int ticks) { DLOG return ticks / 206.49999936; }

int ITTW(float inches) { DLOG return inches * 206.49999936; }
/***********************/
int DTTA(float degrees) { DLOG return (-12.2222 * degrees) + 1450; }

float TTDA(int tics) { DLOG return (-0.081818 * tics) + 118.636; }

int DTTC(float degrees) { DLOG return (12.05 * degrees) + 723.5; }

float TTDC(int tics) { DLOG return (0.082 * tics) - 60; }

template <typename A, typename B, typename C> bool Clamp(A min, B val, C max) {
  DLOG return (min < val && val < max);
}

template <typename A, typename B, typename C>
bool MarginOfError(A inputA, B inputB, C range) {
  DLOG float min = inputB - range;
  float max = inputB + range;
  return Clamp(min, inputA, max);
}

string PrettyTime(int ms) {
  int min, sec;
  int totalms = ms;
  min = totalms / (60 * 1000);
  totalms %= 60 * 1000;
  sec = totalms / 1000;
  totalms %= 1000;

  // Convert totalms to float and then to string to handle decimals
  std::string msStr = std::to_string(totalms / 1000.0f);

  // Remove trailing zeros
  size_t found = msStr.find_last_not_of('0');
  if (found != std::string::npos && found != msStr.size() - 1) {
    msStr = msStr.substr(0, found + 1);
  }

  return std::to_string(min) + ":" + std::to_string(sec) + msStr.substr(1);
}

worldSpace Position(0, 0, 0, 0);

#include "misc.h"
#include "motor.h"
#include "pathfind.h"
#include "sensor.h"
#include "servo.h"
} // namespace BKND
