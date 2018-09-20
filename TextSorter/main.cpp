#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include "Comparator.h"
#include "TextTools.h"
#include "FileTools.h"

int main() {
  char path[] = "text.txt";

  size_t size = getFileSize(path);
  char *text = new char[size + 1];

  readFile(path, text, size);
  text[size + 1] = '\n';

  int lineCount = countLinesAndModify(text, size + 1);
  char **originLinesOfText = new char *[lineCount];
  char **linesOfText = new char *[lineCount];
  setLines(text, linesOfText, size + 1);
  for (int i = 0; i < lineCount; ++i) {
    originLinesOfText[i] = linesOfText[i];
  }

  std::ofstream fSorted("sorted.txt");
  std::ofstream fRevSorted("revSorted.txt");
  std::ofstream fOrigin("origin.txt");

  std::sort(linesOfText, linesOfText + lineCount, LexicographicalOrderComparator());
  printToFile(linesOfText, lineCount, fSorted);

  std::sort(linesOfText, linesOfText + lineCount, ReversedLexicographicalOrderComparator());
  printToFile(linesOfText, lineCount, fRevSorted);

  printToFile(linesOfText, lineCount, fOrigin);

  delete[] text;
  delete[] linesOfText;
  return 0;
}