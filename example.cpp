// #include "../../include/Basic.h"
#include "code/include/basic.h"
void update() {
  while (true) { // indefinitely
    Wait(0.5);   // delay
    std::cout << TTDA(KIPR::get_servo_position(servos::ArmServo)) << std::endl;
  }
}

int main() {
  std::cout << "Hello, world!" << std::endl;
  misc::Start(false);
  newThread UPDATE(update);
  UPDATE.Run();
  Wait(1);
  motors::Accelerate(100, 100, 5);
  motors::Accelerate(0, 0, 5);
  Wait(1);
  return 0;
}
