// Copyright 2025 Viktoria Buzlaeva

#ifndef GAMESTORE_TIME_CTIME_H_
#define GAMESTORE_TIME_CTIME_H_

#include <string>
#include <sstream>
#include <iostream>

class CTime {
    int _hours;
    int _minutes;
    int _seconds;

 public:
    explicit CTime(int hours = 0, int minutes = 0, int seconds = 0);
    CTime(const CTime&);
    explicit CTime(std::string);

    const int& hours() const noexcept;
    const int& minutes() const noexcept;
    const int& seconds() const noexcept;

    bool operator < (const CTime&)const noexcept;
    bool operator == (const CTime&) const noexcept;
    bool operator != (const CTime&) const noexcept;

    std::string to_string() const noexcept;

 private:
    bool is_correct(int, int, int);
};

#endif  // GAMESTORE_TIME_CTIME_H_
