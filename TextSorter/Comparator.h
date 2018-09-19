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
