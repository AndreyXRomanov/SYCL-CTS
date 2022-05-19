// FIXME remove pragma after moving to cts
#pragma once

#include "../common/common.h"

#include "EqualityComparable.h"
#include "LegacyIterator.h"
#include "TypeTraits.h"

#include <type_traits>
#include <utility>
#include <vector>

template <typename It>
void check_legacy_input_iterator_requirement(It valid_iterator,
                                             const size_t size_of_container,
                                             const std::string& type_name) {
  INFO("Verify named requiremnt Legacy Input Iterator for: " + type_name);
  STATIC_CHECK(!std::is_same_v<It, void>);

  check_legacy_iterator_requirement(valid_iterator, size_of_container,
                                    type_name);
  check_equality_comparable_requirement(valid_iterator, type_name);

  constexpr bool is_dereferenceable = type_traits::is_dereferenceable_v<It>;
  constexpr bool can_pre_increment = type_traits::can_pre_increment_v<It>;
  constexpr bool can_post_increment = type_traits::can_post_increment_v<It>;
  constexpr bool has_reference_t = type_traits::has_field::reference_v<It>;
  constexpr bool has_value_type_t = type_traits::has_field::value_type_v<It>;

  {
    INFO("Iterator have to be dereferenceable");
    CHECK(is_dereferenceable);
  }
  {
    INFO("Iterator have to implement prefix and postfix increment operator");
    CHECK(can_pre_increment);
    CHECK(can_post_increment);
  }
  {
    INFO(
        "Iterator have to implement std::iterator_traits<It>::reference and "
        "std::iterator_traits<It>::value_type");
    CHECK(has_reference_t);
    CHECK(has_value_type_t);
  }

  // Size of container have to be > 1
  if (size_of_container < 2) {
    WARN(
        "Some of the tests requires container size that not lower than 2, so "
        "they will be skipped");
  } else {
    It j = valid_iterator;
    It i = valid_iterator;
    if constexpr (can_pre_increment) {
      INFO(
          "Two not equal iterators have to return true with NOT EQUAL "
          "operator");
      // As "Legacy Iterator" implements increment operator we can get two not
      // equal iterators
      ++i;
      CHECK((i != j));
      CHECK((!(i == j)));
    }
    {
      INFO(
          "Two not equal iterators have to return implicit convertble to "
          "bool value with NOT EQUAL operator");
      CHECK((std::is_convertible_v<decltype((i != j)), bool>));
      CHECK((std::is_convertible_v<decltype(!(i == j)), bool>));
    }
  }

  if constexpr (can_pre_increment) {
    INFO(
        "Iterator have to return reference after usage of prefix increment "
        "operator");
    CHECK((std::is_same_v<decltype(++std::declval<It>()), It&>));
  }
  
  using it_traits = std::iterator_traits<It>;

  if constexpr (is_dereferenceable && can_post_increment && has_value_type_t) {
    INFO("Iterator expression *i++ have to be convertble to value_type");
    CHECK((std::is_convertible_v<decltype(*(std::declval<It>()++)),
                                 typename it_traits::value_type>));
  }
  if constexpr (is_dereferenceable && has_reference_t) {
    INFO(
        "Iterator have to return reference when called dereference "
        "operator");
    CHECK((std::is_same_v<decltype(*std::declval<It>()),
                          typename it_traits::reference>));
  }
  if constexpr (is_dereferenceable && has_value_type_t) {
    INFO(
        "Iterator dereference result have to be convertble to "
        "value_type");
    CHECK((std::is_convertible_v<decltype(*std::declval<It>()),
                                 typename it_traits::value_type>));
  }
}
