/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Provides tests for generic accessor properties with sycl::half type
//
*******************************************************************************/
#include "accessor_common.h"
#include "catch2/catch_test_macros.hpp"
#include "generic_accessor_properties.hpp"

namespace generic_accessor_constructors_fp16 {
using namespace generic_accessor_properties;

TEST_CASE("Generic sycl::accessor properties test. fp16 type", "[accessor]") {
  auto queue = sycl_cts::util::get_cts_object::queue();
  if (queue.get_device().has(sycl::aspect::fp16)) {
    const auto types = get_fp16_type();
#ifndef SYCL_CTS_ENABLE_FULL_CONFORMANCE
    run_generic_properties_tests<sycl::half>{}("sycl::half");
#else
    for_type_vectors_marray<run_generic_properties_tests, sycl::half>(
        "sycl::half");
#endif  // SYCL_CTS_ENABLE_FULL_CONFORMANCE
  }
}

}  // namespace generic_accessor_constructors_fp16
