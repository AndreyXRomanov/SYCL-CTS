/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Provides tests for host_accessor properties with sycl::half type
//
*******************************************************************************/
#include "accessor_common.h"
#include "catch2/catch_test_macros.hpp"
#include "host_accessor_properties.hpp"

namespace host_accessor_properties_fp16 {
using namespace host_accessor_properties;

TEST_CASE("sycl::host_accessor properties. fp16 type", "[accessor]") {
  auto queue = sycl_cts::util::get_cts_object::queue();
#ifndef SYCL_CTS_ENABLE_FULL_CONFORMANCE
  run_host_properties_tests<sycl::half>{}("sycl::half");
#else
  for_type_vectors_marray<run_host_properties_tests, sycl::half>("sycl::half");
#endif  // SYCL_CTS_ENABLE_FULL_CONFORMANCE
}
}  // namespace host_accessor_properties_fp16
