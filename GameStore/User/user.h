// Copyright 2025 Viktoria Buzlaeva

#ifndef GAMESTORE_USER_USER_H_
#define GAMESTORE_USER_USER_H_

#include "../Date/date.h"
#include "../Review/review.h"
#include "../Game/game.h"
#include "../TVector/tvector.h"

class Game;
class Review;

class User {
    std::string _name;
    std::string _email;
    std::string _password;
    Date _registration_date;
    TVector<Review*> _reviews;
    TVector<Game*> _purchased_games;
    TVector<Game*> _wishlist_games;
};

#endif  // GAMESTORE_USER_USER_H_
