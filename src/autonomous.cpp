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

int autonVariable = 3;
 void autonSelector(int autonVal){
     autonVariable = autonVal;
     std::string autoString = std::to_string(autonVal);
     pros::lcd::set_text(5, autoString); 
 }


void autonomous() {
    double turnkP = 0.3;
    double turnkI = 0.0;
    double turnkD = 0.0;

    std::shared_ptr<ChassisController> driveController = 
    ChassisControllerBuilder()
        .withMotors(
            {12, 16, 15},
            {20, 19, 18}
        )
        // Green gearset, 4 in wheel diam, 11.5 in wheel track
        .withDimensions(AbstractMotor::gearset::blue, {{3.25_in, 12.5_in}, imev5BlueTPR})
        .build();

    std::shared_ptr<ChassisController> driveBot =
    ChassisControllerBuilder()
        .withMotors(
            {12, 16, 15}, // Left motors
            {20, 19, 18}    // Right motors
        )
        .withDimensions({AbstractMotor::gearset::blue, (36.0 / 60.0)}, {{3.25_in, 12.5_in}, imev5BlueTPR})
        /*.withGains(
            {0.0, 0.0, 0.0}, // Distance controller gains
            {turnkP, turnkI, turnkD} // Turn controller gains
        )*/
        .withLogger(
            std::make_shared<Logger>(
                TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
                "/ser/sout", // Output to the PROS terminal
                Logger::LogLevel::debug // Most verbose log level
            )
        )
        .withMaxVoltage(30.0)
        .build()
        ;

    if(autonVariable == 0){
        skills1();
    }
    else if(autonVariable == 1){
        soloAWP();
    }else if(autonVariable == 2){
        redSide();
    }else if(autonVariable == 3){
        redRoller();
        driveBot->moveDistance(3_in);
        driveBot->waitUntilSettled();
        moveRoller(350, voltageNum);
        pros::delay(400);
        driveBot->moveDistance(-10_in); 
        driveBot->waitUntilSettled();
        driveBot->turnAngle(-250_deg);
        driveBot->waitUntilSettled();
        cataAutonSet(true);
        bool xy = false;
        while(true){
            pros::lcd::set_text(4, "cata good");
            xy = cataOff(0);
            if(xy){
                break;
            }
        }
        //shoot
        driveBot->turnAngle(-110_deg);
        driveBot->waitUntilSettled();
        //intakeOn
        driveBot->moveDistance(30_in);
        driveBot->waitUntilSettled();
        intakeMotor = 127;
        driveBot->moveDistance(30_in);
        driveBot->waitUntilSettled();
        intakeMotor = 0;


    }else if(autonVariable == 4){
        blueSide();
    }else if(autonVariable == 5){
        blueRoller();
    }
}
