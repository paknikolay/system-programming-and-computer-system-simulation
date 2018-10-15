/**
 * @file
 */

#pragma once

#include <stdio.h>
#include <iostream>
#include <sys/stat.h>
#include <fstream>

/**
 *
 * @param path path to the file
 * @return size of file
 */
size_t getFileSize(char* path);

/**
 * @brief read text from file
 * @param path path to the file
 * @param buffer buffer to fill with the text
 * @param size amount symbols to read
 */
void readFile(char* path, char* buffer, size_t size);

/**
 *
 * @param text text to print
 * @param lineCount amount of lines in text
 * @param fout stream to print
 */

void printToFile(char** text, size_t lineCount, std::ofstream& fout);