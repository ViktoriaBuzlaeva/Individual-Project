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

bool test_13_operator_equality_with_equal_tvectors() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1({ 1, 2, 3, 4 });
    TVector<int> v2({ 1, 2, 3, 4 });

    actual_result = (v1 == v2);

    return TestSystem::check(expected_result, actual_result);
}

bool test_14_operator_equality_with_not_equal_tvectors() {
    bool expected_result = false;
    bool actual_result = true;
    TVector<int> v1({ 1, 2, 3, 4 });
    TVector<int> v2({ 1, 2, 3 });

    actual_result = (v1 == v2);

    return TestSystem::check(expected_result, actual_result);
}

bool test_15_operator_inequality_with_equal_tvectors() {
    bool expected_result = false;
    bool actual_result = true;
    TVector<int> v1({ 1, 2, 3, 4 });
    TVector<int> v2({ 1, 2, 3, 4 });

    actual_result = (v1 != v2);

    return TestSystem::check(expected_result, actual_result);
}

bool test_16_operator_inequality_with_not_equal_tvectors() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1({ 1, 2, 3, 4 });
    TVector<int> v2({ 1, 2, 3 });

    actual_result = (v1 != v2);

    return TestSystem::check(expected_result, actual_result);
}

bool test_17_assign_with_size_and_value_tvector() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1(16, 2);
    v1.assign(5, 1);

    TVector<int> v2({ 1, 1, 1, 1, 1 });

    actual_result &= (v1 == v2);

    return TestSystem::check(expected_result, actual_result) &&
        TestSystem::check(v2.size(), v1.size());
}

bool test_18_assign_with_array_tvector() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1;
    v1.assign({1, 1, 1, 1, 1});

    TVector<int> v2({ 1, 1, 1, 1, 1 });

    actual_result &= (v1 == v2);

    return TestSystem::check(expected_result, actual_result) &&
        TestSystem::check(v2.size(), v1.size());
}

bool test_19_assign_tvector_with_reset_memory() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1;
    TVector<int> v3(31, 2);
    v1.assign(16, 1);
    v3.assign(16, 1);

    TVector<int> v2(16, 1);

    actual_result &= (v1 == v2);
    actual_result &= (v3 == v2);
    actual_result &= (v2.capacity() != v3.capacity());

    return TestSystem::check(expected_result, actual_result) &&
        TestSystem::check(v2.size(), v1.size()) &&
        TestSystem::check(v2.capacity(), v1.capacity()) &&
        TestSystem::check(v2.size(), v3.size());
}

bool test_20_operator_assign_other_tvector() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1({ 1, 2, 3, 4 });
    TVector<int> v2({ 1, 2 });
    v1 = v2;

    actual_result &= (v1 == v2);

    return TestSystem::check(expected_result, actual_result) &&
        TestSystem::check(v2.size(), v1.size()) &&
        TestSystem::check(v2.capacity(), v1.capacity());
}

bool test_21_access_elem_at_pos_tvector() {
    int value = 1;
    int mass[4] = { 1, 2, 3, 4 };
    const TVector<int> v1({ 1, 2, 3, 4 });
    TVector<int> v2({ 1, 2, 3, 4 });

    v2.at(3) = value;

    return TestSystem::check(mass[2], v1.at(2)) &&
        TestSystem::check(value, v2.at(3));
}

bool test_22_try_access_elem_at_out_of_range_pos_tvector() {
    bool expected_result = true;
    bool actual_result = false;
    TVector<int> v(6);

    try {
        int elem = v.at(6);
    }
    catch (const std::exception& ex) {
        actual_result = true;
    }

    return TestSystem::check(expected_result, actual_result);
}

bool test_23_operator_brackets_tvector() {
    int value = 1;
    int mass[4] = { 1, 2, 3, 4 };
    const TVector<int> v1({ 1, 2, 3, 4 });
    TVector<int> v2({ 1, 2, 3, 4 });

    v2[3] = value;

    return TestSystem::check(mass[2], v1[2]) &&
        TestSystem::check(value, v2[3]);
}

bool test_24_reserve_with_less_cap() {
    TVector<int> v(16, 2);
    v.reserve(17);

    return TestSystem::check((size_t)16, v.size()) &&
        TestSystem::check((size_t)30, v.capacity());
}

bool test_25_reserve_with_greater_cap() {
    TVector<int> v(14, 2);
    v.reserve(17);

    return TestSystem::check((size_t)14, v.size()) &&
        TestSystem::check((size_t)17, v.capacity());
}

bool test_26_resize_tvector_with_less_size() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1(14, 2);
    v1.resize(10);

    TVector<int> v2(10, 2);

    actual_result &= (v1 == v2);

    return TestSystem::check(expected_result, actual_result) &&
        TestSystem::check(v2.size(), v1.size()) &&
        TestSystem::check(v2.capacity(), v1.capacity());
}

bool test_27_resize_with_less_size_and_cap() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1(16, 2);
    v1.resize(10);

    TVector<int> v2(10, 2);

    actual_result &= (v1 == v2);

    return TestSystem::check(expected_result, actual_result) &&
        TestSystem::check(v2.size(), v1.size()) &&
        TestSystem::check(v2.capacity(), v1.capacity());
}

bool test_28_resize_tvector_with_greater_size() {
    TVector<int> v1(10, 2);
    v1.resize(13);

    TVector<int> v2(13);

    return TestSystem::check(v2.size(), v1.size()) &&
        TestSystem::check(v2.capacity(), v1.capacity());
}

bool test_29_resize_with_greater_size_and_cap() {
    TVector<int> v1(10, 2);
    v1.resize(16);

    TVector<int> v2(16, 2);

    return TestSystem::check(v2.size(), v1.size()) &&
        TestSystem::check(v2.capacity(), v1.capacity());
}

bool test_30_resize_with_new_value() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1(10, 2);
    v1.resize(16, 4);

    TVector<int> v2({ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4 });

    actual_result &= (v1 == v2);

    return TestSystem::check(expected_result, actual_result) &&
        TestSystem::check(v2.size(), v1.size()) &&
        TestSystem::check(v2.capacity(), v1.capacity());
}

bool test_31_push_front_tvector() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1({ 2, 3, 4, 5 });
    v1.push_front(1);

    TVector<int> v2({ 1, 2, 3, 4, 5 });

    actual_result &= (v1 == v2);

    return TestSystem::check(expected_result, actual_result) &&
        TestSystem::check(v2.size(), v1.size()) &&
        TestSystem::check(v2.capacity(), v1.capacity());
}

bool test_32_push_front_with_reset_memory() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1(14, 2);
    v1.push_front(1);
    v1.push_front(3);

    TVector<int> v2({ 3, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 });

    actual_result &= (v1 == v2);

    return TestSystem::check(expected_result, actual_result) &&
        TestSystem::check(v2.size(), v1.size()) &&
        TestSystem::check(v2.capacity(), v1.capacity());
}

bool test_33_push_back_tvector() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1({ 1, 2, 3, 4 });
    v1.push_back(5);

    TVector<int> v2({ 1, 2, 3, 4, 5 });

    actual_result &= (v1 == v2);

    return TestSystem::check(expected_result, actual_result) &&
        TestSystem::check(v2.size(), v1.size()) &&
        TestSystem::check(v2.capacity(), v1.capacity());
}

bool test_34_push_front_with_reset_memory() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1(14, 2);
    v1.push_back(1);
    v1.push_back(3);

    TVector<int> v2({ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 3 });

    actual_result &= (v1 == v2);

    return TestSystem::check(expected_result, actual_result) &&
        TestSystem::check(v2.size(), v1.size()) &&
        TestSystem::check(v2.capacity(), v1.capacity());
}

bool test_35_insert_tvector() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1({ 1, 2, 4, 5 });

    TVector<int> v2({ 1, 2, 3, 4, 5 });
    TVector<int> v3({ 1, 2, 3, 4, 5, 6, 6, 6 });
    TVector<int> v4({ 1, 2, 3, 4, 5, 6, 6, 8, 9, 10, 6});

    v1.insert(2, 3);
    actual_result &= (v1 == v2);
    v1.insert(5, 3, 6);
    actual_result &= (v1 == v3);
    v1.insert(7, { 8, 9, 10});
    actual_result &= (v1 == v4);

    return TestSystem::check(expected_result, actual_result);
}

bool test_36_insert_with_reset_memory() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1(14, 2);
    v1.insert(2, 111);
    v1.insert(9, 333);

    TVector<int> v2({ 2, 2, 111, 2, 2, 2, 2, 2, 2, 333, 2, 2, 2, 2, 2, 2 });

    actual_result &= (v1 == v2);

    return TestSystem::check(expected_result, actual_result) &&
        TestSystem::check(v2.size(), v1.size()) &&
        TestSystem::check(v2.capacity(), v1.capacity());
}

bool test_37_try_insert_out_of_range() {
    bool expected_result = true;
    bool actual_result = false;
    TVector<int> v({ 1, 2, 3, 4, 5 });

    try {
        v.insert(7, 6);
    }
    catch (const std::exception& ex) {
        actual_result = true;
    }

    return TestSystem::check(expected_result, actual_result);
}

bool test_38_clear_tvector() {
    TVector<int> v({ 1, 2, 3, 4, 5 });

    v.clear();

    return TestSystem::check((size_t)0, v.size()) &&
        TestSystem::check((size_t)15, v.capacity());
}

bool test_39_pop_front_tvector() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1({ 1, 2, 3, 4, 5 });
    v1.pop_front();

    TVector<int> v2({ 2, 3, 4, 5 });

    actual_result &= (v1 == v2);

    return TestSystem::check(expected_result, actual_result) &&
        TestSystem::check(v2.size(), v1.size()) &&
        TestSystem::check(v2.capacity(), v1.capacity());
}

bool test_40_pop_front_without_reset_memory_for_delete() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1(14, 2);
    v1.push_back(14);
    v1.pop_front();

    TVector<int> v2({ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 14 });

    actual_result &= (v1 == v2);
    actual_result &= (*(v1.data() + 13) != *(v2.data() + 13));

    return TestSystem::check(expected_result, actual_result);
}

bool test_41_try_pop_front_empty_tvector() {
    bool expected_result = true;
    bool actual_result = false;
    TVector<int> v;

    try {
        v.pop_front();
    }
    catch (const std::exception& ex) {
        actual_result = true;
    }

    return TestSystem::check(expected_result, actual_result);
}

bool test_42_pop_back_tvector() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1({ 1, 2, 3, 4, 5 });
    v1.pop_back();

    TVector<int> v2({ 1, 2, 3, 4 });

    actual_result &= (v1 == v2);

    return TestSystem::check(expected_result, actual_result) &&
        TestSystem::check(v2.size(), v1.size()) &&
        TestSystem::check(v2.capacity(), v1.capacity());
}

bool test_43_try_pop_back_empty_tvector() {
    bool expected_result = true;
    bool actual_result = false;
    TVector<int> v;

    try {
        v.pop_back();
    }
    catch (const std::exception& ex) {
        actual_result = true;
    }

    return TestSystem::check(expected_result, actual_result);
}

bool test_44_erase_tvector() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1({ 1, 2, 3, 4, 5 });

    TVector<int> v2({ 1, 2, 3, 5 });
    TVector<int> v3({ 1, 5 });

    v1.erase(3);
    actual_result &= (v1 == v2);
    v1.erase(1, 2);
    actual_result &= (v1 == v3);

    return TestSystem::check(expected_result, actual_result);
}

bool test_45_erase_without_reset_memory_for_delete() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1(14, 2);
    v1.insert(3, 4);
    v1.erase(3);
    v1.insert(4, 5);

    TVector<int> v2({ 2, 2, 2, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 });

    actual_result &= (v1 == v2);
    actual_result &= (*(v1.data() + 3) != *(v2.data() + 3));

    return TestSystem::check(expected_result, actual_result);
}

bool test_46_try_erase_empty_tvector() {
    bool expected_result = false;
    bool actual_result = true;
    TVector<int> v;

    try {
        v.erase(0);
    }
    catch (const std::exception& ex) {
        actual_result = false;
    }

    return TestSystem::check(expected_result, actual_result);
}

bool test_47_shrink_to_fit_tvector() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1(14, 2);
    v1.insert(2, 333);
    v1.erase(2);

    TVector<int> v2({ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 });

    actual_result &= (*(v1.data() + 2) != *(v2.data() + 2));
    v1.shrink_to_fit();
    actual_result &= (*(v1.data() + 2) == *(v2.data() + 2));

    return TestSystem::check(expected_result, actual_result);
}

bool test_48_replace_tvector() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1({ 1, 2, 3, 4, 5 });

    TVector<int> v2({ 1, 2, 333, 4, 5 });
    TVector<int> v3({ 1, 2, 3, 4, 5 });

    v1.replace(2, 333);
    actual_result &= (v1 == v2);
    v1.replace(v1.data() + 2, 3);
    actual_result &= (v1 == v3);

    return TestSystem::check(expected_result, actual_result);
}

bool test_49_replace_after_delete() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1(14, 2);
    v1.erase(2);
    v1.replace(2, 333);

    TVector<int> v2({ 2, 2, 333, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 });

    actual_result &= (v1 == v2);
    actual_result &= (*(v1.data() + 2) != *(v2.data() + 2));

    return TestSystem::check(expected_result, actual_result);
}

bool test_50_try_replace_out_of_range() {
    bool expected_result = true;
    bool actual_result = false;
    TVector<int> v({ 1, 2, 3, 4, 5 });

    try {
        v.replace(5, 555);
    }
    catch (const std::exception& ex) {
        actual_result = true;
    }

    return TestSystem::check(expected_result, actual_result);
}

bool test_51_try_replace_out_of_range() {
    bool expected_result = true;
    bool actual_result = false;
    TVector<int> v({ 1, 2, 3, 4, 5 });

    try {
        v.replace(v.data() + 5, 555);
    }
    catch (const std::exception& ex) {
        actual_result = true;
    }

    return TestSystem::check(expected_result, actual_result);
}

bool test_52_try_replace_deleted_elem() {
    bool expected_result = true;
    bool actual_result = false;
    TVector<int> v(14, 2);
    v.erase(2);

    try {
        v.replace(v.data() + 2, 555);
    }
    catch (const std::exception& ex) {
        actual_result = true;
    }

    return TestSystem::check(expected_result, actual_result);
}

bool test_53_find_first_elem_tvector() {
    TVector<int> v({ 1, 2, 3, 4, 3 });
    int i = find_first(v, 3);

    return TestSystem::check(2, i);
}

bool test_54_try_find_first_elem_tvector() {
    bool expected_result = true;
    bool actual_result = false;
    TVector<int> v({ 1, 2, 3, 4, 3 });

    try {
        int i = find_first(v, 6);
    }
    catch (const std::exception& ex) {
        actual_result = true;
    }

    return TestSystem::check(expected_result, actual_result);
}

bool test_55_find_last_elem_tvector() {
    TVector<int> v({ 1, 2, 3, 4, 3 });
    int i = find_last(v, 3);

    return TestSystem::check(4, i);
}

bool test_56_try_find_last_elem_tvector() {
    bool expected_result = true;
    bool actual_result = false;
    TVector<int> v({ 1, 2, 3, 4, 3 });

    try {
        int i = find_last(v, 6);
    }
    catch (const std::exception& ex) {
        actual_result = true;
    }

    return TestSystem::check(expected_result, actual_result);
}

bool test_57_find_all_elems_tvector() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v({ 1, 2, 3, 4, 3 });
    TVector<int> i1(find_all(v, 3));

    TVector<int> i2({2, 4});

    actual_result &= (i1 == i2);

    return TestSystem::check(expected_result, actual_result);
}

bool test_58_try_find_all_elems_tvector() {
    bool expected_result = true;
    bool actual_result = false;
    TVector<int> v({ 1, 2, 3, 4, 3 });

    try {
        TVector<int> i = find_all(v, 6);
    }
    catch (const std::exception& ex) {
        actual_result = true;
    }

    return TestSystem::check(expected_result, actual_result);
}

bool test_59_find_first_elem_pointer_tvector() {
    TVector<int> v({ 1, 2, 3, 4, 3 });
    int* i = find_first_pointer(v, 3);

    return TestSystem::check(v.data() + 2, i);
}

bool test_60_try_find_first_elem_pointer_tvector() {
    bool expected_result = true;
    bool actual_result = false;
    TVector<int> v({ 1, 2, 3, 4, 3 });

    try {
        int* i = find_first_pointer(v, 6);
    }
    catch (const std::exception& ex) {
        actual_result = true;
    }

    return TestSystem::check(expected_result, actual_result);
}

bool test_61_find_last_elem_pointer_tvector() {
    TVector<int> v({ 1, 2, 3, 4, 3 });
    int* i = find_last_pointer(v, 3);

    return TestSystem::check(v.data() + 4, i);
}

bool test_62_try_find_last_elem_pointer_tvector() {
    bool expected_result = true;
    bool actual_result = false;
    TVector<int> v({ 1, 2, 3, 4, 3 });

    try {
        int* i = find_last_pointer(v, 6);
    }
    catch (const std::exception& ex) {
        actual_result = true;
    }

    return TestSystem::check(expected_result, actual_result);
}

bool test_63_find_all_elems_pointers_tvector() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v({ 1, 2, 3, 4, 3 });
    TVector<int*> i1(find_all_pointers(v, 3));

    TVector<int*> i2({ v.data() + 2, v.data() + 4 });

    actual_result &= (i1 == i2);

    return TestSystem::check(expected_result, actual_result);
}

bool test_64_try_find_all_elems_pointers_tvector() {
    bool expected_result = true;
    bool actual_result = false;
    TVector<int> v({ 1, 2, 3, 4, 3 });

    try {
        TVector<int*> i = find_all_pointers(v, 6);
    }
    catch (const std::exception& ex) {
        actual_result = true;
    }

    return TestSystem::check(expected_result, actual_result);
}

bool test_65_shuffle_tvector() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1({ 1, 2, 3, 4, 5 });
    TVector<int> v2(v1);

    shuffle(v1);
    actual_result &= (v1 != v2);

    return TestSystem::check(expected_result, actual_result) &&
        TestSystem::check(v2.size(), v1.size()) &&
        TestSystem::check(v2.capacity(), v1.capacity());
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
    TestSystem::start_test(test_13_operator_equality_with_equal_tvectors,
        " operator_equality_with_equal_tvectors");
    TestSystem::start_test(test_14_operator_equality_with_not_equal_tvectors,
        " operator_equality_with_not_equal_tvectors");
    TestSystem::start_test(test_15_operator_inequality_with_equal_tvectors,
        " operator_inequality_with_equal_tvectors");
    TestSystem::start_test(test_16_operator_inequality_with_not_equal_tvectors,
        " operator_inequality_with_not_equal_tvectors");
    TestSystem::start_test(test_17_assign_with_size_and_value_tvector,
        " assign_with_size_and_value_tvector");
    TestSystem::start_test(test_18_assign_with_array_tvector,
        " assign_with_array_tvector");
    TestSystem::start_test(test_19_assign_tvector_with_reset_memory,
        " assign_tvector_with_reset_memory");
    TestSystem::start_test(test_20_operator_assign_other_tvector,
        " operator_assign_other_tvector");
    TestSystem::start_test(test_21_access_elem_at_pos_tvector,
        " access_elem_at_pos_tvector");
    TestSystem::start_test(test_22_try_access_elem_at_out_of_range_pos_tvector,
        " try_access_elem_at_out_of_range_pos_tvector");
    TestSystem::start_test(test_23_operator_brackets_tvector,
        " operator_brackets_tvector");
    TestSystem::start_test(test_24_reserve_with_less_cap,
        " reserve_with_less_cap");
    TestSystem::start_test(test_25_reserve_with_greater_cap,
        " reserve_with_greater_cap");
    TestSystem::start_test(test_26_resize_tvector_with_less_size,
        " resize_tvector_with_less_size");
    TestSystem::start_test(test_27_resize_with_less_size_and_cap,
        " resize_with_less_size_and_cap");
    TestSystem::start_test(test_28_resize_tvector_with_greater_size,
        " resize_tvector_with_greater_size");
    TestSystem::start_test(test_29_resize_with_greater_size_and_cap,
        " resize_with_greater_size_and_cap");
    TestSystem::start_test(test_30_resize_with_new_value,
        " resize_with_new_value");
    TestSystem::start_test(test_31_push_front_tvector, " push_front_tvector");
    TestSystem::start_test(test_32_push_front_with_reset_memory,
        " push_front_with_reset_memory");
    TestSystem::start_test(test_33_push_back_tvector, " push_back_tvector");
    TestSystem::start_test(test_34_push_front_with_reset_memory,
        " push_front_with_reset_memory");
    TestSystem::start_test(test_35_insert_tvector, " insert_tvector");
    TestSystem::start_test(test_36_insert_with_reset_memory,
        " insert_with_reset_memory");
    TestSystem::start_test(test_37_try_insert_out_of_range,
        " try_insert_out_of_range");
    TestSystem::start_test(test_38_clear_tvector, " clear_tvector");
    TestSystem::start_test(test_39_pop_front_tvector, " pop_front_tvector");
    TestSystem::start_test(test_40_pop_front_without_reset_memory_for_delete,
        " pop_front_without_reset_memory_for_delete");
    TestSystem::start_test(test_41_try_pop_front_empty_tvector,
        " try_pop_front_empty_tvector");
    TestSystem::start_test(test_42_pop_back_tvector, " pop_back_tvector");
    TestSystem::start_test(test_43_try_pop_back_empty_tvector,
        " try_pop_back_empty_tvector");
    TestSystem::start_test(test_44_erase_tvector, " erase_tvector");
    TestSystem::start_test(test_45_erase_without_reset_memory_for_delete,
        " erase_without_reset_memory_for_delete");
    TestSystem::start_test(test_46_try_erase_empty_tvector,
        " try_erase_empty_tvector");
    TestSystem::start_test(test_47_shrink_to_fit_tvector,
        " shrink_to_fit_tvector");
    TestSystem::start_test(test_48_replace_tvector, " replace_tvector");
    TestSystem::start_test(test_49_replace_after_delete,
        " replace_after_delete");
    TestSystem::start_test(test_50_try_replace_out_of_range,
        " try_replace_out_of_range");
    TestSystem::start_test(test_51_try_replace_out_of_range,
        " try_replace_out_of_range");
    TestSystem::start_test(test_52_try_replace_deleted_elem,
        " try_replace_deleted_elem");
    TestSystem::start_test(test_53_find_first_elem_tvector,
        " find_first_elem_tvector");
    TestSystem::start_test(test_54_try_find_first_elem_tvector,
        " try_find_first_elem_tvector");
    TestSystem::start_test(test_55_find_last_elem_tvector,
        " find_last_elem_tvector");
    TestSystem::start_test(test_56_try_find_last_elem_tvector,
        " try_find_last_elem_tvector");
    TestSystem::start_test(test_57_find_all_elems_tvector,
        " find_all_elems_tvector");
    TestSystem::start_test(test_58_try_find_all_elems_tvector,
        " try_find_all_elems_tvector");
    TestSystem::start_test(test_59_find_first_elem_pointer_tvector,
        " find_first_elem_pointer_tvector");
    TestSystem::start_test(test_60_try_find_first_elem_pointer_tvector,
        " try_find_first_elem_pointer_tvector");
    TestSystem::start_test(test_61_find_last_elem_pointer_tvector,
        " find_last_elem_pointer_tvector");
    TestSystem::start_test(test_62_try_find_last_elem_pointer_tvector,
        " try_find_last_elem_pointer_tvector");
    TestSystem::start_test(test_63_find_all_elems_pointers_tvector,
        " find_all_elems_pointers_tvector");
    TestSystem::start_test(test_64_try_find_all_elems_pointers_tvector,
        " try_find_all_elems_pointers_tvector");
    TestSystem::start_test(test_65_shuffle_tvector, " shuffle_tvector");

    TestSystem::print_final_info();

    system("pause");
    return 0;
}
