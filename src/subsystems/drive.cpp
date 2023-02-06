#include "main.h"
#include "pros/adi.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include <cmath>
#include <cstdio>

pros::IMU gyro(1);

int forwards;
int turning;
int left_side;
int right_side;
double left_side_volts;
double right_side_volts;
double encoderTicks = 200.0;
double gearTrain = 36.0/60.0;
double rotationTicks = encoderTicks/gearTrain;
double wheelDiameter = 10.2362;
double leftDistance = 0;
double rightDistance = 0;


void setDrive(int left, int right){
    leftFront = left;
    leftMid = left;
    leftBack = left;
    rightFront = right;
    rightMid = right;
    rightBack = right;
}

void resetDriveEncoders(){
    leftFront.tare_position();
    leftMid.tare_position();
    leftBack.tare_position();
    rightFront.tare_position();
    rightMid.tare_position();
    rightBack.tare_position();
}

//Driver control functions
void setDriveMotors(){
    pros::lcd::clear_line(4);
    pros::lcd::clear_line(5);
    
    forwards = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    turning = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    left_side = forwards + turning;
    right_side = forwards - turning;

    left_side_volts = left_side;
    right_side_volts = right_side;

    setDrive(left_side_volts, right_side_volts);
}

double avgDriveEncoder(){
    return (fabs(leftFront.get_position()) + 
           fabs(leftMid.get_position()) + 
           fabs(leftBack.get_position()) + 
           fabs(rightFront.get_position()) + 
           fabs(rightMid.get_position()) + 
           fabs(rightBack.get_position()))/6;
}

void distanceTraveled(){
    double leftEncoder = (fabs(leftFront.get_position()) + 
           fabs(leftMid.get_position()) + 
           fabs(leftBack.get_position()))/3;
    leftDistance = (leftEncoder/rotationTicks)*wheelDiameter;
    double rightEncoder = (fabs(rightFront.get_position()) + 
           fabs(rightMid.get_position()) + 
           fabs(rightBack.get_position()))/3;
    rightDistance = (rightEncoder/rotationTicks)*wheelDiameter;
}

//Autonomous functions
void translate(int units, int voltage){
    int direction = abs(units)/units;
    //reset motor encoders and gyro
    resetDriveEncoders();
    gyro.reset();

    //drive forward until units reached
    while(avgDriveEncoder()< abs(units)){
        setDrive(voltage * direction, voltage * direction);
        pros::delay(10);
    }

    //brake
    setDrive(-10*direction, -10*direction);
    pros::delay(50);

    //set drive back to neutral
    setDrive(0, 0);
}

void rotate(int degrees, int voltage){
    int direction = abs(degrees)/degrees;
    //reset inertial sensor
    gyro.reset();

    //rotate until desired degree
    setDrive(-voltage*direction, voltage*direction);
    while(fabs(gyro.get_heading()) < abs(degrees)){
        pros::delay(10);
    }
    //brake
    /*
    pros::delay(100);
    if(fabs(gyro.get_heading()) > abs(degrees)){
        setDrive(0.5*voltage*direction, 0.5*-voltage*direction);
        while(fabs(gyro.get_heading()) > abs(degrees)){
            pros::delay(10);
        }
    }
    else if(fabs(gyro.get_heading()) < abs(degrees)){
        setDrive(0.5*-voltage*direction, 0.5*voltage*direction);
        while(fabs(gyro.get_heading()) < abs(degrees)){
            pros::delay(10);
        }
    }*/

    setDrive(0, 0);
}