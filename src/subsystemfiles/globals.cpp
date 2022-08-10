#include "main.h"

//CONTROLLER
extern pros::Controller controller(pros::E_CONTROLLER_MASTER);

//MOTORS
pros::Motor Motor1(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
