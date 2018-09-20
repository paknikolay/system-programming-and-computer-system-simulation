#include "Text.h"
#include "TextTools.h"
#include "FileTools.h"

Text::Text(char *pathToFile) {
  textSize_ = getFileSize(pathToFile);
  text_ = new char[textSize_ + 1];
  bzero(text_, textSize_ + 1);

  readFile(pathToFile, text_, textSize_);
  text_[textSize_ + 1] = '\n';

  linesCount_ = countLinesAndModify(text_, textSize_ + 1);
  lines_ = new char *[linesCount_];
  bzero(lines_, linesCount_);

  setLines(text_, lines_, textSize_ + 1);
}

Text::~Text() {
  delete[] text_;
  delete[] lines_;
}

char* Text::begin() {
  return lines_[0];
}

char* Text::end() {
  return lines_[linesCount_];
}
