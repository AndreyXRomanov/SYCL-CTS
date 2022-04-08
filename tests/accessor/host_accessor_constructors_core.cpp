/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Provides host_accessor constructors test for generic types
//
*******************************************************************************/
#include "accessor_common.h"
#include "catch2/catch_test_macros.hpp"
#include "host_accessor_constructors.h"

namespace host_accessor_constructors_core {
using namespace host_accessor_constructors;

TEST_CASE("sycl::host_accessor constructors. core types", "[accessor]") {
#ifndef SYCL_CTS_ENABLE_FULL_CONFORMANCE
  const auto types = get_lightweight_type_pack();
#else
  const auto types = get_full_conformance_type_pack();
#endif  // SYCL_CTS_ENABLE_FULL_CONFORMANCE
  for_all_types_vectors_marray<run_host_constructors_test>(types);
}

}  // namespace host_accessor_constructors_core
