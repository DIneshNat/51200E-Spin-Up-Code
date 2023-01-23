#include "main.h"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include <cmath>
#include <cstdio>

int intakeState(){
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) == 1){
        pros::lcd::set_text(5, "R1 Pressed");
        return 1;
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)== 1){
        return 2;
    }
    return 0;
}

void intakeOn(){
    int intakeStates = intakeState();
    if(intakeStates == 1){
        intakeMotor = 127;
    }
    else if(intakeStates == 2){
        intakeMotor = -127;
    }else{
        intakeMotor = 0;
    }
}

void resetIntakeEncoder(){
    intakeMotor.tare_position();
}
//Autonomous

void moveRoller(int units, int voltage){
    int direction = abs(units)/units;
    //reset intake encoder
    resetIntakeEncoder();

    //drive forward until units reached
    while(abs(intakeMotor.get_position())< abs(units)){
        intakeMotor = 127*direction;
        pros::delay(10);
    }
    //set drive back to neutral
    intakeMotor = 0;
}