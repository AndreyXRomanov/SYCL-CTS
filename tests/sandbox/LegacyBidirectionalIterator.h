// FIXME remove pragma after moving to cts

#pragma once

#include "../common/common.h"

#include "LegacyForwardIterator.h"
#include "TypeTraits.h"
#include "common.h"

#include <type_traits>
#include <utility>

template <typename It>

class legacy_bidirectional_iterator_requirement : requirement_verifier {
 public:
  bool check(It valid_iterator, size_t vector_size,
             const std::string type_name) {
    INFO("Verify named requiremnt Legacy Input Iterator for: " + type_name);
    STATIC_CHECK(!std::is_same_v<It, void>);

    legacy_forward_iterator_requirement<It>{}.check(valid_iterator, vector_size,
                                                    type_name);

    constexpr bool is_dereferenceable = type_traits::is_dereferenceable_v<It>;
    constexpr bool can_pre_increment = type_traits::can_pre_increment_v<It>;
    constexpr bool can_post_increment = type_traits::can_post_increment_v<It>;
    constexpr bool can_pre_decrement = type_traits::can_pre_decrement_v<It>;
    constexpr bool can_post_decrement = type_traits::can_post_decrement_v<It>;
    constexpr bool has_reference_member =
        type_traits::has_field::reference_v<It>;

    if constexpr (can_pre_increment && can_pre_decrement) {
      INFO("Iterator expression --i have to return It& type");

      CHECK((std::is_same_v<decltype(--(++std::declval<It>())), It&>));
    }

    if (vector_size == 0) {
      WARN(
          "Some of the tests requires container size that not lower than 2, so "
          "they will be skipped");
    } else {
      if constexpr (type_traits::is_dereferenceable_v<It>) {
        It a = valid_iterator;
        It b = a;
        {
          INFO(
              "Iterator expression i++ have to be the same type as provided "
              "itrator's type");
          CHECK(--(++a) == a);
        }
        ++a;
        ++b;
        if (--a == --b) {
          INFO("If '--a' == '--b' then 'a' == 'b'");
          CHECK(a == b);
        }
      }
    }
    {
      INFO("Verify that 'a' and '--a' designate the same iterator object");
      CHECK(std::is_same_v<decltype(--std::declval<It>()), It>);
    }

    if constexpr (can_post_increment && can_post_decrement) {
      INFO("Iterator expression *i++ have to be convertble to value_type");
      CHECK((std::is_convertible_v<decltype((++std::declval<It>())--),
                                   const It&>));
    }

    if constexpr (can_post_decrement && is_dereferenceable &&
                  has_reference_member) {
      INFO("Iterator expression *i++ have to be convertble to value_type");
      CHECK((std::is_same_v<decltype(*(std::declval<It>()--)),
                            typename std::iterator_traits<It>::reference>));
    }

    return m_verification_result;
  }
};