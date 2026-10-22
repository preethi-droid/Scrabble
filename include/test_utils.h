#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <iostream>
#include <string>
#include <cassert>

inline void ASSERT_EQ_MSG(auto actual, auto expected, const std::string& msg) {
    if (actual != expected) {
        std::cerr << "[FAIL] " << msg << " | Expected: " << expected << ", Got: " << actual << std::endl;
        assert(false);
    } else {
        std::cout << "[PASS] " << msg << std::endl;
    }
}

#endif