#include "FileTools.h"

size_t getFileSize(char* path) {
  struct stat st;

  if (stat(path, &st) == -1) {
    std::cerr << "No file\n";
    return -1;
  }
  return st.st_size;
}

void readFile(char* path, char* buffer, size_t size) {
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

void printToFile(char** text, size_t lineCount, std::ofstream& fout){
  for (int i = 0; i < lineCount; ++i) {
    fout << text[i] << "\n";
  }
}
