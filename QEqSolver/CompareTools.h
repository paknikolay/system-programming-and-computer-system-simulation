#pragma once

namespace EqSolver {
  const double eps = 0.00001;

  bool isEq(double a, double b) {
    return std::abs(a - b) < eps;
  }
}
