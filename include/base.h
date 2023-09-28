#ifndef Base_H
#define Base_H

#include "main.h"

class Base {
    private:
        pros::Motor_Group* rightMotors;
        pros::Motor_Group* leftMotors;
        bool swappedFront;
        int botSpeedLevel = 2;

    public:
        //base object
        Base(pros::Motor_Group* leftMotors, pros::Motor_Group* rightMotors) {
            this->leftMotors = leftMotors;
            this->rightMotors = rightMotors;
        }
        
        //converts analog stick imput to RPM
        int convertToRPM(int analog) {
            return (int)(analog*1.58);
        }
        
        //speed is Y value of left Joystick
        //turning is X value of right Joystick
        void splitArcadeDrive(int speed, int turning) {
            //sets speeds for drivebase
            int rightControl = (speed + turning);
            int leftControl = (speed - turning);

            // rightMotors relates to the physical right motors on the bot while
            // rightControl is for the motors in relation to the bot being swapped
            // and will change depending on which side is front (applies for left side too)
            if(!this->swappedFront){
                (*rightMotors).move_velocity(convertToRPM(-rightControl)*botSpeedLevel);
                (*leftMotors).move_velocity(convertToRPM(leftControl)*botSpeedLevel);
            } else {
                (*rightMotors).move_velocity(convertToRPM(leftControl)*botSpeedLevel);
                (*leftMotors).move_velocity(convertToRPM(-rightControl)*botSpeedLevel);
            }
        }

        //allows for front of bot to be swapped with back
        void swapBotFront() {
            this->swappedFront = !this->swappedFront;
        }

        //allows to increase the speed level of bot
        void increaseSpeed() {
            if(this->botSpeedLevel<3) this->botSpeedLevel++;
        }
        //allows to decrease the speed level of bot
        void decreaseSpeed() {
            if(this->botSpeedLevel>1) this->botSpeedLevel--;
        }
        void driveForwards(int speed) {
            this->rightMotors->move(speed);
            this->leftMotors->move(speed);
        }
};

#endif