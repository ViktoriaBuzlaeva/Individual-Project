// Copyright 2025 Viktoria Buzlaeva

#include <string>

#include "/GitHub/Individual-Project/GameStore/Time/ctime.h"

CTime::CTime(int hours, int minutes, int seconds) {
    if (!is_correct(hours, minutes, seconds)) throw std::logic_error
        ("Error in init constructor: incorrect data!");
    _hours = hours;
    _minutes = minutes;
    _seconds = seconds;
}

CTime::CTime(const CTime& other) {
    if (&other == NULL) throw std::logic_error
        ("Error in copy constructor: other ctime doesn't exist!");
    _hours = other._hours;
    _minutes = other._minutes;
    _seconds = other._seconds;
}

CTime::CTime(std::string time) {
    int i = 0;
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
    for (; time[i] != ':'; i++) {
        hours = hours * 10 + (time[i] - '0');
    }
    i++;
    for (; time[i] != ':'; i++) {
        minutes = minutes * 10 + (time[i] - '0');
    }
    i++;
    for (int j = 0; j < 2; j++, i++) {
        seconds = seconds * 10 + (time[i] - '0');
    }
    if (!is_correct(hours, minutes, seconds)) throw std::logic_error
        ("Error in string init constructor: incorrect data!");
    _hours = hours;
    _minutes = minutes;
    _seconds = seconds;
}

const int& CTime::hours() const noexcept {
    return _hours;
}

const int& CTime::minutes() const noexcept {
    return _minutes;
}

const int& CTime::seconds() const noexcept {
    return _seconds;
}

bool CTime::operator < (const CTime& other)const noexcept {
    if (*(this) != other) {
        if (_hours != other._hours) return _hours < other._hours;
        if (_minutes != other._minutes) return _minutes < other._minutes;
        return _seconds < other._seconds;
    }
    return false;
}

bool CTime::operator == (const CTime& other) const noexcept {
    return _hours == other._hours
        && _minutes == other._minutes
        && _seconds == other._seconds;
}

bool CTime::operator != (const CTime& other) const noexcept {
    return !(*(this) == other);
}

std::string CTime::to_string() const noexcept {
    std::ostringstream time;
    time << _hours << ":" << _minutes << ":" << _seconds;
    return time.str();
}

bool CTime::is_correct(int h, int m, int s) {
    if (h < 0 || h > 23 || m < 0 || m > 59 || s < 0 || s > 59) {
        return false;
    }
    return true;
}
