#include "LinearEqSolver.h"
#include "CompareTools.h"

//#define TestMode 1

EqSolver::Roots EqSolver::solveLinearEq(const double &a, const double &b) {
  EqSolver::Roots roots;
  if (a == 0) {
    roots.setFiniteness(b != 0);
  } else {
    roots.setFiniteness(true);
    roots.addRoot(-b / a);
  }
  return roots;
}

#ifdef TestMode

#include <iostream>
#include <assert.h>

using std::cout;

  int main(){
    assert(EqSolver::isEq(EqSolver::solveLinearEq(1,1).GetRoots()[0],-1));
    assert(!EqSolver::solveLinearEq(0,0).isFiniteAmountOfRoots());
    assert(EqSolver::solveLinearEq(0,0).getRootCount() == -1);
    assert(EqSolver::solveLinearEq(0,1).isFiniteAmountOfRoots());
    assert(EqSolver::solveLinearEq(0,1).getRootCount() == 0);
    assert(EqSolver::isEq(EqSolver::solveLinearEq(5,2).GetRoots()[0], -0.4));
  }

#endif
