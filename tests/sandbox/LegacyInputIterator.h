// FIXME remove pragma after moving to cts
#pragma once

#include "../common/common.h"

#include "EqualityComparable.h"
#include "LegacyIterator.h"
#include "TypeTraits.h"
#include "common.h"

#include <type_traits>
#include <utility>
#include <vector>

template <typename It>
class legacy_input_iterator_requirement : requirement_verifier {
 public:
  bool check(const std::string& type_name) {
    INFO("Verify named requiremnt Legacy Input Iterator for: " + type_name);
    STATIC_CHECK(!std::is_same_v<It, void>);

    {
      INFO(
          "Iterator have to satisfy Legacy iterator requirement. Testing "
          "type: " +
          type_name);
      verify(legacy_iterator_requirement<It>{}.check(type_name), true);
    }

    constexpr bool is_dereferenceable = type_traits::is_dereferenceable_v<It>;
    constexpr bool can_pre_increment = type_traits::can_pre_increment_v<It>;
    constexpr bool can_post_increment = type_traits::can_post_increment_v<It>;
    constexpr bool has_reference_member =
        type_traits::has_field::reference_v<It>;
    constexpr bool has_value_type_member =
        type_traits::has_field::value_type_v<It>;

    {
      INFO("Iterator have to be dereferenceable");
      verify(is_dereferenceable);
    }
    {
      INFO("Iterator have to implement prefix and postfix increment operator");

      verify(can_pre_increment);
      verify(can_post_increment);
    }
    {
      INFO(
          "Iterator have to implement std::iterator_traits<It>::reference and "
          "std::iterator_traits<It>::value_type");
      verify(has_reference_member);
      verify(has_value_type_member);
    }

    It j{};
    It i{};
    if constexpr (can_pre_increment) {
      INFO(
          "Two not equal iterators have to return true with NOT EQUAL "
          "operator");
      // As "Legacy Iterator" implements increment operator we can get two not
      // equal iterators
      ++i;
      verify((i != j));
      verify(!(i == j));
    }
    {
      INFO(
          "Two not equal iterators have to return implicit convertble to "
          "bool value with NOT EQUAL operator");
      verify(std::is_convertible_v<decltype((i != j)), bool>);
      verify(std::is_convertible_v<decltype(!(i == j)), bool>);
    }

    using it_traits = std::iterator_traits<It>;

    if constexpr (is_dereferenceable && can_post_increment &&
                  has_value_type_member) {
      INFO("Iterator expression *i++ have to be convertble to value_type");
      verify(std::is_convertible_v<decltype(*(std::declval<It>()++)),
                                   typename it_traits::value_type>);
    }
    if constexpr (is_dereferenceable && has_reference_member) {
      INFO(
          "Iterator have to return reference when called dereference "
          "operator");
      verify(std::is_same_v<decltype(*std::declval<It>()),
                            typename it_traits::reference>);
    }
    if constexpr (is_dereferenceable && has_value_type_member) {
      INFO(
          "Iterator dereference result have to be convertble to "
          "value_type");
      verify(std::is_convertible_v<decltype(*std::declval<It>()),
                                   typename it_traits::value_type>);
    }
    return m_verification_result;
  }
};
