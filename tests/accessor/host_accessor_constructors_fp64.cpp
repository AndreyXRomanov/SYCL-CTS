/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Provides host_accessor constructors test for the double type
//
*******************************************************************************/
#include "accessor_common.h"
#include "catch2/catch_test_macros.hpp"
#include "host_accessor_constructors.h"

namespace host_accessor_constructors_fp64 {
using namespace host_accessor_constructors;

TEST_CASE("sycl::host_accessor constructors. fp64 type", "[accessor]") {
  auto queue = sycl_cts::util::get_cts_object::queue();
#ifndef SYCL_CTS_ENABLE_FULL_CONFORMANCE
    run_host_constructors_test<double>{}("double");
#else
    for_type_vectors_marray<run_host_constructors_test, double>("double");
#endif  // SYCL_CTS_ENABLE_FULL_CONFORMANCE
}
}  // namespace accessor_buffer_constructors_fp64
