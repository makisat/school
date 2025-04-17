#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  int rows;
  int cols;
  int *data;
} Matrix;

Matrix* matrix_create(int rows, int cols) {
  Matrix* m = (Matrix*)malloc(sizeof(Matrix));

  m->rows = rows;
  m->cols = cols;
  m->data = (int*)calloc(rows * cols, sizeof(int));

  return m;
}

void matrix_destroy(Matrix* m) {
  free(m->data);
  free(m);
}

void matrix_print(const Matrix* m) {
  for (int i = 0; i < m->rows; ++i) {
    for (int j = 0; j < m->cols; ++j) {
      printf("%4d", m->data[i * m->cols + j]);
    }
    printf("\n");
  }
}

Matrix* matrix_add(const Matrix* a, const Matrix* b) {
  Matrix* result = matrix_create(a->rows, a->cols);

  int size = a->rows * a->cols;
  for (int i = 0; i < size; ++i) {
    result->data[i] = a->data[i] + b->data[i];
  }
  return result;
}

Matrix* matrix_multiply_scalar(const Matrix* m, int scalar) {
  Matrix* result = matrix_create(m->rows, m->cols);

  int size = m->rows * m->cols;
  for (int i = 0; i < size; ++i) {
    result->data[i] = m->data[i] * scalar;
  }
  return result;
}

Matrix* matrix_transpose(const Matrix* m) {
  Matrix* result = matrix_create(m->cols, m->rows);

  for (int i = 0; i < m->rows; ++i) {
    for (int j = 0; j < m->cols; ++j) {
      result->data[j * result->cols + i] = m->data[i * m->cols + j];
    }
  }
  return result;
}

Matrix* matrix_multiply(const Matrix* a, const Matrix* b) {
  Matrix* result = matrix_create(a->rows, b->cols);

  for (int i = 0; i < result->rows; ++i) {
    for (int j = 0; j < result->cols; ++j) {
      int sum = 0;
      for (int k = 0; k < a->cols; ++k) {
        sum += a->data[i * a->cols + k] * b->data[k * b->cols + j];
      }
      result->data[i * result->cols + j] = sum;
    }
  }
  return result;
}

int main() {
  int data_A[][2] = {{6, 4}, {8, 3}};
  int data_B[][3] = {{1, 2, 3}, {4, 5, 6}};
  int data_C[][3] = {{2, 4, 6}, {1, 3, 5}};
  int scalar = 3;

  Matrix *A = matrix_create(2, 2);
  Matrix *B = matrix_create(2, 3);
  Matrix *C = matrix_create(2, 3);

  for(int i=0; i<2; ++i) for(int j=0; j<2; ++j) A->data[i*2+j] = data_A[i][j];
  for(int i=0; i<2; ++i) for(int j=0; j<3; ++j) B->data[i*3+j] = data_B[i][j];
  for(int i=0; i<2; ++i) for(int j=0; j<3; ++j) C->data[i*3+j] = data_C[i][j];

  printf("A:\n");
  matrix_print(A);

  printf("B:\n");
  matrix_print(B);

  printf("C:\n");
  matrix_print(C);

  Matrix *T1 = matrix_multiply_scalar(B, scalar);
  Matrix *T2 = matrix_transpose(C);
  Matrix *T3 = matrix_multiply(T1, T2);
  Matrix *D  = matrix_add(A, T3);

  printf("D = A + (%d * B) * C^T\n", scalar);
  matrix_print(D);

  matrix_destroy(A);
  matrix_destroy(B);
  matrix_destroy(C);
  matrix_destroy(T1);
  matrix_destroy(T2);
  matrix_destroy(T3);
  matrix_destroy(D);

  return 0;
}
