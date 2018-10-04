#pragma once
#define SECUREMODE SECUREMODE

#include <functional>
#include <cstring>
#include <iostream>

/**
 * @brief contains stack data
 * @tparam T
 */
template <typename T>
struct StackData {
#ifdef SECUREMODE
  unsigned int canary1{0xBEDABEDA};
#endif

  T *buffer;
  int nextPosToWrite{0};
  int size{1};

#ifdef SECUREMODE
  T *copy;
  char *bufferFull;
  char *copyFull;
  size_t checkSum{7};
  unsigned int canary2{0xDEADBEEF};
#endif
};

/**
 * @brief содержит виды ошибок
 */
#ifdef SECUREMODE
  enum class Errors {
    ok, emptyStack, wrongCheckSum, wrongCanaryStackData1, wrongCanaryStackData2,
    wrongCanaryBuff1, wrongCanaryBuff2, unequalBufferAndCopy, wrongCanaryCopy1, wrongCanaryCopy2,
    notEqualCopiesOfRealSize, notEqualCopiesOfSize
};

/**
* @brief выводит ошибку error в out
*/
std::ostream& operator<<(std::ostream& out, const Errors& error) {
  switch (error) {
    case Errors::wrongCheckSum:
      out << "wrongCheckSum";
      break;
    case Errors::emptyStack:
      out << "emptyStack";
      break;
    case Errors::wrongCanaryStackData1:
      out << "wrongCanaryStackData1";
      break;
    case Errors::wrongCanaryStackData2:
      out << "wrongCanaryStackData2";
      break;
    case Errors::wrongCanaryBuff1:
      out << "wrongCanaryBuff1";
      break;
    case Errors::wrongCanaryBuff2:
      out << "wrongCanaryBuff2";
      break;
    case Errors::wrongCanaryCopy1:
      out << "wrongCanaryCopy1";
      break;
    case Errors::wrongCanaryCopy2:
      out << "wrongCanaryCopy2";
      break;
    case Errors::unequalBufferAndCopy:
      out << "unequalBufferAndCopy";
      break;
    case Errors::ok:
      out << "ok";
      break;
    default:
      out << "unknown error";
      break;
  }
}
#endif

/**
 * @brief стек с некоторыми видами проверок непредвиденных изменений данных
 * @note необходимо, чтобы у типа была определена hash функция
 */
template <typename T>
class Stack {
 public:
  Stack();

  ~Stack();

  void push(const T &item);

  void pop();

  const T &top() const;

 private:
  StackData<T> data_;

  void resize();

#ifdef SECUREMODE

  /**
   * Считает контрольную сумму
   */
  size_t calcCheckSum() const;

  /**
   *@brief проверяет целостность стека и его копии
   */
  Errors verify() const;

  /**
   * @brief выводит информацию о стеке, ошибку и место, где произошла ошибка
   */
  void dump(Errors error, const char *function) const;

#endif
};

template <typename T>
Stack<T>::Stack() {
#ifdef SECUREMODE
  size_t size = data_.size * sizeof(T) + 2 * sizeof(int);
  data_.copyFull = new char[size]{0};
  *((unsigned int *) (&data_.copyFull[0])) = 0xCACABEEB;
  *((unsigned int *) (&data_.copyFull[size - sizeof(int)])) = 0xABBCACFD;
  data_.bufferFull = new char[size]{0};
  memcpy(data_.bufferFull, data_.copyFull, size);
  data_.buffer = (T *) (data_.bufferFull + sizeof(int));
  data_.copy = (T *) (data_.copyFull + sizeof(int));

  data_.checkSum = calcCheckSum();
#else
  char* buff =  new char[data_.size * sizeof(T)]{0};
  data_.buffer = (T*) buff;
#endif
}

template <typename T>
Stack<T>::~Stack() {
#ifdef SECUREMODE
  Errors error = verify();

  delete[] data_.copyFull;
  delete[] data_.bufferFull;
#else
  char * buf = (char*)data_.buffer;
  delete[] buf;
#endif
}

#ifdef SECUREMODE
template <typename T>
  Errors Stack<T>::verify() const {
  if (data_.canary1 != 0xBEDABEDA) {
    return Errors::wrongCanaryStackData1;
  }
  if (data_.canary2 != 0xDEADBEEF) {
    return Errors::wrongCanaryStackData2;
  }

  size_t checksum = calcCheckSum();
  if (checksum != data_.checkSum) {
    return Errors::wrongCheckSum;
  }

  if (*((int *) data_.bufferFull) != 0xCACABEEB) {
    return Errors::wrongCanaryBuff1;
  }
  if (*((int *) &data_.bufferFull[data_.size * sizeof(T) + 2 * sizeof(int) - sizeof(int)]) != 0xABBCACFD) {
    return Errors::wrongCanaryBuff2;
  }
  if (*((int *) data_.copyFull) != 0xCACABEEB) {
    return Errors::wrongCanaryCopy1;
  }

  if (*((int *) &data_.copyFull[data_.size * sizeof(T) + 2 * sizeof(int) - sizeof(int)]) != 0xABBCACFD) {
    return Errors::wrongCanaryCopy2;
  }
  
  if (memcmp(data_.bufferFull, data_.copyFull, data_.size * sizeof(T) + 2 * sizeof(int))) {
    return Errors::unequalBufferAndCopy;
  }
  return Errors::ok;
}

#endif

template <typename T>
void Stack<T>::resize() {
#ifdef SECUREMODE
  size_t oldSize = data_.size * sizeof(T) + 2 * sizeof(int);
  size_t newSize = data_.size * sizeof(T) * 2 + 2 * sizeof(int);
  char *tmpBuff = new char[newSize]{0};
  char *tmpCopy = new char[newSize]{0};
  memcpy(tmpBuff, data_.bufferFull, oldSize);
  *((int *) &tmpBuff[oldSize - sizeof(int)]) = 0;
  *((int *) &tmpBuff[newSize - sizeof(int)]) = 0xABBCACFD;
  memcpy(tmpCopy, tmpBuff, newSize);
  std::swap(tmpBuff, data_.bufferFull);
  std::swap(tmpCopy, data_.copyFull);
  data_.buffer = (T *) (data_.bufferFull + sizeof(int));
  data_.copy = (T *) (data_.copyFull + sizeof(int));

  delete[] tmpBuff;
  delete[] tmpCopy;
#else
  char *tmpBuff = new char[data_.size * sizeof(T) * 2]{0};
  memcpy(tmpBuff, data_.buffer, data_.size * sizeof(T));
  T* tmpBuffT = (T*) tmpBuff;
  std::swap(tmpBuffT, data_.buffer);
  delete[] tmpBuff;
#endif
  data_.size *= 2;
}

template <typename T>
void Stack<T>::push(const T &item) {
#ifdef SECUREMODE
  Errors error = verify();
  if (error != Errors::ok) {
    dump(error, "push");
  }
#endif

  data_.buffer[data_.nextPosToWrite] = item;

#ifdef SECUREMODE
  memcmp(&data_.copy[data_.nextPosToWrite], &data_.buffer[data_.nextPosToWrite], sizeof(T));
  //data_.copy[data_.nextPosToWrite] = std::move(data_.buffer[data_.nextPosToWrite++]);

#endif
  ++data_.nextPosToWrite;
  if (data_.size == data_.nextPosToWrite) {
    resize();
  }
#ifdef SECUREMODE
  data_.checkSum = calcCheckSum();
#endif
}

template <typename T>
const T& Stack<T>::top() const{
#ifdef SECUREMODE
  Errors error = verify();
        if (error != Errors::ok) {
            dump(error, "top");
        }

        if(data_.nextPosToWrite == 0){
            dump(Errors::emptyStack, "top");
        }
#endif
  return data_.buffer[data_.nextPosToWrite - 1];
}

template <typename T>
void Stack<T>::pop() {
#ifdef SECUREMODE
  Errors error = verify();
        if (error != Errors::ok) {
            dump(error, "pop");
        }
        if(data_.nextPosToWrite == 0){
            dump(Errors::emptyStack, "pop");
        }
#endif

  --data_.nextPosToWrite;
#ifdef SECUREMODE
  data_.checkSum = calcCheckSum();
#endif
}

#ifdef SECUREMODE
template <typename T>
    size_t Stack<T>::calcCheckSum() const {
  size_t sum = 7;
  std::hash<T> hasher;
  std::hash<int> hasherI;
  sum+= hasherI(data_.nextPosToWrite);
  sum*=2;
  sum+= hasherI(data_.size);
  sum*=2;
  sum = sum % 6839465317;
  sum+= hasherI(reinterpret_cast<intptr_t>(data_.copy)) * hasherI(reinterpret_cast<intptr_t>(data_.buffer));
  sum*=5;
  sum+= hasherI(reinterpret_cast<intptr_t>(data_.copyFull)) * hasherI(reinterpret_cast<intptr_t>(data_.bufferFull));
  sum = sum % 6839465317;

  for (size_t i = 0; i < data_.nextPosToWrite; ++i) {
    sum *= 3;
    sum += hasher(data_.buffer[i]);
    sum = sum % 6839465317;
  }
  return sum;
}

template <typename T>
void Stack<T>::dump(Errors error, const char* function) const {
  std::cerr << "\n*****************************************\n";

  std::cerr << error << " occurred in function " << function << "\n";
  std::cerr << "Stack this = " << this << "\n";

  std::cerr << "    canaryStack1 " << data_.canary1 << " expected " << 0xBEDABEDA << "\n";
  std::cerr << "    canaryStack2 " << data_.canary2 << " expected " << 0xDEADBEEF << "\n";
  std::cerr << "    canaryBuff1 " << *((unsigned int *) (&data_.bufferFull[0])) << " expected " << 0xCACABEEB
            << "\n";
  std::cerr << "    canaryBuff2 "
            << *((unsigned int *) (&data_.bufferFull[data_.size * sizeof(T) + 2 * sizeof(int) - sizeof(int)]))
            << " expected " << 0xABBCACFD << "\n";
  std::cerr << "    canaryCopy1 " << *((unsigned int *) (&data_.copyFull[0])) << " expected " << 0xCACABEEB << "\n";
  std::cerr << "    canaryCopy2 "
            << *((unsigned int *) (&data_.copyFull[data_.size * sizeof(T) + 2 * sizeof(int) - sizeof(int)]))
            << " expected " << 0xABBCACFD << "\n";

  std::cerr << "    real size " << data_.size << "\n";
  std::cerr << "    size " << data_.nextPosToWrite << "\n";

  std::cerr << "    checkSum " << data_.checkSum << " expected " << calcCheckSum() << "\n";

  std::cerr << "    values of buffer, copy\n";

    for (size_t i = 0; i < data_.nextPosToWrite; ++i) {
      std::cerr << "        " << data_.buffer[i] << ", " << data_.copy[i] << "\n";
    }


  std::cerr << "*****************************************\n";

  exit(0);

}

#endif
