// Copyright 2025 Viktoria Buzlaeva

#ifndef GAMESTORE_GAME_GAME_H_
#define GAMESTORE_GAME_GAME_H_

#include <string>

#include "../Developer/developer.h"
#include "../Review/review.h"
#include "../TVector/tvector.h"

class Review;
class Developer;

class Game {
    std::string _name;
    std::string _description;
    std::string _type;
    std::string _engine;
    std::string _gaming_platform;
    std::string _price;
    Date _release_date;
    int _rating;
    TVector<Review> _reviews;
    Developer* _developer;
};

#endif  // GAMESTORE_GAME_GAME_H_
