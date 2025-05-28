// Copyright 2025 Viktoria Buzlaeva

#ifndef GAMESTORE_GAME_GAME_H_
#define GAMESTORE_GAME_GAME_H_

#include <string>

#include "../Date/date.h"
#include "../Developer/developer.h"
#include "../Review/review.h"
#include "../TVector/tvector.h"

class Review;
class Developer;

class Game {
    std::string _name;
    int _rating;
    std::string _gaming_platform;
    Date _release_date;
    std::string _type;
    std::string _description;
    std::string _price;
    TVector<Review> _reviews;
    Developer* _developer;
};

#endif  // GAMESTORE_GAME_GAME_H_
