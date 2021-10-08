#include <stdio.h>
#include "colors.h"

void write_indexed_file(int *indices, unsigned int width, unsigned int height, pixel **palette, unsigned int paletteLen, char *filePath);

Compressed *open_idx(char *filePath);
