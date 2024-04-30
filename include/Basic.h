#pragma once
/* EXAMPLE
#include "Basic.h"
misc Misc;
motors Tank(0,0);
pathFind Athena();
sensors Sensor(1);
servos Arm(0,1);

int main()
{
    isCreate = true;
    Misc.Start(false);
    return 0;
}
*/


/* 
* TODO LIST
* Motor 5
* Motor 13
* Basic 439
* Basic 447
* Basic 455
* Basic 463
* Basic 471
* Basic 479
*/


bool isCreate = false;

#include </kipr/wombat.h>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
using std::string;
using std::vector;

auto program_start_time = std::chrono::high_resolution_clock::now();
#define DLOG if(Debugging) {\
	auto now = std::chrono::high_resolution_clock::now();\
	auto elapsedtime = std::chrono::duration_cast<std::chrono::milliseconds>(now-program_start_time);\
	std::cout << __PRETTY_FUNCTION__ << " (" << __LINE__ << ") Time since start: " << PrettyTime(elapsedtime.count()) << std::endl;\
}
class newThread;//thread functionality
class P2D;//2 dimensional coordinate
class P3D;//3 dimensional coordinate
class worldSpace;//2 dimensional coordinate with additional functionality
class motors;//motor control
class buttons;//on screen button control (abcxyz)
class misc;//other stuff i couldn't label
class dgtl;//digital sensors
class nlg;//analog sensors
class accel;//accelerometer control
class gyro;//gyroscope control
class mag;//magnetometer control WIP
class bttry;//battery control
class sensors;//(dgtl,nlg,accel,gyro,mag,bttry) wrapper
class servos;//servo control (inverse kinematics to come
class up;//button up (not pressed)
class down;//button down (pressed)
class pressed;//button down (pressed, only returns true once per press)


std::vector<worldSpace*> Obstacles;

short int LeftMotor;  // left motor port
short int RightMotor; // right motor port
float LMM; // if a motor is drifting, adjust this number accordingly
float RMM; // if its drifting to the left, lower the right motor multiplier
// (between 1 and 0)
float TimeMultiplier = 1; // multiplies time in order to adjust for distance loss (greater than 1)
float LeftSpeed = 0;
float RightSpeed = 0;

short int StartLight; // start on light sensor port

short int ArmServo;
short int ClawServo;

bool Debugging;
long int CurrentMS = 0;

float WheelRadius = 1.5;
float AxleRadius = 3.5;
const float TurnRate = 3.9; // i have no fucking idea how to calculate this man just
// guess until you're right... supposed to be (axle length / wheel length ) +1 but that gives like 3.6 or something and that doesn't work so whatever... maybe my unit conversions are wrong somewhere idk man
const int AthenaMargin = 5;


float Deg(float);/*Convert Radians to Degrees*/
float Rad(float);/*Convert Degrees to Radians*/
float ITDW(float);/*Convert inches to degrees (for the wheel)*/
float DTIW(float);/*convert degrees to inches (for the wheel)*/
int DTTA(float);/*convert degrees to ticks (for the arm servo)*/
int DTTC(float);/*convert degrees to ticks (for the claw servo)*/
int DTTW(float);/*convert degrees to ticks (for the wheel)*/
int ITTW(float);/*convert inches to ticks (for the wheel)*/
float TTDA(int);/*convert ticks to degrees (for the arm servo)*/
float TTDC(int);/*convert ticks to degrees (for the claw servo)*/
float TTDW(int);/*convert ticks to degrees (for the wheel)*/
float TTIW(int);/*convert ticks to inches (for the wheel)*/
float Interpolate(float, float);/*get a smooth transition from point a to point b*/
/*IN {-> Time (from 1 to 0), Delta (from 0 to this number)
* OUT{-> value returned from the equation.
* USE{-> put it in a for loop, i.e.
* for(float i = 0; i < 1; i+=0.01){
*		motors::Speed(Interpolate(i,1),Interpolate(i,1),0.1);
* }
* this leads to a very smooth increase in speed (3rd derivative continuous
*/
template <typename A, typename B, typename C>
bool MarginOfError(A, B, C);/*is a close to b?*/
/*IN {-> Check, Goal, Range
* OUT{-> true/false
* is A within BB1C?
*/
template <typename A, typename B, typename C>
bool Clamp(A, B, C);/*Is B within A and C?*/
/*IN {-> Min, Value, Max
* OUT {-> Min<=Value<=Max
*/
void Wait(float);/*Wait for x seconds*/
string PrettyTime(int);/*display milliseconds as min:sec.ms*/
void AthenaDecision(float, float);/*Decide which algorithm to use, then uses it.*/
/* IN {-> Change in Left wheel position, Change in Right wheel position
*/
void AngularPathfind(float, float);/*Updates orientation based on inputs*/
void LinearPathfind(float, float);/*Updates position based on inputs*/
void DynamicPathfind(float, float);/*Updates position and orientation based on inputs. MAY DIVIDE BY 0*/




class P2D {
public:
  float X;
  float Y;
  P2D(float x = 0, float y = 0) {
    this->X = x;
    this->Y = y;
  }
  float Magnitude() {
    return sqrt(pow(X, 2) + pow(Y, 2));
  }
  float Angle() {
    return Deg(atan2(Y, X));
  }
  P2D operator-(const P2D& other) {
    return P2D(this->X - other.X, this->Y - other.Y);
  }
  P2D operator+(const P2D& other) {
    return P2D(this->X + other.X, this->Y + other.Y);
  }
  void operator=(const P2D& other) {
    this->X = other.X; this->Y = other.Y;
  }
  bool operator==(const P2D& other) {
    return (this->X == other.X) && (this->Y == other.Y);
  }
  void operator+=(const P2D& other) {
    P2D temp(this->X + other.X, this->Y + other.Y);
    this->X = temp.X; this->Y = temp.Y;
  }
  void operator-=(const P2D& other) {
    P2D temp(this->X - other.X, this->Y - other.Y);
    this->X = temp.X; this->Y = temp.Y;
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
    return sqrt(pow(X, 2) + pow(Y, 2) + pow(Z, 2));
  }
  float Pitch() {
    return Deg(atan(Y / Z));
  }
  float Yaw() {
    return Deg(atan(X / Z));
  }
  P3D operator-(const P3D& other) {
    return P3D(this->X - other.X, this->Y - other.Y, this->Z - other.Z);
  }
  P3D operator+(const P3D& other) {
    return P3D(this->X + other.X, this->Y + other.Y, this->Z + other.Z);
  }
  void operator=(const P3D& other) {
    this->X = other.X; this->Y = other.Y; this->Z = other.Z;
  }
  bool operator==(const P3D& other) {
    return (this->X == other.X) && (this->Y == other.Y) && (this->Z == other.Z);
  }
  void operator+=(const P3D& other) {
    P3D temp(this->X + other.X, this->Y + other.Y, this->Z + other.Z);
    this->X = temp.X; this->Y = temp.Y; this->Z = temp.Z;
  }
  void operator-=(const P3D& other) {
    P3D temp(this->X - other.X, this->Y - other.Y, this->Z - other.Z);
    this->X = temp.X; this->Y = temp.Y; this->Z = temp.Z;
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

  bool operator == (const worldSpace& other) {
    return (this->X == other.X) && (this->Y == other.Y);
  }
  bool operator != (const worldSpace& other) {
    return (this->X != other.X) || (this->Y != other.Y);
  }
  worldSpace operator-(const P2D& other) {
    return worldSpace(this->X - other.X, this->Y - other.Y);
  }
  worldSpace operator+(const P2D& other) {
    return worldSpace(this->X + other.X, this->Y + other.Y);
  }
  void operator+=(const P2D& other) {
    P2D temp(this->X + other.X, this->Y + other.Y);
    this->X = temp.X; this->Y = temp.Y;
  }
  void operator-=(const P2D& other) {
    P2D temp(this->X - other.X, this->Y - other.Y);
    this->X = temp.X; this->Y = temp.Y;
  }
  worldSpace operator = (const worldSpace& other) {
    return other;
  }
};

class newThread {
public:
  thread Thread;
  newThread(void(*func)()) {//create a new thread with a function as a parameter
    Thread = thread_create(func);
  }
  void Run();//start the thread
  void Kill();//end the thread
};
class up {
public:
  static bool A();//is a button not pressed
  static bool B();
  static bool C();
  static bool X();
  static bool Y();
  static bool Z();
};
class down {
public:
  static bool A();//is a button pressed
  static bool B();
  static bool C();
  static bool X();
  static bool Y();
  static bool Z();
};
class pressed {
public:
  static bool A();//has a button been clicked
  static bool B();
  static bool C();
  static bool X();
  static bool Y();
  static bool Z();
};
class buttons {
public:
  void Show(bool);//show the buttons on screen?
  bool Visible();//are the buttons on screen?
  pressed Pressed;
  up Up;
  down Down;
};
class misc {
private:
  static void DefStatus(char[]);/*
  print a huge block of sensor values (if enabled)
  in: 3 char hex array (fff,000,fa6,etc)
  00:OXY of the bot (print worldspace)
  01:Battery level of the bot
  02:every motor position in ticks
  03:accelerometer values and average
  04:gyroscope values and average
  05:compass angle
  06:motor multiplier values
  07:servo positions in tics
  08:servos enabled?
  09:digital values
  10:analog values
  11:sets debugging on or off
  */
public:
  static void Timer();//start a clock that updates a global variable. does not end
  static void HandsOff();//starts handsoff/shutdownin
  static void Status(string);//overload of DefStatus
  static void Status(char, char, char);//overload of DefStatus
  static void Start(bool, bool);//initializes variables

  buttons Buttons;
};

class pathFind {
public:
  static void Face(float, float);//face a certain degree heading in given time
  static void GoTo(float, float, float);//go to an (x,y) coordinate in a given time
  static void GoTo(P2D, float);//overload
};

class dgtl {
public:
  static bool Value(int);//get the value of a port
};
class nlg {
public:
  static float Value(int);//get the value of a port as a percent of the max
  static int Raw(int);//get the raw value of a port
};
class accel {
public:
  P3D Value;
  void Calibrate();//calibrates the accelerometer
  float Magnitude();//gets the magnitude of the vector the accelerometer is pointing at
  float Pitch();//gets the pitch of the vector
  float Yaw();//gets the yaw of the vector
  void Update();//update the vector's values. (automatically called on mag,pitch,yaw)
};
class gyro {
public:
  P3D Value;
  void Calibrate();
  float Magnitude();
  float Pitch();
  float Yaw();
  void Update();
};
class mag {
public:
  P3D Value;
  void Calibrate();
  float Magnitude();
  float Pitch();
  float Yaw();
  void Update();
};
class bttry {
public:
  static int Power();//get the power level from 0-100
  static bool Critical();//is the battery less than 33% full?
};
class sensors {
public:
  sensors(int startlight = 0) {
    StartLight = startlight;
  }
  dgtl Digital;
  nlg Analog;
  accel Accel;
  gyro Gyro;
  mag Mag;
  bttry Battery;
};

class servos {
public:
  servos(int armport, int clawport) {
    ArmServo = armport; ClawServo = clawport;
  }
  static void Set(float, float);//go to a degree angle in a certain time
  static void Move(float, float);//change the degree angle in a certain time
  static void Change(float, float);//go to a degree angle smoothly in a certain time
};

class motors {
public:
  motors(int leftport = 0, int rightport = 0, float leftmult = 1, float rightmult = 1) {
    LeftMotor = leftport; RightMotor = rightport; LMM = leftmult; RMM = rightmult;
    ClearMotorRotations();
  }
  static void ClearMotorRotations();//sets the counter to 0
  static void Velocity();//updates the global velocity variables, keep it in a thread. it has no end.
  static void Speed(float, float, float);//drive at a speed for a time
  static void Distance(float, float, float);//drive to a distance per wheel in this time
  static void Rotation(float, float, float);//drive to an angle per wheel in this time
  static void Accelerate(float, float, float);//interpolate to a speed
  static void Brake();//turn on the brakes
};

float Interpolate(float timePercent, float delta) {
  DLOG
    return (pow(timePercent, 2.16) / (pow(timePercent, 2.16) + (pow((1 - timePercent), 2.16)))) * delta;
}

float Rad(float degrees) {
  DLOG
    return degrees * 0.01745329251;
}
float Deg(float radians) {
  DLOG
    return radians * 57.2957795131;
}
float mm(float inches) {
  return inches * 25.4;
}
float inch(float mm) {
  return mm / 25.4;
}

/*
* ATBC();
* A to B for the C
* A = degrees
* B = ticks
* C = wheels
* Degrees to Ticks for the Wheels
*/
int DTTW(float degrees) {
  DLOG
    if ( isCreate ) {
      return 1;
    }
  return degrees * 5.55;
}

float TTDW(int ticks) {
  DLOG
    if ( isCreate ) {
      return 1;
    }
  return ticks / 5.55;
}

float DTIW(float degrees) {
  DLOG
    if ( isCreate ) {
      return 1;
    }
  return WheelRadius * Rad(degrees);
}

float ITDW(float inches) {
  DLOG
    if ( isCreate ) {
      return 1;
    }
  return Deg(WheelRadius / inches);
}

float TTIW(int ticks) {
  DLOG
    if ( isCreate ) {
      return 1;
    }
  return ticks / 206.49999936;
}

int ITTW(float inches) {
  DLOG
    if ( isCreate ) {
      return 1;
    }
  return inches * 206.49999936;
}
/***********************/
int DTTA(float degrees) {
  DLOG
    return (-12.2222 * degrees) + 1450;
}

float TTDA(int tics) {
  DLOG
    return (-0.081818 * tics) + 118.636;

}

int DTTC(float degrees) {
  DLOG
    return (12.05 * degrees) + 723.5;
}

float TTDC(int tics) {
  DLOG
    return (0.082 * tics) - 60;
}

void Wait(float time) {
  DLOG
    motors::Brake();
  msleep(time * 1000);
}

template <typename A, typename B, typename C>
bool Clamp(A min, B val, C max) {
  DLOG
    return (min < val && val < max);
}

template <typename A, typename B, typename C>
bool MarginOfError(A inputA, B inputB, C range) {
  DLOG
    float min = inputB - range;
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
  if ( found != std::string::npos && found != msStr.size() - 1 ) {
    msStr = msStr.substr(0, found + 1);
  }

  return std::to_string(min) + ":" + std::to_string(sec) + msStr.substr(1);
}


worldSpace Position(0, 0, 0, 0);

#include "Misc.h"
#include "Motor.h"
#include "Pathfind.h"
#include "Sensor.h"
#include "Servo.h"