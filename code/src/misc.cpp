#include "../include/declarations.h"
namespace BKND {
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
void Show(bool p_vis) {
  if (p_vis) {
    KIPR::extra_buttons_show();
    return;
  }
  KIPR::extra_buttons_hide();
}
bool Visible() { return KIPR::get_extra_buttons_visible(); }
} // namespace buttons
void waitforlight(int p_port) {
  int on, off;
  std::cout << "Running";
  while (!KIPR::any_button()) {
    on = KIPR::analog(p_port);
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
    off = KIPR::analog(p_port);
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

  for (int i = 0; KIPR::analog(p_port) > thresh; i++) {
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
void Timer() {
  while (1) {
    KIPR::msleep(1);
    BKND::CurrentMS++;
  }
}
} // namespace misc
} // namespace BKND
