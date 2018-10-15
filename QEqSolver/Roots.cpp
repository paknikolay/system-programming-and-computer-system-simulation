#include "Roots.h"
#include <vector>

void EqSolver::Roots::addRoot(double t) {
roots_.push_back(t);
}

int EqSolver::Roots::getRootCount() {
  if(!isFiniteAmountOfRoots_) {
    return -1;
  } else {
    return roots_.size();
  }
}

const std::vector<double>& EqSolver::Roots::GetRoots() {
  return roots_;
}

bool EqSolver::Roots::isFiniteAmountOfRoots() {
  return isFiniteAmountOfRoots_;
}

void EqSolver::Roots::setFiniteness(bool isFinite) {
  isFiniteAmountOfRoots_ = isFinite;
}