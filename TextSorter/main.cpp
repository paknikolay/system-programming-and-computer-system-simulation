#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <algorithm>
#include "Comparator.h"
#include "TextTools.h"

void readFile (char* path, char* text, size_t size) {
  FILE *fd = fopen(path, "r");
  if (fd == NULL) {
    std::cerr << "file descriptor is NULL\n";
  }

  size_t symbolCount;
  if (symbolCount = fread(text, 1, size, fd) != size) {
    std::cerr << "read not enough bytes: read " << symbolCount << " symbols, expected " << size << "\n";
  }
  fclose(fd);

}

int main() {
  char path[] = "text.txt";
  struct stat st;

  if (stat(path, &st) == -1) {
    std::cerr << "No file\n";
    return -1;
  }

  char *text = new char[st.st_size + 1];

  readFile(path, text, st.st_size);

  text[st.st_size + 1] = '\n';

  int lineCount = countLinesAndModify(text, st.st_size + 1);
  char **linesOfText = new char *[lineCount];
  setLines(text, linesOfText, st.st_size + 1);

  std::ofstream fSorted("sorted.txt");
  std::ofstream fRevSorted("revSorted.txt");

  std::sort(linesOfText, linesOfText + lineCount, LexicographicalOrderComparator());
  for (int i = 0; i < lineCount; ++i) {
    fSorted << linesOfText[i] << "\n";
  }

  std::sort(linesOfText, linesOfText + lineCount, ReversedLexicographicalOrderComparator());
  for (int i = 0; i < lineCount; ++i) {
    fRevSorted << linesOfText[i] << "\n";
  }


  return 0;
}