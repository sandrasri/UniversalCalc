// model.c
#include "sampleModel.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#define _USE_MATH_DEFINES
#define NUM_HEXA 16
#define NUM_CONVERSIONS 34
#define MAX_UNIT_LEN 50
#define MAX_VISITED 50

typedef struct {
    char key[50];
    double value;
} KeyValuePair;

KeyValuePair conversionChart[NUM_CONVERSIONS] = {
    {"kilogram_to_lb", 2.20462},
    {"lb_to_kilogram", 0.45359},
    {"meter_to_feet", 3.28084},
    {"feet_to_meter", 0.3048},
    {"centimeter_to_inches", 0.393701},
    {"inches_to_centimeter", 2.54},
    {"kilometer_to_miles", 0.621371},
    {"miles_to_kilometer", 1.60934},
    {"gram_to_ounce", 0.035274},
    {"ounce_to_gram", 28.3495},
    {"litre_to_gallon", 0.264172},
    {"gallon_to_litre", 3.78541},
    {"celsius_to_fahrenheit", 1.8},
    {"fahrenheit_to_celsius", 0.555556},
    {"lb_to_ounce", 16.0},
    {"ounce_to_lb", 0.0625},
    {"kilogram_to_gram", 1000.0},
    {"gram_to_kilogram", 0.001},
    {"meter_to_centimeter", 100.0},
    {"centimeter_to_meter", 0.01},
    {"feet_to_inches", 12.0},
    {"inches_to_feet", 0.0833333},
    {"kilometer_to_meter", 1000.0},
    {"meter_to_kilometer", 0.001},
    {"mile_to_feet", 5280.0},
    {"feet_to_mile", 0.000189394},
    {"litre_to_millilitre", 1000.0},
    {"millilitre_to_litre", 0.001},
    {"gallon_to_ounce", 128.0},
    {"ounce_to_gallon", 0.0078125},
    {"celsius_to_kelvin", 273.15},
    {"kelvin_to_celsius", -273.15},
    {"fahrenheit_to_kelvin", 255.927778},
    {"kelvin_to_fahrenheit", -457.87}
};

KeyValuePair hexaConversion[NUM_HEXA] = {
    {"0", 0},
    {"1", 1},
    {"2", 2},
    {"3", 3},
    {"4", 4},
    {"5", 5},
    {"6", 6},
    {"7", 7},
    {"8", 8},
    {"9", 9},
    {"A", 10},
    {"B", 11},
    {"C", 12},
    {"D", 13},
    {"E", 14},
    {"F", 15},
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

// Recursive DFS to find a path
bool dfs(const char *from, const char *to, double value, double *result, char visited[MAX_VISITED][MAX_UNIT_LEN], int depth) {
    if (depth >= MAX_VISITED) return false;

    for (int i = 0; i < depth; i++) {
        if (strcasecmp(visited[i], from) == 0)
            return false; // already visited
    }
    strcpy(visited[depth], from);

    char key[100];
    sprintf(key, "%s_to_%s", from, to);
    for (int i = 0; i < NUM_CONVERSIONS; i++) {
        if (strcasecmp(conversionChart[i].key, key) == 0) {
            *result = value * conversionChart[i].value;
            return true;
        }
    }

    // Try intermediate paths
    for (int i = 0; i < NUM_CONVERSIONS; i++) {
        char intermediate_from[MAX_UNIT_LEN], intermediate_to[MAX_UNIT_LEN];
        sscanf(conversionChart[i].key, "%[^_]", intermediate_from);
        sscanf(conversionChart[i].key, "%*[^_]_to_%s", intermediate_to);

        if (strcasecmp(intermediate_from, from) == 0) {
            double new_value = value * conversionChart[i].value;
            if (dfs(intermediate_to, to, new_value, result, visited, depth + 1))
                return true;
        }
    }

    return false;
}

double perform_conversion(const char *from, const char *to, double value) {
    double result = 0.0;
    char visited[MAX_VISITED][MAX_UNIT_LEN] = {0};

    if (dfs(from, to, value, &result, visited, 0)) {
        return result;
    } else {
        return 0.0;
    }
}

// Binary and Hexadecimal conversions
char* compute_numconversion(const char *from, const char *to, int number) {
    if (strcmp(to, "binary") == 0) {
        if (number == 0) {
           return "0.0";
        }
        int binary[32];
        int i = 0;
        while (number > 0) {
            binary[i] = number % 2;
            number = number / 2;
            i++;
        }
        
        char* binaryString = malloc(50 * sizeof(char));
        binaryString[0] = '\0'; // Initialize the string
        char temp[2];
        // Append binary digits to the string
        for (int j = i - 1; j >= 0; j--) {
            sprintf(temp, "%d", binary[j]);
            strcat(binaryString, temp);
        }
        return binaryString;
    free(binaryString);
    } else if (strcmp(to, "hexadecimal") == 0) {
        int quotient = number;
        char* answer = malloc(50 * sizeof(char));
        answer[0] = '\0';
        double remainder = 0;
        while (quotient != 0) {
            remainder = quotient % 16;
            char temp[2];
            //answer = realloc(answer, (strlen(answer) + 1) * sizeof(char));
            for (int i = 0; i < NUM_HEXA; i++) {
                if(hexaConversion[i].value == remainder) {
                    strcpy(temp, hexaConversion[i].key);
                }
            }
            memmove(answer + 1, answer, strlen(answer) + 1);
            answer[0] = temp[0];
            quotient = quotient / 16;
        } 
        return answer;
    free(answer);
    }
    return "0.0";
}
