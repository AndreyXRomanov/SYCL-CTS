/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Provides common code for iterator requirements verifications
//
*******************************************************************************/

#ifndef __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_COMMON_H
#define __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_COMMON_H

#include "../common/common.h"

#include <array>
#include <string_view>
#include <type_traits>
#include <utility>

template <size_t Size>
class error_messages_container {
 private:
  std::array<std::basic_string_view<char>, Size> m_error_msgs_container;
  size_t m_index = 0;
  bool m_has_errors = false;

 public:
  void add_error(const std::string_view msg) {
    if (m_index < Size) {
      m_error_msgs_container[m_index] = msg;
      ++m_index;
    } else {
      m_error_msgs_container[Size - 1] =
          "Size for error_messages_container setted wrong!";
    }
    m_has_errors = true;
  }

  template <size_t N>
  void add_errors(const std::array<std::string_view, N> msgs) {
    for (size_t i = 0; i < msgs.size(); ++i) {
      if (msgs[i] != "") {
        add_error(msgs[i]);
      }
    }
  }

  bool has_errors() const { return m_has_errors; }

  auto get_array() const { return m_error_msgs_container; }
};

#endif  // __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_COMMON_H
