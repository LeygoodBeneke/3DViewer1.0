#include "parser.h"
//TODO скорее всего есть утечки, необходимо проверить и исправить
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

void number_of_points_and_planes(int* number_points, int* number_planes, FILE* fp) {
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
    int trigger = 0; //TODO вспомнить зачем это было нужно
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

}