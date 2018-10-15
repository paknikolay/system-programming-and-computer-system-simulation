all:Sorter
Sorter: main.o Comparator.o FileTools.o TextTools.o
		g++ main.o Comparator.o FileTools.o TextTools.o -o Sorter -std=c++11
main.o: main.cpp
		g++ main.cpp -c -std=c++11
Comparator.o: Comparator.cpp
		g++ Comparator.cpp -c -std=c++11
FileTools.o: FileTools.cpp
		g++ FileTools.cpp -c -std=c++11
TextTools.o: TextTools.cpp
		g++ TextTools.cpp -c -std=c++11
clean:
		rm main.o Comparator.o FileTools.o TextTools.o
