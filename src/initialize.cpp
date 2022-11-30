#include "main.h"
#include "pros/imu.hpp"
#include "pros/llemu.hpp"
#include "pros/motors.h"
#include <algorithm>
#include <iostream>
#include <list>

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
 int autonNumber = -1;
 void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "Skills Auton 1!");
		autonNumber = 0;
		autonSelector(autonNumber);
	} else {
		pros::lcd::set_text(2, "Solo AWP!");
		autonNumber = 1;
		autonSelector(autonNumber);
	}
}
 void on_left_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "Red Auton Side!");
		autonNumber = 2;
		autonSelector(autonNumber);
	} else {
		pros::lcd::set_text(2, "Red Auton Roller!");
		autonNumber = 3;
		autonSelector(autonNumber);
	}
}
 void on_right_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "Blue Auton Side!");
		autonNumber = 4;
		autonSelector(autonNumber);
	} else {
		pros::lcd::set_text(2, "Blue Auton Roller!");
		autonNumber = 5;
		autonSelector(autonNumber);
	}
}




/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() 
{
	pros::lcd::initialize();
	pros::lcd::set_background_color(224, 47, 16);
	pros::lcd::set_text(1, "654X Parallax");
	pros::lcd::register_btn1_cb(on_center_button);
	pros::lcd::register_btn0_cb(on_left_button);
	pros::lcd::register_btn2_cb(on_right_button);
	pros::lcd::set_text(3, "Josh is bad!");
	printf("Initialize!\n");

	leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	leftMid.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	rightMid.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

	pros::IMU gyro(1);
	pros::delay(2000);
}


/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

