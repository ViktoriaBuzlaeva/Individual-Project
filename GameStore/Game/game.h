// Copyright 2025 Viktoria Buzlaeva

#ifndef GAMESTORE_GAME_GAME_H_
#define GAMESTORE_GAME_GAME_H_

#include "../Date/date.h"
#include "../Developer/developer.h"
#include "../Review/review.h"

class Review;
class Developer;

class Game {
    char* _name;
    int _rating;
    char* _gaming_platform;
    Date _release_date;
    char* _type;
    char* _description;
    char* _price;
    Review* _reviews;
    Developer* _developer;
};

#endif  // GAMESTORE_GAME_GAME_H_
