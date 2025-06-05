// Copyright 2025 Viktoria Buzlaeva

#ifndef GAMESTORE_USER_USER_H_
#define GAMESTORE_USER_USER_H_

#include <string>

class User {
    std::string _login;
    std::string _password;

 public:
    User(const std::string& login = "", const std::string& password = "");

    const std::string login() const noexcept;
    const std::string password() const noexcept;

    bool operator == (const User&) const noexcept;
};

#endif  // GAMESTORE_USER_USER_H_
