#include <stdio.h>
#include "colors.h"

void write_numbers_line(int *numbers, unsigned int length, FILE *fp);

void write_indexed_file(int *indices, unsigned int pxLen, Color *palette, unsigned int paletteLen, char *filePath);
