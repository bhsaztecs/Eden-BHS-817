//#include "../include/Basic.h"
#include "/home/kipr/Documents/KISS/Default User/Headers/include/Basic.h"
sensors Sensor(0);
pathFind Athena;
motors Tank(0,3);
misc Misc;
servos Arm(0,1);

void update() {
	while ( true ) { // indefinitely
		Wait(0.5); // delay
        std::cout << get_servo_position(ArmServo) << std::endl;
	}
}

int main() {
    //Misc.Start(false);
    //newThread UPDATE(update);
    //UPDATE.Run();
    enable_servos();
		set_servo_position(0, 2047);
    disable_servos();
    Wait(1);
   	//Tank.Accelerate(100,100,5);
    //Tank.Accelerate(0,0,5);
    enable_servos();
		set_servo_position(0, 1000);
    disable_servos();
    Wait(1);
	return 0;
}
