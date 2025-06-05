// Copyright 2025 Viktoria Buzlaeva

#include "/GitHub/Individual-Project/GameStore/User/user.h"

User::User(const std::string& login, const std::string& password) :
    _login(login), _password(password) {}

const std::string User::login() const noexcept {
    return _login;
}

const std::string User::password() const noexcept {
    return _password;
}

bool User::operator == (const User& other) const noexcept {
    if (_login != other._login || _password != other._password) return false;
    return true;
}
