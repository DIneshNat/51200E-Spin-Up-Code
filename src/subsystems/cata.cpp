#include "main.h"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include <cmath>
#include <cstdio>

int cataVolt = 127;
int cataOn = 0;
int cataStop = 100;
int cataCurrentLoc = 0;
int cataDesired = 0;
int cataDesiredSet = 12470;
int cataSet = 1;
bool cataTrue = false;
bool cataCont = false;
bool cataAutons = false;

void cataAutonSet(bool onOff){
    cataAutons = onOff;
    cataDesired = cataDesiredSet;
}


int cataState(){
    int cataAutonStat;
    if(cataAutons){
        cataOn = 1;
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)==1){
        cataOn = 1;
    }
    else{
        cataOn = 0;
    }
    return cataOn;
}

bool cataLocation(int cataCount){
    cataCurrentLoc = cataMotor.get_position();
    if(cataState() == 1){
        cataCont = true;
    }
    if(cataCurrentLoc < cataDesired){
        if(cataCont == true){
            cataMotor = 127;
            cataTrue = true;
            return true;
        }
    } 
    else{
        pros::lcd::set_text(5, "cata okay");
        cataMotor = 0;
        cataAutons = false;
        cataTrue = false;
        cataCont = false;
        cataSet++;
        cataDesired = cataDesired +50;
        cataDesired = cataDesired + cataDesiredSet;
    }    
    return false;
}

bool cataMove(){
    if(cataState() == 1){
        cataMotor = cataVolt;
        return true;
    }
    return false;
}

bool cataOff(int cataCount){
    bool cataMove = cataLocation(cataCount);
    return cataMove;
}

bool cataButt(){
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) == 1){
        pros::lcd::set_text(4, "L2 Pressed");
        return true;
    }
    return false;
}

void cataOns(){
    bool cataStates = cataButt();
    if(cataStates){
         pros::lcd::set_text(6, "bad");
        cataMotor = 127;
    }
    else if(!cataTrue){
        cataMotor = 0;
    }
}