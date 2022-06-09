/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Provides class to verify conformity with named requirement LegacyOutputIterator
//
*******************************************************************************/

#ifndef __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_LEGACY_OUTPUT_ITERATOR_H
#define __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_LEGACY_OUTPUT_ITERATOR_H

#include "EqualityComparable.h"
#include "LegacyIterator.h"
#include "TypeTraits.h"
#include "common.h"

class legacy_output_iterator_requirement {
 public:
  static constexpr size_t count_of_possible_errors =
      legacy_iterator_requirement::count_of_possible_errors + 8;

 private:
  error_messages_container<count_of_possible_errors> errors;

 public:
  template <typename It>
  auto is_satisfied_for() {
    auto legacy_iterator_res =
        legacy_iterator_requirement{}.is_satisfied_for<It>();
    if (legacy_iterator_res.first == false) {
      errors.add_errors(legacy_iterator_res.second);
    }

    constexpr bool is_dereferenceable = type_traits::is_dereferenceable_v<It>;
    constexpr bool can_pre_increment =
        type_traits::has_arithmetic::pre_increment_v<It>;
    constexpr bool can_post_increment =
        type_traits::has_arithmetic::post_increment_v<It>;
    constexpr bool has_value_type_member =
        type_traits::has_field::value_type_v<It>;

    if (!is_dereferenceable) {
      errors.add_error("Iterator have to implement operator*()");
    }

    if (!can_pre_increment || !can_post_increment) {
      errors.add_error("Iterator have to implement operator++() and operator++(int)");
    }

    if (!has_value_type_member) {
      errors.add_error("Iterator have to implement iterator_traits::value_type");
    }

    using it_traits = std::iterator_traits<It>;

    if constexpr (has_value_type_member && is_dereferenceable) {
      if (std::is_assignable_v<decltype(*std::declval<It>()),
                               typename it_traits::value_type> == false)
        errors.add_error(
            "Iterator have to return iterator_traits::value_type from "
            "operator*()");
    }

    if constexpr (can_pre_increment) {
      if (std::is_same_v<decltype(++std::declval<It&>()), It&> == false) {
        errors.add_error("Iterator have to return It& from operator++()");
      }
      if (std::is_convertible_v<decltype(++std::declval<It&>()), const It> ==
          false) {
        errors.add_error(
            "Iterator have to return convertble to const It from operator++()");
      }
    }

    if constexpr (can_post_increment && is_dereferenceable &&
                  has_value_type_member) {
      if (std::is_assignable_v<decltype(*(std::declval<It&>()++)),
                               typename it_traits::value_type> == false) {
        errors.add_error(
            "Iterator have to be assignable with iterator_traits::value_type "
            "after useage of operator++() and operator*()");
      }
    }

    if constexpr (is_dereferenceable && has_value_type_member) {
      if (std::is_assignable_v<decltype(*std::declval<It>()),
                               typename it_traits::value_type> == false) {
        errors.add_error(
            "Iterator have to be assignable with iterator_traits::value_type "
            "after useage of operator*()");
      }
    }

    const bool is_satisfied = !errors.has_errors();
    return std::make_pair(is_satisfied, errors.get_array());
  }
};

#endif  // __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_LEGACY_OUTPUT_ITERATOR_H
