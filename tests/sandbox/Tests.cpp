#include "../common/common.h"
#include "../common/disabled_for_test_case.h"
#include <iostream>
#include <vector>

#include "EqualityComparable.h"
#include "LegacyBidirectionalIterator.h"
#include "LegacyForwardIterator.h"
#include "LegacyInputIterator.h"
#include "LegacyIterator.h"
#include "LegacyOutputIterator.h"
#include "LegacyRandomAccessIterator.h"

#include "user_defined_iterators.h"

class EqualOpImplemented {
 public:
  bool operator==(const EqualOpImplemented&) const { return true; }
};
class EqualOpNotImplemented {
 public:
  bool operator==(const EqualOpImplemented&) = delete;
};

using vec_it = std::vector<int>::iterator;

TEST_CASE("Equal operator") {
  CHECK_FALSE(type_traits::has_comparison::is_equal_v<EqualOpNotImplemented>);
  CHECK(type_traits::has_comparison::is_equal_v<EqualOpImplemented>);
  CHECK(type_traits::has_comparison::is_equal_v<vec_it>);
}

TEST_CASE("Equality comparable check") {
  std::vector v{1, 2, 3, 4, 5};
  // equality_comparable_requirement<vec_it>{}.check("vector<int>::iterator");
}

TEST_CASE("Legacy iterator check") {
  SECTION("std::vector iterator") {
    auto res = legacy_iterator_requirement{}.is_satisfied_for<vec_it>();
    if (!res.first) {
      for (size_t i = 0; i < res.second.size(); ++i) {
        const bool requirement_not_satisfied = false;
        if (res.second[i] != "") {
          INFO(res.second[i]);
          CHECK(requirement_not_satisfied);
        }
      }
    }
  }
  SECTION("user-defined iterator") {
    auto res = legacy_iterator_requirement{}.is_satisfied_for<LegacyIterator>();
    if (!res.first) {
      for (size_t i = 0; i < res.second.size(); ++i) {
        const bool requirement_not_satisfied = false;
        if (res.second[i] != "") {
          INFO(res.second[i]);
          CHECK(requirement_not_satisfied);
        }
      }
    }
  }
}

TEST_CASE("Legacy input iterator check") {
  SECTION("std::vector iterator") {
    auto res = legacy_input_iterator_requirement{}.is_satisfied_for<vec_it>();
    if (!res.first) {
      for (size_t i = 0; i < res.second.size(); ++i) {
        const bool requirement_not_satisfied = false;
        if (res.second[i] != "") {
          INFO(res.second[i]);
          CHECK(requirement_not_satisfied);
        }
      }
    }
  }
  SECTION("user-defined iterator") {
    auto res = legacy_input_iterator_requirement{}
                   .is_satisfied_for<LegacyInputIterator>();
    if (!res.first) {
      for (size_t i = 0; i < res.second.size(); ++i) {
        const bool requirement_not_satisfied = false;
        if (res.second[i] != "") {
          INFO(res.second[i]);
          CHECK(requirement_not_satisfied);
        }
      }
    }
  }
}

TEST_CASE("Legacy output iterator check") {
  SECTION("std::vector iterator") {
    auto res = legacy_output_iterator_requirement{}.is_satisfied_for<vec_it>();
    if (!res.first) {
      for (size_t i = 0; i < res.second.size(); ++i) {
        const bool requirement_not_satisfied = false;
        if (res.second[i] != "") {
          INFO(res.second[i]);
          CHECK(requirement_not_satisfied);
        }
      }
    }
  }
  SECTION("user-defined iterator") {
    auto res = legacy_output_iterator_requirement{}
                   .is_satisfied_for<LegacyOutputIterator>();
    if (!res.first) {
      for (size_t i = 0; i < res.second.size(); ++i) {
        const bool requirement_not_satisfied = false;
        if (res.second[i] != "") {
          INFO(res.second[i]);
          CHECK(requirement_not_satisfied);
        }
      }
    }
  }
}

TEST_CASE("Legacy forward iterator check") {
  SECTION("std::vector iterator") {
    std::vector v{1, 2, 3, 4, 5};
    auto res = legacy_forward_iterator_requirement{}.is_satisfied_for<vec_it>(
        v.begin(), v.size());
    if (!res.first) {
      for (size_t i = 0; i < res.second.size(); ++i) {
        const bool requirement_not_satisfied = false;
        if (res.second[i] != "") {
          INFO(res.second[i]);
          CHECK(requirement_not_satisfied);
        }
      }
    }
  }
  SECTION("user-defined iterator") {
    LegacyForwardIterator v1{1, 2, 3, 4, 5};
    auto res = legacy_forward_iterator_requirement{}
                   .is_satisfied_for<LegacyForwardIterator>(v1, v1.size());
    if (!res.first) {
      for (size_t i = 0; i < res.second.size(); ++i) {
        const bool requirement_not_satisfied = false;
        if (res.second[i] != "") {
          INFO(res.second[i]);
          CHECK(requirement_not_satisfied);
        }
      }
    }
  }
}

TEST_CASE("Legacy bidirectional iterator check") {
  SECTION("std::vector iterator") {
    std::vector v{1, 2, 3, 4, 5};
    auto res =
        legacy_bidirectional_iterator_requirement{}.is_satisfied_for<vec_it>(
            v.begin(), v.size());
    if (!res.first) {
      for (size_t i = 0; i < res.second.size(); ++i) {
        const bool requirement_not_satisfied = false;
        if (res.second[i] != "") {
          INFO(res.second[i]);
          CHECK(requirement_not_satisfied);
        }
      }
    }
  }
  SECTION("user-defined iterator") {
    LegacyBidirectionalIterator v1{1, 2, 3, 4, 5};
    auto res =
        legacy_bidirectional_iterator_requirement{}
            .is_satisfied_for<LegacyBidirectionalIterator>(v1, v1.size());
    if (!res.first) {
      for (size_t i = 0; i < res.second.size(); ++i) {
        const bool requirement_not_satisfied = false;
        if (res.second[i] != "") {
          INFO(res.second[i]);
          CHECK(requirement_not_satisfied);
        }
      }
    }
  }
}

TEST_CASE("Legacy random access iterator check") {
  SECTION("std::vector iterator") {
    std::vector v{1, 2, 3, 4, 5};
    auto res = legacy_random_access_iterator_requirement{}.is_satisfied_for(
        v.begin(), v.size());
    if (!res.first) {
      for (size_t i = 0; i < res.second.size(); ++i) {
        const bool requirement_not_satisfied = false;
        if (res.second[i] != "") {
          INFO(res.second[i]);
          CHECK(requirement_not_satisfied);
        }
      }
    }
  }
  SECTION("user-defined iterator") {
    LegacyRandomAccessIterator v1{1, 2, 3, 4, 5};
    auto res = legacy_random_access_iterator_requirement{}
                   .is_satisfied_for<LegacyRandomAccessIterator>(v1, v1.size());
    if (!res.first) {
      for (size_t i = 0; i < res.second.size(); ++i) {
        const bool requirement_not_satisfied = false;
        if (res.second[i] != "") {
          INFO(res.second[i]);
          CHECK(requirement_not_satisfied);
        }
      }
    }
  }
}

DISABLED_FOR_TEST_CASE(ComputeCpp)
("Testing in kernel")({
  using namespace sycl_cts;
  auto q = util::get_cts_object::queue();
  constexpr size_t size_of_res_array =
      legacy_random_access_iterator_requirement::count_of_possible_errors;
  std::string_view errors[size_of_res_array];
  {
    sycl::buffer<std::string_view, 1> res_buf(errors,
                                              sycl::range(size_of_res_array));
    q.submit([&](sycl::handler& cgh) {
      auto acc = res_buf.get_access<sycl::access_mode::write>(cgh);

      cgh.single_task([=] {
        std::array<int, 5> arr = {1, 2, 3, 4, 5};
        auto res = legacy_random_access_iterator_requirement{}.is_satisfied_for(
            arr.begin(), arr.size());
        if (!res.first) {
          for (int i = 0; i < size_of_res_array; ++i) {
            if (res.second[i] != "") {
              acc[i] = res.second[i];
            }
          }
        }
      });
    });
    q.wait_and_throw();
  }
  const bool requirement_not_satisfied = true;
  for (size_t i = 0; i < size_of_res_array; ++i) {
    if (errors[i] != "") {
      INFO(errors[i]);
      CHECK(requirement_not_satisfied);
    }
  }
});
