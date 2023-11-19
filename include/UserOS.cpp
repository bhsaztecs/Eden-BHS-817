#include "Backend.h"
using string = std::string;
namespace UsOS {
	class coordinate2 {
	public:
		float x;
		float y;
		coordinate2(float X = 0, float Y = 0) {
			this->x = X;
			this->y = Y;
		}
		float magnitude() {
			return sqrt(pow(x, 2) + pow(y, 2));
		}
		float angle() {
			return atan(x / y);
		}
	};
	class coordinate3 {
	public:
		float x;
		float y;
		float z;
		coordinate3(float X = 0, float Y = 0, float Z = 0) {
			this->x = X;
			this->y = Y;
			this->z = Z;
		}
		float magnitude() {
			return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
		}
		float pitch() {
			return atan(y / z);
		}
		float yaw() {
			return atan(x / z);
		}
	};
	class worldspace {
	public:
		float o = 0;
		float radius = 0;
		coordinate2 Position;
		worldspace(float X = 0, float Y = 0, float R = 5, float O = 0) {
			this->o = O;
			coordinate2 Position(X, Y);
			this->radius = R;
		}
	};

	class distance {
	public:
		void Tank(float leftdistance, float rightdistance, float time) {
			bknd::TankDistance(leftdistance, rightdistance, time);
		}
		void Steer(float basedistance, float turnfactor, float time) {
			bknd::DriveDistance(basedistance, turnfactor, time);
		}
	};
	class rotation {
	public:
		void Tank(float leftdistance, float rightdistance, float time) {
			bknd::TankRotation(leftdistance, rightdistance, time);
		}
		void Steer(float basedistance, float turnfactor, float time) {
			bknd::DriveRotation(basedistance, turnfactor, time);
		}
	};
	class speed {
	public:
		void Tank(float leftspeed, float rightspeed, float time) {
			bknd::TankSpeed(leftspeed, rightspeed, time);
		}
		void Steer(float basespeed, float turnfactor, float time) {
			bknd::DriveSpeed(basespeed, turnfactor, time);
		}
	};
	class standard {
	public:
		void Brake() {
			bknd::Stop();
		}
		distance Distance;
		rotation Rotation;
		speed Speed;
	};
	class acceleration {
	public:
		void Tank(float leftgoalspeed, float rightgoalspeed, float accelerationfactor) {
			bknd::TankAccelerate(leftgoalspeed, rightgoalspeed, 1 / accelerationfactor);
		}
		void Drive(float basegoalspeed, float turnfactor, float accelerationfactor) {
			bknd::DriveAccelerate(basegoalspeed, turnfactor, 1 / accelerationfactor);
		}
	};
	class motorc {
	public:
		int Ticks(int port) {
			return gmpc(port);
		}
		int Power(int port) {
			return getpwm(port);
		}
		standard Standard;
		acceleration Accelerate;
	};
	class servoget {
	public:
		int Ticks(int port) {
			return get_servo_position(port);
		}
		float Angle(int port) {
			return bknd::TTDA(Ticks(port));
		}
		bool State(int port) {
			return get_servo_enabled(port);
		}
	};
	class servo {
	public:
		servoget Get;
		void Enable(int port, bool state) {
			set_servo_enabled(port, state);
		}
		void Set(float ArmPosition, float ClawPosition) {
			bknd::SetArm(ArmPosition, ClawPosition);
		}
		void Change(float ArmChange, float ClawChange) {
			bknd::ChangeArm(ArmChange, ClawChange);
		}
		void SlowSet(float ArmPosition, float Time) {
			bknd::SlowSetArm(ArmPosition, Time);
		}
	};
	class accel {
	public:
		coordinate3 Value;
		void Calibrate() {
			accel_calibrate();
		}
		float Magnitude() {
			update();
			return Value.magnitude();
		}
		float Pitch() {
			update();
			return Value.pitch();
		}
		float Yaw() {
			update();
			return Value.yaw();
		}
	private:
		void update() {
			Value.x = accel_x();
			Value.y = accel_y();
			Value.z = accel_z();
		}
	};
	class gyro {
	public:
		coordinate3 Value;
		void Calibrate() {
			gyro_calibrate();
		}
		float Magnitude() {
			update();
			return Value.magnitude();
		}
		float Pitch() {
			update();
			return Value.pitch();
		}
		float Yaw() {
			update();
			return Value.yaw();
		}
	private:
		void update() {
			Value.x = gyro_x();
			Value.y = gyro_y();
			Value.z = gyro_z();
		}
	};
	/*
	class mag {
	public:
		coordinate3 Value;
		void Calibrate() {
			magneto_calibrate();
		}
		float Magnitude() {
			update();
			return Value.magnitude();
		}
		float Pitch() {
			update();
			return Value.pitch();
		}
		float Yaw() {
			update();
			return Value.yaw();
		}
	private:
		void update() {
			Value.x = magneto_x();
			Value.y = magneto_y();
			Value.z = magneto_z();
		}
	};
	*/
	class bat {
	public:
		int Power() {
			return power_level() * 100;
		}
		bool Critical() {
			return Power() < 33;
		}
	};
	class in {
	public:
		accel Accelerometer;
		gyro Gyroscope;
		//mag Magnetometer;
		bat Battery;
	};
	class dgtl {
	public:
		bool Value(int port) {
			return digital(port);
		}
	};
	class nlg {
	public:
		float Value(int port) {
			return float(analog(port)) / 4095;
		}
		int Raw(int port) {
			return analog(port);
		}
	};
	class cam {
	public:

	};
	class ex {
	public:
		cam Camera;
		dgtl Digital;
		nlg Analog;
	};
	class sensor {
	public:
		in Internal;
		ex External;
	};
	class artemis {
	public:
		void GoTo(float x, float y, float time) {
			bknd::GoTo(x, y, time);
		}
		void TurnTo(float Orientation, float Time) {
			bknd::TurnTo(Orientation - bknd::CurrentO, Time);
		}
		void GoAndFace(float x, float y, float Orientation, float Time) {
			bknd::GoAndFace(x, y, Orientation, Time);
		}
		void FollowArc(float Radius, float ArcLength, float Time) {
			bknd::FollowCurve(Radius, ArcLength, Time);
		}
	};
	class hepheastus {
	public:

	};
	class hermes {
	public:

	};
	class pathfinding {
	public:
		artemis Artemis;
		hepheastus Hepheastus;
		hermes Hermes;
	};
	class debug {
	public:
		void Status(char one, char two, char three) {
			char hex[3] = { one,two,three };
			bknd::Status(hex);
		}
		void Menu() {
			bknd::Menu();
		}
	};
	class cons {
	public:
		void Log() {}

		template <typename In1, typename... InN>
		void Log(In1 Current, InN... Rest) {
			if (sizeof...(Rest) > 0) {
				std::cout << Current << ", ";
			}
			else {
				std::cout << Current << ".\n";
			}
			Log(Rest...);
		}
		void Clear() {
			console_clear();

		}
	};
	class graphics {
	public:

	};
	class down {
	public:
		bool a() {
			return a_button();
		}
		bool b() {
			return b_button();
		}
		bool c() {
			return c_button();
		}
		bool x() {
			return x_button();
		}
		bool y() {
			return y_button();
		}
		bool z() {
			return z_button();
		}
	};
	class up {
	public:
		bool a() {
			return not a_button();
		}
		bool b() {
			return not b_button();
		}
		bool c() {
			return not c_button();
		}
		bool x() {
			return not x_button();
		}
		bool y() {
			return not y_button();
		}
		bool z() {
			return not z_button();
		}
	};
	class pressed {
	public:
		bool a() {
			return a_button_clicked();
		}
		bool b() {
			return b_button_clicked();
		}
		bool c() {
			return c_button_clicked();
		}
		bool x() {
			return x_button_clicked();
		}
		bool y() {
			return y_button_clicked();
		}
		bool z() {
			return z_button_clicked();
		}
	};
	class buttons {
	public:
		void show(bool vis) {
			if (vis) {
				extra_buttons_show();
			}
			else {
				extra_buttons_hide();
			}
		}
		bool visible() {
			return get_extra_buttons_visible();
		}
		pressed Pressed;
		up Up;
		down Down;
	};
	class other {
	public:
		cons Console;
		graphics Graphics;
		buttons Buttons;
		debug Debug;
		void HandsOff() {
			bknd::HandsOff();
		}
		void StartUp() {
			bknd::Startup();
		}
		void Wait(float Seconds) {
			bknd::Wait(Seconds);
		}

	};
	class newthread {
	public:
		thread Thread;
		newthread(void(*func)()) {
			this->Thread = thread_create(func);
		}
		void run() {
			thread_start(this->Thread);
		}
		void kill() {
			thread_wait(this->Thread);
			thread_destroy(this->Thread);
		}
	};
	worldspace Location;
	other Misc;
	pathfinding Pathfind;
	sensor Sensor;
	servo Servo;
	motorc Motor;
}
