#define _USE_MATH_DEFINES
#define NUM_HEXA 16
#define NUM_CONVERSIONS 14
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

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

//List of functions possible:
void printMenu() {
    printf("Calculator Menu: \n");
    printf("1. add\n");
    printf("2. subtract\n");
    printf("3. multiply\n");
    printf("4. divide\n");
    printf("5. factorial\n");
    printf("6. exponent\n");
    printf("7. trignometric\n");
    printf("8. logarithm\n");
    printf("9. conversion\n");
    printf("10. statistics\n");
    printf("11. binary\n");
    printf("12. hexadecimal\n");
    printf("If you wish to exit type: 13\n");
}
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
void trig(double angle, const char *function) {
    double radians = (angle * M_PI) / 180;
    double sine = sin(radians);
    double cosine = cos(radians);
    double tangent = tan(radians);

    if (strcmp(function, "sine") == 0) {
        printf("Sine of %lf: %f\n", angle, sine);
    }
    else if (strcmp (function, "cosine") == 0) {
        printf("Cosine of %lf: %f\n", angle, cosine);
    }
    else if (strcmp (function, "tangent") == 0) {
        printf("Tangent of %lf: %f\n", angle, tangent);
    }
}

//Function defining logarithms
double ln(char base[50], double argument) {
    char* endptr;
    if (strcmp(base, "default") == 0) {
        return (log(argument) / log(10));
    } else {
        return (log(argument) / log(strtod(base, &endptr)));
    }
}

//Function handling matrix mathematics


//Function handling polynomial mathematics

// Add memory storage and retrieval (undo/redo)

//Unit Conversion Features
void conversion(char conversion[50], char og_conversion[50], double value) {
    char conversion_string[100];
    sprintf(conversion_string, "%s_to_%s", conversion, og_conversion);
    for (int i = 0; i < NUM_CONVERSIONS; i++) {
        if (strcasecmp(conversionChart[i].key, conversion_string) == 0) {
            if (strcmp(conversion, "f") == 0 && strcmp(og_conversion, "c") == 0) {
                printf("The answer is %f%s \n", ((value - 32) * conversionChart[i].value), og_conversion);
            }
            else if (strcmp(conversion, "c") == 0 && strcmp(og_conversion, "f") == 0) {
                printf("The answer is %f%s \n", ((conversionChart[i].value * value) + 32), og_conversion);
            } else {
                printf("The answer is: %f%s \n", (conversionChart[i].value * value), og_conversion);
            }
        }
    }
}

//helper function to order the list
double* helperMedian(double num_list[50], int count) {
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (num_list[i] > num_list[j]) {
                double temp = num_list[i];
                num_list[i] = num_list[j];
                num_list[j] = temp;
            }
        }
    }
    return num_list;
}

//helper function to find majority element
double helperMode(double num_list[50], int count) {
    int majority, currentMajority  = 0;
    double majorityElement, currentElement = 0;
    for (int i = 0; i < count; i++) {
        majority = 0;
        for (int j = i + 1; j < count; j++) {
            if (num_list[i] == num_list[j]) {
                majority++;
                majorityElement = num_list[i];
            }
        }
        if (currentMajority < majority) {
            currentMajority = majority;
            currentElement = majorityElement;
        }
    }
    return currentElement;
}

//Handle Statistical conversions (mean, median, mode, std, variance)
double statistics(const char *function, double num_list[100], int count, int silent) {
    if (strcmp(function, "mean") == 0) {
        double total = 0;
        for (int i = 0; i < count; i++) {
            total += num_list[i];
        }
        if (!silent) {
            printf("The mean of this list is: %f \n", (total/count));
        }
        return (total/count);
    }
    else if (strcmp(function, "median") == 0) {
        double* newList = helperMedian(num_list, count);
        if (count % 2 == 0) {
            printf("The median of this list is %f \n", ((newList[count/2 - 1] + newList[count/2]) / 2));
            return ((newList[count/2 - 1] + newList[count/2]) / 2);
        } else {
            printf("The median of this list is: %f \n", newList[count / 2]);
            return (newList[count/2]);
        }
    }
    else if (strcmp(function, "mode") == 0) {
        printf("The mode of this list is %f \n", helperMode(num_list, count));
    }
    else if (strcmp(function, "variance") == 0) {
        double mean = statistics("mean", num_list, count, 1);
        double std = 0;
        for (int i = 0; i < count; i++) {
            std += ((num_list[i] - mean)*(num_list[i] - mean));
        }
        if (!silent) {
            printf("The Variance of this list is: %f \n", (std/(count - 1)));
        }
        return (std/(count-1));
    }
    else if (strcmp(function, "std") == 0) {
        double variance = statistics("variance", num_list, count, 1);
        printf("The Standard Deviation of this list is: %f \n", sqrt(variance));
        return sqrt(variance);
    }
    return 0;
}

// Binary and Hexadecimal conversions
void computeConversion(int functionName, int number) {
    if (functionName == 11) {
        if (number == 0) {
            printf("This is the binary of the number: 0");
        }
        int binary[32];
        int i = 0;
        while (number > 0) {
            binary[i] = number % 2;
            number = number / 2;
            i++;
        }
        printf("This is binary of the number: ");
        for (int j = i - 1; j >= 0; j--) {
            printf("%d", binary[j]);
        }
        printf("\n");
    }
    else if (functionName == 12) {
        int quotient = number;
        char* answer = malloc(50 * sizeof(char));
        answer[0] = '\0';
        double remainder = 0;
        while (quotient != 0) {
            remainder = quotient % 16;
            char temp[2];
            answer = realloc(answer, (strlen(answer) + 1) * sizeof(char));
            for (int i = 0; i < NUM_HEXA; i++) {
                if(hexaConversion[i].value == remainder) {
                    strcpy(temp, hexaConversion[i].key);
                }
            }
            memmove(answer + 1, answer, strlen(answer) + 1);
            answer[0] = temp[0];
            quotient = quotient / 16;
        } 
        printf("This is the hexadecimal of the number: %s\n", answer);
        free(answer);
    }
}

int main() {
    printf("Hello, Welcome to the Calculator App\n");
    int number, functionName;
    double number1, number2, angle, argument, value;
    char function[50], base[50], input[50], ogconv[50] = "";
    do {
        printMenu();
        printf("Enter the function name: \n");
        scanf ("%d", &functionName);
        switch (functionName) {
            case 1: // Addition
                printf("Enter a number:\n");
                scanf ("%lf", &number1);
                printf("Enter the second number: \n");
                scanf("%lf", &number2);
                printf("The answer is: %f\n", addition(number1, number2));
                break;
            case 2: //subtraction
                printf("Enter a number:\n");
                scanf ("%lf", &number1);
                printf("Enter the second number: \n");
                scanf("%lf", &number2);
                printf("The answer is: %f\n", subtract(number1, number2));
                break;
            case 3: // multiply
                printf("Enter a number:\n");
                scanf ("%lf", &number1);
                printf("Enter the second number: \n");
                scanf("%lf", &number2);
                printf("The answer is: %f\n", multiply(number1, number2));
                break;
            case 4: // division
                printf("Enter a number:\n");
                scanf ("%lf", &number1);
                printf("Enter the second number: \n");
                scanf("%lf", &number2);
                printf("The answer is: %f\n", division(number1, number2));
                break;
            case 5: // factorial
                printf("Enter a number:\n");
                scanf ("%d", &number);
                printf("The answer is: %d\n", factorial(number));
                break;
            case 6: // exponent
                printf("Enter a number:\n");
                scanf ("%lf", &number1);
                printf("The answer is: %f\n", multiply(number1, number1));
                break;
            case 7: // trignometric
                printf("Enter which function (sine, cosine, tangent): \n");
                scanf("%s", function);
                printf("Enter the angle: ");
                scanf("%lf", &angle);
                trig(angle, function);
                break;
            case 8: // logarithm
                printf("Enter the base # or (default for base 10): \n");
                scanf("%s", base);
                printf("Enter the number: ");
                scanf("%lf", &argument);
                printf("The answer is: %f\n", ln(base, argument));
                break;
            case 9: // UnitConversion
                int i = 0;
                char* num;
                char* unit;
                printf("Enter what you wish to convert: \n");
                scanf("%s", input);
                while (isdigit(input[i])) {
                    i++;
                }

                //Allocate memory and copy the numeric part
                num = (char *)malloc((i + 1) * sizeof(char));
                strncpy(num, input, i);
                num[i] = '\0';
                value = atof(num);

                //Allocate memory and copy the unit part
                unit = (char *)malloc((strlen(input) - i + 1) * sizeof(char));
                strcpy(unit, &input[i]);

                printf("Enter the name of what you wish to convert it to: \n");
                scanf("%s", ogconv);
                conversion(unit, ogconv, value);

                free(unit);
                free(num);
                break;
            case 10: //statistics
                char inp[100];
                printf("Enter a list of numbers (e.g. 1,2,3): \n");
                scanf("%s", inp);

                //Split up the string into numList
                char *token = strtok(inp, ",");
                double num_list[100];
                int count = 0;
                while (token != NULL) {
                    num_list[count++] = atof(token);
                    token = strtok(NULL, ",");
                }

                printf("Enter the statistic you wish to find (mean, median, mode, std, variance): \n");
                scanf("%s", function);
                statistics(function, num_list, count, 0);
                break;
            case 11: // binary
                printf("Enter a number: \n");
                scanf("%d", &number);
                computeConversion(functionName, number);
                break;
            case 12: // hexadecimal
                printf("Enter a number: \n");
                scanf("%d", &number);
                computeConversion(functionName, number);
                break;
        }
    } while (functionName != 13);
    printf("Exiting Application");
}
