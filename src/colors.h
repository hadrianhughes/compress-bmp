typedef struct Color {
  unsigned char r, g, b;
} Color;

int cequal(Color col1, Color col2);

Color *get_unique(Color *pixels, unsigned int pxLen, unsigned int *len);

int get_color_index(Color *palette, unsigned int paletteLen, Color c);

int *index_pixels(Color *pixels, unsigned int pxLen, Color *palette, unsigned int paletteLen);
