#ifndef Pusher_H
#define Pusher_H

#include "main.h"

class Pusher {
    private:
        pros::Motor* leftPusher;
        pros::Motor* rightPusher;
        bool pusherOpen = false;
    public:
        //pusher object
        Pusher(pros::Motor* leftPusher, pros::Motor* rightPusher) {
            this->leftPusher = leftPusher;
            this->rightPusher = rightPusher;
        }

        void openPusher(){
            rightPusher->move_relative(700,200);
            leftPusher->move_relative(-700,200);
        }
        void closePusher(){
            rightPusher->move_relative(-700,200);
            leftPusher->move_relative(700,200);
        }
};

#endif