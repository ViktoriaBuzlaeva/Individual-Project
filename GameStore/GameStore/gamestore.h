// Copyright 2025 Viktoria Buzlaeva

#ifndef GAMESTORE_GAMESTORE_GAMESTORE_H_
#define GAMESTORE_GAMESTORE_GAMESTORE_H_

#include "../Developer/developer.h"
#include "../Game/game.h"
#include "../User/user.h"

class GameStore {
    Game* _games;
    User* _users;
    Developer* _developers;
};

#endif  // GAMESTORE_GAMESTORE_GAMESTORE_H_
