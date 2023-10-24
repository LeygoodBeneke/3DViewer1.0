#include "parser.h"
//TODO скорее всего есть утечки, необходимо проверить и исправить
//TODO написать функцию для очистки массива surface и points
//TODO переписать surface, нужно получить массив типа [[1,2], [2,4], [4,3], [3,1], [4,6],[6,5]]. [1,2]- это структура типа Line
/*
void parser(char *file_path, point **points, int *points_len, surface **surf, int *surf_len) {
    int trigger = 0;
    int error = 0;
    int i = 0;
    int true = 1;
    char* line = NULL; //нужно чистить
    size_t len = 0;
    ssize_t read;

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        error = 1;
    }

    number_of_points_and_planes(points_len, surf_len, fp);
    *points = malloc(*points_len * sizeof(point)); // нужно чистить

    while (true && error == 0) {
        read = getline(&line, &len, fp);

        if(read != -1) {
            if (is_coordinate(line, &trigger)) {
                create_point((*points+i), line);
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

    *surf = malloc(1 * sizeof (surface));
    *surf = get_surface(*points, i, fp, *surf_len, *points);

}

void number_of_points_and_surfaces(int* number_points, int* number_planes, FILE* fp) {
    char* line = NULL; //нужно чистить
    size_t len = 0;
    ssize_t read;
    int trigger = 0;

    *number_points = 0;
    *number_planes = 0;

    while ((read = getline(&line, &len, fp) != -1)) {
        if (is_coordinate(line, &trigger)) {
            *number_points += 1;
        } else if (is_surface(line)) {
            *number_planes += 1;
        }
    }

    fseek(fp, 0, SEEK_SET);

    if(line)
        free(line);
}

int is_coordinate (char *line, int *trigger) {
    int is_coordinate = 0;


    if (line[0] == 'v' && line[1] == ' ') {
        is_coordinate = 1;
        *trigger = 1;
    }

    return is_coordinate;
}

void create_point(point* p, char* line) {
    char *eptr;

    strtok(line, " ");
    //TODO исправить ошибку с точностью при приведении к double
    double x = strtod(strtok(NULL, " "), &eptr);
    double y = strtod(strtok(NULL, " "), &eptr);
    double z = strtod(strtok(NULL, " "), &eptr);

    p->x = x;
    p->y = y;
    p->z = z;
}

surface *get_surface(point *p, int length, FILE *fp, int number_surfaces, point *points) {
    size_t len = 0;
    ssize_t read = 0;
    char* line = NULL;// нужно чистить
    int true = 1;
    int i = 0;


    surface *surfaces = malloc(number_surfaces * sizeof(surface)); //TODO памяти выделяется больше чем надо ПОФИКСИТЬ!!!!

    while(true) {
        read = getline(&line, &len, fp);

        if (read != -1) {
            if(is_surface(line)) {
                int number_of_coord = number_of_coordinates(line);
                surfaces[i].len = number_of_coord;
                surfaces[i].points = malloc(number_of_coord * sizeof(point));

                create_surface(&surfaces[i], line, points);
                i++;
            }
        } else {
            true = 0;
        }
    }

    if(line)
        free(line);

    return surfaces;
}

int is_surface(char* line) {
    int is_surf = 0;

    if (line[0] == 'f' && line[1] == ' ') {
        is_surf = 1;
    }

    return is_surf;
}

int number_of_coordinates(char *line) {
    int str_len = strlen(line);
    char* tmp_line = malloc(str_len * sizeof(char));

    strcpy(tmp_line, line);

    char* token = strtok(tmp_line, " ");
    int i = 0;

    while (token != NULL) {
        token = strtok(NULL, " ");
        i++;
    }
    free(tmp_line);

    //TODO исправить ошибку с подсчетом количества координат
    return i-1;
}

void create_surface(surface *surf, char *line, point *points) {
    int str_len = strlen(line);
    char* tmp_line = malloc(str_len * sizeof(char));

    strcpy(tmp_line, line);

    char* token = strtok(tmp_line, " /");
    int point_num = 0;
    int i = 0;
    //TODO исправить оишбку с точность при приведении к int
    //TODO заменить функцию atoi на strtol
    while(token != NULL) {
        token = strtok(NULL, " /");
        if(token != NULL) {
            point_num = atoi(token);

            surf->points[i].x = points[point_num].x;
            surf->points[i].y = points[point_num].y;
            surf->points[i].z = points[point_num].z;

            i++;

            strtok(NULL, " /");
            strtok(NULL, " /");
        }
    }
    free(tmp_line);
}*/
/****************************** Второй вариант со структурой Line *****************************************************/

void parser(char *file_path, point **points, int *points_len, line **lines, int *surf_len) {
    int trigger = 0;
    int error = 0;
    int i = 0;
    int true = 1;
    char* line = NULL; //нужно чистить
    size_t len = 0;
    ssize_t read;

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        error = 1;
    }

    number_of_points_and_surfaces(points_len, surf_len, fp);
    *points = malloc(*points_len * sizeof(point)); // нужно чистить

    while (true && error == 0) {
        read = getline(&line, &len, fp);

        if(read != -1) {
            if (is_coordinate(line, &trigger)) {
                create_point((*points+i), line);
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

    *lines = malloc(1 * sizeof (surface));
    *lines = get_lines(fp, surf_len);

}

void number_of_points_and_surfaces(int* number_points, int* number_surfaces, FILE* fp) {
    char* line = NULL; //нужно чистить
    size_t len = 0;
    ssize_t read;
    int trigger = 0;

    *number_points = 0;
    *number_surfaces = 0;

    while ((read = getline(&line, &len, fp) != -1)) {
        if (is_coordinate(line, &trigger)) {
            *number_points += 1;
        } else if (is_surface(line)) {
            *number_surfaces += 1;
        }
    }

    fseek(fp, 0, SEEK_SET);

    if(line)
        free(line);
}

int is_coordinate (char *line, int *trigger) {
    int is_coordinate = 0;


    if (line[0] == 'v' && line[1] == ' ') {
        is_coordinate = 1;
        *trigger = 1;
    }

    return is_coordinate;
}

void create_point(point* p, char* line) {
    char *eptr;

    strtok(line, " ");
    //TODO исправить ошибку с точностью при приведении к double
    double x = strtod(strtok(NULL, " "), &eptr);
    double y = strtod(strtok(NULL, " "), &eptr);
    double z = strtod(strtok(NULL, " "), &eptr);

    p->x = x;
    p->y = y;
    p->z = z;
}

line *get_lines(FILE *fp, int *number_surfaces) {
    size_t len = 0;
    ssize_t read = 0;
    char* str = NULL;// нужно чистить
    int true = 1;
    int i = 0;

    read = getline(&str, &len, fp);
    int number_of_coord = number_of_coordinates(str); //TODO поменять как нибудь название функции

    line *lines = malloc(*number_surfaces * number_of_coord * sizeof(line)); //TODO памяти выделяется больше чем надо ПОФИКСИТЬ!!!!

    *number_surfaces *= number_of_coord;

    while(true) {
        if (read != -1) {
            if(is_surface(str)) {
                create_line(lines, str, &i);
//                i++;
            }
        } else {
            true = 0;
        }

        read = getline(&str, &len, fp);
    }

    if(str)
        free(str);

    return lines;
}

void create_line(line *lines, char *str, int *i) {

    int str_len = strlen(str);
    char* tmp_line = malloc(str_len * sizeof(char));

    strcpy(tmp_line, str);

    char* token = strtok(tmp_line, " /");
    int a = 0;
    int b = 0;

    char *prev_token = strtok(NULL, " /");
    strtok(NULL, " /");
    strtok(NULL, " /");

    int first_point = atoi(prev_token);
    a = atoi(prev_token);
    //TODO исправить оишбку с точность при приведении к int
    //TODO заменить функцию atoi на strtol
    while(token != NULL) {
        if (*i == 3) {
            lines[*i].a = a;
            lines[*i].b = first_point;

            *i += 1;
        } else {
            token = strtok(NULL, " /");
            if (token != NULL) {
                b = atoi(token);

                lines[*i].a = a;
                lines[*i].b = b;

                *i += 1;

                strtok(NULL, " /");
                strtok(NULL, " /");

                a = b;
            }
        }
    }

//        free(tmp_line); //TODO какая-то неведомая херня, теряется указатель
}

int is_surface(char* str) {
    int is_surf = 0;

    if (str[0] == 'f' && str[1] == ' ') {
        is_surf = 1;
    }

    return is_surf;
}

int number_of_coordinates(char *line) {
    int str_len = strlen(line);
    char* tmp_line = malloc(str_len * sizeof(char));

    strcpy(tmp_line, line);

    char* token = strtok(tmp_line, " ");
    int i = 0;

    while (token != NULL) {
        token = strtok(NULL, " ");
        i++;
    }

    free(tmp_line);

    //TODO исправить ошибку с подсчетом количества координат
    return i-1;
}
