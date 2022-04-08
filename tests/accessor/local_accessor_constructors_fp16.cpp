/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Provides sycl::local_accessor test for the sycl::half type
//
*******************************************************************************/
#include "accessor_common.h"
#include "catch2/catch_test_macros.hpp"
#include "local_accessor_constructors.h"

namespace local_accessor_constructors_fp16 {
using namespace local_accessor_constructors;

TEST_CASE("sycl::local_accessor constructors. fp16 type", "[accessor]") {
  auto queue = sycl_cts::util::get_cts_object::queue();
  if (queue.get_device().has(sycl::aspect::fp16)) {
#ifndef SYCL_CTS_ENABLE_FULL_CONFORMANCE
    run_local_constructors_test<sycl::half>{}("sycl::half");
#else
    for_type_vectors_marray<run_local_constructors_test, sycl::half>(
        "sycl::half");
#endif  // SYCL_CTS_ENABLE_FULL_CONFORMANCE
  }
}
}  // namespace local_accessor_constructors_fp16
