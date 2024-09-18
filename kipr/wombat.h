class thread {
};

thread thread_create(void()) { thread temp; return temp; }
void thread_start(thread&) {}
void thread_wait(thread&) {}
void thread_destroy(thread&) {}
void msleep(double) {}
void shut_down_in(int) {}
int accel_x() { return 1; }
int accel_y() { return 1; }
int accel_z() { return 1; }
int gyro_x() { return 1; }
int gyro_y() { return 1; }
int gyro_z() { return 1; }
int magneto_x() { return 1; }
int magneto_y() { return 1; }
int magneto_z() { return 1; }
float get_compass_angle() { return 1; }
int get_servo_position(int) { return 1; }
int get_servo_enabled(int) { return 1; }
int digital(int) { return 1; }
int analog(int) { return 1; }
float power_level() { return 1; }
int a_button() { return 1; }
int b_button() { return 1; }
int c_button() { return 1; }
int x_button() { return 1; }
int y_button() { return 1; }
int z_button() { return 1; }
int a_button_clicked() { return 1; }
int b_button_clicked() { return 1; }
int c_button_clicked() { return 1; }
int x_button_clicked() { return 1; }
int y_button_clicked() { return 1; }
int z_button_clicked() { return 1; }
void extra_buttons_show() {}
void extra_buttons_hide() {}
int get_extra_buttons_visible() { return 1; }
void cmpc(int) {}
int gmpc(int) { return 1; }
void motor(int, int) {}
void freeze(int) {}
void accel_calibrate() {}
void gyro_calibrate() {}
void magneto_calibrate() {}
void set_servo_position(int, int) {}
void ao() {}
void disable_servos() {}
void enable_servos() {}
void wait_for_light(int) {}
