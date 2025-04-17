// matrixCalculatorView.c
#include "matrixCalculatorView.h"

GtkWidget* create_matrix_calculator_view() {
    GtkWidget *label = gtk_label_new("Matrix Calculator - Coming Soon!");
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);
    return box;
}
