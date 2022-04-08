/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Provides tests for sycl::local_accessor constructors
//
*******************************************************************************/
#ifndef SYCL_CTS_LOCAL_ACCESSOR_H
#define SYCL_CTS_LOCAL_ACCESSOR_H
#include "catch2/catch_test_macros.hpp"

#include "accessor_common.h"

namespace local_accessor_constructors {
using namespace sycl_cts;
using namespace accessor_tests_common;

constexpr accessor_type AccTypeT = accessor_type::local_accessor;

template <typename DataT, int DimensionT>
void test_default_constructor(const std::string& type_name) {
  const auto section_name =
      get_section_name<DimensionT>(type_name, "Default constructor");

  SECTION(section_name) {
    auto get_acc_functor = [](){
      return sycl_stub::local_accessor<DataT, DimensionT>();
    };
    check_def_constructor<AccTypeT, DataT, DimensionT,
                          sycl::access_mode::read_write,
                          sycl_stub::target::device>(get_acc_functor);
  }
}

template <typename DataT>
void test_zero_dimension_buffer_constructor(const std::string& type_name) {
  const auto section_name =
      get_section_name<0>(type_name, "Zero dimension constructor");

  SECTION(section_name) {
    auto get_acc_functor =
        [](sycl::buffer<DataT, 1> & data_buf, sycl::handler & cgh){
      return sycl_stub::local_accessor<DataT, 0>(cgh);
    };
    check_zero_dim_constructor<AccTypeT, DataT, sycl::access_mode::read_write,
                               sycl_stub::target::device>(get_acc_functor);
  }
}

template <typename DataT, int DimensionT>
void test_common_constructors(const std::string& type_name) {
  auto r = util::get_cts_object::range<DimensionT>::get(1, 1, 1);
  auto offset = sycl::id<DimensionT>();

  auto section_name =
      get_section_name<DimensionT>(type_name, "From sycl::range constructor");

  SECTION(section_name) {
    auto get_acc_functor = [r](
        sycl::buffer<DataT, DimensionT> & data_buf,
        sycl::handler & cgh){
      return sycl_stub::local_accessor<DataT, DimensionT>(r, cgh);
    };
    check_common_constructor<AccTypeT, DataT, DimensionT,
                             sycl::access_mode::read_write,
                             sycl_stub::target::device>(get_acc_functor);
  }
}

template <typename T, typename DimensionTypeT>
class run_tests_constructors {
  static constexpr int DimensionT = DimensionTypeT::value;

 public:
  void operator()(const std::string& type_name) {
    test_zero_dimension_buffer_constructor<T>(type_name);
    test_default_constructor<T, DimensionT>(type_name);
    test_common_constructors<T, DimensionT>(type_name);
  }
};

template <typename T>
class run_local_constructors_test {
 public:
  void operator()(const std::string& type_name) {
    // Type packs instances have to be const, otherwise for_all_combination will
    // not compile
    const auto dimensions = get_dimensions();
    const auto cur_type =
        named_type_pack<T>::generate(type_name_string<T>::get(type_name));

    for_all_combinations<run_tests_constructors>(cur_type, dimensions);
  }
};
}  // namespace local_accessor_constructors
#endif  // SYCL_CTS_LOCAL_ACCESSOR_H
