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
class legacy_output_iterator_requirement : requirement_verifier {
 public:
  bool check(const std::string type_name) {
    INFO("Verify named requirement Legacy Output Iterator for: " + type_name);

    STATIC_CHECK(!std::is_same_v<It, void>);
    {
      INFO(
          "Iterator have to satisfy Legacy iterator requirement. Testing "
          "type: " +
          type_name);
      verify(legacy_iterator_requirement<It>{}.check(type_name), true);
    }

    {
      INFO("Iterator have to be dereferenceable");
      verify(type_traits::is_dereferenceable_v<It>);
    }
    {
      INFO("Iterator have to implement prefix and postfix increment operator");
      verify(type_traits::can_pre_increment_v<It>);
      verify(type_traits::can_post_increment_v<It>);
    }

    constexpr bool precondition = type_traits::is_dereferenceable_v<It> &&
                                  type_traits::can_pre_increment_v<It> &&
                                  type_traits::can_post_increment_v<It>;

    if constexpr (precondition) {
      using value_t = typename std::iterator_traits<It>::value_type;

      {
        INFO("Dereferenced iterator have to be assignble with value_t");
        verify(std::is_assignable_v<decltype(*std::declval<It>()), value_t>);
      }

      {
        INFO(
            "Iterator have to return reference after usage of prefix increment "
            "operator");
        verify(std::is_same_v<decltype(++std::declval<It>()), It &>);
      }

      {
        INFO("Iterator have to be convertble to const It after increment");
        verify(std::is_convertible_v<decltype(++std::declval<It>()), const It>);
      }

      {
        INFO(
            "Iterator have to be assignable with value_t after increment and "
            "dereferencing");
        verify(
            std::is_assignable_v<decltype(*(std::declval<It>()++)), value_t>);
      }
      {
        INFO("Iterator have to be assignable with value_t after dereferencing");
        verify(std::is_assignable_v<decltype(*std::declval<It>()), value_t>);
      }
    }
    return _verification_result;
  }
};
