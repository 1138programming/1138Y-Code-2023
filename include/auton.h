#ifndef AUTON_H
#define AUTON_H

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
                this->base->driveForwards(100);
                pros::delay(10);
            }
            this->base->driveForwards(0);
        }
};


#endif