#include "QuadraticEqSolver.h"
#include "LinearEqSolver.h"
#include "CompareTools.h"

#include <cmath>

#define TestMode 1

EqSolver::Roots EqSolver::solveQuadraticEq(const double &a, const double &b, const double &c) {
  if (std::abs(a) < eps) {
    return solveLinearEq(b, c);
  }

  EqSolver::Roots roots;
  roots.setFiniteness(true);

  double d = b * b - 4 * a * c;
  if (d < 0) {
    return roots;
  }

  d = std::sqrt(d);
  roots.addRoot((-b - d) / 2);
  roots.addRoot((-b + d) / 2);

  return roots;
}

#ifdef TestMode

#include <iostream>
#include <assert.h>

using std::cout;

int main(){
  //проверка линейных уравнений
  assert(EqSolver::isEq(EqSolver::solveQuadraticEq(0,1,1).GetRoots()[0], -1));
  assert(!EqSolver::solveQuadraticEq(0,0,0).isFiniteAmountOfRoots());
  assert(EqSolver::solveQuadraticEq(0,0,0).getRootCount() == -1);
  assert(EqSolver::solveQuadraticEq(0,0,1).isFiniteAmountOfRoots());
  assert(EqSolver::solveQuadraticEq(0,0,1).getRootCount() == 0);
  assert(EqSolver::isEq(EqSolver::solveQuadraticEq(0,5,2).GetRoots()[0], -0.4));

  //проверка квадратных уравнений
  assert(EqSolver::solveQuadraticEq(1,2,1).getRootCount() == 2);
  assert(EqSolver::isEq(EqSolver::solveQuadraticEq(1,2,1).GetRoots()[0], -1));
  assert(EqSolver::isEq(EqSolver::solveQuadraticEq(1,2,1).GetRoots()[1], -1));

  assert(EqSolver::solveQuadraticEq(1,-9,20).getRootCount() == 2);
  assert(EqSolver::isEq(EqSolver::solveQuadraticEq(1,-9,20).GetRoots()[0], 4));
  assert(EqSolver::isEq(EqSolver::solveQuadraticEq(1,-9,20).GetRoots()[1], 5));

  assert(EqSolver::solveQuadraticEq(1,2,5).getRootCount() == 0);
  assert(EqSolver::solveQuadraticEq(1,2,5).isFiniteAmountOfRoots());
}

#endif
