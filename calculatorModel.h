// model.h
#ifndef MODEL_H
#define MODEL_H

// Simple Calculator
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
double modulus(double a, double b);
double exponent(double a, double b);
double factorial (double a);
double sine(double a);
double cosine(double a);
double tangent (double a);
double logarithm(double a);
double naturalLog(double a);
double logBase(double a, double b);
double absoluteValue(double a);
double squareRoot(double a);
double squareRootWBase(double a, double b);
void set_current_value(double value);
double get_current_value();

//Matrix Calculator
void addition_matrix(int matrixA[3][3], int matrixB[3][3], int matrixAns[3][3]);
void subtraction_matrix(int matrixA[3][3], int matrixB[3][3], int matrixAns[3][3]);
void multiplication_matrix(int matrixA[3][3], int matrixB[3][3], int matrixAns[3][3]);
void scalar_matrix(int matrixBase[3][3], int scalar, double matrixSecAns[3][3]);
void inverse_matrix(int matrixBase[3][3],double matrixSecAns[3][3]);
void transpose_matrix(int matrixBase[3][3], double matrixSecAns[3][3]);

// Conversion Calculator
double conversion(char conversion[50], char og_conversion[50], double value);


#endif
