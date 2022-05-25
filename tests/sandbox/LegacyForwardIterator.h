// FIXME remove pragma after moving to cts

#pragma once

#include "../common/common.h"

#include "LegacyInputIterator.h"
#include "LegacyOutputIterator.h"
#include "TypeTraits.h"
#include "common.h"

#include <type_traits>
#include <utility>

template <typename It>
class legacy_forward_iterator_requirement : requirement_verifier {
 public:
  bool check(It valid_iterator, const size_t container_size,
             const std::string& type_name) {
    INFO("Verify named requiremnt Legacy Input Iterator for: " + type_name);
    STATIC_CHECK(!std::is_same_v<It, void>);

    {
      INFO(
          "Iterator have to satisfy Legacy input iterator requirement. Testing "
          "type: " +
          type_name);
      constexpr bool silent_output = true;
      verify(legacy_input_iterator_requirement<It>{}.check(type_name),
             silent_output);
    }

    {
      INFO("Iterator have to be default constructible");
      verify(std::is_default_constructible_v<It>);
    }

    using it_traits = std::iterator_traits<It>;

    constexpr bool is_dereferenceable = type_traits::is_dereferenceable_v<It>;
    constexpr bool can_post_increment = type_traits::can_post_increment_v<It>;
    constexpr bool has_reference_member =
        type_traits::has_field::reference_v<It>;
    constexpr bool has_value_type_member =
        type_traits::has_field::value_type_v<It>;
    constexpr bool is_equality_comparable =
        type_traits::is_equality_comparable_v<It>;
    constexpr bool can_pre_increment = type_traits::can_pre_increment_v<It>;

    // Allows us to use reference_t from iterator_traits
    if constexpr (has_reference_member) {
      INFO("Verify optional legacy iterator requirements");
      // Required silent output because this is an optional requirement, so
      // verification on legacy_output_iterator_requirement could fail without
      // any error messages
      constexpr bool silent_output = true;
      if (legacy_output_iterator_requirement<It>{}.check(type_name,
                                                         silent_output)) {
        INFO(
            "Provided iterator satisfied to legacy output iterator "
            "requirements. Verify that iterator reference is non const");
        verify(!std::is_const_v<typename it_traits::reference>);
      } else {
        INFO(
            "Provided iterator satisfied to legacy output iterator "
            "requirements. Verify that iterator reference is const");
        verify(std::is_const_v<typename it_traits::reference>);
      }
    }

    if constexpr (can_post_increment && is_dereferenceable) {
      INFO(
          "Iterator expression i++ have to be the same type as provided "
          "iterator's type");
      verify((std::is_same_v<decltype(std::declval<It>()++), It>));
    }
    if constexpr (can_post_increment && is_dereferenceable &&
                  has_value_type_member) {
      INFO("Iterator expression *i++ have to be convertble to value_type");
      verify((std::is_convertible_v<decltype(*(std::declval<It>()++)),
                                    typename it_traits::value_type>));
    }

    if (container_size > 0) {
      WARN(
          "Some of the tests requires container size that not greater than 0, "
          "so they will be skipped");
    } else {
      // Verify multipass guarantee
      if constexpr (is_equality_comparable && is_dereferenceable &&
                    can_pre_increment) {
        {
          It a = valid_iterator;
          It b = valid_iterator;
          {
            INFO(
                "If a and b compare equal (a == b) then *a and *b "
                "are references bound to the same object");
            verify(*a == *b);
          }
          {
            INFO("If *a and *b refer to the same object, then a == b");
            verify(a == b);
          }
          {
            INFO("a == b implies ++a == ++b");
            verify(++a == ++b);
          }
        }

        if constexpr (has_value_type_member) {
          // Allows us to compare values without compilation error
          constexpr bool is_value_type_comparable =
              type_traits::is_equality_comparable_v<
                  typename it_traits::value_type>;

          if constexpr (is_dereferenceable && can_pre_increment &&
                        is_value_type_comparable) {
            INFO(
                "Incrementing a copy of a does not change the value read "
                "from a");
            const auto zero_pos_value = *valid_iterator;
            It zero_pos_it = valid_iterator;
            ++zero_pos_it;
            verify(zero_pos_value == *valid_iterator);
          }
        }
      }
    }
    return m_verification_result;
  }
};
