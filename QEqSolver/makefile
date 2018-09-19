all:QuadraticEqSolver
QuadraticEqSolver: QuadraticEqSolver.o LinearEqSolver.o Roots.o
		g++ QuadraticEqSolver.o LinearEqSolver.o Roots.o -o QuadraticEqSolver
QuadraticEqSolver.o: QuadraticEqSolver.cpp
		g++ QuadraticEqSolver.cpp -c
LinearEqSolver: LinearQuaEqSolver.o Roots.o
		g++ LinearEqSolver.o Roots.o -o LinearEqSolver
LinearEqSolver.o: LinearEqSolver.cpp
		g++ LinearEqSolver.cpp -c
Roots.o: Roots.cpp
		g++ Roots.cpp -c
