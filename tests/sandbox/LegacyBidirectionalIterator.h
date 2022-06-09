/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Provides class to verify conformity with named requirement
//  LegacyBidirectionalIterator
//
*******************************************************************************/

#ifndef __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_LEGACY_BIDIRECTIONAL_ITERATOR_H
#define __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_LEGACY_BIDIRECTIONAL_ITERATOR_H

#include "LegacyForwardIterator.h"
#include "TypeTraits.h"
#include "common.h"

class legacy_bidirectional_iterator_requirement {
 public:
  static constexpr int count_of_possible_errors =
      legacy_forward_iterator_requirement::count_of_possible_errors + 7;

 private:
  error_messages_container<count_of_possible_errors> errors;

 public:
  template <typename It>
  auto is_satisfied_for(It valid_iterator, const size_t container_size) {
    auto legacy_forward_iterator_res =
        legacy_forward_iterator_requirement{}.is_satisfied_for<It>(
            valid_iterator, container_size);

    if (legacy_forward_iterator_res.first == false) {
      errors.add_errors(legacy_forward_iterator_res.second);
    }

    using it_traits = std::iterator_traits<It>;

    constexpr bool is_dereferenceable = type_traits::is_dereferenceable_v<It>;
    constexpr bool can_pre_increment =
        type_traits::has_arithmetic::pre_increment_v<It>;
    constexpr bool can_post_increment =
        type_traits::has_arithmetic::post_increment_v<It>;
    constexpr bool can_pre_decrement =
        type_traits::has_arithmetic::pre_decrement_v<It>;
    constexpr bool can_post_decrement =
        type_traits::has_arithmetic::post_decrement_v<It>;
    constexpr bool has_reference_member =
        type_traits::has_field::reference_v<It>;
    constexpr bool has_value_type_member =
        type_traits::has_field::value_type_v<It>;

    if constexpr (can_pre_increment && can_pre_decrement) {
      if (std::is_same_v<decltype(--(++std::declval<It&>())), It&> == false) {
        errors.add_error("Iterator expression --(++i) have to return It& type");
      }
    }

    if (container_size == 0) {
      errors.add_error(
          "Some of the test requires container size more than 0. These tests "
          "have been skipped");
    } else {
      if constexpr (can_pre_decrement && can_pre_increment &&
                    is_dereferenceable) {
        {
          It a = valid_iterator;
          It saved_a = a;
          ++a;
          --a;
          if ((a == saved_a) == false) {
            errors.add_error(
                "Iterator expression --(++i) have to be equal to i");
          }
        }
        {
          It a = valid_iterator;
          It b = a;
          ++a;
          ++b;
          if (--a == --b) {
            if ((a == b) == false) {
              errors.add_error("If --a == --b then a == b have to be true");
            }
          } else {
            errors.add_error(
                "--a have to be equal to --b, if they are copy of same object");
          }
        }
      }
    }

    if constexpr (can_pre_decrement) {
      if (std::is_same_v<decltype(--(std::declval<It&>())), It&> == false) {
        errors.add_error(
            "Iterator expression --i have to return It& data type");
      }
    }

    if constexpr (can_post_increment && can_post_decrement &&
                  has_value_type_member) {
      if (std::is_convertible_v<decltype((++std::declval<It&>())--),
                                const It&> == false) {
        errors.add_error(
            "Iterator expression (i++)-- have to be convertible to const It&");
      }
    }

    if constexpr (can_post_decrement && is_dereferenceable &&
                  has_reference_member) {
      if (std::is_same_v<decltype(*(std::declval<It&>()--)),
                         typename it_traits::reference> == false) {
        errors.add_error(
            "Iterator expression *i-- have to return reference data type");
      }
    }

    const bool is_satisfied = !errors.has_errors();
    return std::make_pair(is_satisfied, errors.get_array());
  }
};

#endif  // __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_LEGACY_BIDIRECTIONAL_ITERATOR_H
