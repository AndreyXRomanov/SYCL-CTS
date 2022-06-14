/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Provides host_accessor constructors test for the double type
//
*******************************************************************************/

#include "../common/common.h"

// FIXME: re-enable when sycl::host_accessor is implemented
#if !defined(__HIPSYCL__) && !defined(__COMPUTECPP__) && \
    !defined(__SYCL_COMPILER_VERSION)
#include "accessor_common.h"
#include "host_accessor_constructors.h"
#endif

#include "../common/disabled_for_test_case.h"
#include "catch2/catch_test_macros.hpp"

namespace host_accessor_constructors_fp64 {

DISABLED_FOR_TEST_CASE(hipSYCL, ComputeCpp, DPCPP)
("sycl::host_accessor constructors. fp64 type", "[accessor]")({
  using namespace host_accessor_constructors;
  auto queue = sycl_cts::util::get_cts_object::queue();
#ifndef SYCL_CTS_ENABLE_FULL_CONFORMANCE
  run_host_constructors_test<double>{}("double");
#else
  for_type_vectors_marray<run_host_constructors_test, double>("double");
#endif  // SYCL_CTS_ENABLE_FULL_CONFORMANCE
})
}  // namespace host_accessor_constructors_fp64
