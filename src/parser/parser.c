#define _POSIX_C_SOURCE 200809L
#include "parser.h"

void create_line(line *lines, char *str, int *iterator);
void create_point(point *p, char *str, int *iterator);
void size_of_surf(char *line, int *num);
void number_of_points_and_surfaces(int *number_points, int *number_surfaces,
                                   FILE *fp);
int is_surface(char *str);
int is_coordinate(char *line);

char *get_token(char *str);
int get_point_number(char *token);

void parser(char *file_path, point **points, int *points_len, line **lines,
            int *surface_len) {
  int error = 0;
  int iterator_lines = 0;
  int iterator_points = 0;
  char *str = NULL;  // нужно чистить
  unsigned long len = 0;
  long read = 0;

  FILE *fp = fopen(file_path, "r");
  if (fp == NULL) {
    error = 1;
  }

  number_of_points_and_surfaces(points_len, surface_len, fp);
  *points = malloc(*points_len * sizeof(point));  // нужно чистить
  *lines = malloc(*surface_len * sizeof(line));

  while (read != -1 && error == 0) {
    read = getline(&str, &len, fp);

    if (read != -1) {
      if (is_coordinate(str)) {
        create_point(*points, str, &iterator_points);
      } else if (is_surface(str)) {
        create_line(*lines, str, &iterator_lines);
      }
    }
  }

  if (str) {
    free(str);
  }

  if (fp) fclose(fp);
}

void number_of_points_and_surfaces(int *number_points, int *number_surfaces,
                                   FILE *fp) {
  char *line = NULL;  // нужно чистить
  unsigned long len = 0;
  long read;

  *number_points = 0;
  *number_surfaces = 0;

  while ((read = getline(&line, &len, fp)) != -1) {
    if (is_coordinate(line)) {
      *number_points += 1;
    } else if (is_surface(line)) {
      size_of_surf(line, number_surfaces);
    }
  }

  fseek(fp, 0, SEEK_SET);

  if (line) free(line);
}

void size_of_surf(char *line, int *num) {
  int i = -1;
  while (line[0] && (line[0] != '\r' && line[0] != '\n')) {
    line = get_token(line);
    i++;
  }

  *num += i;
}

int is_coordinate(char *line) {
  int is_coordinate = 0;

  if (line[0] == 'v' && line[1] == ' ') {
    is_coordinate = 1;
  }

  return is_coordinate;
}

void create_point(point *p, char *str, int *iterator) {
  char *eptr;

  str = get_token(str);
  double x = strtod(str, &eptr);
  double y = strtod(eptr, &eptr);
  double z = strtod(eptr, &eptr);

  (p + *iterator)->x = x;
  (p + *iterator)->y = y;
  (p + *iterator)->z = z;

  *iterator += 1;
}

void create_line(line *lines, char *str, int *iterator) {
  int a, b, first_point = 0;

  str = get_token(str);
  first_point = get_point_number(str);
  a = first_point;
  str = get_token(str);

  while (str[0] && (str[0] != '\r' && str[0] != '\n')) {
    b = get_point_number(str);
    lines[*iterator].a = a;
    lines[*iterator].b = b;

    *iterator += 1;
    a = b;

    str = get_token(str);
  }
  lines[*iterator].a = a;
  lines[*iterator].b = first_point;
  *iterator += 1;
}

int is_surface(char *str) {
  int is_surf = 0;

  if (str[0] == 'f' && str[1] == ' ') {
    is_surf = 1;
  }

  return is_surf;
}

char *get_token(char *str) {
  int shift = 0;

  while (*(str + shift) != ' ') {
    if (*(str + shift) == '\n' || *(str + shift) == '\r') {
      break;
    }
    shift += 1;
  }
  shift += 1;
  return (str + shift);
}

int get_point_number(char *token) {
  char *end;
  int tmp = strtol(token, &end, 10);
  return tmp;
}