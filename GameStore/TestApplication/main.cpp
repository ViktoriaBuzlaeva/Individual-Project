// Copyright 2025 Viktoria Buzlaeva

#include <windows.h>
#include <iostream>
#include <string>

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

    return TestSystem::check(static_cast <size_t>(0), v.size()) &&
        TestSystem::check(static_cast <size_t>(15), v.capacity());
}

bool test_2_create_tvector_with_size() {
    TVector<int> v(30);

    return TestSystem::check(static_cast <size_t>(30), v.size()) &&
        TestSystem::check(static_cast <size_t>(45), v.capacity());
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
        TestSystem::check(static_cast <size_t>(4), v.size()) &&
        TestSystem::check(static_cast <size_t>(15), v.capacity());
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
        TestSystem::check(static_cast <size_t>(4), v.size()) &&
        TestSystem::check(static_cast <size_t>(15), v.capacity());
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
        TestSystem::check(static_cast <size_t>(4), v.size()) &&
        TestSystem::check(static_cast <size_t>(15), v.capacity());
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
        TestSystem::check(static_cast <size_t>(4), v.size()) &&
        TestSystem::check(static_cast <size_t>(15), v.capacity());
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
    TVector<int> v1(16, 2);
    v1.assign(5, 1);

    TVector<int> v2({ 1, 1, 1, 1, 1 });

    return TestSystem::check(v2, v1);
}

bool test_18_assign_with_array_tvector() {
    TVector<int> v1;
    v1.assign({1, 1, 1, 1, 1});

    TVector<int> v2({ 1, 1, 1, 1, 1 });

    return TestSystem::check(v2, v1);
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
    TVector<int> v1({ 1, 2, 3, 4 });
    TVector<int> v2({ 1, 2 });
    v1 = v2;

    return TestSystem::check(v2, v1) &&
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

    return TestSystem::check(static_cast <size_t>(16), v.size()) &&
        TestSystem::check(static_cast <size_t>(30), v.capacity());
}

bool test_25_reserve_with_greater_cap() {
    TVector<int> v(14, 2);
    v.reserve(17);

    return TestSystem::check(static_cast <size_t>(14), v.size()) &&
        TestSystem::check(static_cast <size_t>(17), v.capacity());
}

bool test_26_resize_tvector_with_less_size() {
    TVector<int> v1(14, 2);
    v1.resize(10);

    TVector<int> v2(10, 2);

    return TestSystem::check(v2, v1) &&
        TestSystem::check(v2.capacity(), v1.capacity());
}

bool test_27_resize_with_less_size_and_cap() {
    TVector<int> v1(16, 2);
    v1.resize(10);

    TVector<int> v2(10, 2);

    return TestSystem::check(v2, v1) &&
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
    TVector<int> v1(10, 2);
    v1.resize(16, 4);

    TVector<int> v2({ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4 });

    return TestSystem::check(v2, v1) &&
        TestSystem::check(v2.capacity(), v1.capacity());
}

bool test_31_push_front_tvector() {
    TVector<int> v1({ 2, 3, 4, 5 });
    v1.push_front(1);

    TVector<int> v2({ 1, 2, 3, 4, 5 });

    return  TestSystem::check(v2, v1) &&
        TestSystem::check(v2.capacity(), v1.capacity());
}

bool test_32_push_front_with_reset_memory() {
    TVector<int> v1(14, 2);
    v1.push_front(1);
    v1.push_front(3);

    TVector<int> v2({ 3, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 });

    return TestSystem::check(v2, v1) &&
        TestSystem::check(v2.capacity(), v1.capacity());
}

bool test_33_push_back_tvector() {
    TVector<int> v1({ 1, 2, 3, 4 });
    v1.push_back(5);

    TVector<int> v2({ 1, 2, 3, 4, 5 });

    return TestSystem::check(v2, v1) &&
        TestSystem::check(v2.capacity(), v1.capacity());
}

bool test_34_push_front_with_reset_memory() {
    TVector<int> v1(14, 2);
    v1.push_back(1);
    v1.push_back(3);

    TVector<int> v2({ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 3 });

    return TestSystem::check(v2, v1) &&
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
    TVector<int> v1(14, 2);
    v1.insert(2, 111);
    v1.insert(9, 333);

    TVector<int> v2({ 2, 2, 111, 2, 2, 2, 2, 2, 2, 333, 2, 2, 2, 2, 2, 2 });

    return TestSystem::check(v2, v1) &&
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

    return TestSystem::check(static_cast <size_t>(0), v.size()) &&
        TestSystem::check(static_cast <size_t>(15), v.capacity());
}

bool test_39_pop_front_tvector() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1({ 1, 2, 3, 4, 5 });
    v1.pop_front();

    TVector<int> v2({ 2, 3, 4, 5 });
    actual_result &= (v1 == v2);

    v1.pop_front();
    TVector<int> v3({ 3, 4, 5 });
    actual_result &= (v1 == v3);

    return TestSystem::check(expected_result, actual_result);
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
    TVector<int> v1({ 1, 2, 3, 4, 5 });
    v1.pop_back();

    TVector<int> v2({ 1, 2, 3, 4 });

    return TestSystem::check(v2, v1) &&
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
    v1.insert(3, 5);

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

    return TestSystem::check(expected_result, actual_result) &&
        TestSystem::check(v2.size(), v1.size()) &&
        TestSystem::check(static_cast <size_t>(14), v1.capacity());
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
    TVector<int> v({ 1, 2, 3, 4, 3 });
    TVector<int> i1(find_all(v, 3));

    TVector<int> i2({2, 4});

    return TestSystem::check(i2, i1);
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
    TVector<int> v({ 1, 2, 3, 4, 3 });
    TVector<int*> i1(find_all_pointers(v, 3));

    TVector<int*> i2({ v.data() + 2, v.data() + 4 });

    return TestSystem::check(i2, i1);
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

bool test_66_sort_tvector() {
    TVector<int> v1({ 5, 2, 3, 1, 4 });
    sort_hoare(v1);

    TVector<int> v2({ 1, 2, 3, 4, 5 });

    return TestSystem::check(v2, v1) &&
        TestSystem::check(v2.capacity(), v1.capacity());
}

bool test_67_insert_after_delete() {
    int* mass = new int[100];
    for (int i = 0; i < 100; i++) {
        mass[i] = i + 1;
    }
    TVector<int> v1(100, mass);
    v1.erase(3);
    v1.pop_front();
    v1.pop_back();
    v1.erase(3, 6);
    v1.insert(4, 55);
    v1.insert(6, { 33, 44, 55 });

    TVector<int> v2({ 2, 3, 5, 12, 55, 13, 33, 44, 55, 14, 15,
        16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
        32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
        64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
        80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
        96, 97, 98, 99 });

    return TestSystem::check(v2, v1);
}

bool test_68_replace_after_deleted() {
    int* mass = new int[100];
    for (int i = 0; i < 100; i++) {
        mass[i] = i + 1;
    }
    TVector<int> v1(100, mass);
    v1.erase(3);
    v1.pop_front();
    v1.pop_back();
    v1.erase(3);
    v1.replace(4, 55);

    TVector<int> v2({ 2, 3, 5, 7, 55, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
        33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
        49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64,
        65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
        81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96,
        97, 98, 99 });

    return TestSystem::check(v2, v1);
}

bool test_69_insert_empty_tvector() {
    bool expected_result = true;
    bool actual_result = true;
    TVector<int> v1;
    v1.push_front(1);
    TVector<int> v2({ 1 });
    actual_result &= (v1 == v2);

    TVector<int> v3;
    v3.push_back(10);
    TVector<int> v4({ 10 });
    actual_result &= (v3 == v4);

    TVector<int> v5;
    v5.insert(0, 88);
    TVector<int> v6({ 88 });
    actual_result &= (v5 == v6);

    return TestSystem::check(expected_result, actual_result);
}

bool test_70_replace_by_find_pointer() {
    TVector<int> v1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 7, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
        34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
        52, 53, 54, 7, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
        69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
        7, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100 });
    v1.replace(find_first_pointer(v1, 9), 99);

    TVector<int> v2({ 1, 2, 3, 4, 5, 6, 7, 8, 99, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 7, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
        34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
        52, 53, 54, 7, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
        69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
        7, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100 });

    return TestSystem::check(v2, v1);
}

bool test_71_erase_after_delete() {
    int* mass = new int[100];
    for (int i = 0; i < 100; i++) {
        mass[i] = i + 1;
    }
    TVector<int> v1(100, mass);
    v1.erase(3);
    v1.pop_front();
    v1.erase(3, 6);
    v1.erase(89);
    v1.erase(85, 6);

    TVector<int> v2({ 2, 3, 5, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
            24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
            41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
            58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
            75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91,
            92, 93 });

    return TestSystem::check(v2, v1);
}

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
    Date date_1;
    Developer developer_1;
    Game game_1;
    GameStore gamestore_1;
    Review review_1;
    CTime time_1;
    User user_1;

    TestSystem::start_test(test_1_create_default_tvector,
        " TVector.create_default_tvector");
    TestSystem::start_test(test_2_create_tvector_with_size,
        " TVector.create_tvector_with_size");
    TestSystem::start_test(test_3_create_tvector_with_array_and_size,
        " TVector.create_tvector_with_array_and_size");
    TestSystem::start_test(test_4_create_tvector_with_array_and_size,
        " TVector.create_tvector_with_array_and_size");
    TestSystem::start_test(test_5_create_tvector_with_array,
        " TVector.create_tvector_with_array");
    TestSystem::start_test(test_6_create_tvector_with_copying,
        " TVector.create_tvector_with_copying");
    TestSystem::start_test(test_7_try_create_tvector_with_copying,
        " TVector.try_create_tvector_with_copying");
    TestSystem::start_test(test_8_create_tvector_with_size_and_value,
        " TVector.create_tvector_with_size_and_value");
    TestSystem::start_test(test_9_access_front_elem_tvector,
        " TVector.access_front_elem_tvector");
    TestSystem::start_test(test_10_access_back_elem_tvector,
        " TVector.access_back_elem_tvector");
    TestSystem::start_test(test_11_try_access_front_elem_empty_tvector,
        " TVector.try_access_front_elem_empty_tvector");
    TestSystem::start_test(test_12_try_access_back_elem_empty_tvector,
        " TVector.try_access_back_elem_empty_tvector");
    TestSystem::start_test(test_13_operator_equality_with_equal_tvectors,
        " TVector.operator_equality_with_equal_tvectors");
    TestSystem::start_test(test_14_operator_equality_with_not_equal_tvectors,
        " TVector.operator_equality_with_not_equal_tvectors");
    TestSystem::start_test(test_15_operator_inequality_with_equal_tvectors,
        " TVector.operator_inequality_with_equal_tvectors");
    TestSystem::start_test(test_16_operator_inequality_with_not_equal_tvectors,
        " TVector.operator_inequality_with_not_equal_tvectors");
    TestSystem::start_test(test_17_assign_with_size_and_value_tvector,
        " TVector.assign_with_size_and_value_tvector");
    TestSystem::start_test(test_18_assign_with_array_tvector,
        " TVector.assign_with_array_tvector");
    TestSystem::start_test(test_19_assign_tvector_with_reset_memory,
        " TVector.assign_tvector_with_reset_memory");
    TestSystem::start_test(test_20_operator_assign_other_tvector,
        " TVector.operator_assign_other_tvector");
    TestSystem::start_test(test_21_access_elem_at_pos_tvector,
        " TVector.access_elem_at_pos_tvector");
    TestSystem::start_test(test_22_try_access_elem_at_out_of_range_pos_tvector,
        " TVector.try_access_elem_at_out_of_range_pos_tvector");
    TestSystem::start_test(test_23_operator_brackets_tvector,
        " TVector.operator_brackets_tvector");
    TestSystem::start_test(test_24_reserve_with_less_cap,
        " TVector.reserve_with_less_cap");
    TestSystem::start_test(test_25_reserve_with_greater_cap,
        " TVector.reserve_with_greater_cap");
    TestSystem::start_test(test_26_resize_tvector_with_less_size,
        " TVector.resize_tvector_with_less_size");
    TestSystem::start_test(test_27_resize_with_less_size_and_cap,
        " TVector.resize_with_less_size_and_cap");
    TestSystem::start_test(test_28_resize_tvector_with_greater_size,
        " TVector.resize_tvector_with_greater_size");
    TestSystem::start_test(test_29_resize_with_greater_size_and_cap,
        " TVector.resize_with_greater_size_and_cap");
    TestSystem::start_test(test_30_resize_with_new_value,
        " TVector.resize_with_new_value");
    TestSystem::start_test(test_31_push_front_tvector,
        " TVector.push_front_tvector");
    TestSystem::start_test(test_32_push_front_with_reset_memory,
        " TVector.push_front_with_reset_memory");
    TestSystem::start_test(test_33_push_back_tvector,
        " TVector.push_back_tvector");
    TestSystem::start_test(test_34_push_front_with_reset_memory,
        " TVector.push_front_with_reset_memory");
    TestSystem::start_test(test_35_insert_tvector, " TVector.insert_tvector");
    TestSystem::start_test(test_36_insert_with_reset_memory,
        " TVector.insert_with_reset_memory");
    TestSystem::start_test(test_37_try_insert_out_of_range,
        " TVector.try_insert_out_of_range");
    TestSystem::start_test(test_38_clear_tvector, " TVector.clear_tvector");
    TestSystem::start_test(test_39_pop_front_tvector,
        " TVector.pop_front_tvector");
    TestSystem::start_test(test_40_pop_front_without_reset_memory_for_delete,
        " TVector.pop_front_without_reset_memory_for_delete");
    TestSystem::start_test(test_41_try_pop_front_empty_tvector,
        " TVector.try_pop_front_empty_tvector");
    TestSystem::start_test(test_42_pop_back_tvector,
        " TVector.pop_back_tvector");
    TestSystem::start_test(test_43_try_pop_back_empty_tvector,
        " TVector.try_pop_back_empty_tvector");
    TestSystem::start_test(test_44_erase_tvector, " TVector.erase_tvector");
    TestSystem::start_test(test_45_erase_without_reset_memory_for_delete,
        " TVector.erase_without_reset_memory_for_delete");
    TestSystem::start_test(test_46_try_erase_empty_tvector,
        " TVector.try_erase_empty_tvector");
    TestSystem::start_test(test_47_shrink_to_fit_tvector,
        " TVector.shrink_to_fit_tvector");
    TestSystem::start_test(test_48_replace_tvector,
        " TVector.replace_tvector");
    TestSystem::start_test(test_49_replace_after_delete,
        " TVector.replace_after_delete");
    TestSystem::start_test(test_50_try_replace_out_of_range,
        " TVector.try_replace_out_of_range");
    TestSystem::start_test(test_51_try_replace_out_of_range,
        " TVector.try_replace_out_of_range");
    TestSystem::start_test(test_52_try_replace_deleted_elem,
        " TVector.try_replace_deleted_elem");
    TestSystem::start_test(test_53_find_first_elem_tvector,
        " TVector.find_first_elem_tvector");
    TestSystem::start_test(test_54_try_find_first_elem_tvector,
        " TVector.try_find_first_elem_tvector");
    TestSystem::start_test(test_55_find_last_elem_tvector,
        " TVector.find_last_elem_tvector");
    TestSystem::start_test(test_56_try_find_last_elem_tvector,
        " TVector.try_find_last_elem_tvector");
    TestSystem::start_test(test_57_find_all_elems_tvector,
        " TVector.find_all_elems_tvector");
    TestSystem::start_test(test_58_try_find_all_elems_tvector,
        " TVector.try_find_all_elems_tvector");
    TestSystem::start_test(test_59_find_first_elem_pointer_tvector,
        " TVector.find_first_elem_pointer_tvector");
    TestSystem::start_test(test_60_try_find_first_elem_pointer_tvector,
        " TVector.try_find_first_elem_pointer_tvector");
    TestSystem::start_test(test_61_find_last_elem_pointer_tvector,
        " TVector.find_last_elem_pointer_tvector");
    TestSystem::start_test(test_62_try_find_last_elem_pointer_tvector,
        " TVector.try_find_last_elem_pointer_tvector");
    TestSystem::start_test(test_63_find_all_elems_pointers_tvector,
        " TVector.find_all_elems_pointers_tvector");
    TestSystem::start_test(test_64_try_find_all_elems_pointers_tvector,
        " TVector.try_find_all_elems_pointers_tvector");
    TestSystem::start_test(test_65_shuffle_tvector,
        " TVector.shuffle_tvector");
    TestSystem::start_test(test_66_sort_tvector, " TVector.sort_tvector");
    TestSystem::start_test(test_67_insert_after_delete,
        " TVector.insert_after_delete");
    TestSystem::start_test(test_68_replace_after_deleted,
        " TVector.replace_after_deleted");
    TestSystem::start_test(test_69_insert_empty_tvector,
        " TVector.insert_empty_tvector");
    TestSystem::start_test(test_70_replace_by_find_pointer,
        " TVector.replace_by_find_pointer");
    TestSystem::start_test(test_71_erase_after_delete,
        " TVector.erase_after_delete");

    TestSystem::start_test(test_1_create_default_ctime,
        " CTime.create_default_ctime");
    TestSystem::start_test(test_2_create_ctime_with_init,
        " CTime.create_ctime_with_init");
    TestSystem::start_test(test_3_try_create_ctime_with_init,
        " CTime.try_create_ctime_with_init");
    TestSystem::start_test(test_4_create_ctime_with_copying,
        " CTime.create_ctime_with_copying");
    TestSystem::start_test(test_5_try_create_ctime_with_copying,
        " CTime.try_create_ctime_with_copying");
    TestSystem::start_test(test_6_create_ctime_with_str_init,
        " CTime.create_ctime_with_str_init");
    TestSystem::start_test(test_7_try_create_ctime_with_str_init,
        " CTime.try_create_ctime_with_str_init");
    TestSystem::start_test(test_8_convert_ctime_to_string,
        " CTime.convert_ctime_to_string");

    TestSystem::print_final_info();

    system("pause");
    return 0;
}
