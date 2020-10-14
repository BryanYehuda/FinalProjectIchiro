#include <webots/keyboard.h>
#include <webots/led.h>
#include <webots/motor.h>
#include <webots/robot.h>

#include <stdio.h>
#include <stdlib.h>

// Macros to determine min or max between 2 inputs.
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int main(int argc, char **argv) {
  wb_robot_init();

  const int timestep = (int)wb_robot_get_basic_time_step();
  // printf ("Time Step= %d\n", timestep);
  wb_keyboard_enable(timestep);

  printf("- Up/Down arrow: move first pivot.\n");
  printf("Control the grabber base with the computer keyboard:\n");
  printf("- Ctrl + Left/Right arrow: grab or release fingers.\n");

  // Get the motors.
  WbDeviceTag pivot = wb_robot_get_device("pivot");
  WbDeviceTag finger_a = wb_robot_get_device("grabber finger A");
  WbDeviceTag finger_b = wb_robot_get_device("grabber finger B");
  WbDeviceTag finger_c = wb_robot_get_device("grabber finger C");

  // Set LED colors.
  // wb_led_set(wb_robot_get_device("pivot led"), 0x00FF00);
  // wb_led_set(wb_robot_get_device("grabber led"), 0x00FFFF);

  // Motor position variables.
  double p = -1.57;
  double g = 0.1;

  // Loop until the simulator stops the controller.
  while (wb_robot_step(timestep) != -1) {
    // Update the motor positions depending on the keyboard input.
    int key = 0;
    do {
      key = wb_keyboard_get_key();
      if (key == WB_KEYBOARD_DOWN)
        p = MAX(wb_motor_get_min_position(pivot), p + 0.01);
      else if (key == WB_KEYBOARD_UP)
        p = MIN(wb_motor_get_max_position(pivot), p - 0.01);
      else if (key == WB_KEYBOARD_CONTROL + WB_KEYBOARD_LEFT)
        g = MAX(0.1, g - 0.01);
      else if (key == WB_KEYBOARD_CONTROL + WB_KEYBOARD_RIGHT)
        g = MIN(wb_motor_get_max_position(finger_a), g + 0.01);
    } while (key > 0);

    // Actually set the motor positions.
    wb_motor_set_position(pivot, p);
    wb_motor_set_position(finger_a, g);
    wb_motor_set_position(finger_b, g);
    wb_motor_set_position(finger_c, g);
  };

  wb_robot_cleanup();

  return EXIT_SUCCESS;
}