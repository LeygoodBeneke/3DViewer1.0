#ifndef C8_3DVIEWER_V1_0_2_PARSER_H
#define C8_3DVIEWER_V1_0_2_PARSER_H

#include "string.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct {
    double x;
    double y;
    double z;
}point;

typedef struct {
    point *points;
    int len;
}surface;

typedef struct {
    int a;
    int b;
}line;

void parser(char *file_path, point **points, int *points_len, line **lines, int *surf_len);
int is_coordinate (char *line, int *trigger);
void create_point(point* p, char* line);
line *get_lines(FILE *fp, int *number_surfaces);
int is_surface(char* str);
void create_line(line *lines, char *str, int *i);
void number_of_points_and_surfaces(int* number_points, int* number_surfaces, FILE* fp);

char* get_token(char *str);
int get_point_number(char *token);

#endif //C8_3DVIEWER_V1_0_2_PARSER_H
