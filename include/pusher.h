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
            this->rightPusher->move_relative(700,200);
            this->leftPusher->move_relative(-700,200);
        }
        void closePusher(){
            this->rightPusher->move_relative(-700,200);
            this->leftPusher->move_relative(700,200);
        }
};

#endif