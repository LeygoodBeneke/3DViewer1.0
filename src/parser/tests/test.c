#include "test.h"

#include "check.h"

#define eps 1e-6

START_TEST(cube_equals) {
  point *points;
  line *lines;
  int points_len;
  int line_len;

  char *file_path = "obj_files_for_testing/cube.txt";

  parser(file_path, &points, &points_len, &lines, &line_len);

  double point_mass[8][3] = {
      {48.656645, 48.864150, 4.766477},  {58.189599, 48.864150, 4.766477},
      {48.656645, 58.397104, 4.766477},  {58.189599, 58.397104, 4.766477},
      {48.656645, 58.397104, -4.766477}, {58.189599, 58.397104, -4.766477},
      {48.656645, 48.864150, -4.766477}, {58.189599, 48.864150, -4.766477}};

  int line_mass[24][2] = {{1, 2}, {2, 4}, {4, 3}, {3, 1}, {3, 4}, {4, 6},
                          {6, 5}, {5, 3}, {5, 6}, {6, 8}, {8, 7}, {7, 5},
                          {7, 8}, {8, 2}, {2, 1}, {1, 7}, {2, 8}, {8, 6},
                          {6, 4}, {4, 2}, {7, 1}, {1, 3}, {3, 5}, {5, 7}};

  ck_assert_int_eq(points_len, 8);
  ck_assert_int_eq(line_len, 24);

  for (int i = 0; i < 8; i++) {
    ck_assert_double_eq_tol(points[i].x, point_mass[i][0], eps);
    ck_assert_double_eq_tol(points[i].y, point_mass[i][1], eps);
    ck_assert_double_eq_tol(points[i].z, point_mass[i][2], eps);
  }

  for (int i = 0; i < 24; ++i) {
    ck_assert_int_eq(lines[i].a, line_mass[i][0]);
    ck_assert_int_eq(lines[i].b, line_mass[i][1]);
  }

  free(points);
  free(lines);
}

int main(void) {
  Suite *parser_test = suite_create("parser");
  TCase *tc = tcase_create("parser");
  SRunner *sr = srunner_create(parser_test);

  suite_add_tcase(parser_test, tc);

  tcase_add_test(tc, cube_equals);

  //  srunner_run_all(sr, CK_NORMAL);
  srunner_run(sr, "parser", "parser", CK_NORMAL);

  free(sr);
  free(tc);
  free(parser_test);

  return 0;
}