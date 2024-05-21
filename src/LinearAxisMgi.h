#pragma once

#include <Arduino.h>
#include <AccelStepper.h>

//LinearAxisMgi(AccelStepper &motor, int home_sensor_pin, int lead_screw_pitch, int steps_per_rev, int axis_length);
//void Home();
float StepsToMm(long steps, int pitch, int steps_per_rev);
long MmToSteps(float dist_mm, int pitch, int steps_per_rev);
void HomeAxis(AccelStepper &motor, int home_sensor_pin=2, int speed_percent=100, bool motor_dir_inv = true, long move_dist_steps=0);
