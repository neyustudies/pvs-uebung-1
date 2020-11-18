#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <omp.h>

#define EPSILON 0.0001f

// ---------------------------------------------------------------------------
// allocate space for empty matrix A[row][col]
// access to matrix elements possible with:
// - A[row][col]
// - A[0][row*col]

float** alloc_mat(int row, int col) {
  float **A1, *A2;

  A1 = (float**)calloc(row, sizeof(float*));      // pointer on rows
  A2 = (float*)calloc(row * col, sizeof(float));  // all matrix elements
  for (int i = 0; i < row; i++)
    A1[i] = A2 + i * col;

  return A1;
}

// ---------------------------------------------------------------------------
// random initialisation of matrix with values [0..9]

void init_mat(float** A, int row, int col) {
  for (int i = 0; i < row * col; i++)
    A[0][i] = (float)(rand() % 10);
}

// ---------------------------------------------------------------------------
// DEBUG FUNCTION: printout of all matrix elements

void print_mat(float** A, int row, int col, char const* tag) {
  int i, j;

  printf("Matrix %s:\n", tag);
  for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++)
      printf("%6.1f   ", A[i][j]);
    printf("\n");
  }
}

// ---------------------------------------------------------------------------
// free dynamicly allocated memory, which was used to store a 2D matrix
void free_mat(float** A, int num_rows) {
  int i;
  for (i = 0; i < num_rows; ++i) {
    free(A[i]);
  }
  free(A);
}

void matmult_serial(float **A, float **B, float **C, int d1, int d2, int d3) {
  int i, j, k;          // loop variables

  printf("Perform serial matrix multiplication...\n");

  for (i = 0; i < d1; i++)
    for (j = 0; j < d3; j++)
      for (k = 0; k < d2; k++)
        C[i][j] += A[i][k] * B[k][j];
}

void matmult_parallel(float **A, float **B, float **C, int d1, int d2, int d3) {
  printf("Perform parallel matrix multiplication...\n");

#pragma omp parallel for collapse(2)
  for (int i = 0; i < d1; i++)
    for (int j = 0; j < d3; j++)
      for (int k = 0; k < d2; k++)
        C[i][j] += A[i][k] * B[k][j];
}

bool mat_equal(float **mat1, float **mat2, int m, int n) {
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (abs(mat1[i][j] - mat2[i][j]) > EPSILON) {
        return false;
      }
    }
  }
  return true;
}

void test_mat_equal(int m, int n) {
  float **mat1 = alloc_mat(m, n);
  init_mat(mat1, m, n);
  assert(mat_equal(mat1, mat1, m, n));
  float **mat2 = alloc_mat(m, n);
  init_mat(mat2, m, n);

  // ensure mat1 and mat2 are different
  mat1[m/2][n/2] = 0;
  mat2[m/2][n/2] = 42;
  assert(!mat_equal(mat1, mat2, m, n));
  assert(!mat_equal(mat2, mat1, m, n));
}

// ---------------------------------------------------------------------------

int main(int argc, char* argv[]) {
  float **A, **B, **C;  // matrices
  int d1, d2, d3;       // dimensions of matrices

  /* print user instruction */
  if (argc < 4) {
    printf("Matrix multiplication: C = A x B\n");
    printf("Usage: %s <NumRowA> <NumColA> <NumColB> [mode]\n", argv[0]);
    printf("    Mode may be 'test', 'serial', 'parallel' or omitted.\n");
    printf("    If ommitted, calculations are performed in parallel.\n");
    printf("    The 'test' mode uses both methods, measures time taken\n");
    printf("    and verifies that results match.\n");
    return 0;
  }

  /* read user input */
  d1 = atoi(argv[1]);  // rows of A and C
  d2 = atoi(argv[2]);  // cols of A and rows of B
  d3 = atoi(argv[3]);  // cols of B and C

  printf("Matrix sizes C[%d][%d] = A[%d][%d] x B[%d][%d]\n", d1, d3, d1, d2, d2,
         d3);

  /* prepare matrices */
  A = alloc_mat(d1, d2);
  init_mat(A, d1, d2);
  B = alloc_mat(d2, d3);
  init_mat(B, d2, d3);
  // no initialisation of C, because it gets filled by matmult
  C = alloc_mat(d1, d3);


  /* matmult */
  if (argc == 5 && strcmp(argv[4], "test") == 0) {
    printf("Testing matrix equality function...\n");
    test_mat_equal(d1, d3);

    double start_s = omp_get_wtime();
    matmult_serial(A, B, C, d1, d2, d3);
    double end_s = omp_get_wtime();
    printf("Serial multiplication took %f seconds.\n", (end_s - start_s));

    float **C_parallel = alloc_mat(d1, d3);
    double start_p = omp_get_wtime();
    matmult_parallel(A, B, C_parallel, d1, d2, d3);
    double end_p = omp_get_wtime();
    printf("Parallel multiplication took %f seconds.\n", (end_p - start_p));

    assert(mat_equal(C, C_parallel, d1, d3));

    // sanity check
    C[0][0] = 1;
    C_parallel[0][0] = 2;
    assert(!mat_equal(C, C_parallel, d1, d3));

    return 0;

  } else if (argc == 5 && argv[4][0] == 's') {
    matmult_serial(A, B, C, d1, d2, d3);
  } else {
    matmult_parallel(A, B, C, d1, d2, d3);
  }

  /* print output */
  print_mat(A, d1, d2, "A");
  print_mat(B, d2, d3, "B");
  print_mat(C, d1, d3, "C");

  printf("\nDone.\n");

  return 0;
}
