#include "LinearAxisMgi.h"

float StepsToMm(long steps, int pitch, int steps_per_rev)
{
  float dist_mm = float(steps) * (float(pitch) / float(steps_per_rev));
  return dist_mm;
}

long MmToSteps(float dist_mm, int pitch, int steps_per_rev)
{
  int steps = round(dist_mm * (float (steps_per_rev) / float(pitch)));
  return steps;
}

void HomeAxis(AccelStepper &motor, int home_sensor_pin, int speed_percent, bool motor_dir_inv, long move_dist_steps)
{
    long curr_motor_max_speed = motor.maxSpeed();
    long curr_motor_accel = motor.acceleration();

    // if the home speed percentage is not 100, set the home speed and acceleration
    if (speed_percent != 100)
    {
        motor.setMaxSpeed(curr_motor_max_speed * (speed_percent / 100));
        motor.setAcceleration(curr_motor_accel * (speed_percent / 100));
    }

    // set the direction for the motor to move
    // this is used in the move command
    int motor_dir = 0;
    if (motor_dir_inv)
    {
        motor_dir = -1;
    }
    else
    {
        motor_dir = 1;
    }

    //read the home sensor
    bool home_sensor_state = digitalRead(home_sensor_pin);
    
    //set the move distance and run the motor until it reaches the home switch
    motor.move(move_dist_steps * motor_dir);
    while (!home_sensor_state)
    {
        motor.run();
        home_sensor_state = digitalRead(home_sensor_pin);
    }

    motor.setCurrentPosition(0);
    motor.move(0);

    //set the speed and acceleration back to their original values
    motor.setMaxSpeed(curr_motor_max_speed);
    motor.setAcceleration(curr_motor_accel);
}