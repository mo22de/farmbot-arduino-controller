
/*
 * F13Handler.cpp
 *
 *  Created on: 2014/07/21
 *      Author: MattLech
 */

#include "F13Handler.h"


static F13Handler* instance;

F13Handler * F13Handler::getInstance() {
        if (!instance) {
                instance = new F13Handler();
        };
        return instance;
}
;

F13Handler::F13Handler() {
}

int F13Handler::execute(Command* command) {

Serial.print("home\n");

        if (LOGGING) {
                Serial.print("R99 HOME Z\n");
        }

        StepperControl::getInstance()->moveAbsoluteConstant(0,0,0, 0,0,0, false, false, true);
        if (LOGGING) {
                CurrentState::getInstance()->print();
        }
        return 0;
}

