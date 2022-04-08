/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Provides tests for generic accessor properties with generic types
//
*******************************************************************************/
#include "accessor_common.h"
#include "catch2/catch_test_macros.hpp"
#include "generic_accessor_properties.hpp"

namespace generic_accessor_constructors_core {
using namespace generic_accessor_properties;

TEST_CASE("Generic sycl::accessor properties test. core types", "[accessor]") {
#ifndef SYCL_CTS_ENABLE_FULL_CONFORMANCE
  const auto types = get_lightweight_type_pack();
#else
  const auto types = get_full_conformance_type_pack();
#endif  // SYCL_CTS_ENABLE_FULL_CONFORMANCE
  for_all_types_vectors_marray<run_generic_properties_tests>(types);
}

}  // namespace generic_accessor_constructors_core
