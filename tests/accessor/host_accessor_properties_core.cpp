/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Provides tests for host_accessor properties with generic types
//
*******************************************************************************/
#include "accessor_common.h"
#include "catch2/catch_test_macros.hpp"
#include "host_accessor_properties.hpp"

namespace host_accessor_properties_core {
using namespace host_accessor_properties;

TEST_CASE("sycl::host_accessor properties. core types", "[accessor]") {
#ifndef SYCL_CTS_ENABLE_FULL_CONFORMANCE
  const auto types = get_lightweight_type_pack();
#else
  const auto types = get_full_conformance_type_pack();
#endif  // SYCL_CTS_ENABLE_FULL_CONFORMANCE
  for_all_types_vectors_marray<run_host_properties_tests>(types);
}

}  // namespace host_accessor_properties_core
