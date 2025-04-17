// view.c
#include "calculatorView.h"
#include "sampleModel.h"
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

GtkWidget *entry;  // Entry widget to display results

// Callback function for number button clicks
void on_button_number_clicked(GtkButton *button, gpointer data) {
    const char *button_text = gtk_button_get_label(button);
    const char *current_text = gtk_entry_get_text(GTK_ENTRY(entry));
    char new_text[256];
    
    // Append the button's label to the current text
    snprintf(new_text, sizeof(new_text), "%s%s", current_text, button_text);
    
    gtk_entry_set_text(GTK_ENTRY(entry), new_text);
}

// Callback function for operator button clicks
void on_button_operator_clicked(GtkButton *button, gpointer data) {
    const char *button_text = gtk_button_get_label(button);
    const char *current_text = gtk_entry_get_text(GTK_ENTRY(entry));
    char new_text[256];
    
    // If there's a number already, store it
    snprintf(new_text, sizeof(new_text), "%s %s ", current_text, button_text);
    gtk_entry_set_text(GTK_ENTRY(entry), new_text);
}

// Callback function for equal button
void on_button_equal_clicked(GtkButton *button, gpointer data) {
    const char *text = gtk_entry_get_text(GTK_ENTRY(entry));
    
    // Extract the numbers and operator
    double num1, num2;
    char operator;
    
    if (sscanf(text, "%lf %c %lf", &num1, &operator, &num2) == 3) {
        double result;
        
        // Perform calculation based on operator
        switch (operator) {
            case '+': result = add(num1, num2); break;
            case '-': result = subtract(num1, num2); break;
            case '*': result = multiply(num1, num2); break;
            case '/': result = divide(num1, num2); break;
            default: result = 0.0;
        }
        
        // Update the entry with the result
        char result_str[50];
        snprintf(result_str, sizeof(result_str), "%.2f", result);
        gtk_entry_set_text(GTK_ENTRY(entry), result_str);
    }
}

// Callback function for clear button
void on_button_clear_clicked(GtkButton *button, gpointer data) {
    gtk_entry_set_text(GTK_ENTRY(entry), "");
}

// Initialize the view (creating buttons, entries, etc.)
GtkWidget* create_calculator_view() {
    GtkWidget *grid;
    GtkWidget *button_0, *button_point, *button_1, *button_2, *button_3, *button_4, *button_5, *button_6, *button_7, *button_8, *button_9;
    GtkWidget *button_add, *button_subtract, *button_multiply, *button_divide;
    GtkWidget *button_equal, *button_clear;

    grid = gtk_grid_new();

    // Create an entry field
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 4, 1);
    
    // Create number buttons
    button_1 = gtk_button_new_with_label("1");
    button_2 = gtk_button_new_with_label("2");
    button_3 = gtk_button_new_with_label("3");
    button_4 = gtk_button_new_with_label("4");
    button_5 = gtk_button_new_with_label("5");
    button_6 = gtk_button_new_with_label("6");
    button_7 = gtk_button_new_with_label("7");
    button_8 = gtk_button_new_with_label("8");
    button_9 = gtk_button_new_with_label("9");
    button_0 = gtk_button_new_with_label("0");
    button_point = gtk_button_new_with_label(".");
    
    gtk_grid_attach(GTK_GRID(grid), button_0, 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_point, 1, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_1, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_2, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_3, 2, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_4, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_5, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_6, 2, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_7, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_8, 1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_9, 2, 4, 1, 1);
    
    // Create operator buttons
    button_add = gtk_button_new_with_label("+");
    button_subtract = gtk_button_new_with_label("-");
    button_multiply = gtk_button_new_with_label("*");
    button_divide = gtk_button_new_with_label("/");
    
    gtk_grid_attach(GTK_GRID(grid), button_add, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_subtract, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_multiply, 2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_divide, 3, 1, 1, 1);
    
    // Create equal and clear buttons
    button_equal = gtk_button_new_with_label("=");
    button_clear = gtk_button_new_with_label("C");
    
    gtk_grid_attach(GTK_GRID(grid), button_equal, 3, 2, 1, 4);
    gtk_grid_attach(GTK_GRID(grid), button_clear, 2, 5, 1, 1);
    
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
    
    g_signal_connect(button_add, "clicked", G_CALLBACK(on_button_operator_clicked), NULL);
    g_signal_connect(button_subtract, "clicked", G_CALLBACK(on_button_operator_clicked), NULL);
    g_signal_connect(button_multiply, "clicked", G_CALLBACK(on_button_operator_clicked), NULL);
    g_signal_connect(button_divide, "clicked", G_CALLBACK(on_button_operator_clicked), NULL);
    
    g_signal_connect(button_equal, "clicked", G_CALLBACK(on_button_equal_clicked), NULL);
    g_signal_connect(button_clear, "clicked", G_CALLBACK(on_button_clear_clicked), NULL);
    
    return grid;
}
