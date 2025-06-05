// Copyright 2025 Viktoria Buzlaeva

#ifndef GAMESTORE_GAMESTORE_GAMESTORE_H_
#define GAMESTORE_GAMESTORE_GAMESTORE_H_

#include <string>
#include "../Player/player.h"
#include "../Developer/developer.h"
#include "../Game/game.h"
#include "../TVector/tvector.h"

class GameStore {
    TVector<Game> _games;
    TVector<User> _users;

 public:
    GameStore();

    bool check_user_login(const std::string&);
    bool check_user_for_signing(const User&);
};

#endif  // GAMESTORE_GAMESTORE_GAMESTORE_H_
