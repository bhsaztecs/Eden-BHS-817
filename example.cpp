// #include "../../include/Basic.h"
#include "code/include/basic.h"
sensors Sensor(0);
pathFind Athena;
motors Tank(0, 3);
misc Misc;
servos Arm(0, 1);

void update() {
  while (true) { // indefinitely
    Wait(0.5);   // delay
    std::cout << TTDA(get_servo_position(ArmServo)) << std::endl;
  }
}

int main() {
  std::cout << "Hello, world!" << std::endl;
  Misc.Start(false);
  newThread UPDATE(update);
  UPDATE.Run();
  Wait(1);
  Tank.Accelerate(100, 100, 5);
  Tank.Accelerate(0, 0, 5);
  Wait(1);
  return 0;
}
