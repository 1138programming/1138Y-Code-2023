#ifndef Auton_H
#define Auton_H

#include "main.h"
#include "base.h"

class Auton {
    Base* base;

    public:
        Auton(Base* base) {
            this->base = base;
        }

        void driveForwardsAuton(double timeSecs){
            double initialTime = pros::millis()/1000;

            while(pros::millis()/1000 - initialTime < timeSecs) {
                //100 is the speed of the motors during auton
                this->base->driveForwards(80);
                pros::delay(10);
            }
            this->base->driveForwards(0);
        }
        void driveBackwardsAuton(double timeSecs){
            double initialTime = pros::millis()/1000;

            while(pros::millis()/1000 - initialTime < timeSecs) {
                //100 is the speed of the motors during auton
                this->base->driveBackwards(50);
                pros::delay(10);
            }
            this->base->driveForwards(0);
        }
};


#endif