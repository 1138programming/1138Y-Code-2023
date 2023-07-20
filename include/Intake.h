#ifndef Intake_H
#define Intake_H

#include "main.h"

class Intake {
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

        void holdToSpinIntake(int speed) {
            if (master.get_digital(DIGITAL_L2)) spinIntakeInwards(speed);
            if (master.get_digital(DIGITAL_L1)) spinIntakeOutwards(speed);
        }

        void toggleSpinIntake(int speed) {
            if (master.get_digital(DIGITAL_L2)) spinIntakeInwardsUntilStop(speed);
            if (master.get_digital(DIGITAL_L1)) spinIntakeOutwardsUntilStop(speed);
        }

        void smartSpinIntake(int speed) {
            // if (master.get_digital(DIGITAL_L2)) 
            // if (master.get_digital(DIGITAL_L1)) 
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
        void spinIntakeInwardsUntilStop(int speed) {
            int intakeSpeed = (speed);
            (*intakeMotors).move(intakeSpeed);
        }
        void spinIntakeOutwardsUntilStop(int speed) {
            int intakeSpeed = (-speed);
            (*intakeMotors).move(intakeSpeed);
        }
        //will spin until a game object is picked up
        void spinUntilPickup(int speed) {
            while(!objectInIntake){
                spinIntakeInwards(speed);
                if ((*limitSwitch).get_value()) {
                    stopIntake();
                    objectInIntake = true;
                }
            }

        }
        //will outtake game object and then stop automatically
        void smartOuttake(int speed) {
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