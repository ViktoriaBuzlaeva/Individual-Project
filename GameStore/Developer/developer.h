// Copyright 2025 Viktoria Buzlaeva

#ifndef GAMESTORE_DEVELOPER_DEVELOPER_H_
#define GAMESTORE_DEVELOPER_DEVELOPER_H_

#include <string>

#include "../Date/date.h"
#include "../User/user.h"
#include "../Game/game.h"
#include "../TVector/tvector.h"

class Game;

class Developer: public User {
    std::string _name;
    std::string _country;
    Date _founding_date;
    int _rating;
    TVector<Game*> _games;
};

#endif  // GAMESTORE_DEVELOPER_DEVELOPER_H_
