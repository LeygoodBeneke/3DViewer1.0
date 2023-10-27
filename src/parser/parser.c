#include "parser.h"

void size_of_surf(char *line, int *num);

void parser(char *file_path, point **points, int *points_len, line **lines, int *surf_len) {
    int trigger = 0;
    int error = 0;
    int i = 0;
    int true = 1;
    char *line = NULL; //нужно чистить
    size_t len = 0;
    long read = 0;

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        error = 1;
    }

    number_of_points_and_surfaces(points_len, surf_len, fp);
    *points = malloc(*points_len * sizeof(point)); // нужно чистить

    while (read != -1 && error == 0) {
        read = getline(&line, &len, fp);

        if (read != -1) {
            if (is_coordinate(line, &trigger)) {
                create_point((*points + i), line);
                i++;
            } else if (trigger == 1) {
                true = 0;
            }
        } else {
            true = 0;
        }
    }

    if (line) {
        free(line);
    }

    fseek(fp, 0, SEEK_SET);

    *lines = get_lines(fp, surf_len);

    if (fp)
        fclose(fp);
}

void number_of_points_and_surfaces(int *number_points, int *number_surfaces, FILE *fp) {
    char *line = NULL; //нужно чистить
    size_t len = 0;
    ssize_t read;
    int trigger = 0;

    *number_points = 0;
    *number_surfaces = 0;

    while ((read = getline(&line, &len, fp) != -1)) {
        if (is_coordinate(line, &trigger)) {
            *number_points += 1;
        } else if (is_surface(line)) {
            size_of_surf(line, number_surfaces);
        }
    }

    fseek(fp, 0, SEEK_SET);

    if (line)
        free(line);
}

void size_of_surf(char *line, int *num) {

    int i = -1;
    while(line[0] && (line[0] != '\r' && line[0] != '\n')){
        line = get_token(line);
        i++;
    }

    *num += i;
}

int is_coordinate(char *line, int *trigger) {
    int is_coordinate = 0;


    if (line[0] == 'v' && line[1] == ' ') {
        is_coordinate = 1;
        *trigger = 1;
    }

    return is_coordinate;
}

void create_point(point *p, char *line) {
    char *eptr;

    strtok(line, " ");
    double x = strtod(strtok(NULL, " "), &eptr);
    double y = strtod(strtok(NULL, " "), &eptr);
    double z = strtod(strtok(NULL, " "), &eptr);

    p->x = x;
    p->y = y;
    p->z = z;
}

line *get_lines(FILE *fp, int *number_surfaces) {
    ssize_t read = 0;
    line *lines;

    while(read != -1) {
        size_t len = 0;

        char *str = NULL;
        int true = 1;
        int i = 0;

        read = getline(&str, &len, fp);

        while (!is_surface(str)) {
            read = getline(&str, &len, fp);
        }

        lines = malloc(*number_surfaces * sizeof(line));

        while (true) {
            if (read != -1) {
                if (is_surface(str)) {
                    create_line(lines, str, &i);
                }
            } else {
                true = 0;
            }

            read = getline(&str, &len, fp);
        }

        if (str) {
            free(str);
        }
    }
    return lines;
}

void create_line(line *lines, char *str, int *i) {
    int a,b = 0;

    str = get_token(str);
    int first_point = get_point_number(str);
    a = first_point;
    str = get_token(str);
    while (str[0] && (str[0] != '\r' && str[0] != '\n')) {
        b = get_point_number(str);
         lines[*i].a = a;
         lines[*i].b = b;

         *i += 1;
         a = b;

         str = get_token(str);
    }
    lines[*i].a = a;
    lines[*i].b = first_point;
    *i += 1;
}

int is_surface(char *str) {
    int is_surf = 0;

    if (str[0] == 'f' && str[1] == ' ') {
        is_surf = 1;
    }

    return is_surf;
}

char* get_token(char *str) {
    int shift = 0;

    while(*(str + shift) != ' ') {
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