#ifndef Intake_H
#define Intake_H

#include main.h

class Intake {
    pros::Motor_Group* intake;

    public:
        Intake(pros::Motor_Group* intake) {
            this->intake = intake;
        }

        void spinIntake(int speed) {
            
        }
}


#endif