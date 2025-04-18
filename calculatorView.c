// view.c
#include "calculatorView.h"
#include "view.h"
#include "sampleModel.h"
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern GtkWidget *stack;
GtkWidget *entry;  // Entry widget to display results

// Callback function for number button clicks
void on_button_number_clicked(GtkButton *button, gpointer data) {
    const char *button_text = gtk_button_get_label(button);
    const char *current_text = gtk_entry_get_text(GTK_ENTRY(entry));
    char new_text[256];
    
    // Append the button's label to the current text
    if (strcmp(button_text, "π") == 0) {
        snprintf(new_text, sizeof(new_text), "%s%f", current_text, M_PI);
        gtk_entry_set_text(GTK_ENTRY(entry), new_text);
    }
    if (strcmp(button_text, "e") == 0) {
        snprintf(new_text, sizeof(new_text), "%s%f", current_text, exp(1.0));
        gtk_entry_set_text(GTK_ENTRY(entry), new_text);
    } else {
        snprintf(new_text, sizeof(new_text), "%s%s", current_text, button_text);
        gtk_entry_set_text(GTK_ENTRY(entry), new_text);
    }
}

// Callback function for operator button clicks
void on_button_operator_clicked(GtkButton *button, gpointer data) {
    const char *button_text = gtk_button_get_label(button);
    const char *current_text = gtk_entry_get_text(GTK_ENTRY(entry));
    char new_text[256];
    
    // If there's a number already, store it
    if (strcmp(button_text, "-") == 0 || strcmp(button_text, "*") == 0 || strcmp(button_text, "/") == 0 || strcmp(button_text, "+") == 0 || strcmp(button_text, "^") == 0) {
        snprintf(new_text, sizeof(new_text), "%s%s", current_text, button_text);
        gtk_entry_set_text(GTK_ENTRY(entry), new_text);
    } else {
        snprintf(new_text, sizeof(new_text), "%s %s ", current_text, button_text);
        gtk_entry_set_text(GTK_ENTRY(entry), new_text);
    }
}

// Callback function for equal button
void on_button_equal_clicked(GtkButton *button, gpointer data) {
    const char *text = gtk_entry_get_text(GTK_ENTRY(entry));
    
    // Extract the numbers and operator
    double num, num1, num2;
    char func[10];
    double result;
    char operator;

    if (sscanf(text, "%lf %s %lf", &num1, func, &num2) == 3) {
        if (strcmp(func, "log_") == 0) result = logBase(num1, num2);
        if (strcmp(func, "x_√") == 0) result = squareRootWBase(num1, num2);
    }
    else if (sscanf(text, "%lf %c %lf", &num1, &operator, &num2) == 3) {
        // Perform calculation based on operator
        switch (operator) {
            case '+': result = add(num1, num2); break;
            case '-': result = subtract(num1, num2); break;
            case '*': result = multiply(num1, num2); break;
            case '/': result = divide(num1, num2); break;
            case '%': result = modulus(num1, num2); break;
            case '^': result = exponent(num1, num2); break;
            default: result = 0.0;
        }
    } 
    else if (sscanf(text, "%lf %c", &num1, &operator) == 2) {

        switch (operator) {
            case '!': result = factorial(num1); break;
            default: result = 0.0;
        }
    }
    else if (sscanf(text, "%s %lf", func, &num) == 2) {
        if (strcmp(func, "sin") == 0) result = sine(num);
        else if (strcmp(func, "cos") == 0) result = cosine(num);
        else if (strcmp(func, "tan") == 0) result = tangent(num);
        else if (strcmp(func, "log") == 0) result = logarithm(num);
        else if (strcmp(func, "ln") == 0) result = naturalLog(num);
        else if (strcmp(func, "abs") == 0) result = absoluteValue(num);
        else if (strcmp(func, "√") == 0) result = squareRoot(num);
    }
    else {
        gtk_entry_set_text(GTK_ENTRY(entry), "Unknown Function");
        return;
    }
    // Update the entry with the result
    char result_str[50];
    snprintf(result_str, sizeof(result_str), "%.2f", result);
    gtk_entry_set_text(GTK_ENTRY(entry), result_str);
}

// Callback function for clear button
void on_button_clear_clicked(GtkButton *button, gpointer data) {
    gtk_entry_set_text(GTK_ENTRY(entry), "");
}

// Callback function for delete button
void on_button_delete_clicked(GtkButton *button, gpointer data) {
    const char *current_text = gtk_entry_get_text(GTK_ENTRY(entry));

    if (strlen(current_text) > 0) {
        char new_text[256];
        strncpy(new_text, current_text, strlen(current_text) - 1);
        new_text[strlen(current_text) - 1] = '\0';
        gtk_entry_set_text(GTK_ENTRY(entry), new_text);
    }
}

// Initialize the view (creating buttons, entries, etc.)
GtkWidget* create_calculator_view() {
    GtkWidget *grid;
    GtkWidget *button_0, *button_point, *button_1, *button_2, *button_3, *button_4, *button_5, *button_6, *button_7, *button_8, *button_9;
    GtkWidget *button_add, *button_subtract, *button_multiply, *button_divide, *button_factorial, *button_exponent;
    GtkWidget *button_equal, *button_clear, *button_sine, *button_cosine, *button_tangent, *button_logarithm, *button_ln, *button_remainder;
    GtkWidget *button_logBase, *button_abs, *button_pi, *button_euler, *button_del, *button_squareRoot, *button_squareRootWBase;

    GtkCssProvider *cssProvider;

    grid = gtk_grid_new();

    // Load CSS for styling
    cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(cssProvider,
        "button.number, button.number * {"
        "  background-image: none;"
        "  background-color:rgb(202, 255, 246);"
        "  color: rgb(0, 150, 170);"
        "  font-weight: bold;"
        "  font-size: 18px;"
        "  border: none;"
        "  border-radius: 10px;"
        "  padding: 12px;"
        "}"

        "button.number:hover, button.number:hover * {"
        "  background-color: rgb(202, 255, 246);"
        "}"
    
        "button.operator, button.operator * {"
        "  background-image: none;"
        "  background-color:rgb(255, 221, 202);"
        "  color: rgb(226, 139, 0);"
        "  font-weight: bold;"
        "  font-size: 18px;"
        "  border: none;"
        "  border-radius: 10px;"
        "  padding: 12px;"
        "}"
    
        "button.operator:hover, button.operator:hover * {"
        "  background-color: rgb(255, 221, 202);"
        "}"

        "button.equal, button.equal * {"
        "  background-image: none;"
        "  background-color:rgb(213, 255, 216);"
        "  color: rgb(0, 152, 5);"
        "  font-weight: bold;"
        "  font-size: 18px;"
        "  border: none;"
        "  border-radius: 10px;"
        "  padding: 12px;"
        "}"
    
        "button.equal:hover, button.equal:hover * {"
        "  background-color: rgb(213, 255, 216);"
        "}"

        "button.clear, button.clear * {"
        "  background-image: none;"
        "  background-color:rgb(239, 175, 175);"
        "  color: rgb(104, 0, 10);"
        "  font-weight: bold;"
        "  font-size: 18px;"
        "  border: none;"
        "  border-radius: 10px;"
        "  padding: 12px;"
        "}"

        "button.clear:hover, button.clear:hover * {"
        "  background-color: rgb(239, 175, 175);"
        "}"
    
        "entry {"
        "  font-size: 22px;"
        "  padding: 10px;"
        "  border-radius: 8px;"
        "}"
    , -1, NULL);
    

    // Create entry
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 6, 1);

    // Helper macro to create button with class
    #define CREATE_BUTTON(var, label, style_class) \
        var = gtk_button_new_with_label(label); \
        gtk_style_context_add_class(gtk_widget_get_style_context(var), style_class)

    // Number buttons
    CREATE_BUTTON(button_0, "0", "number");
    CREATE_BUTTON(button_1, "1", "number");
    CREATE_BUTTON(button_2, "2", "number");
    CREATE_BUTTON(button_3, "3", "number");
    CREATE_BUTTON(button_4, "4", "number");
    CREATE_BUTTON(button_5, "5", "number");
    CREATE_BUTTON(button_6, "6", "number");
    CREATE_BUTTON(button_7, "7", "number");
    CREATE_BUTTON(button_8, "8", "number");
    CREATE_BUTTON(button_9, "9", "number");
    CREATE_BUTTON(button_point, ".", "number");
    CREATE_BUTTON(button_pi, "π", "number");
    CREATE_BUTTON(button_euler, "e", "number");

    // Operator buttons
    CREATE_BUTTON(button_add, "+", "operator");
    CREATE_BUTTON(button_subtract, "-", "operator");
    CREATE_BUTTON(button_multiply, "*", "operator");
    CREATE_BUTTON(button_divide, "/", "operator");
    CREATE_BUTTON(button_remainder, "%", "operator");
    CREATE_BUTTON(button_factorial, "!", "operator");
    CREATE_BUTTON(button_squareRoot, "√", "operator");
    CREATE_BUTTON(button_squareRootWBase, "x_√", "operator");
    CREATE_BUTTON(button_abs, "abs", "operator");
    CREATE_BUTTON(button_exponent, "^", "operator");
    CREATE_BUTTON(button_sine, "sin", "operator");
    CREATE_BUTTON(button_cosine, "cos", "operator");
    CREATE_BUTTON(button_tangent, "tan", "operator");
    CREATE_BUTTON(button_logarithm, "log", "operator");
    CREATE_BUTTON(button_ln, "ln", "operator");
    CREATE_BUTTON(button_logBase, "log_", "operator");

    // Equal and Clear
    CREATE_BUTTON(button_equal, "=", "equal");
    CREATE_BUTTON(button_clear, "C", "clear");
    CREATE_BUTTON(button_del, "Del", "clear");

    // Layout grid
    gtk_grid_attach(GTK_GRID(grid), button_0, 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_point, 1, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_pi, 2, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_1, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_2, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_3, 2, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_factorial, 3, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_sine, 4, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_euler, 3, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_squareRoot, 4, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_4, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_5, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_6, 2, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_exponent, 3, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_cosine, 4, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_7, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_8, 1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_9, 2, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_logarithm, 3, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_tangent, 4, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_ln, 5, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_logBase, 5, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_squareRootWBase, 5, 4, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), button_add, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_subtract, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_multiply, 2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_divide, 3, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_remainder, 4, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_abs, 5, 1, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), button_equal, 0, 6, 5, 1);
    gtk_grid_attach(GTK_GRID(grid), button_clear, 5, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_del, 5, 6, 1, 1);

    // Home button to return to the main menu
    GtkWidget *button_home = gtk_button_new_with_label("Home");
    g_signal_connect(button_home, "clicked", G_CALLBACK(on_button_home_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_home, 2, 7, 1, 1);

    // Connect signals
    g_signal_connect(button_1, "clicked", G_CALLBACK(on_button_number_clicked), NULL);
    g_signal_connect(button_2, "clicked", G_CALLBACK(on_button_number_clicked), NULL);
    g_signal_connect(button_3, "clicked", G_CALLBACK(on_button_number_clicked), NULL);
    g_signal_connect(button_4, "clicked", G_CALLBACK(on_button_number_clicked), NULL);
    g_signal_connect(button_5, "clicked", G_CALLBACK(on_button_number_clicked), NULL);
    g_signal_connect(button_6, "clicked", G_CALLBACK(on_button_number_clicked), NULL);
    g_signal_connect(button_7, "clicked", G_CALLBACK(on_button_number_clicked), NULL);
    g_signal_connect(button_8, "clicked", G_CALLBACK(on_button_number_clicked), NULL);
    g_signal_connect(button_9, "clicked", G_CALLBACK(on_button_number_clicked), NULL);
    g_signal_connect(button_0, "clicked", G_CALLBACK(on_button_number_clicked), NULL);
    g_signal_connect(button_point, "clicked", G_CALLBACK(on_button_number_clicked), NULL);
    g_signal_connect(button_pi, "clicked", G_CALLBACK(on_button_number_clicked), NULL);
    g_signal_connect(button_euler, "clicked", G_CALLBACK(on_button_number_clicked), NULL);

    g_signal_connect(button_add, "clicked", G_CALLBACK(on_button_operator_clicked), NULL);
    g_signal_connect(button_subtract, "clicked", G_CALLBACK(on_button_operator_clicked), NULL);
    g_signal_connect(button_multiply, "clicked", G_CALLBACK(on_button_operator_clicked), NULL);
    g_signal_connect(button_divide, "clicked", G_CALLBACK(on_button_operator_clicked), NULL);
    g_signal_connect(button_factorial, "clicked", G_CALLBACK(on_button_operator_clicked), NULL);
    g_signal_connect(button_exponent, "clicked", G_CALLBACK(on_button_operator_clicked), NULL);
    g_signal_connect(button_remainder, "clicked", G_CALLBACK(on_button_operator_clicked), NULL);
    g_signal_connect(button_sine, "clicked", G_CALLBACK(on_button_operator_clicked), NULL);
    g_signal_connect(button_cosine, "clicked", G_CALLBACK(on_button_operator_clicked), NULL);
    g_signal_connect(button_tangent, "clicked", G_CALLBACK(on_button_operator_clicked), NULL);
    g_signal_connect(button_logarithm, "clicked", G_CALLBACK(on_button_operator_clicked), NULL);
    g_signal_connect(button_ln, "clicked", G_CALLBACK(on_button_operator_clicked), NULL);
    g_signal_connect(button_logBase, "clicked", G_CALLBACK(on_button_operator_clicked), NULL);
    g_signal_connect(button_abs, "clicked", G_CALLBACK(on_button_operator_clicked), NULL);
    g_signal_connect(button_squareRoot, "clicked", G_CALLBACK(on_button_operator_clicked), NULL);
    g_signal_connect(button_squareRootWBase, "clicked", G_CALLBACK(on_button_operator_clicked), NULL);

    g_signal_connect(button_equal, "clicked", G_CALLBACK(on_button_equal_clicked), NULL);
    g_signal_connect(button_clear, "clicked", G_CALLBACK(on_button_clear_clicked), NULL);
    g_signal_connect(button_del, "clicked", G_CALLBACK(on_button_delete_clicked), NULL);

    // Apply styling globally
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    
    return grid;
}
