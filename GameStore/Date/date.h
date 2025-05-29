// Copyright 2025 Viktoria Buzlaeva

#ifndef GAMESTORE_DATE_DATE_H_
#define GAMESTORE_DATE_DATE_H_

#include <iostream>
#include <string>
#include <sstream>

class Date {
    int _year;
    int _month;
    int _day;

 public:
    explicit Date(int day = 1, int month = 1, int year = 2000);
    Date(const Date&);

    const int& year() const noexcept;
    const int& month() const noexcept;
    const int& day() const noexcept;

    bool operator < (const Date&)const noexcept;
    bool operator == (const Date&) const noexcept;
    bool operator != (const Date&) const noexcept;

    std::string to_string() const noexcept;

 private:
    bool is_correct(int, int, int);
    bool is_leap_year(int);
    int days_in_month(int, int);
};

#endif  // GAMESTORE_DATE_DATE_H_
