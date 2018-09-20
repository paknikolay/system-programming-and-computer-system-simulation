#pragma once

class Text {
 public:
  explicit
  Text(char *pathToFile);

  ~Text();

  char *begin();

  char *end();

 private:
  char *text_;
  char **lines_;
  size_t textSize_;
  size_t linesCount_;
};
