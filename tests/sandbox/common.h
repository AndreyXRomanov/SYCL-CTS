/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Provides common code for iterator requirements verifications
//
*******************************************************************************/

#ifndef __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_COMMON_H
#define __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_COMMON_H

#include "../common/common.h"

class requirement_verifier {
 protected:
  bool m_verification_result = true;
  void verify(const bool logic_expression, bool silence_output = false) {
    if (!silence_output) {
      CHECK(logic_expression);
    }
    m_verification_result &= logic_expression;
  }
};

#endif  // __SYCLCTS_TESTS_ITERATOR_REQUIREMENTS_COMMON_H
