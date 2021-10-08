#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/cbmp.h"
#include "files.h"
#include "colors.h"

void compress_routine(char *path) {
  unsigned int w, h;
  unsigned int *width = &w;
  unsigned int *height = &h;
  pixel *pixels = load_pixels(path, width, height);
  unsigned int pixelLen = (*width) * (*height);

  unsigned int pl;
  unsigned int *paletteLen = &pl;
  pixel *palette = get_unique(pixels, pixelLen, paletteLen);

  int *indices = index_pixels(pixels, pixelLen, palette, *paletteLen);

  write_indexed_file(indices, *width, *height, palette, *paletteLen, path);

  free(palette);
  free(indices);
}

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("%s: Usage: %s <subcommand> <input_file>\n", argv[0], argv[0]);
    return 1;
  }

  char *subcommand = argv[1];
  char *path = argv[2];

  if (strcmp(subcommand, "compress") == 0) {
    compress_routine(path);
  } else {
    printf("%s: Subcommand '%s' not recognised.\n", argv[0], argv[1]);
  }

  return 0;
}
