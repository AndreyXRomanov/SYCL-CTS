/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Provides functions to verify equality comparable requirements
//
*******************************************************************************/

#ifndef __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_EQUALITY_COMPARABLE_H
#define __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_EQUALITY_COMPARABLE_H

#include "../common/common.h"

#include "TypeTraits.h"
#include "common.h"

#include <chrono>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

template <typename It>
class equality_comparable_requirement : requirement_verifier {
 public:
  bool check(const std::string& type_name) {
    INFO("Verify named requiremnt Equality Comparable for: " + type_name);

    STATIC_CHECK(!std::is_same_v<It, void>);

    {
      INFO("Have to be able to be compared with equal operator");
      verify(type_traits::has_comparison::is_equal_v<It>);
    }

    // It will delete branch from code in compile time to not fail a compilation
    if constexpr (type_traits::has_comparison::is_equal_v<It>) {
      It a;
      It b;
      It c;
      const It const_a;
      const It const_b;
      const It const_c;

      {
        INFO(
            "Non-const copies of one object are actually equal during "
            "comparing");
        verify(a == b);
        verify(b == a);
        verify(b == c);
        verify(a == c);
      }
      {
        INFO(
            "Non-const copies of one object returns convertble to bool value "
            "after compairing");
        verify(std::is_convertible_v<decltype((a == b)), bool>);
        verify(std::is_convertible_v<decltype((b == a)), bool>);
        verify(std::is_convertible_v<decltype((b == c)), bool>);
        verify(std::is_convertible_v<decltype((a == c)), bool>);
      }

      {
        INFO("Const copies of one object are actually equal during comparing");
        verify(const_a == const_b);
        verify(const_b == const_c);
        verify(const_a == const_c);
        verify(const_b == const_a);
      }
      {
        INFO(
            "Const copies of one object returns convertble to bool value after "
            "compairing");
        verify(std::is_convertible_v<decltype((const_a == const_b)), bool>);
        verify(std::is_convertible_v<decltype((const_b == const_c)), bool>);
        verify(std::is_convertible_v<decltype((const_a == const_c)), bool>);
        verify(std::is_convertible_v<decltype((const_b == const_a)), bool>);
      }
    }
    return m_verification_result;
  }
};

#endif  // __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_EQUALITY_COMPARABLE_H
