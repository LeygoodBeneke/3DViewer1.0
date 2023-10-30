#ifndef C8_3DVIEWER_V1_0_2_PARSER_H
#define C8_3DVIEWER_V1_0_2_PARSER_H

#include "stdio.h"
#include "stdlib.h"

typedef struct {
  double x;
  double y;
  double z;
} point;

typedef struct {
  point *points;
  int len;
} surface;

typedef struct {
  int a;
  int b;
} line;

void parser(char *file_path, point **points, int *points_len, line **lines,
            int *surface_len);

#endif  // C8_3DVIEWER_V1_0_2_PARSER_H
