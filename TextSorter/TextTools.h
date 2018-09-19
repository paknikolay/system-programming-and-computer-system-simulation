/**
 * @file
 */

#include <stdio.h>

/**
 * @brief read text from file
 * @param path path to the file
 * @param buffer buffer to fill with the text
 * @param size amount symbols to read
 */
void getTextFromFile(char* path, char* buffer, size_t size) {
  FILE *fd = fopen(path, "r");
  if (fd == NULL) {
    std::cerr << "file descriptor is NULL\n";
  }

  size_t symbolCount;
  if (symbolCount = fread(buffer, 1, size, fd) != size) {
    std::cerr << "read not enough bytes: read " << symbolCount << " symbols, expected " << size << "\n";
  }
  fclose(fd);
}


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

