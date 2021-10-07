#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

char *get_file_name(char *path) {
  char *name = malloc(sizeof(char));
  int nameLen = 0;

  int i = 0;
  while (path[i] != '\0') {
    if (path[i] == '.') {
      break;
    } else {
      nameLen++;
      name = realloc(name, sizeof(char) * nameLen);
      name[nameLen - 1] = path[i];
    }

    i++;
  }

  name[nameLen] = '\0';

  return name;
}
