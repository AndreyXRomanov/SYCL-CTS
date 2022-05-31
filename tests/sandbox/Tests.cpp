#include "../common/common.h"
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

TEST_CASE("Equal operator") {
  CHECK_FALSE(type_traits::has_comparison::is_equal_v<EqualOpNotImplemented>);
  CHECK(type_traits::has_comparison::is_equal_v<EqualOpImplemented>);
  CHECK(type_traits::has_comparison::is_equal_v<std::vector<int>::iterator>);
}

TEST_CASE("Legacy iterator check") {
  legacy_iterator_requirement<std::vector<int>::iterator>{}.check(
      "vector<int>::iterator");

  legacy_iterator_requirement<LegacyIterator>{}.check(
      "LegacyIterator");
}

TEST_CASE("Legacy input iterator check") {
  legacy_input_iterator_requirement<std::vector<int>::iterator>{}.check(
      "vector<int>::iterator");

  legacy_input_iterator_requirement<LegacyInputIterator>{}
      .check("LegacyInputIterator");
}

TEST_CASE("Equality comparable check") {
  std::vector v{1, 2, 3, 4, 5};
  equality_comparable_requirement<std::vector<int>::iterator>{}.check(
      "vector<int>::iterator");
}

TEST_CASE("Legacy output iterator check") {
  legacy_output_iterator_requirement<std::vector<int>::iterator>{}.check(
      "vector<int>::iterator");

  legacy_output_iterator_requirement<LegacyOutputIterator>{}
      .check("LegacyOutputIterator");
}

TEST_CASE("Legacy forward iterator check") {
  std::vector v{1, 2, 3, 4, 5};
  legacy_forward_iterator_requirement<std::vector<int>::iterator>{}.check(
      v.begin(), v.size(), "vector<int>::iterator");

  LegacyForwardIterator v1{1, 2, 3, 4, 5};
  legacy_forward_iterator_requirement<LegacyForwardIterator>{}.check(
      v1, v1.size(), "LegacyForwardIterator");
}

TEST_CASE("Legacy biderectional iterator check") {
  std::vector v{1, 2, 3, 4, 5};
  legacy_bidirectional_iterator_requirement<std::vector<int>::iterator>{}.check(
      v.begin(), v.size(), "vector<int>::iterator");

  LegacyBidirectionalIterator v1{1, 2, 3, 4, 5};
  legacy_forward_iterator_requirement<LegacyBidirectionalIterator>{}.check(
      v1, v1.size(), "LegacyBidirectionalIterator");
}

TEST_CASE("Legacy random access iterator check") {
  std::vector v{1, 2, 3, 4, 5};
  legacy_random_access_iterator_requirement<std::vector<int>::iterator>{}.check(
      v.begin(), v.size(), "vector<int>::iterator");

  LegacyRandomAccessIterator v1{1, 2, 3, 4, 5};
  legacy_random_access_iterator_requirement<LegacyRandomAccessIterator>{}.check(
      v1, v1.size(), "LegacyRandomAccessIterator");
}
