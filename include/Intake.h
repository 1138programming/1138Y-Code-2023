#ifndef Intake_H
#define Intake_H

#include "main.h"

class Intake {
    pros::Motor_Group* intakeMotors;
    pros::ADIDigitalIn* limitSwitch;
    bool objectInIntake = false;

    public:
        //intake object
        Intake(pros::Motor_Group* intakeMotors,pros::ADIDigitalIn* limitSwitch) {
            this->intakeMotors = intakeMotors;
            this->limitSwitch = limitSwitch;
        }

        //spins intake based on prefered speed and direction
        void spinIntakeInwards(int speed) {
            int intakeSpeed = (speed);
            (*intakeMotors).move(intakeSpeed);
        }
        void spinIntakeOutwards(int speed) {
            int intakeSpeed = (-speed);
            (*intakeMotors).move(intakeSpeed);
        }
        void spinUntilPickup(int speed) {
            while(!objectInIntake){
                spinIntakeInwards(speed);
                if ((*limitSwitch).get_value()) {
                    stopIntake();
                    objectInIntake = true;
                }
            }

        }
        void outtake(int speed) {
            while(objectInIntake){
                spinIntakeOutwards(speed);
                if(!(*limitSwitch).get_value()){
                    pros::delay(200);//needs to be fine tuned to find right time in ms
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