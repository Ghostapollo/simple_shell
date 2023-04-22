#include "main.h"

#define BUFFER_SIZE 1024

/**
 * my_getline - custom implementation of getline using a buffer to read many
 * characters at once and minimize the number of calls to the read system call
 *
 * Return: a pointer to the line read, or NULL on failure or end-of-file
 */

