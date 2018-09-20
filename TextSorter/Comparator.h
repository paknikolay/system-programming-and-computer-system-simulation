#pragma once

/** @brief base class for LexicographicalOrderComparators
*/
class ComparatorBase {
 protected:
/**
 *
 * @param s symbol
 * @return true if s is symbol or digit
 */
  bool isSymbol(char s);

/**
 *
 * @param i reference to index
 * @param str pointer to string
 * @param step 1 is to move forward or -1 to move backward
 */
  void skip(int &i, char *str, char step);

/**
 *
 * @param s symbol
 * @return makes symbol small if required
 */
  char lower(char s);

/**
 *
 * @param a first string
 * @param b second string
 * @param step if 1 - lexicographical order, -1 - reversed order
 * @return true if first is less than second
 */
  bool compare(char *a, char *b, char step);
};


/**
 * @brief class to compare strings in lexicographical order
 */
class LexicographicalOrderComparator : public ComparatorBase{
 public:
  bool operator()(char *a, char *b) {
    return compare(a, b, 1);
  }
};


/**
 * @brief class to compare strings in reversed lexicographical order
 */
class ReversedLexicographicalOrderComparator : public ComparatorBase {
 public:
  bool operator()(char *a, char *b) {
    return compare(a, b, -1);
  }
};

#include "Comparator.h"

bool ComparatorBase::isSymbol(char s) {
  return (s >= 'A' && s <= 'Z') || (s >= 'a' && s <= 'z') || (s >= '0' && s <= '9');
}

void ComparatorBase::skip(int &i, char *str, char step) {
  while (i >= 0 && str[i] != '\0' && !isSymbol(str[i])) {
    i += step;
  }
}

char ComparatorBase::lower(char s) {
  if (s >= 'A' && s <= 'Z') {
    return s - 'A' + 'a';
  } else return s;
}

bool ComparatorBase::compare(char *a, char *b, char step) {
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
      return lower(a[i]) < lower(b[j]);
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

