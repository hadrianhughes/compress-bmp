#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "files.h"

void write_numbers_line(int *numbers, unsigned int length, FILE *fp) {
  for (int i = 0;i < length;i++) {
    putw(numbers[i], fp);
    putc(' ', fp);
  }

  putc('\n', fp);
}

void write_indexed_file(int *indices, unsigned int pxLen, Color *palette, unsigned int paletteLen, char *filePath) {
  char *inputFileName = get_file_name(filePath);
  char *newFileName = strcat(inputFileName, ".idx");

  FILE *fp = fopen(newFileName, "w");

  for (int c = 0;c < paletteLen;c++) {
    int row[4] = { c, palette[c].r, palette[c].g, palette[c].b };
    write_numbers_line(row, 4, fp);
  }

  fclose(fp);
}
