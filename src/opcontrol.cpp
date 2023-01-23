#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
pros::ADIDigitalOut expansionMec('A', false);

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
int cataCount = 0;
void opcontrol() {
    while(true){
        //drive code
        setDriveMotors();

        //intake code
        intakeOn();

        //cata code 
        //bool cataMove = cataOff(cataCount);
        //cataOns();
        cataRun();

        //expansion code
        expansionState();

        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)==1 && controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)==1){
            expansionMec.set_value(true);
        }

        pros::delay(10);
    }
}
