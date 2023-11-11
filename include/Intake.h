#ifndef Intake_H
#define Intake_H

#include "main.h"
#include "constants.h"

class Intake {
    private:
        pros::Motor_Group* intakeMotors;
        pros::ADIDigitalIn* limitSwitch;
        bool intakeStopped = false;
        bool objectInIntake = false;

    public:
        //intake object
        Intake(pros::Motor_Group* intakeMotors,pros::ADIDigitalIn* limitSwitch) {
            this->intakeMotors = intakeMotors;
            this->limitSwitch = limitSwitch;
        }

        //spins intake based on prefered speed and direction
        void spinIntakeInwards() {
            (*intakeMotors).move(KIntakeSpeed);
        }
        void spinIntakeOutwards() {
            (*intakeMotors).move(-KIntakeSpeed);
        }
        //will spin until a game object is picked up
        void spinUntilPickup() {
            while(!objectInIntake){
                spinIntakeInwards();
                if ((*limitSwitch).get_value()) {
                    stopIntake();
                    objectInIntake = true;
                }
            }

        }
        //will outtake game object and then stop automatically
        void smartOuttake() {
            while(objectInIntake){
                spinIntakeOutwards();
                if(!(*limitSwitch).get_value()){
                    pros::delay(200);//doesn't actually work, just delays entire bot code I think
                    stopIntake();
                    objectInIntake = false;
                }
            }
        }
        void stopIntake() {
            (*intakeMotors).move(0);
        }
};

#endif