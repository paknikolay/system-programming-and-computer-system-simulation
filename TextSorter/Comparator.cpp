#include <ctype.h>

#include "Comparator.h"

void ComparatorBase::skip(int &i, char *str, char step) {
  while (i >= 0 && str[i] != '\0' && !isalnum(str[i])) {
    i += step;
  }
}

bool ComparatorBase::compare(char *a, char *b, Order order) {
  int step = order == Order::direct ? 1 : -1;

  if (b[0] == '\0') {
    return false;
  }
  if (a[0] == '\0') {
    return true;
  }

  int i = 0, j = 0;
  if (step == -1) {
    while (a[i] != '\0') {
      ++i;
    }
    while (b[j] != '\0') {
      ++j;
    }

    i += step;
    j += step;
  }

  skip(i, a, step);
  skip(j, b, step);

  while (step == -1 ? (i >= 0 && j >= 0) : (a[i] != '\0' && b[j] != '\0')) {
    if (a[i] == b[j]) {
      i += step;
      j += step;
    } else {
      return tolower(a[i]) < tolower(b[j]);
    }
    skip(i, a, step);
    skip(j, b, step);
  }

  if (step == -1 ? j == 0 : b[j] == '\0') {
    return false;
  } else {
    if (step == -1) {
      if (i == 0) {
        return true;
      } else return a[i] < b[j];
    } else {
      if (a[i] == '\0') {
        return true;
      } else {
        return a[i] < b[j];
      }
    }
  }
}
