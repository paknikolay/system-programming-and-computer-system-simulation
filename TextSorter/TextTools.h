/**
 * @file
 */
#pragma once

/**
 *
 * @param text pointer to text
 * @param size size of the text
 * @return returns amount of lines
 */
int countLinesAndModify(char* text, size_t size){
  int cnt = 0;
  for (int i = 0; i < size; ++i) {
    if(text[i] == '\n' || text[i] == '\0') {
      ++cnt;
      text[i] = '\0';
    }
  }
  return cnt;
}

/**
 *
 * @param text pointer to text
 * @param lines pointer to array to write beginnings of lines
 * @param size size of the text
 */
void setLines(char* text, char** lines, size_t size){
  lines[0] = &text[0];
  int cnt = 1;
  for (int i = 1; i < size; ++i) {
    if(text[i-1] == '\0') {
      while(text[i] == ' ') {
        ++i;
      }
      lines[cnt] = &text[i];
      ++cnt;
    }
  }
}

