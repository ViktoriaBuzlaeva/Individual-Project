// Copyright 2025 Viktoria Buzlaeva

#ifndef GAMESTORE_USER_USER_H_
#define GAMESTORE_USER_USER_H_

#include <string>

#include "../Date/date.h"
#include "../TVector/tvector.h"

class User {
    std::string _login;
    std::string _password;
    Date _registration_date;
};

#endif  // GAMESTORE_USER_USER_H_
