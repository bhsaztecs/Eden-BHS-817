#pragma once
#include "Basic.h"

bool down::A() {
	return a_button();
}
bool down::B() {
	return b_button();
}
bool down::C() {
	return c_button();
}
bool down::X() {
	return x_button();
}
bool down::Y() {
	return y_button();
}
bool down::Z() {
	return z_button();
}

bool up::A() {
	return !a_button();
}
bool up::B() {
	return !b_button();
}
bool up::C() {
	return !c_button();
}
bool up::X() {
	return !x_button();
}
bool up::Y() {
	return !y_button();
}
bool up::Z() {
	return !z_button();
}

bool pressed::A() {
	return a_button_clicked();
}
bool pressed::B() {
	return b_button_clicked();
}
bool pressed::C() {
	return c_button_clicked();
}
bool pressed::X() {
	return x_button_clicked();
}
bool pressed::Y() {
	return y_button_clicked();
}
bool pressed::Z() {
	return z_button_clicked();
}

void buttons::Show(bool vis) {
	if ( vis ) {
		extra_buttons_show();
		return;
	}
	extra_buttons_hide();
}
bool buttons::Visible() {
	return get_extra_buttons_visible();
}

void misc::DefStatus(char hex[]) {
	DLOG

		int onoff[12] = { 1,1,1,1, 1,1,1,1, 1,1,1,1 };
	int loopn = 0;

	while ( loopn < 12 ) {
		if ( hex[loopn / 4] == '0' ) {
			onoff[loopn] = 0;
			onoff[loopn + 1] = 0;
			onoff[loopn + 2] = 0;
			onoff[loopn + 3] = 0;
			loopn = loopn + 4;
		}
		else if ( hex[loopn / 4] == '1' ) {
			onoff[loopn] = 0;
			onoff[loopn + 1] = 0;
			onoff[loopn + 2] = 0;
			onoff[loopn + 3] = 1;
			loopn = loopn + 4;
		}
		else if ( hex[loopn / 4] == '2' ) {
			onoff[loopn] = 0;
			onoff[loopn + 1] = 0;
			onoff[loopn + 2] = 1;
			onoff[loopn + 3] = 0;
			loopn = loopn + 4;
		}
		else if ( hex[loopn / 4] == '3' ) {
			onoff[loopn] = 0;
			onoff[loopn + 1] = 0;
			onoff[loopn + 2] = 1;
			onoff[loopn + 3] = 1;
			loopn = loopn + 4;
		}
		else if ( hex[loopn / 4] == '4' ) {
			onoff[loopn] = 0;
			onoff[loopn + 1] = 1;
			onoff[loopn + 2] = 0;
			onoff[loopn + 3] = 0;
			loopn = loopn + 4;
		}
		else if ( hex[loopn / 4] == '5' ) {
			onoff[loopn] = 0;
			onoff[loopn + 1] = 1;
			onoff[loopn + 2] = 0;
			onoff[loopn + 3] = 1;
			loopn = loopn + 4;
		}
		else if ( hex[loopn / 4] == '6' ) {
			onoff[loopn] = 0;
			onoff[loopn + 1] = 1;
			onoff[loopn + 2] = 1;
			onoff[loopn + 3] = 0;
			loopn = loopn + 4;
		}
		else if ( hex[loopn / 4] == '7' ) {
			onoff[loopn] = 0;
			onoff[loopn + 1] = 1;
			onoff[loopn + 2] = 1;
			onoff[loopn + 3] = 1;
			loopn = loopn + 4;
		}
		else if ( hex[loopn / 4] == '8' ) {
			onoff[loopn] = 1;
			onoff[loopn + 1] = 0;
			onoff[loopn + 2] = 0;
			onoff[loopn + 3] = 0;
			loopn = loopn + 4;
		}
		else if ( hex[loopn / 4] == '9' ) {
			onoff[loopn] = 1;
			onoff[loopn + 1] = 0;
			onoff[loopn + 2] = 0;
			onoff[loopn + 3] = 1;
			loopn = loopn + 4;
		}
		else if ( hex[loopn / 4] == 'A' ) {
			onoff[loopn] = 1;
			onoff[loopn + 1] = 0;
			onoff[loopn + 2] = 1;
			onoff[loopn + 3] = 0;
			loopn = loopn + 4;
		}
		else if ( hex[loopn / 4] == 'B' ) {
			onoff[loopn] = 1;
			onoff[loopn + 1] = 0;
			onoff[loopn + 2] = 1;
			onoff[loopn + 3] = 1;
			loopn = loopn + 4;
		}
		else if ( hex[loopn / 4] == 'C' ) {
			onoff[loopn] = 1;
			onoff[loopn + 1] = 1;
			onoff[loopn + 2] = 0;
			onoff[loopn + 3] = 0;
			loopn = loopn + 4;
		}
		else if ( hex[loopn / 4] == 'D' ) {
			onoff[loopn] = 1;
			onoff[loopn + 1] = 1;
			onoff[loopn + 2] = 0;
			onoff[loopn + 3] = 1;
			loopn = loopn + 4;
		}
		else if ( hex[loopn / 4] == 'E' ) {
			onoff[loopn] = 1;
			onoff[loopn + 1] = 1;
			onoff[loopn + 2] = 1;
			onoff[loopn + 3] = 0;
			loopn = loopn + 4;
		}
		else if ( hex[loopn / 4] == 'F' ) {
			onoff[loopn] = 1;
			onoff[loopn + 1] = 1;
			onoff[loopn + 2] = 1;
			onoff[loopn + 3] = 1;
			loopn = loopn + 4;
		}
	}
	printf("\n\n       ==========================\n");
	int loop = 0;
	for ( loop = 0; loop < 12; loop++ ) {
		printf("%d", onoff[loop]);
	}
	printf(" || ");
	for ( loop = 0; loop < 3; loop++ ) {
		printf("%c", hex[loop]);
	}
	printf("\n\n");
	if ( hex[0] == '0' && hex[1] == '0' && hex[2] == '0' ) {
		return;
	}

	if ( onoff[0] ) {
		printf("O: %f, X: %f, Y: %f\n", Position.O, Position.X, Position.Y);
	}

	if ( onoff[1] ) {
		printf("Battery: %.0f%% \n", power_level() * 100);
	}
	if ( onoff[2] ) {
		printf("GMPC Left: %i, Right: %i, Average: %i \n", gmpc(LeftMotor),
					 gmpc(RightMotor), ((gmpc(LeftMotor) + gmpc(RightMotor)) / 2));
	}
	if ( onoff[3] ) {
		printf("Accelerometer X: %i Y: %i Z: %i Average: %i \n", accel_x(),
					 accel_y(), accel_z(), (accel_x() + accel_y() + accel_z()) / 3);
	}

	printf("\n");

	if ( onoff[4] ) {
		printf("Gyroscope X: %i Y: %i Z: %i Average: %i \n", gyro_x(), gyro_y(),
					 gyro_z(), (gyro_x() + gyro_y() + gyro_z()) / 3);
	}

	if ( onoff[5] ) {
		printf("Compass %f \n", get_compass_angle());
	}
	if ( onoff[6] ) {
		printf("Motor Multipliers LMM: %f, RMM: %f, TMM: %f \n", LMM, RMM, TimeMultiplier);
	}

	if ( onoff[7] ) {
		printf("Servo Positions 0: %i 1: %i 2: %i 3: %i \n", get_servo_position(0),
					 get_servo_position(1), get_servo_position(2), get_servo_position(3));
	}

	printf("\n");

	if ( onoff[8] ) {
		printf("Servos Enabled 0:%i 1:%i 2:%i 3:%i \n", get_servo_enabled(0),
					 get_servo_enabled(1), get_servo_enabled(2), get_servo_enabled(3));
	}

	if ( onoff[9] ) {
		printf("Digitals 0:%i 1:%i 2:%i 3:%i 4:%i 5:%i 6:%i 7:%i \n", digital(0),
					 digital(1), digital(2), digital(3), digital(4), digital(5),
					 digital(6), digital(7));
	}

	if ( onoff[10] ) {
		printf("Analogs 0: %i 1: %i 2: %i 3: %i 4: %i 5: %i 6: %i 7: %i \n",
					 analog(0), analog(1), analog(2), analog(3), analog(4), analog(5),
					 analog(6), analog(7));
	}

	if ( onoff[11] ) {
		printf("Debugging: On \n");
		Debugging = 1;
	}

	else {
		printf("Debugging: Off \n");
		Debugging = 0;
	}

	printf("       ==========================\n\n");
	return;
}
void misc::Timer() {
	DLOG
		while ( 1 ) {
			msleep(1);
			CurrentMS++;
		}
}
void misc::HandsOff() {
	DLOG
		printf("and god said... /n");
	wait_for_light(StartLight);
	shut_down_in(119);
	printf("...let there be light /n");
}
void misc::Status(string hex) {
	char arr[3] = { hex[0], hex[1], hex[2] };
	DefStatus(arr);
}
void misc::Status(char one, char two, char three) {
	char arr[3] = { one,two,three };
	DefStatus(arr);
}
void misc::Start(bool tournament) {
	newThread Vel(motors::Velocity);
	Vel.Run();

	float WMM = 1;
	if ( LMM > RMM ) {
		WMM = 1 / LMM;
	}
	else {
		WMM = 1 / RMM;
	}

	RMM = RMM * WMM;
	LMM = LMM * WMM;
	TimeMultiplier = WMM;

	motors::Brake();
	motors::ClearMotorRotations();
	enable_servos();
	servos::Set(90, 90);

	if ( tournament ) {
		Wait(1);
		Debugging = false;
		HandsOff();
		std::cout << "The way to get started is to quit talking and begin doing." << std::endl;
	}
	newThread Time(Timer);
	Time.Run();
}

void newThread::Run() {
	thread_start(this->Thread);
}
void newThread::Kill() {
	thread_wait(this->Thread);
	thread_destroy(this->Thread);
}