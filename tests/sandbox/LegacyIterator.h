/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Provides class to verify conformity with named requirement LegacyIterator
//
*******************************************************************************/

#ifndef __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_LEGACY_ITERATOR_H
#define __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_LEGACY_ITERATOR_H

#include "TypeTraits.h"
#include "common.h"

class legacy_iterator_requirement {
 public:
  static constexpr size_t count_of_possible_errors = 12;

 private:
  error_messages_container<count_of_possible_errors> errors;

 public:
  template <typename It>
  auto is_satisfied_for() {
    if (std::is_copy_constructible_v<It> == false) {
      errors.add_error("Iterator have to be copy constructable");
    }

    if (std::is_copy_assignable_v<It> == false) {
      errors.add_error("Iterator have to be copy assignable");
    }

    if (std::is_destructible_v<It> == false) {
      errors.add_error("Iterator have to be destructible");
    }

    if (std::is_swappable_v<It> == false) {
      errors.add_error("Iterator have to be swappable");
    }

    if (type_traits::has_field::value_type_v<It> == false) {
      errors.add_error("Iterator doesn't have value_type member typedef");
    }

    if (type_traits::has_field::difference_type_v<It> == false) {
      errors.add_error("Iterator doesn't have difference_type member typedef");
    }

    if (type_traits::has_field::reference_v<It> == false) {
      errors.add_error("Iterator doesn't have reference member typedef");
    }

    if (type_traits::has_field::pointer_v<It> == false) {
      errors.add_error("Iterator doesn't have pointer member typedef");
    }

    if (type_traits::has_field::iterator_category_v<It> == false) {
      errors.add_error(
          "Iterator doesn't have iterator_category member typedef");
    }

    if (type_traits::has_arithmetic::pre_increment_v<It> == false) {
      errors.add_error("Iterator doesn't have implemented operator++()");
    }

    if constexpr (type_traits::has_arithmetic::pre_increment_v<It>) {
      if (std::is_same_v<decltype(++std::declval<It>()), It&> == false) {
        errors.add_error(
            "Iterator have to return It& after useage of operator++()");
      }
    }

    if (type_traits::is_dereferenceable_v<It> == false) {
      errors.add_error("Iterator doesn't have implemented operator*()");
    }

    const bool is_satisfied = !errors.has_errors();
    return std::make_pair(is_satisfied, errors.get_array());
  }
};

#endif  // __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_LEGACY_ITERATOR_H
