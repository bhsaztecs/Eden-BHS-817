#include <iostream>
using namespace std;

class Robot {
	WorldSpace Position;
	float orientation;

	class Port {
		class Analog {
			int portone = 0;
			int porttwo = 1;
			int portthree = 2;
			int portfour = 3;
		};
		class Digital {
			int portone = 0;
			int porttwo = 1;
			int portthree = 2;
			int portfour = 3;
		};
		class Servo {
			int portone = 0;
			int porttwo = 1;
			int portthree = 2;
			int portfour = 3;
		};
		class Motor {
			int portone = 0;
			int porttwo = 1;
			int portthree = 2;
			int portfour = 3;

			float leftmotormultiplier;
			float rightmotormultiplier;
			float timemultiplier;
			float speedlossmultiplier;
		};
	};
	class Measurements {
		class Physical {
			class Wheel {
				float wheelradius;
				float axelradius;
				float turnrate;	
			};
			class Arm {
				float armlength;
				float armoffsetz;
				float armoffsetx;
			};
		};
		class Digital {
			float leftdelta;
			float rightdelta;

			float leftvelocity;
			float rightvelocity;
			float leftpercent;
			float rightpercent;

			int leftstart;
			int leftend;
			int rightstart;
			int rightend;
		};
	};
	class SubSystems {
		bool athena;
		float athenamargin;
		bool collision;
		char hex[] = {'F', 'F', 'F'};
		int commandCalls = 0;
	};
};

class Obstacle {
	Worldspace Object;
	float radius;
};

class WorldSpace {
	float x;
	float y;
	bool collider;
};

class Time {
	int centisec;
	int sec;
	int min;
};

class Menu {
	bool autotravel = false;
	bool confirm = false;
	bool diagnostics = false;
	bool athena = true;
	bool handsoff = false;
	bool collision = true;
	int menubuffer = 0;
};
