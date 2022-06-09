/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Provides class to verify conformity with named requirement LegacyInputIterator
//
*******************************************************************************/

#ifndef __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_LEGACY_INPUT_ITERATOR_H
#define __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_LEGACY_INPUT_ITERATOR_H

#include "EqualityComparable.h"
#include "LegacyIterator.h"
#include "TypeTraits.h"
#include "common.h"

class legacy_input_iterator_requirement {
 public:
  static constexpr size_t count_of_possible_errors =
      legacy_iterator_requirement::count_of_possible_errors + 10;

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
    constexpr bool has_reference_member =
        type_traits::has_field::reference_v<It>;
    constexpr bool has_value_type_member =
        type_traits::has_field::value_type_v<It>;
    constexpr bool has_equal_operator =
        type_traits::has_comparison::is_equal_v<It>;
    constexpr bool has_not_equal_operator =
        type_traits::has_comparison::not_equal_v<It>;

    if (!has_equal_operator) {
      errors.add_error("Iterator doesn't have implemented operator==()");
    }

    if (!has_not_equal_operator) {
      errors.add_error("Iterator doesn't have implemented operator!=()");
    }

    if (!is_dereferenceable) {
      errors.add_error("Iterator doesn't have implemented operator*()");
    }

    if (!can_pre_increment || !can_post_increment) {
      errors.add_error(
          "Iterator doesn't have implemented operator++() or operator++(int)");
    }

    if (!has_reference_member || !has_value_type_member) {
      errors.add_error(
          "Iterator doesn't have implemented iterator_traits::reference or "
          "iterator_traits::value_type");
    }

    if constexpr (can_pre_increment && has_not_equal_operator) {
      It j{};
      It i{};
      // As "Legacy Iterator" implements increment operator we can get two not
      // equal iterators
      ++i;
      if ((i != j) == false) {
        errors.add_error(
            "Two not equal iterators have to return true with NOT EQUAL "
            "operator");
      }

      if (std::is_convertible_v<decltype((i != j)), bool> == false) {
        errors.add_error(
            "Two not equal iterators have to return implicit convertible to "
            "bool value with NOT EQUAL operator");
      }
    }

    if constexpr (can_pre_increment) {
      if (std::is_same_v<decltype(++std::declval<It&>()), It&> == false) {
        errors.add_error("Iterator have to return It& from operator++()");
      }
    }

    using it_traits = std::iterator_traits<It>;

    if constexpr (is_dereferenceable && can_post_increment &&
                  has_value_type_member) {
      if (std::is_convertible_v<decltype(*(std::declval<It&>()++)),
                                typename it_traits::value_type> == false) {
        errors.add_error(
            "Iterator expression *i++ have to be convertible to "
            "iterator_traits::value_type");
      }
    }

    if constexpr (is_dereferenceable && has_reference_member) {
      if (std::is_same_v<decltype(*std::declval<It>()),
                         typename it_traits::reference> == false) {
        errors.add_error(
            "Iterator have to return iterator_traits::reference from "
            "operator*()");
      }
    }

    if constexpr (is_dereferenceable && has_value_type_member) {
      if (std::is_convertible_v<decltype(*std::declval<It>()),
                                typename it_traits::value_type> == false)
        errors.add_error(
            "operator*() result have to be convertible to "
            "iterator_traits::value_type");
    }

    const bool is_satisfied = !errors.has_errors();
    return std::make_pair(is_satisfied, errors.get_array());
  }
};

#endif  // __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_LEGACY_INPUT_ITERATOR_H
