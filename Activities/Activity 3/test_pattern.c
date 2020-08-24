#include <stdio.h>
#include <stdlib.h>

// void print_pixmap8(uint8_t *pixmap, int width, int height) {
  
  
//   for (int y = 0; y < height; y++) {
//     for (int x = 0; x < width; x++) {
//       uint8_t *pixel = &pixmap[4*((y * width) + x)];
//       printf("#%02x%02x%02x ",
//              pixel[0],
//              pixel[1],
//              pixel[2]);
//     }
//     printf("\n");
//   }

// }

void fail(char *s) {
  printf("Error: %s\n\n", s);
  printf("Usage:\n");
  printf("test_pattern BAR_WIDTH BAR_HEIGHT\n\n");
  exit(1);
}

#define col 255

uint8_t bar_color[] = {
  col, col, col,
  col, col,   0,
    0, col, col,
    0, col,   0,
  col,   0, col,
  col,   0,   0,
    0,   0, col
};

int main(int argc, char *argv[]) {

  if (argc != 3) {
    fail("Wrong number of arguments.");
  }

  int bar_width = atoi(argv[1]);
  int bar_height = atoi(argv[2]);

  if (bar_width <= 0) {
    fail("Bad width argument.");
  }

  if (bar_height <= 0) {
    fail("Bad height argument.");
  }

  int pixmap_size = 7*bar_width*bar_height*4;
  uint8_t *pixmap = malloc(pixmap_size);
  uint8_t *pixel = pixmap;

  for (int y = 0; y < bar_height; y += 1) {
    for (int c = 0; c < 7; c += 1) {
      for (int x = 0; x < bar_width; x += 1) {
        pixel[0] = bar_color[c*3+0];
        pixel[1] = bar_color[c*3+1];
        pixel[2] = bar_color[c*3+2];
        pixel[3] = 255;
        pixel += 4;
      }
    }
  }

  FILE *fp = fopen("image.data", "w");

  fwrite(pixmap, 1, pixmap_size, fp);

  // print_pixmap8(pixmap, bar_width*7, bar_height);

  fclose(fp);

  return 0;
}