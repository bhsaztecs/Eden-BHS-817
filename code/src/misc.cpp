#include "../include/declarations.h"
namespace BKND {
namespace misc {
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
  int onvalue, offvalue;
  std::cout << "Running";
  while (!any_button()) {
    onvalue = analog(p_port);
    std::cout << "ON: " << onvalue << std::endl;
    console_clear();
    msleep(25);
    if (any_button()) {
      break;
    }
    msleep(25);
  }
  msleep(500);
  while (!any_button()) {
    offvalue = analog(p_port);
    std::cout << "OFF: " << offvalue << std::endl;
    console_clear();
    msleep(25);
    if (any_button()) {
      break;
    }
    msleep(25);
  }
  msleep(500);
  int minimumtorun = (offvalue - onvalue) * 0.1 + onvalue;
  std::cout << "thresh: " << minimumtorun << std::endl;

  for (int i = 0; analog(p_port) > minimumtorun; i++) {
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
void Timer() {
  while (1) {
    msleep(1);
    BKND::G_CurrentMS++;
  }
}
} // namespace misc
} // namespace BKND
