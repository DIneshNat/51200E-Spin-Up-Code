#include "main.h"
#include "pros/misc.h"
#include <cmath>

void setDrive(int left, int right){
    leftFront = left;
    leftMid = left;
    leftBack = left;
    rightFront = right;
    rightMid = right;
    rightBack = right;
}
//Driver control functions
void setDriveMotors(){
    int leftJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    if(abs(leftJoystick)<10){
        leftJoystick = 0;
    }
    if(abs(rightJoystick)<10){
        rightJoystick = 0;
    }
    setDrive(leftJoystick, rightJoystick);
}