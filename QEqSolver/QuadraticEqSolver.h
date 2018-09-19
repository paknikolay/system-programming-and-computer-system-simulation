#pragma once

#include <vector>
#include "Roots.h"

/** @file */

namespace EqSolver {
  /**
   * @brief Решает линейное уравнение ax^2 + bx + c = 0
   * @param a коэффициент при x^2
   * @param b коэффициент при x
   * @param c свободный коэффициент
   * @return возвращает корни уравнения в порядке невозрастания
   * @see Roots
   */

  Roots solveQuadraticEq(const double &a, const double &b, const double &c);
}
