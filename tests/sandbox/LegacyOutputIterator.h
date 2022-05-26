/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Provides functions to verify Legacy output iterator requirements
//
*******************************************************************************/

#ifndef __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_LEGACY_OUTPUT_ITERATOR_H
#define __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_LEGACY_OUTPUT_ITERATOR_H

#include "../common/common.h"

#include "EqualityComparable.h"
#include "LegacyIterator.h"
#include "TypeTraits.h"
#include "common.h"

#include <type_traits>
#include <utility>
#include <vector>

template <typename It>
class legacy_output_iterator_requirement : requirement_verifier {
 public:
  bool check(const std::string type_name, bool silence_output = false) {
    INFO("Verify named requirement Legacy Output Iterator for: " + type_name);

    STATIC_CHECK(!std::is_same_v<It, void>);
    {
      INFO(
          "Iterator have to satisfy Legacy iterator requirement. Testing "
          "type: " +
          type_name);
      verify(legacy_iterator_requirement<It>{}.check(type_name), true);
    }

    constexpr bool is_dereferenceable = type_traits::is_dereferenceable_v<It>;
    constexpr bool can_pre_increment =
        type_traits::has_arithmetic::pre_increment_v<It>;
    constexpr bool can_post_increment =
        type_traits::has_arithmetic::post_increment_v<It>;
    constexpr bool has_value_type_member =
        type_traits::has_field::value_type_v<It>;

    {
      INFO("Iterator have to be dereferenceable");
      verify(is_dereferenceable, silence_output);
    }
    {
      INFO("Iterator have to implement prefix and postfix increment operator");
      verify(can_pre_increment, silence_output);
      verify(can_post_increment, silence_output);
    }
    {
      INFO("Iterator have to implement std::iterator_traits<It>::value_type");
      verify(has_value_type_member, silence_output);
    }

    using it_traits = std::iterator_traits<It>;

    if constexpr (has_value_type_member && is_dereferenceable) {
      INFO("Dereferenced iterator have to be assignable with value_t");
      verify(std::is_assignable_v<decltype(*std::declval<It>()),
                                  typename it_traits::value_type>,
             silence_output);
    }

    if constexpr (can_pre_increment) {
      {
        INFO(
            "Iterator have to return reference after usage of prefix "
            "increment "
            "operator");
        verify(std::is_same_v<decltype(++std::declval<It>()), It &>,
               silence_output);
      }
      {
        INFO("Iterator have to be convertible to const It after increment");
        verify(std::is_convertible_v<decltype(++std::declval<It>()), const It>,
               silence_output);
      }
    }

    if constexpr (can_post_increment && is_dereferenceable &&
                  has_value_type_member) {
      INFO(
          "Iterator have to be assignable with value_t after increment and "
          "dereferencing");
      verify(std::is_assignable_v<decltype(*(std::declval<It>()++)),
                                  typename it_traits::value_type>,
             silence_output);
    }

    if constexpr (is_dereferenceable && has_value_type_member) {
      INFO("Iterator have to be assignable with value_t after dereferencing");
      verify(std::is_assignable_v<decltype(*std::declval<It>()),
                                  typename it_traits::value_type>,
             silence_output);
    }

    return m_verification_result;
  }
};

#endif  // __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_LEGACY_OUTPUT_ITERATOR_H
