#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/cbmp.h"
#include "files.h"

void compress_routine(char *path) {
  Compressed *c = (Compressed*) malloc(sizeof(Compressed));

  pixel **pixels = load_pixels(c, path);
  unsigned int pixelLen = (c->width) * (c->height);

  get_unique(c, pixels, pixelLen);

  index_pixels(c, pixels, pixelLen);

  write_indexed_file(c->indices, c->width, c->height, c->palette, c->paletteLen, path);

  close_compressed(c);
}

void decompress_routine(char *path) {
  printf("Decompress\n");
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
  } else if (strcmp(subcommand, "decompress") == 0) {
    decompress_routine(path);
  } else {
    printf("%s: Subcommand '%s' not recognised.\n", argv[0], argv[1]);
  }

  return 0;
}
