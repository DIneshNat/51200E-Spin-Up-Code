#include "main.h"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include <cmath>
#include <cstdio>

void expansionState(){
    bool yState = controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)==1;
    bool leftState = controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)==1;
    if(yState && leftState){
        pros::ADIDigitalOut piston ('A');
        piston.set_value(true);
        pros::lcd::set_text(6, "Expanded");
    }
}