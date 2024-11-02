#pragma once
#include "../../../libwallaby/kipr.h"
#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
namespace BKND {
class Thread;     // thread functionality
class P2D;        // 2 dimensional coordinate
class P3D;        // 3 dimensional coordinate
class worldSpace; // 2 dimensional coordinate with additional functionality
struct pass {
  int leftmotor; // left motor port
  int rightmotor;
  float lmm; // left motor multiplier
  float rmm;
  float tmm;
  float margin;
  float turnrate;
  float &leftspeed;
  float &rightspeed;
  pass(int lm, int rm, float l, float r, float t, float m, float tr, float &ls,
       float &rs)
      : leftmotor(lm), rightmotor(rm), lmm(l), rmm(r), tmm(t), margin(m),
        turnrate(tr), leftspeed(ls), rightspeed(rs) {}
};
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
bool Clamp(A p_min, B p_val, C p_max) {
  return (p_min < p_val && p_val < p_max);
}

template <typename A, typename B, typename C>
bool MarginOfError(A p_inputa, B p_inputb, C p_range) {
  float min = p_inputb - p_range;
  float max = p_inputb + p_range;
  return Clamp(min, p_inputa, max);
}
string PrettyTime(int); /*display milliseconds as min:sec.ms*/

namespace misc {
void waitforlight(int);
void Timer();    // start a clock that updates a global variable. does not end
void HandsOff(); // starts handsoff/shutdownin
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
void AthenaDecision(float, float,
                    pass); /*Decide which algorithm to use, then uses it.*/
/* IN {-> Change in Left wheel position, Change in Right wheel position
 */
void AngularPathfind(float, float,
                     pass);         /*Updates orientation based on inputs*/
void LinearPathfind(float, float);  /*Updates position based on inputs*/
void DynamicPathfind(float, float); /*Updates position and orientation based on
                                       inputs. MAY DIVIDE BY 0*/
void Face(float, float, pass); // face a certain degree heading in given time
void GoTo(BKND::P2D, float, pass); // go to an (x,y) coordinate in a given time
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
void Calibrate();  // calibrates the accelerometer
float Magnitude(); // gets the magnitude of the vector the accelerometer is
                   // pointing at
float Pitch();     // gets the pitch of the vector
float Yaw();       // gets the yaw of the vector
void Update();     // update the vector's values. (automatically called on
                   // mag,pitch,yaw)
}; // namespace accel
namespace gyro {
void Calibrate();
float Magnitude();
float Pitch();
float Yaw();
void Update();
}; // namespace gyro
namespace mag {
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
void Set(int, float);
void Change(int, float);
void Move(int, float, float);
}; // namespace servos

namespace motors {
void ClearMotorRotations(pass); // sets the counter to 0
void Velocity(pass); // updates the global velocity variables, keep it in a
                     // thread. it has no end.
void Speed(float p_leftpercent, float p_rightpercent, float p_timeinseconds,
           pass Vals); // drive at a speed for a time
void Distance(float p_leftinches, float p_rightinches, float p_timeinseconds,
              pass Vals); // drive to a distance per wheel in this time
void Rotation(float p_leftdegrees, float p_rightdegrees, float p_timeinseconds,
              pass Vals); // drive to an angle per wheel in this time
void Accelerate(float p_leftmaxpercent, float p_rightmaxpercent,
                float p_timeinseconds, pass Vals); // interpolate to a speed
void Brake(pass Vals);                             // turn on the brakes
}; // namespace motors

class P2D {
public:
  float m_X;
  float m_Y;
  P2D(float x = 0, float y = 0);
  float Magnitude();
  float Angle();
  P2D operator-(const P2D &p_other);
  P2D operator+(const P2D &p_other);
  void operator=(const P2D &p_other);
  bool operator==(const P2D &p_other);
  void operator+=(const P2D &p_other);
  void operator-=(const P2D &p_other);
};
class P3D {

public:
  float m_X;
  float m_Y;
  float m_Z;
  P3D(float p_x = 0, float p_y = 0, float p_z = 0);
  float Magnitude();
  float Pitch();
  float Yaw();
  P3D operator-(const P3D &p_other);
  P3D operator+(const P3D &p_other);
  void operator=(const P3D &p_other);
  bool operator==(const P3D &p_other);
  void operator+=(const P3D &p_other);
  void operator-=(const P3D &p_other);
};
class worldSpace : public P2D {
public:
  float m_O;
  float m_Radius;

  worldSpace(float p_x = 0, float p_y = 0, float p_r = 0, float p_o = 0);

  bool operator==(const worldSpace &p_other);
  bool operator!=(const worldSpace &p_other);
  worldSpace operator-(const P2D &p_other);
  worldSpace operator+(const P2D &p_other);
  void operator+=(const P2D &p_other);
  void operator-=(const P2D &p_other);
  worldSpace operator=(const worldSpace &p_other);
}; // namespace worldSpace:public P2D

float Interpolate(float p_timepercent, float p_delta);
class Thread {
public:
  thread m_Thethread;
  Thread(void (*p_func)());
  void Run();  // start the thread
  void Kill(); // end the thread
}; // namespace newThread

inline long int CurrentMS;
inline std::vector<worldSpace *> Obstacles;
inline worldSpace Position(0, 0, 0, 0);

} // namespace BKND
