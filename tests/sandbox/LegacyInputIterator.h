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

  {
    INFO("Iterator have to be dereferenceable");
    CHECK(type_traits::is_dereferenceable_v<It>);
  }
  {
    INFO("Iterator have to implement prefix and postfix increment operator");
    CHECK(type_traits::can_pre_increment_v<It>);
    CHECK(type_traits::can_post_increment_v<It>);
  }
  {
    INFO(
        "Iterator have to implement std::iterator_traits<It>::reference and "
        "std::iterator_traits<It>::value_type");
    CHECK(type_traits::has_field::reference_v<It>);
    CHECK(type_traits::has_field::value_type_v<It>);
  }

  using reference_t = typename std::iterator_traits<It>::reference;
  using value_t = typename std::iterator_traits<It>::value_type;

  {
    INFO(
        "Two not equal iterators have to return true with NOT EQUAL "
        "operator");
    It j = valid_iterator;
    It i = valid_iterator;

    // Size of container have to be > 1
    if (size_of_container < 2) {
      INFO(
          "Some test requires conteiner size that not lower than 2, so they "
          "will be skipped");
      CHECK(false);
    } else {
      // As "Legacy Iterator" implements increment operator we can get two not
      // equal iterators
      ++i;
      CHECK((i != j));
      CHECK((!(i == j)));
      INFO(
          "Two not equal iterators have to return implicit convertble to "
          "bool value with NOT EQUAL operator");
      CHECK((std::is_convertible_v<decltype((i != j)), bool>));
      CHECK((std::is_convertible_v<decltype((i == j)), bool>));

      if constexpr (type_traits::can_pre_increment_v<It>) {
        INFO(
            "Iterator have to return reference after usage of prefix increment "
            "operator");
        CHECK((std::is_same_v<decltype(++std::declval<It>()), It&>));
      }
      if constexpr (type_traits::is_dereferenceable_v<It> &&
                    type_traits::can_post_increment_v<It> &&
                    type_traits::has_field::value_type_v<It>) {
        INFO("Iterator expression *i++ have to be convertble to value_type");
        CHECK((
            std::is_convertible_v<decltype(*(std::declval<It>()++)), value_t>));
      }
    }
  }
  if constexpr (type_traits::is_dereferenceable_v<It> &&
                type_traits::has_field::reference_v<It>) {
    INFO(
        "Iterator have to return reference when called dereference "
        "operator");
    CHECK((std::is_same_v<decltype(*std::declval<It>()), reference_t>));
  }
  if constexpr (type_traits::is_dereferenceable_v<It> &&
                type_traits::has_field::value_type_v<It>) {
    INFO(
        "Iterator dereference result have to be convertble to "
        "value_type");
    // If i == j and (i, j) is in the domain of == then this is equivalent to *j
    CHECK((std::is_convertible_v<decltype(*std::declval<It>()), value_t>));
  }
}
