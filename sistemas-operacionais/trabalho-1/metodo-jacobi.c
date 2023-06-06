// uses C standard library
// uses math library
// there is no matrix library

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>

#define EPSILON 0.01
#define MAX_ITERATIONS 100000000

// function that implements the Jacobi method
// receives a matrix A, a vector b, a vector x and the size of the matrix
// returns the number of iterations
int jacobi(double **A, double *b, double *x, int n) {
    int i, j, k;
    double *x_new, *x_old, sum, error;

    // Allocates memory for the new and old vectors
    x_new = (double *) malloc(n * sizeof(double));
    x_old = (double *) malloc(n * sizeof(double));

    // Copies the initial vector to the old vector
    for (i = 0; i < n; i++) {
        x_old[i] = x[i];
    }

    // Iterates until the convergence or the maximum number of iterations is reached
    for (k = 0; k < MAX_ITERATIONS; k++) {
        // Updates the vector elements
        for (i = 0; i < n; i++) {
            sum = 0;
            for (j = 0; j < n; j++) {
                if (j != i) {
                    sum += A[i][j] * x_old[j];
                }
            }
            x_new[i] = (b[i] - sum) / A[i][i];
        }

        // Checks convergence
        error = 0;
        for (i = 0; i < n; i++) {
            error += fabs(x_new[i] - x_old[i]);
        }

        // Convergence condition
        if (error < EPSILON) {
            printf("Converged in %d iterations.\n", k);
            break;
        }

        // Copies the new vector to the old vector
        for (i = 0; i < n; i++) {
            x_old[i] = x_new[i];
        }
    }

    // Frees the memory allocated for the vectors
    free(x_new);
    free(x_old);

    // Returns the number of iterations
    return k;
}


// parallelized version of jacobi() that uses fork()
// receives a matrix A, a vector b, a vector x, the size of the matrix and the number of processes
// returns the number of iterations
int jacobi_parallel(double **A, double *b, double *x, int n, int num_procs) {
    int i, j, k, pid, status;
    double *x_new, *x_old, sum, error;

    // Allocates memory for the new and old vectors
    x_new = (double *) malloc(n * sizeof(double));
    x_old = (double *) malloc(n * sizeof(double));

    // Copies the initial vector to the old vector
    for (i = 0; i < n; i++) {
        x_old[i] = x[i];
    }

    // Iterates until the convergence or the maximum number of iterations is reached
    for (k = 0; k < MAX_ITERATIONS; k++) {
        // Updates the vector elements
        for (i = 0; i < n; i++) {
            sum = 0;
            for (j = 0; j < n; j++) {
                if (j != i) {
                    sum += A[i][j] * x_old[j];
                }
            }
            x_new[i] = (b[i] - sum) / A[i][i];
        }

        // Checks convergence
        error = 0;
        for (i = 0; i < n; i++) {
            error += fabs(x_new[i] - x_old[i]);
        }

        // Convergence condition
        if (error < EPSILON) {
            printf("Converged in %d iterations.\n", k);
            break;
        }

        // Copies the new vector to the old vector
        for (i = 0; i < n; i++) {
            x_old[i] = x_new[i];
        }
    }

    // Frees the memory allocated for the vectors
    free(x_new);
    free(x_old);

    // Returns the number of iterations
    return k;
}
    
    



// function that prints a matrix
// receives a matrix A and the size of the matrix
void print_matrix(double **A, int n) {
    int i, j;

    // iterates through the lines of the matrix
    for (i = 0; i < n; i++) {
        // iterates through the columns of the matrix
        for (j = 0; j < n; j++) {
            // prints the matrix element
            printf("%lf ", A[i][j]);
        }
        // prints a new line
        printf("\n");
    }
}

// function that prints a vector
// receives a vector x and the size of the vector
void print_vector(double *x, int n) {
    int i;

    // iterates through the vector
    for (i = 0; i < n; i++) {
        // prints the vector element
        printf("%lf ", x[i]);
    }
    // prints a new line
    printf("\n");
}

// function that allocates memory for a matrix
// receives the size of the matrix
// returns the matrix
double **allocate_matrix(int n) {
    int i;
    double **A;

    // allocates memory for the matrix
    A = (double **) malloc(n * sizeof(double *));
    // allocates memory for the matrix elements
    for (i = 0; i < n; i++) {
        A[i] = (double *) malloc(n * sizeof(double));
    }

    // returns the matrix
    return A;
}

// function that frees the memory allocated for a matrix
// receives a matrix A and the size of the matrix
void free_matrix(double **A, int n) {
    int i;

    // frees the memory allocated for the matrix elements
    for (i = 0; i < n; i++) {
        free(A[i]);
    }
    // frees the memory allocated for the matrix
    free(A);
}

// function that allocates memory for a vector
// receives the size of the vector
// returns the vector
double *allocate_vector(int n) {
    // allocates memory for the vector
    return (double *) malloc(n * sizeof(double));
}

// function that frees the memory allocated for a vector
// receives a vector x
void free_vector(double *x) {
    // frees the memory allocated for the vector
    free(x);
}

// Function to generate a diagonally dominant matrix
void generate_diagonally_dominant_matrix(double **A, int n) {
    int i, j;

    // Initialize the matrix with zeros
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            A[i][j] = 0.0;
        }
    }

    // Set diagonal elements to a large value
    for (i = 0; i < n; i++) {
        A[i][i] = 10.0;
    }

    // Set off-diagonal elements to a small value
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (j != i) {
                A[i][j] = 1.0;
            }
        }
    }
}

// Function that mocks the matrix A and the vector b
void mock_matrix(double **A, double *b, int n) {
    // Generate a diagonally dominant matrix
    generate_diagonally_dominant_matrix(A, n);

    // Set vector b to a specific value (e.g., all ones)
    int i;
    for (i = 0; i < n; i++) {
        b[i] = 1.0;
    }
}

// function that mocks the vector x
// receives a vector x and the size of the vector
void mock_vector(double *x, int n) {
    int i;

    // iterates through the vector
    for (i = 0; i < n; i++) {
        // sets the vector element to 0
        x[i] = 0;
    }
}

// main function
// get the size of the matrix from the program arguments
// allocates memory for the matrix A, the vector b and the vector x
// mocks the matrix A, the vector b and the vector x
// prints the matrix A, the vector b and the vector x
// calls the Jacobi method
// prints the vector x
// frees the memory allocated for the matrix A, the vector b and the vector x
int main(int argc, char *argv[]) {
    int n, i, iterations;
    double **A, *b, *x;

    // gets the size of the matrix from the program arguments
    n = atoi(argv[1]);

    // allocates memory for the matrix A
    A = allocate_matrix(n);
    // allocates memory for the vector b
    b = allocate_vector(n);
    // allocates memory for the vector x
    x = allocate_vector(n);

    // mocks the matrix A and the vector b
    mock_matrix(A, b, n);
    // mocks the vector x
    mock_vector(x, n);

    // // prints the matrix A
    // printf("A = \n");
    // print_matrix(A, n);
    // // prints the vector b
    // printf("b = \n");
    // print_vector(b, n);
    // // prints the vector x
    // printf("x = \n");
    // print_vector(x, n);

    // calls the Jacobi method
    // iterations = jacobi(A, b, x, n);

    // calls the Jacobi method(Parallel)
    iterations = jacobi_parallel(A, b, x, n, 8);

    // // prints the vector x
    // printf("x = \n");
    // print_vector(x, n);
    // prints the number of iterations
    printf("iterations = %d\n", iterations);

    // frees the memory allocated for the matrix A
    free_matrix(A, n);
    // frees the memory allocated for the vector b
    free_vector(b);
    // frees the memory allocated for the vector x
    free_vector(x);

    // returns 0, which means the program has run successfully
    return 0;
}