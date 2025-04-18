// model.c
#include "sampleModel.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#define _USE_MATH_DEFINES
#define NUM_CONVERSIONS 14

typedef struct {
    char key[50];
    double value;
} KeyValuePair;

KeyValuePair conversionChart[NUM_CONVERSIONS] = {
    {"kg_to_lb", 2.20462},
    {"lb_to_kg", 0.45359},
    {"m_to_ft", 3.28084},
    {"ft_to_m", 0.3048},
    {"cm_to_in", 0.393701},
    {"in_to_cm", 2.54},
    {"km_to_miles", 0.621371},
    {"miles_to_km", 1.60934},
    {"g_to_oz", 0.035274},
    {"oz_to_g", 28.3495},
    {"l_to_gal", 0.264172},
    {"gal_to_l", 3.78541},
    {"c_to_f", 1.8},
    {"f_to_c", 0.555556},
};

// This will store the current value
static double current_value = 0.0;

// Functions to perform calculations
double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (b != 0) {
        return a / b;
    } else {
        printf("Error: Division by zero!\n");
        return 0.0;
    }
}

double modulus(double a, double b) {
    if (b != 0) {
        return fmod(a, b);
    } else {
        printf("Error: Division by zero!\n");
        return 0.0;
    }
}

double factorial (double n) {
    if (n < 0) {
        return -1;
    } else {
        return tgamma(n+1);
    }
}

double exponent(double a, double b) {
    return pow(a, b);
}

double sine(double angle) {
    return sin((angle * M_PI) / 180);
}

double cosine(double angle) {
    return cos((angle * M_PI) / 180);
}

double tangent(double angle) {
    return tan((angle * M_PI) / 180);
}

double logarithm(double a) {
    return log(a);
}

double logBase(double a, double b) {
    if (b > 0 && a > 0 && a != 1) {
        return log(b) / log(a);  // Change-of-base formula
    } else {
        return 0.0;
    }
}

double naturalLog(double a) {
    return 2.302 * log(a);
}

double absoluteValue(double a) {
    return fabs(a);
}

double squareRoot(double a) {
    return sqrt(a);
}

double squareRootWBase(double a , double b) {
    return pow(b, 1.0/a);
}

// Set current value
void set_current_value(double value) {
    current_value = value;
}

// Get current value
double get_current_value() {
    return current_value;
}

//matrix addition
void addition_matrix(int matrixA[3][3], int matrixB[3][3], int matrixAns[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrixAns[i][j] = (matrixA[i][j] + matrixB[i][j]);
        }
    }
}

//matrix subtraction
void subtraction_matrix(int matrixA[3][3], int matrixB[3][3], int matrixAns[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrixAns[i][j] = (matrixA[i][j] - matrixB[i][j]);
        }
    }
}

//matrix multiplication
void multiplication_matrix(int matrixA[3][3], int matrixB[3][3], int matrixAns[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrixAns[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                matrixAns[i][j] += (matrixA[i][k] * matrixB[k][j]);
            }
        }
    }
}

//matrix scalar multiplication
void scalar_matrix(int matrixBase[3][3], int scalar, double matrixSecAns[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrixSecAns[i][j] = (double)(matrixBase[i][j] * scalar);            
        }
    }
}

//Find determinant of a matrix
int determinant(int** matrix, int n) {
    int det = 0;

    if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    for (int j = 0; j < n; j++) {
       int **minorMatrix = (int **)malloc((n-1) * sizeof(int *));
        for (int i = 0; i < n - 1; i++) {
            minorMatrix[i] = (int *)malloc((n-1) * sizeof(int));
        }

        for (int i = 1; i < n; i++) {
            int colIndex = 0;
            for (int k = 0; k < n; k++) {
                if (k != j) {
                    minorMatrix[i-1][colIndex] = matrix[i][k];
                    colIndex++;
                }
            }
        }

        det += (int) (matrix[0][j] * determinant(minorMatrix, n - 1) * (j % 2 == 0 ? 1 : -1));

        for (int i = 0; i < n - 1; i++) {
            free(minorMatrix[i]);
        }
        free(minorMatrix);
    }
    return det;
}

//Find Minor Matrix
int** findMinor(int** matrix, int n, int rowToRemove, int colToRemove) {
    int** minor = malloc((n-1) * sizeof(int*));
    for (int i = 0; i < n - 1; i++) {
        minor[i] = malloc((n-1) * sizeof(int));
    }
    int mi = 0, mj = 0;

    for (int i = 0; i < n; i++) {
        if (i == rowToRemove) continue;

        mj = 0;
        for (int j = 0; j < n; j++) {
            if (j == colToRemove) continue;
            
            minor[mi][mj] = matrix[i][j];
            mj++;
        } 
        mi++;
    }
    return minor;
}

//matrix inverse
void inverse_matrix(int matrixBase[3][3], double matrixSecAns[3][3]) {
    int** base = malloc(3 * sizeof(int*));
    double cofactor[3][3];
    for (int i = 0; i < 3; i++) {
        base[i] = malloc(3 * sizeof(int));
        for (int j = 0; j < 3; j++) {
            base[i][j] = matrixBase[i][j];
        }
    }

    int det = determinant(base, 3);
    //Matrix Inverse
    if (det != 0) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int**matrix = findMinor(base, 3, i, j);
                double minorDet = determinant(matrix, 2);
                cofactor[i][j] = pow(-1, i+j) * minorDet;

                for (int k = 0; k < 2; k++) {
                    free(matrix[k]);
                }
                free (matrix);
            }
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                matrixSecAns[i][j] = (cofactor[j][i] / det);                
            }
        }
    }
}

//matrix transpose
void transpose_matrix(int matrixBase[3][3], double matrixSecAns[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrixSecAns[i][j] = matrixBase[j][i];
        }
    }
}

//Unit Conversion Features
double conversion(char conversion[50], char og_conversion[50], double value) {
    char conversion_string[100];
    sprintf(conversion_string, "%s_to_%s", conversion, og_conversion);
    for (int i = 0; i < NUM_CONVERSIONS; i++) {
        if (strcasecmp(conversionChart[i].key, conversion_string) == 0) {
            if (strcmp(conversion, "f") == 0 && strcmp(og_conversion, "c") == 0) {
                return ((value - 32) * conversionChart[i].value);
            } else if (strcmp(conversion, "c") == 0 && strcmp(og_conversion, "f") == 0) {
                return ((conversionChart[i].value * value) + 32);
            } else {
                return conversionChart[i].value * value;
            }
        }
    }
    return 0.0;
}
