#include "main.h"
#include "okapi/api/util/mathUtil.hpp"
#include "pros/rtos.hpp"
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
pros::ADIDigitalOut pistonBoosted('H', 2);
int voltageNum = 30;
void redRoller(){
    pros::lcd::set_text(4, "Red Roller Auton Running...");   
} 
void redSide(){
    pros::lcd::set_text(4, "Red Side Auton Running...");  
}
void blueRoller(){
    pros::lcd::set_text(4, "Blue Roller Auton Running..."); 
}
void blueSide(){
    pros::lcd::set_text(4, "Red Side Auton Running...");  
}
void skills1(){
    pros::lcd::set_text(4, "Skills 1 Auton Running...");
}
void soloAWP(){
    pros::lcd::set_text(4, "Solo AWP Running...");  
}

int autonVariable = 1;
 void autonSelector(int autonVal){
     autonVariable = autonVal;
     std::string autoString = std::to_string(autonVal);
     pros::lcd::set_text(5, autoString); 
 }


void autonomous() {
    if(autonVariable == 0){
        skills1();
        pistonBoosted.set_value(1);
    }
    else if(autonVariable == 1){
        soloAWP();
        pistonBoosted.set_value(1);
    }else if(autonVariable == 2){
        redSide();
        pistonBoosted.set_value(1);
    }else if(autonVariable == 3){
        redRoller();
    }else if(autonVariable == 4){
        blueSide();
        pistonBoosted.set_value(1);
    }else if(autonVariable == 5){
        blueRoller();
        pistonBoosted.set_value(1);
    }
}