// Copyright 2025 Viktoria Buzlaeva

#include "/GitHub/Individual-Project/GameStore/Date/date.h"

Date::Date(int day, int month, int year) {
    if (!is_correct(day, month, year)) throw std::logic_error
        ("Error in init constructor: incorrect data!");
    _day = day;
    _month = month;
    _year = year;
}

Date::Date(const Date& other) {
    if (&other == NULL) throw std::logic_error
        ("Error in copy constructor: other date doesn't exist!");
    _day = other._day;
    _month = other._month;
    _year = other._year;
}

const int& Date::year() const noexcept {
    return _year;
}

const int& Date::month() const noexcept {
    return _month;
}

const int& Date::day() const noexcept {
    return _day;
}

bool Date::operator < (const Date& other)const noexcept {
    if (*(this) != other) {
        if (_year != other._year) return _year < other._year;
        if (_month != other._month) return _month < other._month;
        return _day < other._day;
    }
    return false;
}

bool Date::operator == (const Date& other) const noexcept {
    return _year == other._year
        && _month == other._month
        && _day == other._day;
}

bool Date::operator != (const Date& other) const noexcept {
    return !(*(this) == other);
}

std::string Date::to_string() const noexcept {
    std::ostringstream date;
    date << _day << "." << _month << "." << _year;
    return date.str();
}

bool Date::is_correct(int d, int m, int y) {
    if (y < 1980 || m < 0 || m > 12 || d < 0 || d > days_in_month(m, y)) {
        return false;
    }
    return true;
}

bool Date::is_leap_year(int y) {
    if (y % 4 == 0 && y % 100 != 0 || y % 400 == 0) return true;
}

int Date::days_in_month(int m, int y) {
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (m == 2 && is_leap_year(y)) return 29;
    return days[m - 1];
}
