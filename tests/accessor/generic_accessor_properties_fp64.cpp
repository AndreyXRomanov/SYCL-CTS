/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Provides tests for generic accessor properties with double type
//
*******************************************************************************/

#include "../common/common.h"

// FIXME: re-enable when sycl::accessor is implemented
#if !defined(__HIPSYCL__) && !defined(__COMPUTECPP__) && \
    !defined(__SYCL_COMPILER_VERSION)
#include "accessor_common.h"
#include "generic_accessor_properties.h"
#endif

#include "../common/disabled_for_test_case.h"
#include "catch2/catch_test_macros.hpp"

namespace generic_accessor_properties_fp64 {

DISABLED_FOR_TEST_CASE(hipSYCL, ComputeCpp, DPCPP)
("Generic sycl::accessor properties test. fp64 type", "[accessor]")({
  using namespace generic_accessor_properties;
  auto queue = sycl_cts::util::get_cts_object::queue();
  if (queue.get_device().has(sycl::aspect::fp16)) {
    const auto types = get_fp16_type();
#ifndef SYCL_CTS_ENABLE_FULL_CONFORMANCE
    run_generic_properties_tests<sycl::half>{}("double");
#else
    for_type_vectors_marray<run_generic_properties_tests, double>("double");
#endif  // SYCL_CTS_ENABLE_FULL_CONFORMANCE
  }
});

}  // namespace generic_accessor_properties_fp64
