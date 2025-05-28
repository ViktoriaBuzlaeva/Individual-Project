// Copyright 2025 Viktoria Buzlaeva

#ifndef GAMESTORE_REVIEW_REVIEW_H_
#define GAMESTORE_REVIEW_REVIEW_H_

#include "../Date/date.h"
#include "../Time/ctime.h"
#include "../User/user.h"

class User;

class Review {
    int _rate;
    std::string _text;
    User* _user;
    Date _publication_date;
    CTime _publication_time;
};

#endif  // GAMESTORE_REVIEW_REVIEW_H_
