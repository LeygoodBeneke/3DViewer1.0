#include "parser.h"
#include "stdio.h"

int main(void) {
  point *points = NULL;
  line *lines = NULL;
  int points_len, surfaces_len = 0;

  char *path = "obj_files_for_testing/cube.txt";

  parser(path, &points, &points_len, &lines, &surfaces_len);
  int j = 0;

  printf("/*****************POINTS*****************/\n");
  for (int i = 0; i < points_len; i++) {
    printf("[%f, %f, %f], ", points[i].x, points[i].y, points[i].z);
    if (j == 1) {
      printf("\n");
      j = 0;
    } else {
      j++;
    }
  }

  printf("\n/*****************LINES*****************/\n");
  j = 0;
  for (int i = 0; i < surfaces_len; i++) {
    printf("{%d, %d},", lines[i].a, lines[i].b);
    if (j == 3) {
      printf("\n");
      j = 0;
    } else {
      j++;
    }
  }

  free(points);
  free(lines);
}