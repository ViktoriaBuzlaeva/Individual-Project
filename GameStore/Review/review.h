// Copyright 2025 Viktoria Buzlaeva

#ifndef GAMESTORE_REVIEW_REVIEW_H_
#define GAMESTORE_REVIEW_REVIEW_H_

#include <string>

#include "../Time/ctime.h"
#include "../Player/player.h"

class Player;

class Review {
    int _rate;
    std::string _text;
    Player* _author;
    Date _publication_date;
    CTime _publication_time;
};

#endif  // GAMESTORE_REVIEW_REVIEW_H_
