// Copyright 2025 Viktoria Buzlaeva

#ifndef GAMESTORE_DEVELOPER_DEVELOPER_H_
#define GAMESTORE_DEVELOPER_DEVELOPER_H_

#include <string>

#include "../Game/game.h"
#include "../TVector/tvector.h"

class Game;

class Developer {
    std::string _country;
    std::string _game_engine;
    int _rating;
    TVector<Game*> _games;
};

#endif  // GAMESTORE_DEVELOPER_DEVELOPER_H_
