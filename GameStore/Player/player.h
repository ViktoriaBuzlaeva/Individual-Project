// Copyright 2025 Viktoria Buzlaeva

#ifndef GAMESTORE_PLAYER_PLAYER_H_
#define GAMESTORE_PLAYER_PLAYER_H_

#include <string>

#include "../User/user.h"
#include "../Review/review.h"
#include "../Game/game.h"
#include "../TVector/tvector.h"

class Game;
class Review;

class Player: public User {
    std::string _name;
    Date _registration_date;
    TVector<Review*> _reviews;
    TVector<Game*> _purchased_games;
    TVector<Game*> _wishlist_games;
};

#endif  // GAMESTORE_PLAYER_PLAYER_H_
