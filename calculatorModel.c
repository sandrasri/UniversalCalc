// model.c
#include "sampleModel.h"
#include <stdio.h>
#include <stdlib.h>

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
        return 0.0;  // return 0 for error case
    }
}

// Set current value
void set_current_value(double value) {
    current_value = value;
}

// Get current value
double get_current_value() {
    return current_value;
}
