#pragma once
#include "basic.h"
namespace misc {
namespace buttons {
namespace down {
bool A() { return KIPR::a_button(); }
bool B() { return KIPR::b_button(); }
bool C() { return KIPR::c_button(); }
bool X() { return KIPR::x_button(); }
bool Y() { return KIPR::y_button(); }
bool Z() { return KIPR::z_button(); }
} // namespace down
namespace up {
bool A() { return !KIPR::a_button(); }
bool B() { return !KIPR::b_button(); }
bool C() { return !KIPR::c_button(); }
bool X() { return !KIPR::x_button(); }
bool Y() { return !KIPR::y_button(); }
bool Z() { return !KIPR::z_button(); }
} // namespace up
namespace pressed {
bool A() { return KIPR::a_button_clicked(); }
bool B() { return KIPR::b_button_clicked(); }
bool C() { return KIPR::c_button_clicked(); }
bool X() { return KIPR::x_button_clicked(); }
bool Y() { return KIPR::y_button_clicked(); }
bool Z() { return KIPR::z_button_clicked(); }
} // namespace pressed
void Show(bool vis) {
  if (vis) {
    KIPR::extra_buttons_show();
    return;
  }
  KIPR::extra_buttons_hide();
}
bool Visible() { return KIPR::get_extra_buttons_visible(); }
} // namespace buttons
} // namespace misc
void waitforlight(int port) {
  int on, off;
  std::cout << "Running";
  while (!KIPR::any_button()) {
    on = KIPR::analog(port);
    std::cout << "ON: " << on << std::endl;
    KIPR::console_clear();
    KIPR::msleep(25);
    if (KIPR::any_button()) {
      break;
    }
    KIPR::msleep(25);
  }
  KIPR::msleep(500);
  while (!KIPR::any_button()) {
    off = KIPR::analog(port);
    std::cout << "OFF: " << off << std::endl;
    KIPR::console_clear();
    KIPR::msleep(25);
    if (KIPR::any_button()) {
      break;
    }
    KIPR::msleep(25);
  }
  KIPR::msleep(500);
  int thresh = (off - on) * 0.1 + on;
  std::cout << "thresh: " << thresh << std::endl;

  for (int i = 0; KIPR::analog(port) > thresh; i++) {
    std::cout << "Waiting";
    if (i % 4 == 0) {
      std::cout << std::endl;
    } else if (i % 4 == 1) {
      std::cout << "." << std::endl;
    } else if (i % 4 == 2) {
      std::cout << ".." << std::endl;
    } else if (i % 4 == 3) {
      std::cout << "..." << std::endl;
    }
    KIPR::msleep(500);
    KIPR::console_clear();
  }
}
namespace misc {
void DefStatus(int in) {
  DLOG std::cout << "Todo" << std::endl;
  return;
}
void Timer() {
  DLOG while (1) {
    KIPR::msleep(1);
    CurrentMS++;
  }
}
void HandsOff() {
  DLOG waitforlight(sensors::StartLight);
  KIPR::shut_down_in(119);
}
void Start(bool tournament, bool debug = false) {
  Debugging = debug;
  newThread Vel(motors::Velocity);
  Vel.Run();

  float WMM = 1;
  if (motors::LMM > motors::RMM) {
    WMM = 1 / motors::LMM;
  } else {
    WMM = 1 / motors::RMM;
  }

  motors::RMM = motors::RMM * WMM;
  motors::LMM = motors::LMM * WMM;
  motors::TimeMultiplier = WMM;

  motors::Brake();
  motors::ClearMotorRotations();
  KIPR::enable_servos();

  if (tournament) {
    Wait(1);
    Debugging = false;
    HandsOff();
  }
  newThread Time(Timer);
  Time.Run();
}
} // namespace misc
void newThread::Run() { thread_start(this->Thread); }
void newThread::Kill() {
  thread_wait(this->Thread);
  thread_destroy(this->Thread);
}
