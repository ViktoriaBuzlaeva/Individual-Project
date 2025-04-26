// Copyright 2025 Viktoria Buzlaeva

#ifndef GAMESTORE_DEVELOPER_DEVELOPER_H_
#define GAMESTORE_DEVELOPER_DEVELOPER_H_

#include "../Game/game.h"

class Game;

class Developer {
    char* _country;
    char* _game_engine;
    int _rating;
    Game** _games;
};

#endif  // GAMESTORE_DEVELOPER_DEVELOPER_H_
