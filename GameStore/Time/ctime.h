// Copyright 2025 Viktoria Buzlaeva

#include <string>

#ifndef GAMESTORE_TIME_CTIME_H_
#define GAMESTORE_TIME_CTIME_H_

class CTime {
    int _hours;
    int _minutes;
    int _seconds;

 public:
    explicit CTime(int hours = 0, int minutes = 0, int seconds = 0);
    CTime(const CTime&);
    explicit CTime(std::string);

    inline const int hours() const noexcept;
    inline const int minutes() const noexcept;
    inline const int seconds() const noexcept;

    void print() noexcept;
};

#endif  // GAMESTORE_TIME_CTIME_H_
