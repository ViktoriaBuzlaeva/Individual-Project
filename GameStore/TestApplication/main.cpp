// Copyright 2025 Viktoria Buzlaeva

#include <windows.h>
#include <iostream>
#include <string>

#include "../Application/application.h"
#include "../Date/date.h"
#include "../Developer/developer.h"
#include "../Game/game.h"
#include "../Gamestore/gamestore.h"
#include "../Review/review.h"
#include "../Time/ctime.h"
#include "../User/user.h"

void set_color(int text_color, int bg_color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bg_color << 4) | text_color);
}

namespace TestSystem {
int count_success = 0, count_failed = 0;
    
void start_test(bool(*test)(), const char* name_of_test) {
    set_color(2, 0);
    std::cout << "[ RUN      ]";
    set_color(7, 0);
    std::cout << name_of_test << std::endl;

    bool status = test();

    if (status == true) {
        set_color(2, 0);
        std::cout << "[       OK ]" << std::endl;
        count_success++;
    } else {
        set_color(4, 0);
        std::cout << "[  FAILED  ]" << std::endl;
        count_failed++;
    }
    set_color(7, 0);
}

template <class T>
bool check(const T& expected, const T& actual) {
    if (expected == actual) {
        return true;
    } else {
        std::cerr << "Expected result is " << expected <<
            ", but actual is " << actual << "." << std::endl;
        return false;
    }
}

void print_init_info() {
    set_color(2, 0);
    std::cout << "[==========] " << std::endl;
    set_color(7, 0);
}

void print_final_info() {
    set_color(2, 0);
    std::cout << "[==========] ";
    set_color(7, 0);
    std::cout << count_success + count_failed << " test" <<
        (count_success + count_failed > 1 ? "s" : "") << " ran." << std::endl;
    set_color(2, 0);
    std::cout << "[  PASSED  ] ";
    set_color(7, 0);
    std::cout << count_success << " test" <<
        (count_success > 1 ? "s" : "") << std::endl;
    if (count_failed > 0) {
        set_color(4, 0);
        std::cout << "[  FAILED  ] ";
        set_color(7, 0);
        std::cout << count_failed << " test" <<
            (count_failed > 1 ? "s." : ".") << std::endl;
    }
}
};  // namespace TestSystem

bool test_1_create_default_ctime() {
    CTime t;

    return TestSystem::check(0, t.hours()) &&
        TestSystem::check(0, t.minutes()) &&
        TestSystem::check(0, t.seconds());
}

bool test_2_create_ctime_with_init() {
    CTime t(2, 30, 59);

    return TestSystem::check(2, t.hours()) &&
        TestSystem::check(30, t.minutes()) &&
        TestSystem::check(59, t.seconds());
}

bool test_3_try_create_ctime_with_init() {
    bool expected_result = true;
    bool actual_result = false;

    try {
        CTime t(-2, 30, 59);
    }
    catch (const std::exception& ex) {
        actual_result = true;
    }

    return TestSystem::check(expected_result, actual_result);
}

bool test_4_create_ctime_with_copying() {
    CTime t1(2, 30, 59);
    CTime t2(t1);

    return TestSystem::check(t1.hours(), t2.hours()) &&
        TestSystem::check(t1.minutes(), t2.minutes()) &&
        TestSystem::check(t1.seconds(), t2.seconds());
}

bool test_5_try_create_ctime_with_copying() {
    bool expected_result = true;
    bool actual_result = false;
    CTime* t1 = NULL;

    try {
        CTime t2(*t1);
    }
    catch (const std::exception& ex) {
        actual_result = true;
    }

    return TestSystem::check(expected_result, actual_result);
}

bool test_6_create_ctime_with_str_init() {
    CTime t("2:30:59");

    return TestSystem::check(2, t.hours()) &&
        TestSystem::check(30, t.minutes()) &&
        TestSystem::check(59, t.seconds());
}

bool test_7_try_create_ctime_with_str_init() {
    bool expected_result = true;
    bool actual_result = false;

    try {
        CTime t("2:30:60");
    }
    catch (const std::exception& ex) {
        actual_result = true;
    }

    return TestSystem::check(expected_result, actual_result);
}

bool test_8_convert_ctime_to_string() {
    std::string t_str = "2:30:59";
    CTime t(t_str);

    return TestSystem::check(t_str, t.to_string());
}

int main() {
    Application application_1;
    Date date_1;
    Developer developer_1;
    Game game_1;
    GameStore gamestore_1;
    Review review_1;
    CTime time_1;
    User user_1;

    TestSystem::start_test(test_1_create_default_ctime,
        "CTime.create_default_ctime");
    TestSystem::start_test(test_2_create_ctime_with_init,
        "CTime.create_ctime_with_init");
    TestSystem::start_test(test_3_try_create_ctime_with_init,
        "CTime.try_create_ctime_with_init");
    TestSystem::start_test(test_4_create_ctime_with_copying,
        "CTime.create_ctime_with_copying");
    TestSystem::start_test(test_5_try_create_ctime_with_copying,
        "CTime.try_create_ctime_with_copying");
    TestSystem::start_test(test_6_create_ctime_with_str_init,
        "CTime.create_ctime_with_str_init");
    TestSystem::start_test(test_7_try_create_ctime_with_str_init,
        "CTime.try_create_ctime_with_str_init");
    TestSystem::start_test(test_8_convert_ctime_to_string,
        "CTime.convert_ctime_to_string");

    TestSystem::print_final_info();

    return 0;
}
