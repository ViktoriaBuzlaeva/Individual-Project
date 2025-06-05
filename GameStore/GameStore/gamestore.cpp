// Copyright 2025 Viktoria Buzlaeva

#include <string>
#include "/GitHub/Individual-Project/GameStore/GameStore/gamestore.h"

GameStore::GameStore() {
    User user_1("viktoria", "123456");
    User user_2("valve_studio", "11111111");
    _users.push_back(user_1);
    _users.push_back(user_2);
}

bool GameStore::check_user_login(const std::string& login) {
    for (int i = 0; i < _users.size(); i++) {
        if (_users[i].login() == login) return true;
    }
    return false;
}

bool GameStore::check_user_for_signing(const User& signing_user) {
    for (int i = 0; i < _users.size(); i++) {
        if (_users[i] == signing_user) return true;
    }
    return false;
}
