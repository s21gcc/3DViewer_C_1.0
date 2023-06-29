#include <check.h>

#include "viewer.h"
#define ACCURACY 1e-4

START_TEST(model_load_test_1) {
  ObjData obj = {0, 0, NULL, NULL};
  char file[20] = "test_empty.obj";
  parse_obj_file(file, &obj);
  ObjData objTest = {0, 0, NULL, NULL};
  ck_assert_int_eq(obj.num_facets, objTest.num_facets);
  ck_assert_int_eq(obj.num_vertexes, objTest.num_vertexes);
  ck_assert_ptr_null(obj.face);
  ck_assert_ptr_null(obj.vertexes);
}

START_TEST(model_load_test_2) {
  ObjData obj = {0, 0, NULL, NULL};
  char file[20] = "test_trash.obj";
  parse_obj_file(file, &obj);
  ObjData objTest = {0, 0, NULL, NULL};
  ck_assert_int_eq(obj.num_facets, objTest.num_facets);
  ck_assert_int_eq(obj.num_vertexes, objTest.num_vertexes);
  ck_assert_ptr_null(obj.face);
  ck_assert_ptr_null(obj.vertexes);
}

START_TEST(model_load_test_3) {
  ObjData obj = {0, 0, NULL, NULL};
  char file[20] = "cube.obj";
  parse_obj_file(file, &obj);
  ObjData objTest = {8, 30, NULL, NULL};
  ck_assert_int_eq(obj.num_facets, objTest.num_facets);
  ck_assert_int_eq(obj.num_vertexes, objTest.num_vertexes);
  ck_assert_ptr_nonnull(obj.face);
  ck_assert_ptr_nonnull(obj.vertexes);
  free(obj.face);
  free(obj.vertexes);
}

START_TEST(model_load_test_4) {
  ObjData obj = {0, 0, NULL, NULL};
  char file[20] = "nothing.obj";
  int result = parse_obj_file(file, &obj);
  ck_assert_int_eq(result, 1);
}

START_TEST(affine_test_1) {
  ObjData obj = {0, 0, NULL, NULL};
  char file[20] = "cube.obj";
  parse_obj_file(file, &obj);
  translate(10, 0, 0, &obj);
  ck_assert_int_eq(1, 1);
  double temp = 0;
  for (int i = 0; i < obj.num_vertexes * 3; i++) {
    temp += obj.vertexes[i];
  }
  free(obj.face);
  free(obj.vertexes);
  ck_assert_double_eq_tol(temp, 104, ACCURACY);
}

START_TEST(affine_test_2) {
  ObjData obj = {0, 0, NULL, NULL};
  char file[20] = "cube.obj";
  parse_obj_file(file, &obj);
  translate(0, 21, 0, &obj);
  double temp = 0;
  for (int i = 0; i < obj.num_vertexes * 3; i++) {
    temp += obj.vertexes[i];
  }
  free(obj.face);
  free(obj.vertexes);
  ck_assert_double_eq_tol(temp, 192, ACCURACY);
}

START_TEST(affine_test_3) {
  ObjData obj = {0, 0, NULL, NULL};
  char file[20] = "cube.obj";
  parse_obj_file(file, &obj);
  translate(0, 0, 99, &obj);
  double temp = 0;
  for (int i = 0; i < obj.num_vertexes * 3; i++) {
    temp += obj.vertexes[i];
  }
  free(obj.face);
  free(obj.vertexes);
  ck_assert_double_eq_tol(temp, 816, ACCURACY);
}

START_TEST(affine_test_4) {
  ObjData obj = {0, 0, NULL, NULL};
  char file[20] = "cube.obj";
  parse_obj_file(file, &obj);
  scale(2, 1, &obj);
  double temp = 0;
  for (int i = 0; i < obj.num_vertexes * 3; i++) {
    temp += obj.vertexes[i];
  }
  free(obj.face);
  free(obj.vertexes);
  ck_assert_double_eq_tol(temp, 32, ACCURACY);
}

START_TEST(affine_test_5) {
  ObjData obj = {0, 0, NULL, NULL};
  char file[20] = "cube.obj";
  parse_obj_file(file, &obj);
  scale(1, 5, &obj);
  double temp = 0;
  for (int i = 0; i < obj.num_vertexes * 3; i++) {
    temp += obj.vertexes[i];
  }
  free(obj.face);
  free(obj.vertexes);
  ck_assert_double_eq_tol(temp, 56, ACCURACY);
}

START_TEST(affine_test_6) {
  ObjData obj = {0, 0, NULL, NULL};
  char file[20] = "cube.obj";
  parse_obj_file(file, &obj);
  rotation(&obj, 90, 0);
  double temp = 0;
  for (int i = 0; i < obj.num_vertexes * 3; i++) {
    temp += obj.vertexes[i];
  }
  free(obj.face);
  free(obj.vertexes);
  ck_assert_double_eq_tol(temp, 8, ACCURACY);
}

START_TEST(affine_test_7) {
  ObjData obj = {0, 0, NULL, NULL};
  char file[20] = "cube.obj";
  parse_obj_file(file, &obj);
  rotation(&obj, 45, 1);
  double temp = 0;
  for (int i = 0; i < obj.num_vertexes * 3; i++) {
    temp += obj.vertexes[i];
  }
  free(obj.face);
  free(obj.vertexes);
  ck_assert_double_eq_tol(temp, 19.3137, ACCURACY);
}

START_TEST(affine_test_8) {
  ObjData obj = {0, 0, NULL, NULL};
  char file[20] = "cube.obj";
  parse_obj_file(file, &obj);
  rotation(&obj, 69, 2);
  double temp = 0;
  for (int i = 0; i < obj.num_vertexes * 3; i++) {
    temp += obj.vertexes[i];
  }
  free(obj.face);
  free(obj.vertexes);
  ck_assert_double_eq_tol(temp, 13.7339, ACCURACY);
}

int main() {
  Suite *s1 = suite_create("3D Viewer Tests");
  TCase *tc1_1 = tcase_create("3D Viewer Tests");
  SRunner *sr = srunner_create(s1);
  double result = 0;

  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, model_load_test_1);
  tcase_add_test(tc1_1, model_load_test_2);
  tcase_add_test(tc1_1, model_load_test_3);
  tcase_add_test(tc1_1, model_load_test_4);
  tcase_add_test(tc1_1, affine_test_1);
  tcase_add_test(tc1_1, affine_test_2);
  tcase_add_test(tc1_1, affine_test_3);
  tcase_add_test(tc1_1, affine_test_4);
  tcase_add_test(tc1_1, affine_test_5);
  tcase_add_test(tc1_1, affine_test_6);
  tcase_add_test(tc1_1, affine_test_7);
  tcase_add_test(tc1_1, affine_test_8);

  srunner_run_all(sr, CK_ENV);
  result = srunner_ntests_failed(sr);
  srunner_free(sr);
  return result == 0 ? 0 : 1;
}
