#include "s21_matrix.h"

int s21_isokey(matrix_t *A) {
  return (A != NULL && A->rows > 0 && A->columns > 0 && A->matrix != NULL);
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = 0;
  if (rows < 1 || columns < 1) {
    error = 1;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    error = 0;
  }
  if (result->matrix != NULL) {
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
      if (!result->matrix[i]) {
        for (int j = 0; j < i; j++) free(result->matrix[j]);
        free(result->matrix);
      }
    }
    error = 0;
  }
  return error;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i] != NULL) free(A->matrix[i]);
    }
    free(A->matrix);
  }
  if (A->rows) {
    A->rows = 0;
  }
  if (A->columns) {
    A->columns = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if ((A->columns == B->columns) && (A->rows == B->rows) && s21_isokey(A) &&
      s21_isokey(B)) {
    for (int i = 0; i < A->rows && result; i++) {
      for (int j = 0; j < A->columns && result; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= 1e-6) {
          result = FAILURE;
        }
      }
    }
  } else {
    result = FAILURE;
  }
  return result;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if (s21_isokey(A) && s21_isokey(B)) {
    if ((A->columns == B->columns) && (A->rows == B->rows)) {
      if (s21_create_matrix(A->rows, A->columns, result) == 0) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          }
        }
      } else {
        error = 1;
      }
    } else {
      error = 2;
    }
  } else {
    error = 1;
  }
  return error;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if (s21_isokey(A) && s21_isokey(B)) {
    if ((A->columns == B->columns) && (A->rows == B->rows)) {
      if (s21_create_matrix(A->rows, A->columns, result) == 0) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
          }
        }
      } else {
        error = 1;
      }
    } else {
      error = 2;
    }
  } else {
    error = 1;
  }
  return error;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = 0;
  if (s21_isokey(A) && s21_create_matrix(A->rows, A->columns, result) == 0) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  } else {
    error = 1;
  }
  return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if (s21_isokey(A) && s21_isokey(B)) {
    result->columns = B->columns;
    result->rows = A->rows;
    s21_create_matrix(result->rows, result->columns, result);
    if (A->columns == B->rows) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          result->matrix[i][j] = 0;
          for (int k = 0; k < B->rows; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    } else {
      error = 2;
    }
  } else {
    error = 1;
  }
  return error;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (s21_isokey(A)) {
    result->rows = A->columns;
    result->columns = A->rows;
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  } else {
    error = 1;
  }
  return error;
}

void s21_minor(matrix_t *mat, matrix_t *A, int l, int m) {
  int k = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i != l) {
      int k1 = 0;
      for (int j = 0; j < A->columns; j++) {
        if (j != m) {
          mat->matrix[k][k1] = A->matrix[i][j];
          k1++;
        }
      }
      k++;
    }
  }
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (s21_isokey(A)) {
    if (A->rows == A->columns) {
      s21_create_matrix(A->rows, A->columns, result);
      if (A->rows == 1) {
        result->matrix[0][0] = A->matrix[0][0];
      } else {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            matrix_t matrix;
            s21_create_matrix(A->rows - 1, A->columns - 1, &matrix);
            s21_minor(&matrix, A, i, j);
            s21_determinant(&matrix, &result->matrix[i][j]);
            s21_remove_matrix(&matrix);
          }
        }
        for (int i = 0; i < result->rows; i++) {
          for (int j = 0; j < result->columns; j++) {
            result->matrix[i][j] = result->matrix[i][j] * pow(-1, i + j);
          }
        }
      }
    } else {
      error = 2;
    }
  } else {
    error = 1;
  }
  return error;
}

double s21_converting(matrix_t *A) {
  double rez = 0;
  double resul = 0;
  int k = 1;
  for (int j = 0; j < A->columns; j++) {
    matrix_t mat;
    s21_create_matrix(A->rows - 1, A->columns - 1, &mat);
    s21_minor(&mat, A, 0, j);
    s21_determinant(&mat, &rez);
    resul += A->matrix[0][j] * k * rez;
    k *= -1;
    s21_remove_matrix(&mat);
  }
  return resul;
}

int s21_determinant(matrix_t *A, double *result) {
  int error = 0;
  if (s21_isokey(A)) {
    if (A->columns == A->rows) {
      if (A->columns == 1) {
        *result = A->matrix[0][0];
      } else if (A->columns == 2) {
        *result = A->matrix[0][0] * A->matrix[1][1] -
                  A->matrix[0][1] * A->matrix[1][0];
      } else {
        *result = s21_converting(A);
      }
    } else {
      error = 2;
    }
  } else {
    error = 1;
  }
  return error;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (s21_isokey(A)) {
    if (A->rows == A->columns) {
      if (A->columns == 1) {
        s21_create_matrix(1, 1, result);
        result->matrix[0][0] = 1 / A->matrix[0][0];
      } else {
        double rez = 0;
        s21_determinant(A, &rez);
        if (rez != 0) {
          matrix_t mat;
          s21_calc_complements(A, &mat);
          s21_transpose(&mat, result);
          for (int i = 0; i < result->rows; i++) {
            for (int j = 0; j < result->columns; j++) {
              result->matrix[i][j] = result->matrix[i][j] * 1 / rez;
            }
          }
          s21_remove_matrix(&mat);
        }
      }
    } else {
      error = 2;
    }
  } else {
    error = 1;
  }
  return error;
}
