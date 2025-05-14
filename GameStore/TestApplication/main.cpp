// Copyright 2025 Viktoria Buzlaeva

#include <windows.h>
#include <iostream>

#include "../Application/application.h"
#include "../Date/date.h"
#include "../Developer/developer.h"
#include "../Game/game.h"
#include "../Gamestore/gamestore.h"
#include "../Review/review.h"
#include "../Time/ctime.h"
#include "../TVector/tvector.h"
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

bool test_1_create_default_tvector() {
    TVector<int> v;

    return TestSystem::check((size_t)0, v.size()) &&
        TestSystem::check((size_t)15, v.capacity());
}

bool test_2_create_tvector_with_size() {
    TVector<int> v(20);

    return TestSystem::check((size_t)20, v.size()) &&
        TestSystem::check((size_t)30, v.capacity());
}

bool test_3_create_tvector_with_array_and_size() {
    bool expected_result = true;
    bool actual_result = true;
    int mass[4] = { 1, 2, 3, 4 };
    TVector<int> v(4, mass);

    for (int i = 0; i < v.size(); i++) {
        actual_result &= (*(v.data() + i) == mass[i]);
    }

    return TestSystem::check(expected_result, actual_result) &&
        TestSystem::check((size_t)4, v.size()) &&
        TestSystem::check((size_t)15, v.capacity());
}

bool test_4_create_tvector_with_array_and_size() {
    bool expected_result = true;
    bool actual_result = true;
    int mass[4] = { 1, 2, 3, 4 };
    TVector<int> v(4, { 1, 2, 3, 4 });

    for (int i = 0; i < v.size(); i++) {
        actual_result &= (*(v.data() + i) == mass[i]);
    }

    return TestSystem::check(expected_result, actual_result) &&
        TestSystem::check((size_t)4, v.size()) &&
        TestSystem::check((size_t)15, v.capacity());
}

bool test_5_create_tvector_with_array() {
    bool expected_result = true;
    bool actual_result = true;
    int mass[4] = { 1, 2, 3, 4 };
    TVector<int> v({ 1, 2, 3, 4 });

    for (int i = 0; i < v.size(); i++) {
        actual_result &= (*(v.data() + i) == mass[i]);
    }

    return TestSystem::check(expected_result, actual_result) &&
        TestSystem::check((size_t)4, v.size()) &&
        TestSystem::check((size_t)15, v.capacity());
}

bool test_6_create_tvector_with_copying() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1({ 1, 2, 3, 4 });
    TVector<int> v2(v1);

    for (int i = 0; i < v1.size(); i++) {
        actual_result &= (*(v1.data() + i) == *(v2.data() + i));
    }

    return TestSystem::check(expected_result, actual_result) &&
        TestSystem::check(v1.size(), v2.size()) &&
        TestSystem::check(v1.capacity(), v2.capacity());
}

bool test_7_try_create_tvector_with_copying() {
    bool expected_result = true;
    bool actual_result = false;
    TVector<int>* v1 = NULL;

    try {
        TVector<int> v2(*v1);
    }
    catch (const std::exception& ex) {
        actual_result = true;
    }

    return TestSystem::check(expected_result, actual_result);
}

bool test_8_create_tvector_with_size_and_value() {
    bool expected_result = true;
    bool actual_result = true;
    int mass[4] = { 4, 4, 4, 4 };
    TVector<int> v(4, 4);

    for (int i = 0; i < v.size(); i++) {
        actual_result &= (*(v.data() + i) == mass[i]);
    }

    return TestSystem::check(expected_result, actual_result) &&
        TestSystem::check((size_t)4, v.size()) &&
        TestSystem::check((size_t)15, v.capacity());
}

bool test_9_access_front_elem_tvector() {
    int value = 4;
    int mass[4] = { 1, 2, 3, 4 };
    TVector<int> v({ 1, 2, 3, 4 });

    int first_elem = v.front();
    v.front() = value;

    return TestSystem::check(mass[0], first_elem) &&
        TestSystem::check(value, v.front());
}

bool test_10_access_back_elem_tvector() {
    int value = 1;
    int mass[4] = { 1, 2, 3, 4 };
    TVector<int> v({ 1, 2, 3, 4 });

    int last_elem = v.back();
    v.back() = value;

    return TestSystem::check(mass[3], last_elem) &&
        TestSystem::check(value, v.back());
}

bool test_11_try_access_front_elem_empty_tvector() {
    bool expected_result = true;
    bool actual_result = false;
    TVector<int> v;

    try {
        int elem = v.front();
    }
    catch (const std::exception& ex) {
        actual_result = true;
    }

    return TestSystem::check(expected_result, actual_result);
}

bool test_12_try_access_back_elem_empty_tvector() {
    bool expected_result = true;
    bool actual_result = false;
    TVector<int> v;

    try {
        int elem = v.back();
    }
    catch (const std::exception& ex) {
        actual_result = true;
    }

    return TestSystem::check(expected_result, actual_result);
}

int main() {
    Application application_1;
    Date date_1;
    Developer developer_1;
    Game game_1;
    GameStore gamestore_1;
    Review review_1;
    Time time_1;
    User user_1;

    TestSystem::start_test(test_1_create_default_tvector,
        " create_default_tvector");
    TestSystem::start_test(test_2_create_tvector_with_size,
        " create_tvector_with_size");
    TestSystem::start_test(test_3_create_tvector_with_array_and_size,
        " create_tvector_with_array_and_size");
    TestSystem::start_test(test_4_create_tvector_with_array_and_size,
        " create_tvector_with_array_and_size");
    TestSystem::start_test(test_5_create_tvector_with_array,
        " create_tvector_with_array");
    TestSystem::start_test(test_6_create_tvector_with_copying,
        " create_tvector_with_copying");
    TestSystem::start_test(test_7_try_create_tvector_with_copying,
        " try_create_tvector_with_copying");
    TestSystem::start_test(test_8_create_tvector_with_size_and_value,
        " create_tvector_with_size_and_value");
    TestSystem::start_test(test_9_access_front_elem_tvector,
        " access_front_elem_tvector");
    TestSystem::start_test(test_10_access_back_elem_tvector,
        " access_back_elem_tvector");
    TestSystem::start_test(test_11_try_access_front_elem_empty_tvector,
        " try_access_front_elem_empty_tvector");
    TestSystem::start_test(test_12_try_access_back_elem_empty_tvector,
        " try_access_back_elem_empty_tvector");

    TestSystem::print_final_info();

    system("pause");
    return 0;
}
