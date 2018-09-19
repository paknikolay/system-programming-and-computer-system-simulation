#pragma once

#include <vector>
#include "Roots.h"
/** @file */
namespace EqSolver{
  /**
   *
   * @brief Решает линейное уравнение ax + b = 0
   * @param a коэффициент при x
   * @param b свободный коэффициент
   * @see Roots
   */

  Roots solveLinearEq(const double& a, const double& b);
}
