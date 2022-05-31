/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Provides functions to verify Legacy random access iterator requirements
//
*******************************************************************************/

#ifndef __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_LEGACY_RANDOM_ACCESS_ITERATOR_H
#define __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_LEGACY_RANDOM_ACCESS_ITERATOR_H

#include "../../util/type_traits.h"
#include "../common/common.h"

#include "LegacyBidirectionalIterator.h"
#include "TypeTraits.h"
#include "common.h"

#include <type_traits>
#include <utility>

template <typename It>
class legacy_random_access_iterator_requirement : requirement_verifier {
 public:
  bool check(It valid_iterator, const size_t container_size,
             const std::string type_name) {
    INFO("Verify named requirement Legacy Random Access Iterator for: " +
         type_name);
    STATIC_CHECK(!std::is_same_v<It, void>);

    {
      INFO(
          "Iterator have to satisfy Legacy bidirectional iterator requirement. "
          "Testing type: " +
          type_name);
      legacy_bidirectional_iterator_requirement<It>{}.check(
          valid_iterator, container_size, type_name);
    }

    using diff_t = typename std::iterator_traits<It>::difference_type;

    constexpr bool has_addition_operator =
        type_traits::compound_assignment::addition_v<It, diff_t>;
    constexpr bool has_subtraction_operator =
        type_traits::compound_assignment::subtraction_v<It, diff_t>;

    constexpr bool has_diff_type_plus_iterator_operator =
        type_traits::has_arithmetic::addition_v<diff_t, It>;
    constexpr bool has_iterator_plus_diff_type_operator =
        type_traits::has_arithmetic::addition_v<It, diff_t>;
    constexpr bool has_iterator_minus_diff_type_operator =
        type_traits::has_arithmetic::subtraction_v<It, diff_t>;
    constexpr bool has_diff_type_minus_iterator_operator =
        type_traits::has_arithmetic::subtraction_v<diff_t, It>;
    constexpr bool has_iterator_minus_iterator_operator =
        type_traits::has_arithmetic::subtraction_v<It, It>;

    constexpr bool has_greater_operator =
        type_traits::has_comparison::greater_than_v<It>;
    constexpr bool has_lower_operator =
        type_traits::has_comparison::less_than_v<It>;
    constexpr bool has_greater_or_equal_operator =
        type_traits::has_comparison::greater_or_equal_v<It>;
    constexpr bool has_lower_or_equal_operator =
        type_traits::has_comparison::less_or_equal_v<It>;
    constexpr bool has_subscript_operator =
        type_traits::has_subscript_operator_v<It>;

    constexpr bool has_reference_member =
        type_traits::has_field::reference_v<It>;
    constexpr bool difference_type =
        type_traits::has_field::difference_type_v<It>;

    {
      INFO("Iterator have append operator");
      verify(has_addition_operator);
    }
    {
      INFO("Iterator have reduce operator");
      verify(has_subtraction_operator);
    }
    {
      INFO("Iterator have difference type plus iterator operator");
      verify(has_diff_type_plus_iterator_operator);
    }
    {
      INFO("Iterator have iterator plus difference type operator");
      verify(has_iterator_plus_diff_type_operator);
    }
    {
      INFO("Iterator iterator minus difference type operator");
      verify(has_iterator_minus_diff_type_operator);
    }
    {
      INFO("Iterator have difference type minus iterator operator");
      verify(has_diff_type_minus_iterator_operator);
    }
    {
      INFO("Iterator iterator minus iterator operator");
      verify(has_iterator_minus_iterator_operator);
    }
    {
      INFO("Iterator have subscript operator");
      verify(has_subscript_operator);
    }

    typename std::iterator_traits<It>::difference_type n = 1;
    if constexpr (has_addition_operator && has_subtraction_operator) {
      INFO(
          "Append and reduce operator should return It& for positive and "
          "negative vales");
      verify(std::is_same_v<decltype(std::declval<It>() += n), It&>);
      verify(std::is_same_v<decltype(std::declval<It>() -= n), It&>);
      verify(std::is_same_v<decltype(std::declval<It>() += -n), It&>);
      verify(std::is_same_v<decltype(std::declval<It>() -= -n), It&>);
    }
    if constexpr (has_diff_type_plus_iterator_operator &&
                  has_iterator_plus_diff_type_operator) {
      {
        INFO(
            "Append and reduce operator should return It& for positive and "
            "negative vales");
        It a{};
        // For positive n
        verify(std::is_same_v<decltype(a + n), It>);
        verify(std::is_same_v<decltype(n + a), It>);
        verify(a + n == n + a);
        // For negative n
        verify(std::is_same_v<decltype(a - n), It>);
        verify(std::is_same_v<decltype(-n + a), It>);
      }
      INFO("It + difference type should be equal to difference type + It");
      It a{};
      verify(a + n == n + a);
    }
    if constexpr (has_iterator_minus_diff_type_operator) {
      INFO(
          "Iterator object minus std::iterator_traits::difference_type should "
          "return iterator data type");
      It a{};
      verify(std::is_same_v<decltype(a - n), It>);
    }
    if (container_size == 0) {
      WARN(
          "Some of the tests requires container size equal to zero, so they "
          "will be skipped");
    } else {
      It a{};
      It b{};
      // If current iterator has iterator plus difference_type make b iterator
      // differ than a iterator
      if constexpr (has_iterator_plus_diff_type_operator) {
        b + n;
      }
      using it_traits = std::iterator_traits<It>;
      if constexpr (has_iterator_minus_iterator_operator && difference_type) {
        INFO(
            "Objects of type It a - b have to return "
            "std::iterator_traits::difference_type");
        verify(std::is_same_v<decltype(a - b),
                              typename it_traits::difference_type>);
      }
      if constexpr (has_subscript_operator && has_reference_member) {
        INFO(
            "Subscript operator result have to be convertible to "
            "std::iterator_traits::reference");
        verify(std::is_convertible_v<decltype(a[0]),
                                     typename it_traits::reference>);
      }
    }
    {
      INFO("Iterator have greater operator");
      verify(has_greater_operator);
    }
    {
      INFO("Iterator have Lower operator");
      verify(has_lower_operator);
    }
    {
      INFO("Iterator have greater or equal operator");
      verify(has_greater_or_equal_operator);
    }
    {
      INFO("Iterator have Lower or equal operator");
      verify(has_lower_or_equal_operator);
    }

    It a{};
    It b{};
    if constexpr (has_greater_operator) {
      INFO("Greater operator result have to contextually convertible to bool");
      verify(std::is_convertible_v<decltype(a > b), bool>);
    }
    if constexpr (has_lower_operator) {
      INFO("Lower operator result have to contextually convertible to bool");
      verify(std::is_convertible_v<decltype(a < b), bool>);
    }
    if constexpr (has_greater_or_equal_operator) {
      INFO(
          "Greater or equal operator result have to contextually convertible "
          "to bool");
      verify(std::is_convertible_v<decltype(a >= b), bool>);
    }
    if constexpr (has_lower_or_equal_operator) {
      INFO(
          "Lower or equal operator result have to contextually convertible to "
          "bool");
      verify(std::is_convertible_v<decltype(a <= b), bool>);
    }

    return m_verification_result;
  }
};

#endif  // __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_LEGACY_RANDOM_ACCESS_ITERATOR_H
