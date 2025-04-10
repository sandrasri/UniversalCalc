#define _USE_MATH_DEFINES
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//Function to calculate addition
double addition (double n1, double n2) {return n1 + n2;}

//Function to calculate subtraction
double subtract (double n1, double n2) {return n1 - n2;}

//Function to calculate multiplication
double multiply (double n1, double n2) {return n1 * n2;}

//Function to calculate division
double division (double n1, double n2) {return n1 / n2;}

//Function to calculate factorial
int factorial (int n) {
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n-1);
    }
}

//Function for trignometric functions
double trig(double angle, char functionName[]) {
    double radians = (angle * M_PI) / 180;
    double sine = sin(radians);
    double cosine = cos(radians);
    double tangent = tan(radians);

    if (strcmp(functionName, "sine")) {
        printf("Sine of %d: %d\n", angle, sine);
    }
    else if (strcmp (functionName, "cosine")) {
        printf("Cosine of %d: %d\n", angle, cosine);
    }
    else if (strcmp (functionName, "tangent")) {
        printf("Tangent of %d: %d\n", angle, tangent);
    }
}

//Function defining logarithms
double logarithm(char base[], double argument) {
    char* endptr;
    if (strcmp(base, "default")) {
        return log(argument);
    } else {
        return (log(argument) / log(strtod(base, &endptr)));
    }
}

int main() {
    char functionName[] = "";
    printf("Hello, Welcome to the Calculator App\n");
    printf("Enter the function name: \n");
    scanf ("%s", &functionName);
    int number;
    double number1;
    double number2;
    if (strcmp(functionName, "subtract")) {
        printf("Enter a number:\n");
        scanf ("%d", &number1);
        printf("Enter the second number: \n");
        scanf("%d", &number2);
        printf("The answer is: %d\n", subtract(number1, number2));
    } else if (strcmp(functionName, "addition")) {
        printf("Enter a number:\n");
        scanf ("%d", &number1);
        printf("Enter the second number: \n");
        scanf("%d", &number2);
        printf("The answer is: %d\n", addition(number1, number2));
    } else if (strcmp(functionName, "multiplication")) {
        printf("Enter a number:\n");
        scanf ("%d", &number1);
        printf("Enter the second number: \n");
        scanf("%d", &number2);
        printf("The answer is: %d\n", multiply(number1, number2));
    } else if (strcmp(functionName, "division")) {
        printf("Enter a number:\n");
        scanf ("%d", &number1);
        printf("Enter the second number: \n");
        scanf("%d", &number2);
        printf("The answer is: %d\n", division(number1, number2));
    } else if (strcmp(functionName, "factorial")) {
        printf("Enter a number:\n");
        scanf ("%d", &number);
        printf("The answer is: %d\n", factorial(number));
    } else if (strcmp(functionName, "exponent")) {
        printf("Enter a number:\n");
        scanf ("%d", &number1);
        printf("The answer is: %d\n", multiply(number1, number1));
    } else if (strcmp(functionName, "trignometric")) {
        char function[] = "";
        double angle;
        printf("Enter which function (sine, cosine, tangent):");
        scanf("%s", function);
        printf("Enter the angle: ");
        scanf("%d", angle);
        trig(angle, function);
    } else if (strcmp(functionName, "Logarithm")) {
        char base[] = "";
        double argument;
        printf("Enter the base # or (default for base 10): ");
        scanf("%s", base);
        printf("Enter the number: ");
        scanf("%d", argument);
        printf("The answer is: %d\n", logarithm(base, argument));
    }
    else {
        printf("Incorrect argument type");
    }
}
