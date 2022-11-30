#include "okapi/api.hpp"

void setDrive(int left, int right);

void resetDriveEncoders();

double avgDriveEncoder();

//Driver control functions
void setDriveMotors();

void distanceTraveled();

//Autonomous functions
void translate(int units, int voltage);

void rotate(int degrees, int voltage);