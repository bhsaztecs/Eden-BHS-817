// figure out how to put this in a seperate namespace

//#include "C:\Users\samiy\Downloads\Robotics\kipr\kipr\wombat.h"
//#include "C:\Users\samiy\Downloads\kipr.wallaby\wombat.h"
#include <kipr/wombat.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
extern "C" {
#include <math.h>
#include <stdio.h>
#include <assert.h>	
#include <float.h>
#include <signal.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <stddef.h>	
#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>
	namespace bknd {

		/////////////////
		//  constants  //
		//  //  /  //  //
		//    ports    //
		//  //  /  //  //
		short int LeftMotor;  // left motor port
		short int RightMotor; // right motor port
		short int ClawServo;   // claw servo port
		short int ArmServo;    // arm servo port
		//  //  /  //  //
		short int LeftButton;  // back left button port
		short int RightButton; // back right button port
		short int FrontButton; // front bar button port
		//  //  /  //  //
		short int StartLight; // start on light sensor port
		short int DownLight;  // downward light sensor port
		short int FrontLight; // frontward light sensor port
		//  //  /  //  //
		//    other    //
		//  //  /  //  //
		//  //  /  //  //
		float LMM = 1; // if a motor is drifting, adjust this number accordingly
		float RMM = 1; // if its drifting to the left, lower the right motor multiplier
		// (between 1 and 0)
		float timemult =
			1; // multiplies time in order to adjust for distance loss (greater than 1)

		const float WheelRadius = 1.5; // radius of the wheel in inches
		const float AxelRadius = 3.25; // radius of the axel in inches
		const float TurnRate = 3.8; // i have no fucking idea how to calculate this man just
		// guess until youre right

		float CurrentO; // robot's starting orientation relative to global setup
		float CurrentX; // robot's X offset relative to global setup
		float CurrentY; // robot's Y offset relative to global setup

		bool AthenaOn = true; // disables pathfinding if its draining too many recources
		float athenaMargin = 5;  // margin of error in which math is chosen, higher for
		// less recourses, lower for more precision
		bool CollisionChecks = 1; // disables collision checks

		// IGNORE THIS SHIT
		float DeltaL = 0;
		float DeltaR = 0;

		int Lv = 0;
		int Rv = 0;
		float Lp = 0;
		float Rp = 0;

		float WMM = 1;
		const char Sfff[3] = { 'f', 'f', 'f' };
		const char S000[3] = { '0', '0', '0' };
		bool commandCalls = 0;
		bool Collision = 0;

		int centisec = 0;
		int sec = 0;
		int min = 0;

		bool AutoTravel = false;
		bool Confirm = false;
		bool Diagnostics = false;
		bool AthenaToggle = true;
		bool HandsOffToggle = false;
		bool CollisionToggle = true;
		int menubuffer = 0;
		char hex[3];
		////////////////////
		//  DECLARATIONS  //
		////////////////////

		float SmoothLine(float,float);
		//in (Percent time elapsed, Change in position(static))
		//out (Value from 0 - delta)

		//float absolute(float);
		// in (value)
		// Get the absolute value of an input
		// abs() wasnt working for whatever reason idk
		// out (absolute value)

		// void(*CollisionCheck());
		//  Checks if the robot is attempting to move and failing
		//  WIP (need to check the Gs in the direction its not going)

		//void CollisionReset();
		// Brings the robot to face the south wall and the west wall in order to find
		// the location of the colision

		//void CollisionRecovery(float, float, float);
		// in (x offset, y offset, angular offset)
		// Brings the robot to the point of collision, with an optional offset ((0,0,0)
		// for no offset.)

		void AthenaDecision(float, float);
		// in (left delta, right delta)
		// decides which method of position/orientation calculation to preform

		void AOPivot(float, float);
		// in(Delta L, Delta R)
		// calculates the change in orientation of the robot given a pivot

		void APCount(float, float);
		// in(Delta L, Delta R)
		// calculates the change position given a straight movement

		void APOTrig(float, float);
		// in(Delta L, Delta R);
		// calculates the change in position given complex deltas

		void AOCalc(float);
		// calculates the new orientation given the previous orientation and the change
		// from previous orientation

		void APCalc(float, float);
		// calculates the new position given the previous orientation and the previous
		// location, as well as the delta orientation and delta position

		int Status(char hex[]);
		// in (hexadecimal string which prints a set of chosen values)
		/*
		Type the function like this
		hex[0] = 'F';
		hex[1] = 'F';
		hex[2] = 'F';
		Status(hex);
		*/
		// OXY/Athena, Battery, Motor positions, Accelerometer, Gyro, Compass, Motor
		// Multipliers, Servo Positions, Enabled Servos, Digitals, Analogs,
		// CommandCalls(updates until further notice) hex value will be 3 characters
		// (use https://www.rapidtables.com/convert/number/binary-to-hex.html) FFF
		// prints all values 000 prints none prints the current state of the robot
		// out(orientation, position, sensor values, wheel positions, servo
		// positions, etc)

		int MOE(float, float, float);
		// in (value one, value two, range)
		// calculates if value one is within a certain range of value two
		// out (1 if values are within range, 0 if not)

		void ArmVertical(float, float);
		// in (goal position, time)
		// locks the arm on the z axis as it attempts to go from the current position to
		// the goal position

		float rad(float);
		// in (degrees)
		// converts degrees to radians
		// math.h's was busted idk
		// out (radians)

		float degrees(float);
		// in (radians)
		// converts radians to degrees
		// out (degrees)

		void Velocity();
		// calculates the current velocity of each wheel in powerpercent

		void Timer();
		// Acts as a stopwatch. records time as: min,sec,centisec
		// sec and centisec rollover. youll never see 61 seconds, just 1 min 1 sec.

		int clamp(float, float, float);
		// in (min, val, max)
		// checks that a value is within the minimum and maximum value
		// out (1 true, 0 false)

		void TankSpeed(float, float, float);
		// in (left speed, right speed, time)
		// moves the wheels independently at a certain speed for a certain amount of
		// time

		void TankRotation(float, float, float);
		// in (left wheel goal, right wheel goal, time)
		// moves the wheels independently to a goal position in a certain amount of time

		void TankDistance(float, float, float);
		// in (left wheel goal, right wheel goal, time)
		// moves the wheels independently to a goal position in a certain amount of time

		void DriveSpeed(float, float, float);
		// in (base speed, turn percent, time);
		// moves the wheels together at a certain speed for a certain amount of time

		void DriveRotation(float, float, float);
		// in (base rotations, turn rotations, time);
		// moves the wheels together to a goal position in a certain amount of time

		void DriveDistance(float, float, float);
		// in (base distance, turn distance, time);
		// moves the wheels together to a goal position in a certain amount of time

		void TankAccelerate(float, float, float);
		// in (left goal, right goal, acceleration value)
		// moves the wheels independently, going faster over time

		void DriveAccelerate(float, float, float);
		// in (base speed goal, turn speed goal, acceleration value)
		// moves the wheels together, going faster over time

		void SmoothTankTime(float, float, float, float, int, float);
		// in (first left acceleration goal, first right acceleration goal, second left
		// acceleration goal, second right acceleration goal, 	acceleration value, how
		// long to move at first goal) moves from current speed to a new goal, stays at
		// the goal for a certain amount of time, and then goes from that goal to the
		// second goal

		void SmoothDriveTime(float, float, float, float, int, float);
		// in (first base acceleration goal, first turn acceleration goal, second base
		// acceleration goal, second turn acceleration goal, 	acceleration value, how
		// long to move at first goal) moves from current speed to a new goal, stays at
		// the goal for a certain amount of time, and then goes from that goal to the
		// second goal

		void SetArm(float, float);
		// in (arm goal, claw goal)
		// sets the arm and claw to a goal position

		void ChangeArm(float, float);
		// in (delta arm position, delta claw position)
		// changes the arm from the current position to the goal position

		void SlowSetArm(float, float);
		// in (goal arm position, time)
		// goes to the goal arm position in a certain amount of time

		int DTTW(float);
		// in (Degrees)
		// converts degrees to wheel ticks
		// out (Ticks)

		float TTDW(int);
		// in (Ticks)
		// converts wheel ticks to degrees
		// out (Degrees)

		float DTIW(float);
		// in (Degrees)
		// converts wheel degrees to inches
		// out (Inches)

		float ITDW(float);
		// in (Inches)
		// converts inches to wheel degrees
		// out (Degrees)

		float TTIW(int);
		// in (Ticks)
		// converts wheel ticks into inches
		// out (Inches)

		int ITTW(float);
		// in (Inches)
		// converts inches to wheel ticks
		// out (Ticks)

		int DTTA(float);
		// in (Degrees)
		// converts degrees to arm tics
		// out (Tics)

		float TTDA(int);
		// in (Tics)
		// converts arm tics to degrees
		// out (Degrees)

		int DTTC(float);
		// in(Degrees)
		// converts degrees to claw tics
		// out(Tics)

		float TTDC(int);
		// in(Tics)
		// converts claw tics to degrees
		// out(Degrees)

		void Wait(float);
		// in (seconds)
		// a pause

		void Stop();
		// employs braking in both wheels

		void CMR();
		// clears motor tick counters

		void HandsOff();
		// initiates wait for light program
		// stop touching the robot!

		void Startup();
		// initiates systems, prepares the robot to run

		void Menu();
		// Start menu allowing for live run adjustment

		void TankSpeed(float SpeedL, float SpeedR, float Time) {
			if (commandCalls) {
				printf("TankSpeed called. \n");
			}
			float Lo = TTIW(gmpc(LeftMotor));
			float Ro = TTIW(gmpc(RightMotor));
			motor(LeftMotor, (SpeedL * LMM));
			motor(RightMotor, (SpeedR * RMM));
			msleep((Time * 1000) * timemult);
			float Lt = TTIW(gmpc(LeftMotor));
			float Rt = TTIW(gmpc(RightMotor));
			float DelL = Lt - Lo;
			float DelR = Rt - Ro;
			if (AthenaOn) {
				AthenaDecision(DelL, DelR);
			}
		}

		void TankRotation(float RotL, float RotR, float Time) {
			if (commandCalls) {
				printf("TankRotation called. \n");
			}
			float DistL = DTIW(RotL);
			float DistR = DTIW(RotR);
			TankDistance(DistL, DistR, Time);
		}

		void TankDistance(float DistL, float DistR, float Time) {
			if (commandCalls) {
				printf("TankDistance called. \n");
			}
			float Ls = (ITTW(DistL) / Time) / 15;
			float Rs = (ITTW(DistR) / Time) / 15;
			if (Ls > 100 || Rs > 100) {
				if (Ls > Rs) {
					float t = ((Time * (Ls / 100)) + 0.01);
					printf("Speed (%f) is too high. increase time to %.2f \n", Ls, t);
				}
				else {
					float t = ((Time * (Rs / 100)) + 0.01);
					printf("Speed (%f) is too high. increase time to %.2f \n", Rs, t);
				}
			}
			else {
				TankSpeed(Ls, Rs, Time);
			}
		}

		void DriveSpeed(float BaseS, float DifS, float Time) {
			if (commandCalls) {
				printf("DriveSpeed called. \n");
			}
			float SpeedL = BaseS + DifS;
			float SpeedR = BaseS - DifS;

			TankSpeed(SpeedL, SpeedR, Time);
		}

		void DriveRotation(float BaseRot, float DifRot, float Time) {
			if (commandCalls) {
				printf("DriveRotation called. \n");
			}
			float RotL = BaseRot + DifRot;
			float RotR = BaseRot - DifRot;

			TankRotation(RotL, RotR, Time);
		}

		void DriveDistance(float BaseD, float DifD, float Time) {
			if (commandCalls) {
				printf("DriveDistance called. \n");
			}
			float DistL = BaseD + DifD;
			float DistR = BaseD - DifD;

			TankDistance(DistL, DistR, Time);
		}

		void TankAccelerate(float GoalSpeedL, float GoalSpeedR, float time) {
			if (commandCalls) {
				printf("TankAccelerate called. \n");
			}
			float SpeedL = Lp;
			float DeltaLp = GoalSpeedL - SpeedL;

			float SpeedR = Rp;
			float DeltaRp = GoalSpeedR - SpeedR;
			float i = 0;

			for (i = 0; i < 1; i+=0.01) {
				TankSpeed(SmoothLine(i,DeltaLp)+SpeedL, SmoothLine(i, DeltaRp)+SpeedR, time/100);
			}
		}

		void DriveAccelerate(float GoalBase, float GoalDif, float Time) {
			if (commandCalls) {
				printf("DriveAccelerate called. \n");
			}
			float CurrentBase = (Lp + Rp) / 2;
			float CurrentDif = CurrentBase - Rp;
			float SpeedDifB = GoalBase - CurrentBase;
			float SpeedDifD = GoalDif - CurrentDif;
			int i = 0;

			for (i = 0; i < 1; i+=0.01) {
				DriveSpeed(SmoothLine(i,SpeedDifB), SmoothLine(i,SpeedDifD), Time/100);
			}
		}

		void SmoothTankTime(float TopL, float TopR, float BotL, float BotR,
			int Acceleration, float Time) {
			if (commandCalls) {
				printf("SmoothTankTime called. \n");
			}
			TankAccelerate(TopL, TopR, Acceleration);
			TankSpeed(TopL, TopR, Time);
			TankAccelerate(BotL, BotR, Acceleration);
		}

		void SmoothDriveTime(float TopB, float TopD, float BotB, float BotD,
			int Acceleration, float Time) {
			if (commandCalls) {
				printf("SmoothDriveTime called. \n");
			}
			DriveAccelerate(TopB, TopD, Acceleration);
			DriveSpeed(TopB, TopD, Time);
			DriveAccelerate(BotB, BotD, Acceleration);
		}

		void SetArm(float PosA, float PosC) {
			if (commandCalls) {
				printf("SetArm called. \n");
			}
			enable_servos();
			set_servo_position(ArmServo, DTTA(PosA));
			msleep(10);
			set_servo_position(ClawServo, DTTC(PosC));
			msleep(10);
			disable_servos();
		}

		void ChangeArm(float DeltaA, float DeltaC) {
			if (commandCalls) {
				printf("ChangeArm called. \n");
			}
			int CurA = TTDA(get_servo_position(ArmServo));
			int CurC = TTDA(get_servo_position(ClawServo));
			int PosA = CurA + DeltaA;
			int PosC = CurC + DeltaC;

			SetArm(PosA, PosC);
		}

		void SlowSetArm(float Pos, float Time) {
			if (commandCalls) {
				printf("SlowSetArm called. \n");
			}
			int CurPos = get_servo_position(ArmServo);
			int distance = Pos - CurPos;
			int Distn = distance / 50;
			int Timen = Time / 50;
			int count = 0;
			while (count < 50) {
				ChangeArm(Distn, 0);
				msleep(Timen);
				count += 1;
			}
		}
		/*void ArmVertical(float Position, float Time) {
			if (commandCalls) {
				printf("ArmVertical called. \n");
			}
			Position = Position - Armoffsety;
			while (MOE(TTDA(get_servo_position(ArmServo)), Position, 10) != 1) {
				float armdist = TTDA(get_servo_position(Arm)) - Position;
				int Divisor = round(armdist * (-(armdist / 10)) + 10);
				float Increment = armdist / Divisor;
				float NextPosition = TTDA(get_servo_position(Arm)) + Increment;
				float Angle = asin(NextPosition / Armlength);
				float Versin =
					(Armlength - (sqrt(pow(Armlength, 2) - pow(NextPosition, 2)))) -
					Armoffsetx;

				SlowSetArm(TTDA(Angle), Time);
				TankDistance(Versin, Versin, Time);
			}
		}*/
		float SmoothLine(float TimePercent,float Delta) {
			float power = pow(TimePercent,2.16);
			return (power / (power + (pow((1 - TimePercent),2.16)))) * Delta;
		}

		float rad(float degrees) {
			if (commandCalls) {
				printf("rad called. \n");
			}
			float rad = degrees * 0.01745329251;
			return rad;
		}
		float degrees(float radians) {
			if (commandCalls) {
				printf("degrees called. \n");
			}
			float degrees = radians * 57.2957795131;
			return degrees;
		}
		int DTTW(float Degrees) {
			if (commandCalls) {
				printf("DTTW called. \n");
			}
			int Ticks = Degrees * 5.55;
			return Ticks;
		}

		float TTDW(int Ticks) {
			if (commandCalls) {
				printf("TTDW called. \n");
			}
			float Degrees = Ticks / 5.55;
			return Degrees;
		}

		float DTIW(float Degrees) {
			if (commandCalls) {
				printf("DTIW called. \n");
			}
			float Inches = WheelRadius * rad(Degrees);
			return Inches;
		}

		float ITDW(float Inches) {
			if (commandCalls) {
				printf("ITDW called. \n");
			}
			float Degrees = degrees(WheelRadius / Inches);
			return Degrees;
		}

		float TTIW(int Ticks) {
			if (commandCalls) {
				printf("TTIW called. \n");
			}
			float Inches = Ticks / 206.49999936;
			return Inches;
		}

		int ITTW(float Inches) {
			if (commandCalls) {
				printf("ITTW called. \n");
			}
			int Ticks = Inches * 206.49999936;
			return Ticks;
		}

		int DTTA(float Degrees) {
			if (commandCalls) {
				printf("DTTA called. \n");
			}
			int Tics = (0.09 / Degrees) + 57.15;
			return Tics;
		}

		float TTDA(int Tics) {
			if (commandCalls) {
				printf("TTDA called. \n");
			}
			float Degrees = (0.09 * Tics) - 57.15;
			return Degrees;
		}

		int DTTC(float Degrees) {
			if (commandCalls) {
				printf("DTTC called. \n");
			}
			int Tics = (12.05 * Degrees) + 723.5;
			return Tics;
		}

		float TTDC(int Tics) {
			if (commandCalls) {
				printf("TTDC called. \n");
			}
			float Degrees = (0.082 * Tics) - 60;
			return Degrees;
		}

		float Accelerometer() { return (accel_x() + accel_y() + accel_z()) / 3; }
		void Wait(float Time) {
			if (commandCalls) {
				printf("Wait called. \n");
			}
			Stop();
			ao();
			disable_servos();
			msleep(Time * 1000);
			enable_servos();
		}

		void Stop() {
			if (commandCalls) {
				printf("Stop called. \n");
			}
			freeze(LeftMotor);
			freeze(RightMotor);
		}

		void CMR() {
			if (commandCalls) {
				printf("CMR called. \n");
			}
			cmpc(LeftMotor);
			cmpc(RightMotor);
		}

		void HandsOff() {
			if (commandCalls) {
				printf("HandsOff called. \n");
			}
			printf("and god said... /n");
			wait_for_light(StartLight);
			shut_down_in(119);
			printf("...let there be light /n");
		}

		void Startup() {
			if (commandCalls) {
				printf("Startup called. \n");
			}

			if (LMM > RMM) {
				WMM = 1 / LMM;
			}
			if (LMM < RMM) {
				WMM = 1 / RMM;
			}

			RMM = RMM * WMM;
			LMM = LMM * WMM;

			if (LMM > RMM) {
				timemult = (1 - RMM) + 1;
			}
			if (LMM < RMM) {
				timemult = (1 - LMM) + 1;
			}

			enable_servos();
			Stop();
			CMR();
			SetArm(90, 90);
			/*
						thread Vel = thread_create(Velocity);
						thread_start(Vel);

						thread Time = thread_create(Timer);
						thread_start(Time);
			*/
		}
		int Status(char hex[]) {

			if (commandCalls) {
				printf("Status called. \n");
			}

			int onoff[12] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
			int loopn = 0;

			while (loopn < 12) {

				if (hex[loopn / 4] == '0') {
					onoff[loopn] = 0;
					onoff[loopn + 1] = 0;
					onoff[loopn + 2] = 0;
					onoff[loopn + 3] = 0;
					loopn = loopn + 4;
				}
				else if (hex[loopn / 4] == '1') {
					onoff[loopn] = 0;
					onoff[loopn + 1] = 0;
					onoff[loopn + 2] = 0;
					onoff[loopn + 3] = 1;
					loopn = loopn + 4;
				}
				else if (hex[loopn / 4] == '2') {
					onoff[loopn] = 0;
					onoff[loopn + 1] = 0;
					onoff[loopn + 2] = 1;
					onoff[loopn + 3] = 0;
					loopn = loopn + 4;
				}
				else if (hex[loopn / 4] == '3') {
					onoff[loopn] = 0;
					onoff[loopn + 1] = 0;
					onoff[loopn + 2] = 1;
					onoff[loopn + 3] = 1;
					loopn = loopn + 4;
				}
				else if (hex[loopn / 4] == '4') {
					onoff[loopn] = 0;
					onoff[loopn + 1] = 1;
					onoff[loopn + 2] = 0;
					onoff[loopn + 3] = 0;
					loopn = loopn + 4;
				}
				else if (hex[loopn / 4] == '5') {
					onoff[loopn] = 0;
					onoff[loopn + 1] = 1;
					onoff[loopn + 2] = 0;
					onoff[loopn + 3] = 1;
					loopn = loopn + 4;
				}
				else if (hex[loopn / 4] == '6') {
					onoff[loopn] = 0;
					onoff[loopn + 1] = 1;
					onoff[loopn + 2] = 1;
					onoff[loopn + 3] = 0;
					loopn = loopn + 4;
				}
				else if (hex[loopn / 4] == '7') {
					onoff[loopn] = 0;
					onoff[loopn + 1] = 1;
					onoff[loopn + 2] = 1;
					onoff[loopn + 3] = 1;
					loopn = loopn + 4;
				}
				else if (hex[loopn / 4] == '8') {
					onoff[loopn] = 1;
					onoff[loopn + 1] = 0;
					onoff[loopn + 2] = 0;
					onoff[loopn + 3] = 0;
					loopn = loopn + 4;
				}
				else if (hex[loopn / 4] == '9') {
					onoff[loopn] = 1;
					onoff[loopn + 1] = 0;
					onoff[loopn + 2] = 0;
					onoff[loopn + 3] = 1;
					loopn = loopn + 4;
				}
				else if (hex[loopn / 4] == 'A') {
					onoff[loopn] = 1;
					onoff[loopn + 1] = 0;
					onoff[loopn + 2] = 1;
					onoff[loopn + 3] = 0;
					loopn = loopn + 4;
				}
				else if (hex[loopn / 4] == 'B') {
					onoff[loopn] = 1;
					onoff[loopn + 1] = 0;
					onoff[loopn + 2] = 1;
					onoff[loopn + 3] = 1;
					loopn = loopn + 4;
				}
				else if (hex[loopn / 4] == 'C') {
					onoff[loopn] = 1;
					onoff[loopn + 1] = 1;
					onoff[loopn + 2] = 0;
					onoff[loopn + 3] = 0;
					loopn = loopn + 4;
				}
				else if (hex[loopn / 4] == 'D') {
					onoff[loopn] = 1;
					onoff[loopn + 1] = 1;
					onoff[loopn + 2] = 0;
					onoff[loopn + 3] = 1;
					loopn = loopn + 4;
				}
				else if (hex[loopn / 4] == 'E') {
					onoff[loopn] = 1;
					onoff[loopn + 1] = 1;
					onoff[loopn + 2] = 1;
					onoff[loopn + 3] = 0;
					loopn = loopn + 4;
				}
				else if (hex[loopn / 4] == 'F') {
					onoff[loopn] = 1;
					onoff[loopn + 1] = 1;
					onoff[loopn + 2] = 1;
					onoff[loopn + 3] = 1;
					loopn = loopn + 4;
				}
			}
			printf("\n\n       ==========================\n");
			int loop = 0;
			for (loop = 0; loop < 12; loop++) {
				printf("%d", onoff[loop]);
			}
			loop = 0;
			printf(" || ");
			for (loop = 0; loop < 3; loop++) {
				printf("%c", hex[loop]);
			}
			printf("\n\n");
			if (hex[0] == '0' && hex[1] == '0' && hex[2] == '0') {
				return 0;
			}

			if (onoff[0] ) {
				printf("O: %f, X: %f, Y: %f, Athena: %i\n", CurrentO, CurrentX, CurrentY,
					AthenaOn);
			}

			if (onoff[1] ) {
				printf("Battery: %.0f%% \n", power_level() * 100);
			}

			if (onoff[2] ) {
				printf("GMPC Left: %i, Right: %i, Average: %i \n", gmpc(LeftMotor),
					gmpc(RightMotor), ((gmpc(LeftMotor) + gmpc(RightMotor)) / 2));
			}

			if (onoff[3] ) {
				printf("Accelerometer X: %i Y: %i Z: %i Average: %i \n", accel_x(),
					accel_y(), accel_z(), (accel_x() + accel_y() + accel_z()) / 3);
			}

			printf("\n");

			if (onoff[4] ) {
				printf("Gyroscope X: %i Y: %i Z: %i Average: %i \n", gyro_x(), gyro_y(),
					gyro_z(), (gyro_x() + gyro_y() + gyro_z()) / 3);
			}

			if (onoff[5] ) {
				printf("Compass %f \n", get_compass_angle());
			}

			if (onoff[6] ) {
				printf("Motor Multipliers LMM: %f, RMM: %f, WMM: %f, TMM: %f \n", LMM, RMM,
					WMM, timemult);
			}

			if (onoff[7] ) {
				printf("Servo Positions 0: %i 1: %i 2: %i 3: %i \n", get_servo_position(0),
					get_servo_position(1), get_servo_position(2), get_servo_position(3));
			}

			printf("\n");

			if (onoff[8] ) {
				printf("Servos Enabled 0:%i 1:%i 2:%i 3:%i \n", get_servo_enabled(0),
					get_servo_enabled(1), get_servo_enabled(2), get_servo_enabled(3));
			}

			if (onoff[9] ) {
				printf("Digitals 0:%i 1:%i 2:%i 3:%i 4:%i 5:%i 6:%i 7:%i \n", digital(0),
					digital(1), digital(2), digital(3), digital(4), digital(5),
					digital(6), digital(7));
			}

			if (onoff[10] ) {
				printf("Analogs 0: %i 1: %i 2: %i 3: %i 4: %i 5: %i 6: %i 7: %i \n",
					analog(0), analog(1), analog(2), analog(3), analog(4), analog(5),
					analog(6), analog(7));
			}

			if (onoff[11] ) {
				printf("Command calls: On \n");
				commandCalls = 1;
			}

			else {
				printf("Command calls: Off \n");
				commandCalls = 0;
			}

			printf("       ==========================\n\n");
			return 1;
		}
		void Menu() {
			extra_buttons_show();

			while (! Confirm) {
				menubuffer++;
				msleep(1);
				if (c_button_clicked()) {
					Diagnostics = !Diagnostics;
					console_clear();
					msleep(1);

					if (power_level() < 0.33) {
						printf("Battery Critical: %.0f%% \n", power_level() * 100);
					}
					if (MOE(Accelerometer(), 0, 0.25)) {
						printf("Accelerometer Calibration Recomended \n\n");
					}
                    
					hex[0] = 'F';
					hex[1] = 'F';
					hex[2] = 'F';
					Status(hex);
					hex[0] = '0';
					hex[1] = '0';
					hex[2] = '0';
					Menu();
				}
				if (menubuffer % 100 == 0 && Diagnostics == false) {
					console_clear();
					if (power_level() < 0.33) {
						printf("Battery Critical: %.0f%% \n", power_level() * 100);
					}
					if (MOE(Accelerometer(), 0, 0.25)) {
						printf("Accelerometer Calibration Recomended \n\n");
					}

					printf("   AutoTravel    CONFIRM?    Diagnostic \n\n");
					printf("    Athena %d    HandsOff %d  Collisions %d\n", AthenaToggle,
						HandsOffToggle, CollisionToggle);
					if (a_button_clicked()) {
						AutoTravel = !AutoTravel;
					}
					if (b_button_clicked()) {
						Confirm = true;
						break;
					}
					if (x_button_clicked()) {
						AthenaToggle = !AthenaToggle;
					}
					if (y_button_clicked()) {
						HandsOffToggle = !HandsOffToggle;
					}

					if (z_button_clicked()) {
						CollisionToggle = !CollisionToggle;
					}
				}
			}

			if (CollisionToggle) {
				CollisionChecks = 1;
			}
			else {
				CollisionChecks = 0;
			}

			if (AthenaToggle) {
				AthenaOn = 1;
			}
			else {
				AthenaOn = 0;
			}
			if (HandsOffToggle) {
				HandsOff();
			}
			hex[0] = 'F';
			hex[1] = 'F';
			hex[2] = 'F';
		}
		void Velocity() {
			if (commandCalls) {
				printf("Velocity called. \n");
			}
			while (1) {
				float VLo = gmpc(LeftMotor);
				float VRo = gmpc(RightMotor);
				msleep(100);
				float VLt = gmpc(LeftMotor);
				float VRt = gmpc(RightMotor);

				Lv = (VLt - VLo) * 10;
				Rv = (VRt - VRo) * 10;
				Lp = Lv * 0.06;
				Rp = Rv * 0.06;
			}
		}
		void Timer() {
			if (commandCalls) {
				printf("Timer called. \n");
			}
			while (1) {
				centisec = centisec + 1;
				msleep(10);
				if (centisec % 100 == 0) {
					centisec = 0;
					sec = sec + 1;
					std::cout << sec;
					if (sec % 60 == 0) {
						sec = 0;
						min = min + 1;
					}
				}
			}
		}
		int MOE(float InputA, float InputB, float Range) {
			if (commandCalls) {
				printf("MOE called. \n");
			}
			float Min = InputB - Range;
			float Max = InputB + Range;
			return clamp(Min, InputA, Max);
		}

		int clamp(float min, float val, float max) {
			if (commandCalls) {
				printf("clamp called. \n");
			}
			if (min < val && val < max) {
				return 1;
			}
			else {
				return 0;
			}
		}

		/*
		float Accelerometer() {
				if (commandCalls) {
						printf("Accelerometer called. \n");
				}
				float AccelAvg = (accel_x() + accel_z()) / 2;
				return AccelAvg;
		}

		void(*CollisionCheck()) {
				if (commandCalls) {
						printf("CollisionCheck called. \n");
				}
				float Acceleration = 0;
				float Movement = 0;
				Collision = 0;
				if (MOE(Accelerometer(), 0, 0.1) ) {
						Acceleration = 0;
				} else {
						Acceleration = 1;
				}

				if (MOE(DeltaL, 0, 10) ) {
						Movement = 0;
				} else {
						Movement = 1;
				}

				if (Acceleration  && Movement ) {
						Collision = 1;
				} else {
						Collision = 0;
				}
				return 0;
		}

		void CollisionReset() {
				if (commandCalls) {
						printf("CollisionReset called. \n");
				}
				// face bottom
				// drive
				// back up
				// face left
				// drive
				// back up
		}

		void CollisionRecovery(float x, float y, float o) {
				if (commandCalls) {
						printf("CollisionRecovery called. \n");
				}
				// if collided
				// run reset
				// adjust values for offset
				// trig n follow values
				// turn to orrientation
		}
		*/

		void AthenaDecision(float DeltaL, float DeltaR) {
			if (commandCalls) {
				printf("AthenaDecision called. \n");
			}

			if (MOE(abs(DeltaL), abs(DeltaR), athenaMargin) &&
				DeltaL != DeltaR) {
				AOPivot(DeltaL, DeltaR);
			}
			else if (MOE(DeltaL, DeltaR, athenaMargin)) {
				APCount(DeltaL, DeltaR);
			}
			else {
				APOTrig(DeltaL, DeltaR);
			}
		}

		void AOPivot(float DeltaL, float DeltaR) {
			if (commandCalls) {
				printf("AOPivot called. \n");
			}

			float Wa = (abs(DeltaL) + abs(DeltaR)) / 2;
			float Ooffset = Wa / TurnRate;

			AOCalc(Ooffset);
		}

		void APCount(float DeltaL, float DeltaR) {
			if (commandCalls) {
				printf("APCount called. \n");
			}
			float Dist = (DeltaL + DeltaR) / 2;
			float Ang = rad(CurrentO);
			float Yoffset = Dist * sin(Ang);
			float Xoffset = Dist * cos(Ang);
			APCalc(Xoffset, Yoffset);
		}

		void APOTrig(float DeltaL, float DeltaR) {
			if (commandCalls) {
				printf("APOTrig called. \n");
			}
			float T = (DeltaL + DeltaR) / (DeltaL - DeltaR);

			float A = (DeltaL + DeltaR) / 2;
			float Ao = A / abs(T);

			float Gx = abs(T);
			float Gy = 0;

			float x1 = (Gx * cos(Ao)) - (Gy * sin(Ao));
			float y1 = (Gy * cos(Ao)) + (Gx * sin(Ao));

			float G2x = (x1 - Gx) + CurrentX;
			float G2y = (y1 - Gy) + CurrentY;

			float D2x = G2x - CurrentX;
			float D2y = G2y - CurrentY;

			float x2 = (D2x * cos(CurrentO)) - (D2y * sin(CurrentO));
			float y2 = (D2y * cos(CurrentO)) + (D2x * sin(CurrentO));

			APCalc(x2, y2);
			AOCalc(Ao);
		}

		void AOCalc(float Ooffset) {
			if (commandCalls) {
				printf("AOCalc called. \n");
			}
			CurrentO = Ooffset + CurrentO;
		}

		void APCalc(float Xoffset, float Yoffset) {
			if (commandCalls) {
				printf("APCalc called. \n");
			}
			CurrentY = Yoffset + CurrentY;
			CurrentX = Xoffset + CurrentX;
		}

		void TurnTo(int DeltaO, float Time) {
			if (commandCalls) {
				printf("TurnTo called. \n");
			}

			float GoalO = CurrentO + rad(DeltaO);
			printf("goalo = %f", GoalO);
			float WheelAngle = degrees(GoalO * (TurnRate / 2));
			printf("wheel angle = %f", WheelAngle);
			TankRotation(WheelAngle, -WheelAngle, Time);
		}

		void GoTo(float GoalX, float GoalY, float Time) {
			if (commandCalls) {
				printf("GoTo called. \n");
			}
			float DistX = GoalX - CurrentX;
			float DistY = GoalY - CurrentY;
			float DistC = sqrt(pow(DistX, 2) + pow(DistY, 2));
			float arc = degrees(atan(DistY / DistX));
			printf("Arc = %f, deltax = %f, deltay = %f, distance = %f. \n", arc, DistX,
				DistY, DistC);

			TurnTo(arc, Time / 4);

			Stop();
			Wait(0.01);

			TankDistance(DistC, DistC, ((Time / 4) * 3));
		}

		void GoAndFace(float GoalX, float GoalY, int GoalO, float Time) {
			if (commandCalls) {
				printf("GoAndFace called. \n");
			}
			GoTo(GoalX, GoalY, (Time / 5) * 4);
			TurnTo(GoalO, Time / 5);
		}

		void FollowCurve(float Radius, float Distance, float Time) {
			if (commandCalls) {
				printf("FollowCurve called. \n");
			}
			float SlowRad = Radius - AxelRadius;
			float FastRad = Radius + AxelRadius;
			float SlowSpeed = SlowRad * tan(0.785398);
			float FastSpeed = FastRad * tan(0.785398);
			FastSpeed = (FastSpeed / SlowSpeed) * Distance;
			SlowSpeed = (SlowSpeed / SlowSpeed) * Distance;
			if (Radius > 0) {
				TankDistance(FastSpeed, SlowSpeed, Time);
			}
			if (Radius < 0) {
				TankDistance(SlowSpeed, FastSpeed, Time);
			}
		}
	} // namespace bknd
}
