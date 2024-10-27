#pragma once
#include "basic.h"
namespace misc {
using namespace BKND;
using namespace KIPR;
namespace buttons {
namespace down {
bool A() { return a_button(); }
bool B() { return b_button(); }
bool C() { return c_button(); }
bool X() { return x_button(); }
bool Y() { return y_button(); }
bool Z() { return z_button(); }
} // namespace down
namespace up {
bool A() { return !a_button(); }
bool B() { return !b_button(); }
bool C() { return !c_button(); }
bool X() { return !x_button(); }
bool Y() { return !y_button(); }
bool Z() { return !z_button(); }
} // namespace up
namespace pressed {
bool A() { return a_button_clicked(); }
bool B() { return b_button_clicked(); }
bool C() { return c_button_clicked(); }
bool X() { return x_button_clicked(); }
bool Y() { return y_button_clicked(); }
bool Z() { return z_button_clicked(); }
} // namespace pressed
void Show(bool p_vis) {
  if (p_vis) {
    extra_buttons_show();
    return;
  }
  extra_buttons_hide();
}
bool Visible() { return get_extra_buttons_visible(); }
} // namespace buttons
void waitforlight(int p_port) {
  int on, off;
  std::cout << "Running";
  while (!any_button()) {
    on = analog(p_port);
    std::cout << "ON: " << on << std::endl;
    console_clear();
    msleep(25);
    if (any_button()) {
      break;
    }
    msleep(25);
  }
  msleep(500);
  while (!any_button()) {
    off = analog(p_port);
    std::cout << "OFF: " << off << std::endl;
    console_clear();
    msleep(25);
    if (any_button()) {
      break;
    }
    msleep(25);
  }
  msleep(500);
  int thresh = (off - on) * 0.1 + on;
  std::cout << "thresh: " << thresh << std::endl;

  for (int i = 0; analog(p_port) > thresh; i++) {
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
    msleep(500);
    console_clear();
  }
}
void Status(int p_in) {
  DLOG std::cout << "Todo" << std::endl;
  return;
}
void Timer() {
  DLOG while (1) {
    msleep(1);
    CurrentMS++;
  }
}
} // namespace misc
void BKND::Thread::Run() { thread_start(this->m_Thethread); }
void BKND::Thread::Kill() {
  thread_wait(this->m_Thethread);
  thread_destroy(this->m_Thethread);
}
