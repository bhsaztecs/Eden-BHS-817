#include "UserOS.h"
using namespace UsOS;
void Tournament();
void Initialize();

int main() {
	Initialize();
	//Tournament();
	Motor.Standard.Brake();
	Motor.Standard.Speed.Tank(10, 10, 10);
	Servo.Set(90, 0);
	Servo.Set(0, 0);
	Motor.Standard.Speed.Tank(10, 10, 10);
	Servo.Set(90, 90);
	Pathfind.Artemis.GoTo(10, 24, 10);
	return 0;
}

void Tournament() {
	Misc.StartUp();
	Misc.Wait(1);
	bknd::commandCalls = false;
	Misc.HandsOff();
	std::cout << "The way to get started is to quit talking and begin doing.";
}
void Initialize() {
	using namespace bknd;
	LeftMotor = 0;
	RightMotor = 3;
	LMM = 1;
	RMM = 1;

	ClawServo = 1;
	ArmServo = 3;

	LeftButton = 0;
	RightButton = 1;
	StartLight = 0;
	DownLight = 1;
	FrontLight = 2;
	CurrentO = 0;
	CurrentX = 0;
	CurrentY = 0;
	using namespace UsOS;
	worldspace Pipe1(5, 12, 5);
}
