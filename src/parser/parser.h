#ifndef C8_3DVIEWER_V1_0_2_PARSER_H
#define C8_3DVIEWER_V1_0_2_PARSER_H

#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"

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
    point *points;
    surface *s;
}test_s;

void parser(char *file_path, point **points, int *points_len, surface **surf, int *surf_len);
int is_coordinate (char *line, int *trigger);
void create_point(point* p, char* line);
surface *get_surface(point *p, int length, FILE *fp, int number_surfaces, point *points);
int is_surface(char* line);
void create_surface(surface *surf, char *line, point *points);
int number_of_coordinates(char *line);
void number_of_points_and_planes(int* number_points, int* number_planes, FILE* fp);

#endif //C8_3DVIEWER_V1_0_2_PARSER_H
