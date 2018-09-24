#pragma once
enum class Order {
  direct, reverse
};

/** @brief base class for LexicographicalOrderComparators
*/
class ComparatorBase {
 protected:

/**
 *
 * @param i reference to index
 * @param str pointer to string
 * @param step 1 is to move forward or -1 to move backward
 */
  void skip(int &i, char *str, char step);



/**
 *
 * @param a first string
 * @param b second string
 * @param step if 1 - lexicographical order, -1 - reversed order
 * @return true if first is less than second
 */
  bool compare(char *a, char *b, Order order);
};


/**
 * @brief class to compare strings in lexicographical order
 */
class LexicographicalOrderComparator : public ComparatorBase{
 public:
  bool operator()(char *a, char *b) {
    return compare(a, b, Order::direct);
  }
};


/**
 * @brief class to compare strings in reversed lexicographical order
 */
class ReversedLexicographicalOrderComparator : public ComparatorBase {
 public:
  bool operator()(char *a, char *b) {
    return compare(a, b, Order::reverse);
  }
};
