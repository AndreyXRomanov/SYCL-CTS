/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Provides class to verify conformity with named requirement EqualityComparable
//
*******************************************************************************/

#ifndef __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_EQUALITY_COMPARABLE_H
#define __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_EQUALITY_COMPARABLE_H

#include "TypeTraits.h"
#include "common.h"

class equality_comparable_requirement {
 public:
  static constexpr size_t count_of_possible_errors = 4;

 private:
  error_messages_container<count_of_possible_errors> errors;

 public:
  template <typename It>
  auto is_satisfied_for() {
    if (!type_traits::has_comparison::is_equal_v<It>) {
      errors.add_error("Doesn't have implemented operator==()");
    }

    // It will delete branch from code in compile time to not fail a compilation
    if constexpr (type_traits::has_comparison::is_equal_v<It>) {
      It a;
      It b;
      It c;
      const It const_a;
      const It const_b;
      const It const_c;

      if (!(a == b) || !(b == a) || !(b == c) || !(a == c)) {
        errors.add_error(
            "Non-const copies of one object doesn't equal to each other equal "
            "during comparing");
      }

      if ((!std::is_convertible_v<decltype((a == b)), bool>) ||
          (!std::is_convertible_v<decltype((b == a)), bool>) ||
          (!std::is_convertible_v<decltype((b == c)), bool>) ||
          (!std::is_convertible_v<decltype((a == c)), bool>)) {
        errors.add_error(
            "Non-const copies of one object doesn't return convertible to bool "
            "value after comparing");
      }

      if (!(const_a == const_b) || !(const_b == const_a) ||
          !(const_b == const_c) || !(const_a == const_c)) {
        errors.add_error(
            "Const copies of one object doesn't equal to each other equal "
            "during comparing");
      }

      if ((!std::is_convertible_v<decltype((const_a == const_b)), bool>) ||
          (!std::is_convertible_v<decltype((const_b == const_c)), bool>) ||
          (!std::is_convertible_v<decltype((const_a == const_c)), bool>) ||
          (!std::is_convertible_v<decltype((const_b == const_a)), bool>)) {
        errors.add_error(
            "Const copies of one object doesn't return convertible to bool "
            "value after comparing");
      }
    }

    const bool is_satisfied = !errors.has_errors();
    return std::make_pair(is_satisfied, errors.get_array());
  }
};

#endif  // __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_EQUALITY_COMPARABLE_H
