/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Provides sycl::local_accessor constructors test for generic types
//
*******************************************************************************/
#include "accessor_common.h"
#include "catch2/catch_test_macros.hpp"
#include "local_accessor_constructors.h"

namespace local_accessor_constructors_core {
using namespace local_accessor_constructors;

TEST_CASE("sycl::local_accessor constructors. core types", "[accessor]") {
#ifndef SYCL_CTS_ENABLE_FULL_CONFORMANCE
  const auto types = get_lightweight_type_pack();
#else
  const auto types = get_full_conformance_type_pack();
#endif  // SYCL_CTS_ENABLE_FULL_CONFORMANCE
  for_all_types_vectors_marray<run_local_constructors_test>(types);
}

}  // namespace local_accessor_constructors_core
