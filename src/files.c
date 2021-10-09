#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "files.h"

void write_indexed_file(int *indices, unsigned int width, unsigned int height, pixel **palette, unsigned int paletteLen, char *filePath) {
  char *inputFileName = get_file_name(filePath);
  char *newFileName = strcat(inputFileName, ".idx");

  FILE *fp = fopen(newFileName, "w");

  for (int c = 0;c < paletteLen;c++) {
    fprintf(fp, "%d %d %d %d\n", c, palette[c]->red, palette[c]->green, palette[c]->blue);
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

Compressed *open_idx(char *filePath) {
  FILE *fp = fopen(filePath, "r");

  // Load palette
  pixel **palette = malloc(0);
  unsigned int paletteLen = 0;
  char line[10000];
  while (strcmp(fgets(line, 10000, fp), "\n")) {
    paletteLen++;
    palette = realloc(palette, sizeof(pixel*) * paletteLen);

    int components[3];
    char *partStr = strtok(line, " ");
    for (int p = 0;p < 3;p++) {
      partStr = strtok(NULL, " ");
      components[p] = atoi(partStr);
    }

    pixel* color = malloc(sizeof(pixel));
    color->red = components[0];
    color->green = components[1];
    color->blue = components[2];
    color->alpha = 1;

    palette[paletteLen - 1] = color;
  }

  // Load bitmap
  int *indices = malloc(0);
  unsigned int pixelCount = 0;
  unsigned int imageWidth, imageHeight;
  int firstIter = 1;
  while (fgets(line, 10000, fp) != NULL) {
    char *pixelString = strtok(line, " ");
    while (pixelString != NULL) {
      pixelCount++;
      indices = realloc(indices, sizeof(int) * pixelCount);

      int colorIndex = atoi(pixelString);
      indices[pixelCount - 1] = colorIndex;

      pixelString = strtok(NULL, " ");
    }

    if (firstIter) {
      imageWidth = pixelCount;
      firstIter = 0;
    }
  }

  fclose(fp);

  imageHeight = pixelCount / imageWidth;

  // Build Compressed struct
  Compressed *c = malloc(sizeof(Compressed));
  c->palette = palette;
  c->indices = indices;
  c->width = imageWidth;
  c->height = imageHeight;
  c->paletteLen = paletteLen;

  return c;
}
