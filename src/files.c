#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "files.h"

void write_indexed_file(int *indices, unsigned int width, unsigned int height, Color *palette, unsigned int paletteLen, char *filePath) {
  char *inputFileName = get_file_name(filePath);
  char *newFileName = strcat(inputFileName, ".idx");

  FILE *fp = fopen(newFileName, "w");

  for (int c = 0;c < paletteLen;c++) {
    fprintf(fp, "%d %d %d %d\n", c, palette[c].r, palette[c].g, palette[c].b);
  }

  putc('\n', fp);

  for (int r = 0;r < height;r++) {
    for (int i = 0;i < width;i++) {
      fprintf(fp, "%d", indices[r * height + i]);

      if (i != width - 1) {
        putc(' ', fp);
      }
    }

    putc('\n', fp);
  }

  fclose(fp);
}
