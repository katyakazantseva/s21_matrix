#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_matrix.h"

START_TEST(test_creat_1) {
  matrix_t mat;
  ck_assert_int_eq(0, s21_create_matrix(1, 1, &mat));
  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(test_creat_2) {
  matrix_t mat = {0};
  ck_assert_int_eq(1, s21_create_matrix(1, 0, &mat));
  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(test_eq_1) {
  matrix_t mat1;
  matrix_t mat2;
  s21_create_matrix(1, 1, &mat1);
  s21_create_matrix(1, 1, &mat2);
  mat1.matrix[0][0] = 1;
  mat2.matrix[0][0] = 1;
  ck_assert_int_eq(1, s21_eq_matrix(&mat1, &mat2));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(test_eq_2) {
  matrix_t mat1;
  matrix_t mat2;
  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 2, &mat2);
  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = 2;
  mat1.matrix[1][0] = 1;
  mat1.matrix[1][1] = 2;
  mat2.matrix[0][0] = 1;
  mat2.matrix[0][1] = 2;
  mat2.matrix[1][0] = 1;
  mat2.matrix[1][1] = 2;
  ck_assert_int_eq(1, s21_eq_matrix(&mat1, &mat2));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(test_eq_3) {
  matrix_t mat1;
  matrix_t mat2;
  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 2, &mat2);
  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = 2;
  mat1.matrix[1][0] = 1;
  mat1.matrix[1][1] = 2;
  mat2.matrix[0][0] = 1;
  mat2.matrix[0][1] = 2;
  mat2.matrix[1][0] = 1;
  mat2.matrix[1][1] = 3;
  ck_assert_int_eq(0, s21_eq_matrix(&mat1, &mat2));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(test_eq_4) {
  matrix_t mat1;
  matrix_t mat2;
  s21_create_matrix(1, 2, &mat1);
  s21_create_matrix(2, 2, &mat2);
  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = 2;
  mat2.matrix[0][0] = 1;
  mat2.matrix[0][1] = 2;
  mat2.matrix[1][0] = 1;
  mat2.matrix[1][1] = 2;
  ck_assert_int_eq(0, s21_eq_matrix(&mat1, &mat2));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(test_eq_5) {
  matrix_t mat1;
  matrix_t mat2;
  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 1, &mat2);
  mat2.matrix[0][0] = 1;
  mat2.matrix[1][0] = 2;
  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = 2;
  mat1.matrix[1][0] = 1;
  mat1.matrix[1][1] = 2;
  ck_assert_int_eq(0, s21_eq_matrix(&mat1, &mat2));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(test_eq_6) {
  matrix_t mat1;
  matrix_t mat2;
  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 2, &mat2);
  mat1.matrix[0][0] = 1.111111;
  mat1.matrix[0][1] = 1.919191;
  mat1.matrix[1][0] = 1.000000;
  mat1.matrix[1][1] = 2.123456;
  mat2.matrix[0][0] = 1.111111;
  mat2.matrix[0][1] = 1.919191;
  mat2.matrix[1][0] = 1.000000;
  mat2.matrix[1][1] = 2.123456;
  ck_assert_int_eq(1, s21_eq_matrix(&mat1, &mat2));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

int compare_matrices(matrix_t A, matrix_t B) {
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      if (A.matrix[i][j] != B.matrix[i][j]) {
        return 1;
      }
    }
  }
  return 0;
}

START_TEST(test_sum_1) {
  matrix_t mat1;
  matrix_t mat2;
  matrix_t rez;
  matrix_t rez1;
  s21_create_matrix(1, 1, &mat1);
  s21_create_matrix(1, 1, &mat2);
  s21_create_matrix(1, 1, &rez1);
  mat1.matrix[0][0] = 1;
  mat2.matrix[0][0] = 1;
  rez1.matrix[0][0] = 2;
  ck_assert_int_eq(0, s21_sum_matrix(&mat1, &mat2, &rez));
  ck_assert_int_eq(0, compare_matrices(rez, rez1));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&rez);
  s21_remove_matrix(&rez1);
}
END_TEST

START_TEST(test_sum_2) {
  matrix_t mat1;
  matrix_t mat2;
  matrix_t rez;
  matrix_t rez1;
  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 2, &mat2);
  s21_create_matrix(2, 2, &rez1);
  mat1.matrix[0][0] = 2;
  mat1.matrix[0][1] = 3;
  mat1.matrix[1][0] = 4;
  mat1.matrix[1][1] = 5;
  mat2.matrix[0][0] = 1;
  mat2.matrix[0][1] = 1;
  mat2.matrix[1][0] = 1;
  mat2.matrix[1][1] = 1;
  rez1.matrix[0][0] = 3;
  rez1.matrix[0][1] = 4;
  rez1.matrix[1][0] = 5;
  rez1.matrix[1][1] = 6;
  ck_assert_int_eq(0, s21_sum_matrix(&mat1, &mat2, &rez));
  ck_assert_int_eq(0, compare_matrices(rez, rez1));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&rez);
  s21_remove_matrix(&rez1);
}
END_TEST

START_TEST(test_sum_3) {
  matrix_t mat1;
  matrix_t mat2;
  matrix_t rez;
  matrix_t rez1;
  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 2, &mat2);
  s21_create_matrix(2, 2, &rez1);
  mat1.matrix[0][0] = 2.111111;
  mat1.matrix[0][1] = 3.444444;
  mat1.matrix[1][0] = 4.333333;
  mat1.matrix[1][1] = 5.666666;
  mat2.matrix[0][0] = 3.111111;
  mat2.matrix[0][1] = 4.555555;
  mat2.matrix[1][0] = 5.333333;
  mat2.matrix[1][1] = 6.444444;
  rez1.matrix[0][0] = 5.222222;
  rez1.matrix[0][1] = 7.999999;
  rez1.matrix[1][0] = 9.666666;
  rez1.matrix[1][1] = 12.11111;
  ck_assert_int_eq(0, s21_sum_matrix(&mat1, &mat2, &rez));
  ck_assert_int_eq(0, compare_matrices(rez, rez1));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&rez);
  s21_remove_matrix(&rez1);
}

START_TEST(test_sum_4) {
  matrix_t mat1;
  matrix_t mat2;
  matrix_t rez;
  matrix_t rez1;
  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 2, &mat2);
  s21_create_matrix(2, 2, &rez1);
  mat1.matrix[0][0] = 2.111111;
  mat1.matrix[0][1] = 3.444444;
  mat1.matrix[1][0] = 4.333333;
  mat1.matrix[1][1] = 5.666666;
  mat2.matrix[0][0] = 3.111111;
  mat2.matrix[0][1] = 4.555555;
  mat2.matrix[1][0] = 5.333333;
  mat2.matrix[1][1] = 6.444444;
  rez1.matrix[0][0] = 5.222222;
  rez1.matrix[0][1] = 7.999999;
  rez1.matrix[1][0] = 9.666666;
  rez1.matrix[1][1] = 12;
  ck_assert_int_eq(0, s21_sum_matrix(&mat1, &mat2, &rez));
  ck_assert_int_eq(1, compare_matrices(rez, rez1));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&rez);
  s21_remove_matrix(&rez1);
}

START_TEST(test_sum_5) {
  matrix_t mat1 = {0};
  matrix_t mat2 = {0};
  matrix_t rez = {0};
  s21_create_matrix(1, 1, &mat1);
  s21_create_matrix(2, 2, &mat2);
  mat1.matrix[0][0] = 2.111111;
  mat2.matrix[0][0] = 3.111111;
  mat2.matrix[0][1] = 4.555555;
  mat2.matrix[1][0] = 5.333333;
  mat2.matrix[1][1] = 6.444444;
  ck_assert_int_eq(2, s21_sum_matrix(&mat1, &mat2, &rez));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&rez);
}

START_TEST(test_sum_6) {
  matrix_t mat1 = {0};
  matrix_t mat2;
  matrix_t rez;
  s21_create_matrix(2, 2, &mat2);
  mat2.matrix[0][0] = 3.111111;
  mat2.matrix[0][1] = 4.555555;
  mat2.matrix[1][0] = 5.333333;
  mat2.matrix[1][1] = 6.444444;
  ck_assert_int_eq(1, s21_sum_matrix(&mat1, &mat2, &rez));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}

START_TEST(test_sub_1) {
  matrix_t mat1;
  matrix_t mat2;
  matrix_t rez;
  matrix_t rez1;
  s21_create_matrix(1, 1, &mat1);
  s21_create_matrix(1, 1, &mat2);
  s21_create_matrix(1, 1, &rez1);
  mat1.matrix[0][0] = 1;
  mat2.matrix[0][0] = 1;
  rez1.matrix[0][0] = 0;
  ck_assert_int_eq(0, s21_sub_matrix(&mat1, &mat2, &rez));
  ck_assert_int_eq(0, compare_matrices(rez, rez1));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&rez);
  s21_remove_matrix(&rez1);
}
END_TEST

START_TEST(test_sub_2) {
  matrix_t mat1;
  matrix_t mat2;
  matrix_t rez;
  matrix_t rez1;
  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 2, &mat2);
  s21_create_matrix(2, 2, &rez1);
  mat1.matrix[0][0] = 5;
  mat1.matrix[0][1] = 4;
  mat1.matrix[1][0] = 3;
  mat1.matrix[1][1] = 2;
  mat2.matrix[0][0] = 1;
  mat2.matrix[0][1] = 1;
  mat2.matrix[1][0] = 1;
  mat2.matrix[1][1] = 1;
  rez1.matrix[0][0] = 4;
  rez1.matrix[0][1] = 3;
  rez1.matrix[1][0] = 2;
  rez1.matrix[1][1] = 1;
  ck_assert_int_eq(0, s21_sub_matrix(&mat1, &mat2, &rez));
  ck_assert_int_eq(0, compare_matrices(rez, rez1));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&rez);
  s21_remove_matrix(&rez1);
}
END_TEST

START_TEST(test_sub_4) {
  matrix_t mat1;
  matrix_t mat2;
  matrix_t rez = {0};
  s21_create_matrix(1, 1, &mat1);
  s21_create_matrix(2, 2, &mat2);
  mat1.matrix[0][0] = 2.111111;
  mat2.matrix[0][0] = 3.111111;
  mat2.matrix[0][1] = 4.555555;
  mat2.matrix[1][0] = 5.333333;
  mat2.matrix[1][1] = 6.444444;
  ck_assert_int_eq(2, s21_sub_matrix(&mat1, &mat2, &rez));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&rez);
}
END_TEST

START_TEST(test_sub_5) {
  matrix_t mat1 = {0};
  matrix_t mat2;
  matrix_t rez;
  s21_create_matrix(1, 1, &mat2);
  mat2.matrix[0][0] = 3.111111;
  ck_assert_int_eq(1, s21_sub_matrix(&mat1, &mat2, &rez));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(test_muln_1) {
  matrix_t mat1;
  matrix_t rez;
  matrix_t rez1;
  double m = 5;
  s21_create_matrix(1, 1, &mat1);
  s21_create_matrix(1, 1, &rez1);
  mat1.matrix[0][0] = 1;
  rez1.matrix[0][0] = 5;
  ck_assert_int_eq(0, s21_mult_number(&mat1, m, &rez));
  ck_assert_int_eq(0, compare_matrices(rez, rez1));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&rez);
  s21_remove_matrix(&rez1);
}
END_TEST

START_TEST(test_muln_2) {
  matrix_t mat1;
  matrix_t rez;
  matrix_t rez1;
  double m = 2;
  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 2, &rez1);
  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = 2;
  mat1.matrix[1][0] = 3;
  mat1.matrix[1][1] = 4;
  rez1.matrix[0][0] = 2;
  rez1.matrix[0][1] = 4;
  rez1.matrix[1][0] = 6;
  rez1.matrix[1][1] = 8;
  ck_assert_int_eq(0, s21_mult_number(&mat1, m, &rez));
  ck_assert_int_eq(0, compare_matrices(rez, rez1));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&rez);
  s21_remove_matrix(&rez1);
}
END_TEST

START_TEST(test_muln_4) {
  matrix_t mat1 = {0};
  matrix_t rez;
  double m = 2.1;
  ck_assert_int_eq(1, s21_mult_number(&mat1, m, &rez));
  s21_remove_matrix(&mat1);
}
END_TEST

// START_TEST(test_muln_5) {
//   matrix_t mat1;
//   matrix_t rez;
//   s21_create_matrix(2, 2, &mat1);
//   mat1.matrix[0][0] = 1;
//   mat1.matrix[0][1] = 2;
//   mat1.matrix[1][0] = 3;
//   mat1.matrix[1][1] = 4;
//   ck_assert_int_eq(2, s21_mult_number(&mat1, *nan, &rez));
//   s21_remove_matrix(&mat1);
//   s21_remove_matrix(&rez);
// }
// END_TEST

START_TEST(test_mulm_1) {
  matrix_t mat1;
  matrix_t mat2;
  matrix_t rez;
  matrix_t rez1;
  s21_create_matrix(1, 1, &mat1);
  s21_create_matrix(1, 1, &mat2);
  s21_create_matrix(1, 1, &rez1);
  mat1.matrix[0][0] = 1;
  mat2.matrix[0][0] = 1;
  rez1.matrix[0][0] = 1;
  ck_assert_int_eq(0, s21_mult_matrix(&mat1, &mat2, &rez));
  ck_assert_int_eq(0, compare_matrices(rez, rez1));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&rez);
  s21_remove_matrix(&rez1);
}
END_TEST

START_TEST(test_mulm_2) {
  matrix_t mat1;
  matrix_t mat2;
  matrix_t rez;
  matrix_t rez1;
  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 2, &mat2);
  s21_create_matrix(2, 2, &rez1);
  mat1.matrix[0][0] = 2;
  mat1.matrix[0][1] = 3;
  mat1.matrix[1][0] = 6;
  mat1.matrix[1][1] = 3;
  mat2.matrix[0][0] = 1;
  mat2.matrix[0][1] = 6;
  mat2.matrix[1][0] = 2;
  mat2.matrix[1][1] = 0;
  rez1.matrix[0][0] = 8;
  rez1.matrix[0][1] = 12;
  rez1.matrix[1][0] = 12;
  rez1.matrix[1][1] = 36;
  ck_assert_int_eq(0, s21_mult_matrix(&mat1, &mat2, &rez));
  ck_assert_int_eq(0, compare_matrices(rez, rez1));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&rez);
  s21_remove_matrix(&rez1);
}
END_TEST

START_TEST(test_mulm_3) {
  matrix_t mat1;
  matrix_t mat2;
  matrix_t rez;
  matrix_t rez1;
  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 2, &mat2);
  s21_create_matrix(2, 2, &rez1);
  mat1.matrix[0][0] = 2;
  mat1.matrix[0][1] = 3;
  mat1.matrix[1][0] = 6;
  mat1.matrix[1][1] = 3;
  mat2.matrix[0][0] = 1;
  mat2.matrix[0][1] = 6;
  mat2.matrix[1][0] = 2;
  mat2.matrix[1][1] = 0;
  rez1.matrix[0][0] = 8;
  rez1.matrix[0][1] = 12;
  rez1.matrix[1][0] = 12;
  rez1.matrix[1][1] = 36;
  ck_assert_int_eq(0, s21_mult_matrix(&mat1, &mat2, &rez));
  ck_assert_int_eq(0, compare_matrices(rez, rez1));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&rez);
  s21_remove_matrix(&rez1);
}
END_TEST

START_TEST(test_mulm_4) {
  matrix_t mat1;
  matrix_t mat2;
  matrix_t rez;
  matrix_t rez1;
  s21_create_matrix(1, 2, &mat1);
  s21_create_matrix(2, 3, &mat2);
  s21_create_matrix(1, 3, &rez1);
  mat1.matrix[0][0] = 2;
  mat1.matrix[0][1] = 3;
  mat2.matrix[0][0] = 1;
  mat2.matrix[0][1] = 6;
  mat2.matrix[0][2] = 6;
  mat2.matrix[1][0] = 2;
  mat2.matrix[1][1] = 0;
  mat2.matrix[1][1] = 0;
  rez1.matrix[0][0] = 8;
  rez1.matrix[0][1] = 12;
  rez1.matrix[0][2] = 12;
  ck_assert_int_eq(0, s21_mult_matrix(&mat1, &mat2, &rez));
  ck_assert_int_eq(0, compare_matrices(rez, rez1));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&rez);
  s21_remove_matrix(&rez1);
}
END_TEST

START_TEST(test_mulm_5) {
  matrix_t mat1;
  matrix_t mat2;
  matrix_t rez;
  s21_create_matrix(1, 1, &mat1);
  s21_create_matrix(2, 3, &mat2);
  mat1.matrix[0][0] = 2;
  mat2.matrix[0][0] = 1;
  mat2.matrix[0][1] = 6;
  mat2.matrix[1][0] = 2;
  mat2.matrix[1][1] = 0;
  ck_assert_int_eq(2, s21_mult_matrix(&mat1, &mat2, &rez));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&rez);
}
END_TEST

START_TEST(test_mulm_6) {
  matrix_t mat1;
  matrix_t mat2 = {0};
  matrix_t rez;
  s21_create_matrix(1, 1, &mat1);
  mat1.matrix[0][0] = 2;
  ck_assert_int_eq(1, s21_mult_matrix(&mat1, &mat2, &rez));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(test_trans_1) {
  matrix_t mat1;
  matrix_t rez;
  matrix_t rez1;
  s21_create_matrix(1, 1, &mat1);
  s21_create_matrix(1, 1, &rez1);
  mat1.matrix[0][0] = 1;
  rez1.matrix[0][0] = 1;
  ck_assert_int_eq(0, s21_transpose(&mat1, &rez));
  ck_assert_int_eq(0, compare_matrices(rez, rez1));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&rez);
  s21_remove_matrix(&rez1);
}
END_TEST

START_TEST(test_trans_2) {
  matrix_t mat1;
  matrix_t rez;
  matrix_t rez1;
  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 2, &rez1);
  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = 2;
  mat1.matrix[1][0] = 3;
  mat1.matrix[1][1] = 4;
  rez1.matrix[0][0] = 1;
  rez1.matrix[0][1] = 3;
  rez1.matrix[1][0] = 2;
  rez1.matrix[1][1] = 4;
  ck_assert_int_eq(0, s21_transpose(&mat1, &rez));
  ck_assert_int_eq(0, compare_matrices(rez, rez1));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&rez);
  s21_remove_matrix(&rez1);
}
END_TEST

START_TEST(test_trans_3) {
  matrix_t mat1;
  matrix_t rez;
  matrix_t rez1;
  s21_create_matrix(2, 3, &mat1);
  s21_create_matrix(3, 2, &rez1);
  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = 2;
  mat1.matrix[0][2] = 3;
  mat1.matrix[1][0] = 3;
  mat1.matrix[1][1] = 4;
  mat1.matrix[1][2] = 5;
  rez1.matrix[0][0] = 1;
  rez1.matrix[0][1] = 3;
  rez1.matrix[1][0] = 2;
  rez1.matrix[1][1] = 4;
  rez1.matrix[2][0] = 3;
  rez1.matrix[2][1] = 5;
  ck_assert_int_eq(0, s21_transpose(&mat1, &rez));
  ck_assert_int_eq(0, compare_matrices(rez, rez1));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&rez);
  s21_remove_matrix(&rez1);
}
END_TEST

START_TEST(test_trans_4) {
  matrix_t rez;
  matrix_t mat1 = {0};
  ck_assert_int_eq(1, s21_transpose(&mat1, &rez));
  s21_remove_matrix(&mat1);
}
END_TEST

START_TEST(test_calc_1) {
  matrix_t mat1;
  matrix_t rez;
  matrix_t rez1;
  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 2, &rez1);
  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = 2;
  mat1.matrix[1][0] = 3;
  mat1.matrix[1][1] = 5;
  rez1.matrix[0][0] = 5;
  rez1.matrix[0][1] = -3;
  rez1.matrix[1][0] = -2;
  rez1.matrix[1][1] = 1;
  ck_assert_int_eq(0, s21_calc_complements(&mat1, &rez));
  ck_assert_int_eq(0, compare_matrices(rez, rez1));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&rez);
  s21_remove_matrix(&rez1);
}
END_TEST

START_TEST(test_calc_2) {
  matrix_t mat1;
  matrix_t rez;
  matrix_t rez1;
  s21_create_matrix(3, 3, &mat1);
  s21_create_matrix(3, 3, &rez1);
  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = 2;
  mat1.matrix[0][2] = 3;
  mat1.matrix[1][0] = 0;
  mat1.matrix[1][1] = 4;
  mat1.matrix[1][2] = 2;
  mat1.matrix[2][0] = 5;
  mat1.matrix[2][1] = 2;
  mat1.matrix[2][2] = 1;
  rez1.matrix[0][0] = 0;
  rez1.matrix[0][1] = 10;
  rez1.matrix[0][2] = -20;
  rez1.matrix[1][0] = 4;
  rez1.matrix[1][1] = -14;
  rez1.matrix[1][2] = 8;
  rez1.matrix[2][0] = -8;
  rez1.matrix[2][1] = -2;
  rez1.matrix[2][2] = 4;
  ck_assert_int_eq(0, s21_calc_complements(&mat1, &rez));
  ck_assert_int_eq(0, compare_matrices(rez, rez1));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&rez);
  s21_remove_matrix(&rez1);
}
END_TEST

START_TEST(test_calc_3) {
  matrix_t mat1;
  matrix_t rez = {0};
  s21_create_matrix(3, 2, &mat1);
  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = 2;
  mat1.matrix[1][0] = 0;
  mat1.matrix[1][1] = 4;
  mat1.matrix[2][0] = 5;
  mat1.matrix[2][1] = 2;
  ck_assert_int_eq(2, s21_calc_complements(&mat1, &rez));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&rez);
}
END_TEST

START_TEST(test_calc_4) {
  matrix_t rez;
  matrix_t mat1 = {0};
  ck_assert_int_eq(1, s21_calc_complements(&mat1, &rez));
  s21_remove_matrix(&mat1);
}
END_TEST

START_TEST(test_determ_1) {
  matrix_t mat1;
  double rez = 0;
  s21_create_matrix(1, 1, &mat1);
  mat1.matrix[0][0] = 1;
  ck_assert_int_eq(0, s21_determinant(&mat1, &rez));
  ck_assert_double_eq(1, rez);
  s21_remove_matrix(&mat1);
}
END_TEST

START_TEST(test_determ_2) {
  matrix_t mat1;
  double rez = 0;
  s21_create_matrix(2, 2, &mat1);
  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = 2;
  mat1.matrix[1][0] = 3;
  mat1.matrix[1][1] = 4;
  ck_assert_int_eq(0, s21_determinant(&mat1, &rez));
  ck_assert_double_eq(-2, rez);
  s21_remove_matrix(&mat1);
}
END_TEST

START_TEST(test_determ_3) {
  matrix_t mat1;
  double rez = 0;
  s21_create_matrix(3, 3, &mat1);
  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = 2;
  mat1.matrix[0][2] = 3;
  mat1.matrix[1][0] = 4;
  mat1.matrix[1][1] = 5;
  mat1.matrix[1][2] = 6;
  mat1.matrix[2][0] = 7;
  mat1.matrix[2][1] = 8;
  mat1.matrix[2][2] = 9;
  ck_assert_int_eq(0, s21_determinant(&mat1, &rez));
  ck_assert_double_eq(0, rez);
  s21_remove_matrix(&mat1);
}
END_TEST

START_TEST(test_inverse_1) {
  matrix_t mat1;
  matrix_t rez;
  matrix_t rez1;
  s21_create_matrix(1, 1, &mat1);
  s21_create_matrix(1, 1, &rez1);
  mat1.matrix[0][0] = 5;
  rez1.matrix[0][0] = 0.2;
  ck_assert_int_eq(0, s21_inverse_matrix(&mat1, &rez));
  ck_assert_int_eq(0, compare_matrices(rez, rez1));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&rez);
  s21_remove_matrix(&rez1);
}
END_TEST

START_TEST(test_inverse_2) {
  matrix_t mat1;
  matrix_t rez;
  matrix_t rez1;
  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 2, &rez1);
  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = 2;
  mat1.matrix[1][0] = 3;
  mat1.matrix[1][1] = 4;
  rez1.matrix[0][0] = -2;
  rez1.matrix[0][1] = 1;
  rez1.matrix[1][0] = 1.5;
  rez1.matrix[1][1] = -0.5;
  ck_assert_int_eq(0, s21_inverse_matrix(&mat1, &rez));
  ck_assert_int_eq(0, compare_matrices(rez, rez1));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&rez);
  s21_remove_matrix(&rez1);
}
END_TEST

START_TEST(test_inverse_3) {
  matrix_t mat1;
  matrix_t rez;
  matrix_t rez1;
  s21_create_matrix(3, 3, &mat1);
  s21_create_matrix(3, 3, &rez1);
  mat1.matrix[0][0] = 2;
  mat1.matrix[0][1] = 5;
  mat1.matrix[0][2] = 7;
  mat1.matrix[1][0] = 6;
  mat1.matrix[1][1] = 3;
  mat1.matrix[1][2] = 4;
  mat1.matrix[2][0] = 5;
  mat1.matrix[2][1] = -2;
  mat1.matrix[2][2] = -3;
  rez1.matrix[0][0] = 1;
  rez1.matrix[0][1] = -1;
  rez1.matrix[0][2] = 1;
  rez1.matrix[1][0] = -38;
  rez1.matrix[1][1] = 41;
  rez1.matrix[1][2] = -34;
  rez1.matrix[2][0] = 27;
  rez1.matrix[2][1] = -29;
  rez1.matrix[2][2] = 24;
  ck_assert_int_eq(0, s21_inverse_matrix(&mat1, &rez));
  ck_assert_int_eq(0, compare_matrices(rez, rez1));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&rez);
  s21_remove_matrix(&rez1);
}
END_TEST

START_TEST(test_inverse_4) {
  matrix_t mat1;
  matrix_t rez;
  s21_create_matrix(2, 3, &mat1);
  mat1.matrix[0][0] = 2;
  mat1.matrix[0][1] = 5;
  mat1.matrix[0][2] = 7;
  mat1.matrix[1][0] = 6;
  mat1.matrix[1][1] = 3;
  mat1.matrix[1][2] = 4;
  ck_assert_int_eq(2, s21_inverse_matrix(&mat1, &rez));
  s21_remove_matrix(&mat1);
  //   s21_remove_matrix(&rez);
}
END_TEST

START_TEST(test_inverse_5) {
  matrix_t rez;
  matrix_t mat1 = {0};
  ck_assert_int_eq(1, s21_inverse_matrix(&mat1, &rez));
  s21_remove_matrix(&mat1);
}
END_TEST

START_TEST(test_inverse_6) {
  matrix_t mat1;
  matrix_t rez;
  matrix_t rez1;
  s21_create_matrix(4, 4, &mat1);
  s21_create_matrix(4, 4, &rez1);
  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = 1;
  mat1.matrix[0][2] = 3;
  mat1.matrix[0][3] = 4;
  mat1.matrix[1][0] = 5;
  mat1.matrix[1][1] = 5;
  mat1.matrix[1][2] = 5;
  mat1.matrix[1][3] = 5;
  mat1.matrix[2][0] = 3;
  mat1.matrix[2][1] = 5;
  mat1.matrix[2][2] = 5;
  mat1.matrix[2][3] = 5;
  mat1.matrix[3][0] = 6;
  mat1.matrix[3][1] = 7;
  mat1.matrix[3][2] = 8;
  mat1.matrix[3][3] = 9;
  rez1.matrix[0][0] = 0;
  rez1.matrix[0][1] = 0.5;
  rez1.matrix[0][2] = -0.5;
  rez1.matrix[0][3] = 0;
  rez1.matrix[1][0] = -1;
  rez1.matrix[1][1] = -1;
  rez1.matrix[1][2] = 0;
  rez1.matrix[1][3] = 1;
  rez1.matrix[2][0] = 2;
  rez1.matrix[2][1] = 2.3;
  rez1.matrix[2][2] = 1.5;
  rez1.matrix[2][3] = -3;
  rez1.matrix[3][0] = -1;
  rez1.matrix[3][1] = -1.6;
  rez1.matrix[3][2] = -1;
  rez1.matrix[3][3] = 2;
  ck_assert_int_eq(0, s21_inverse_matrix(&mat1, &rez));
  ck_assert_int_eq(0, compare_matrices(rez, rez1));
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&rez);
  s21_remove_matrix(&rez1);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, test_creat_1);
  tcase_add_test(tc1_1, test_creat_2);
  tcase_add_test(tc1_1, test_eq_1);
  tcase_add_test(tc1_1, test_eq_2);
  tcase_add_test(tc1_1, test_eq_3);
  tcase_add_test(tc1_1, test_eq_4);
  tcase_add_test(tc1_1, test_eq_5);
  tcase_add_test(tc1_1, test_eq_6);
  tcase_add_test(tc1_1, test_sum_1);
  tcase_add_test(tc1_1, test_sum_2);
  tcase_add_test(tc1_1, test_sum_3);
  tcase_add_test(tc1_1, test_sum_4);
  tcase_add_test(tc1_1, test_sum_5);
  tcase_add_test(tc1_1, test_sum_6);
  tcase_add_test(tc1_1, test_sub_1);
  tcase_add_test(tc1_1, test_sub_2);
  tcase_add_test(tc1_1, test_sub_4);
  tcase_add_test(tc1_1, test_sub_5);
  tcase_add_test(tc1_1, test_muln_1);
  tcase_add_test(tc1_1, test_muln_2);
  tcase_add_test(tc1_1, test_muln_4);
  tcase_add_test(tc1_1, test_mulm_1);
  tcase_add_test(tc1_1, test_mulm_2);
  tcase_add_test(tc1_1, test_mulm_3);
  tcase_add_test(tc1_1, test_mulm_4);
  tcase_add_test(tc1_1, test_mulm_5);
  tcase_add_test(tc1_1, test_mulm_6);
  tcase_add_test(tc1_1, test_trans_1);
  tcase_add_test(tc1_1, test_trans_2);
  tcase_add_test(tc1_1, test_trans_3);
  tcase_add_test(tc1_1, test_trans_4);
  tcase_add_test(tc1_1, test_calc_1);
  tcase_add_test(tc1_1, test_calc_2);
  tcase_add_test(tc1_1, test_calc_3);
  tcase_add_test(tc1_1, test_calc_4);
  tcase_add_test(tc1_1, test_determ_1);
  tcase_add_test(tc1_1, test_determ_2);
  tcase_add_test(tc1_1, test_determ_3);
  tcase_add_test(tc1_1, test_inverse_1);
  tcase_add_test(tc1_1, test_inverse_2);
  tcase_add_test(tc1_1, test_inverse_3);
  tcase_add_test(tc1_1, test_inverse_4);
  tcase_add_test(tc1_1, test_inverse_5);
  tcase_add_test(tc1_1, test_inverse_6);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  srunner_free(sr);
  return 0;
}
