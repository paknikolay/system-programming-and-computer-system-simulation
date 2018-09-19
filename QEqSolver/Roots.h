#pragma once

#include <vector>

/**
 * @namespace EQSolver
 * @brief namespace содержащий функции и классы для решения уравнений
 */
namespace EqSolver {

   /**
       @brief Класс для хранения решений уравнений
   */
  class Roots {
   public:

    /**
         @brief Возвращает true, если количество корней конечно, иначе false
    */
    bool isFiniteAmountOfRoots();

    /**
         @brief Возвращает константную ссылку на вектор, хранящий корни уравнения
    */
    const std::vector<double> &GetRoots();

    /**
         @brief Добавляет корень
         @param root - добавляемый корень
    */
    void addRoot(double root);

    /**
         @brief Возвращает количество корней, если их конечно, иначе -1
    */
    int getRootCount();

    /**
         @brief Устанавливает флаг isFiniteAmountOfRoots
    */
    void setFiniteness(bool isFinite);

   private:
    bool isFiniteAmountOfRoots_{1};
    std::vector<double> roots_;
  };
}