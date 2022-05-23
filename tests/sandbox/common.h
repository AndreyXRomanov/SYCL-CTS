#pragma once

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
