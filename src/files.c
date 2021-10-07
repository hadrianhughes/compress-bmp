#include <stdio.h>
#include <string.h>
#include "./colors.c"
#include "./utils.c"

void write_indexed_file(int *indices, unsigned int pxLen, Color *palette, unsigned int paletteLen, char *filePath) {
  char *inputFileName = get_file_name(filePath);
  char *newFileName = strcat(inputFileName, ".idx");

  FILE *fp = fopen(newFileName, "w");

  for (int c = 0;c < paletteLen;c++) {
  }

  fputs("Hello world!", fp);

  fclose(fp);
}
