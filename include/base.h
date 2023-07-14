#ifndef BASE_H
#define BASE_H

#include "main.h"

class Base {
    pros::Motor_Group* rightMotors;
    pros::Motor_Group* leftMotors;
    
    public:
        //base object
        Base(pros::Motor_Group* leftMotors, pros::Motor_Group* rightMotors) {
            this->leftMotors = leftMotors;
            this->rightMotors = rightMotors;
        }
        //speed is Y value of left Joystick
        //turning is X value of right Joystick
        void splitArcadeDrive(int speed, int turning) {
            //sets speeds for drivebase
            int rightControl = (speed + turning);
            int leftControl = (speed - turning);

            (*rightMotors).move(rightControl);
            (*leftMotors).move(leftControl);
        }
};

#endif