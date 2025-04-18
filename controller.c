// controller.c
#include "controller.h"
#include "calculatorView.h"
#include "matrixCalculatorView.h"
#include "conversionView.h"
#include <gtk/gtk.h>

extern GtkWidget *stack;  // shared stack for view switching

void on_button_basic_clicked(GtkButton *button, gpointer user_data) {
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "basic");
}

void on_button_matrix_clicked(GtkButton *button, gpointer user_data) {
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "matrix");
}

void on_button_conversion_clicked(GtkButton *button, gpointer user_data) {
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "conversion");
}

void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *main_box;
    GtkWidget *main_menu;
    GtkWidget *button_basic, *button_matrix, *button_conversion;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Calculator Launcher");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), main_box);

    stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
    gtk_box_pack_start(GTK_BOX(main_box), stack, TRUE, TRUE, 0);

    // Main Menu Page
    main_menu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(main_menu), 20);

    button_basic = gtk_button_new_with_label("Basic Calculator");
    button_matrix = gtk_button_new_with_label("Matrix Calculator");
    button_conversion = gtk_button_new_with_label("Conversion Calculator");

    gtk_box_pack_start(GTK_BOX(main_menu), button_basic, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(main_menu), button_matrix, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(main_menu), button_conversion, FALSE, FALSE, 0);

    gtk_stack_add_named(GTK_STACK(stack), main_menu, "menu");

    // Add calculator views to the stack
    GtkWidget *basic_view = create_calculator_view();
    gtk_stack_add_named(GTK_STACK(stack), basic_view, "basic");

    GtkWidget *matrix_view = create_matrix_calculator_view();
    gtk_stack_add_named(GTK_STACK(stack), matrix_view, "matrix");

    GtkWidget *conversion_view = create_conversion_calculator_view();
    gtk_stack_add_named(GTK_STACK(stack), conversion_view, "conversion");

    // Signal connections
    g_signal_connect(button_basic, "clicked", G_CALLBACK(on_button_basic_clicked), NULL);
    g_signal_connect(button_matrix, "clicked", G_CALLBACK(on_button_matrix_clicked), NULL);
    g_signal_connect(button_conversion, "clicked", G_CALLBACK(on_button_conversion_clicked), NULL);

    gtk_stack_set_visible_child_name(GTK_STACK(stack), "menu");  // start with menu
    gtk_widget_show_all(window);
}
