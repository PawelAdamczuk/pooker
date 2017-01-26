//
// Created by Janusz Grzesik on 26.01.2017.
//

#ifndef POOKER_PRESENTER_H
#define POOKER_PRESENTER_H


#include "GameRound.h"

class Presenter {
public:

    void update(GameRound *g);
    void update(Player *p);
};


#endif //POOKER_PRESENTER_H
