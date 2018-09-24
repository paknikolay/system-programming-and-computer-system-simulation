/**
 * @file
 */
#pragma once
#include <cstddef>
/**
 *
 * @param text pointer to text
 * @param size size of the text
 * @return returns amount of lines
 */
int countLinesAndModify(char* text, size_t size);

/**
 *
 * @param text pointer to text
 * @param lines pointer to array to write beginnings of lines
 * @param size size of the text
 */
void setLines(char* text, char** lines, size_t size);
