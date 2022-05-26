/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Provides functions to verify Legacy iterator requirements
//
*******************************************************************************/

#ifndef __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_LEGACY_ITERATOR_H
#define __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_LEGACY_ITERATOR_H

#include "../common/common.h"

#include "TypeTraits.h"
#include "common.h"

#include <chrono>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

template <typename It>
class legacy_iterator_requirement : requirement_verifier {
 public:
  bool check(const std::string& type_name) {
    INFO("Verify named requiremnt Legacy Iterator: " + type_name);
    STATIC_CHECK(!std::is_same_v<It, void>);
    {
      INFO("Iterator have to be copy constructble");
      verify(std::is_copy_constructible_v<It>);
    }
    {
      INFO("Iterator have to be copy assignble");
      verify(std::is_copy_assignable_v<It>);
    }
    {
      INFO("Iterator have to be destrcutble");
      verify(std::is_destructible_v<It>);
    }
    {
      INFO("Iterator have to be swappable");
      verify(std::is_swappable_v<It>);
    }
    {
      INFO("Iterator have to have value_type member typedef");
      verify(type_traits::has_field::value_type_v<It>);
    }
    {
      INFO("Iterator have to have difference_type member typedef");
      verify(type_traits::has_field::difference_type_v<It>);
    }
    {
      INFO("Iterator have to have reference member typedef");
      verify(type_traits::has_field::reference_v<It>);
    }
    {
      INFO("Iterator have to have pointer member typedef");
      verify(type_traits::has_field::pointer_v<It>);
    }
    {
      INFO("Iterator have to have iterator_category member typedef");
      verify(type_traits::has_field::iterator_category_v<It>);
    }
    {
      INFO("Iterator have to implement prefix increment operator");
      verify(type_traits::has_arithmetic::pre_increment_v<It>);
    }
    if constexpr (type_traits::has_arithmetic::pre_increment_v<It>) {
      INFO("Have to return reference after using prefix increment operator");
      verify(std::is_same_v<decltype(++std::declval<It>()), It&>);
    }
    {
      INFO("Iterator have to be dereferenceble");
      verify(type_traits::is_dereferenceable_v<It>);
    }

    return m_verification_result;
  }
};

#endif  // __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_LEGACY_ITERATOR_H
