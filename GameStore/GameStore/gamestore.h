// Copyright 2025 Viktoria Buzlaeva

#ifndef GAMESTORE_GAMESTORE_GAMESTORE_H_
#define GAMESTORE_GAMESTORE_GAMESTORE_H_

#include "../Player/player.h"
#include "../Developer/developer.h"
#include "../Game/game.h"
#include "../TVector/tvector.h"

class GameStore {
    TVector<Game> _games;
    TVector<User> _players;
    TVector<Developer> _developers;
};

#endif  // GAMESTORE_GAMESTORE_GAMESTORE_H_
