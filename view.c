#include <gtk/gtk.h>
#include <math.h>

typedef struct {
    GtkWidget *entriesA[3][3];
    GtkWidget *entriesB[3][3];
    GtkWidget *entriesAns[3][3];
    GtkWidget  *entriesBase[3][3];
    GtkWidget *entriesSecAns[3][3];
    GtkWidget *entryScalar;
    int matrixA[3][3];
    int matrixB[3][3];
    int matrixAns[3][3];
    int matrixBase[3][3];
    double matrixSecAns[3][3];
    int scalar;
} AppWidgets;

static void reset_clicked(GtkButton *button, gpointer user_data) {
    AppWidgets *widgets = (AppWidgets *)user_data;

    // Clear all entries after saving
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            gtk_entry_set_text(GTK_ENTRY(widgets->entriesA[i][j]), "");
            gtk_entry_set_text(GTK_ENTRY(widgets->entriesB[i][j]), "");
            gtk_entry_set_text(GTK_ENTRY(widgets->entriesBase[i][j]), "");
        }
    }
    gtk_entry_set_text(GTK_ENTRY(widgets->entryScalar), "");
}

void helperSave(AppWidgets *widgets) {
    // Save Matrix A
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            const char *textA = gtk_entry_get_text(GTK_ENTRY(widgets->entriesA[i][j]));
            widgets->matrixA[i][j] = atoi(textA);
        }
    }

    // Save Matrix B
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            const char *textB = gtk_entry_get_text(GTK_ENTRY(widgets->entriesB[i][j]));
            widgets->matrixB[i][j] = atoi(textB);
        }
    }

    // Save Matrix Base
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            const char *textBase = gtk_entry_get_text(GTK_ENTRY(widgets->entriesBase[i][j]));
            widgets->matrixBase[i][j] = atoi(textBase);
        }
    }
}

static void addition_clicked(GtkButton *button, gpointer user_data) {
    AppWidgets *widgets = (AppWidgets *)user_data;

    //Save Matrixes
    helperSave(widgets);

    //Matrix Addition
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            widgets->matrixAns[i][j] = (widgets->matrixA[i][j] + widgets->matrixB[i][j]);
            char result[10];
            snprintf(result, sizeof(result), "%d", widgets->matrixAns[i][j]);
            gtk_entry_set_text(GTK_ENTRY(widgets->entriesAns[i][j]), result);
        }
    }
}

static void subtraction_clicked(GtkButton *button, gpointer user_data) {
    AppWidgets *widgets = (AppWidgets *)user_data;

    //Save Matrixes
    helperSave(widgets);

    //Matrix Subtraction
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            widgets->matrixAns[i][j] = (widgets->matrixA[i][j] - widgets->matrixB[i][j]);            
            char result[10];
            snprintf(result, sizeof(result), "%d", widgets->matrixAns[i][j]);
            gtk_entry_set_text(GTK_ENTRY(widgets->entriesAns[i][j]), result);
        }
    }
}

static void multiplication_clicked(GtkButton *button, gpointer user_data) {
    AppWidgets *widgets = (AppWidgets *)user_data;

    //Save Matrixes
    helperSave(widgets);

    //Matrix Multiplication
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            widgets->matrixAns[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                widgets->matrixAns[i][j] += (widgets->matrixA[i][k] * widgets->matrixB[k][j]);
            }
            char result[10];
            snprintf(result, sizeof(result), "%d", widgets->matrixAns[i][j]);
            gtk_entry_set_text(GTK_ENTRY(widgets->entriesAns[i][j]), result);
        }
    }
}

static void scalar_multiplication_clicked(GtkButton *button, gpointer user_data) {
    AppWidgets *widgets = (AppWidgets *)user_data;

    const char *scalarText = gtk_entry_get_text(GTK_ENTRY(widgets->entryScalar));
    widgets->scalar = atoi(scalarText);

    //Save Matrixes
    helperSave(widgets);

    //Matrix Scalar Multiply
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            widgets->matrixSecAns[i][j] = (double)(widgets->matrixBase[i][j] * widgets->scalar);            
            char result[10];
            snprintf(result, sizeof(result), "%.2f", widgets->matrixSecAns[i][j]);
            gtk_entry_set_text(GTK_ENTRY(widgets->entriesSecAns[i][j]), result);
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

//Find inverse matrix
static void inverse_clicked(GtkButton *button, gpointer user_data) {
    AppWidgets *widgets = (AppWidgets *)user_data;

    //Save Matrixes
    helperSave(widgets);

    int** base = malloc(3 * sizeof(int*));
    double cofactor[3][3];
    for (int i = 0; i < 3; i++) {
        base[i] = malloc(3 * sizeof(int));
        for (int j = 0; j < 3; j++) {
            base[i][j] = widgets->matrixBase[i][j];
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
                widgets->matrixSecAns[i][j] = (cofactor[j][i] / det);                
                char result[10];
                snprintf(result, sizeof(result), "%.2f", widgets->matrixSecAns[i][j]);
                gtk_entry_set_text(GTK_ENTRY(widgets->entriesSecAns[i][j]), result);
            }
        }
    }
}

//Find transpose matrix
static void transpose_clicked(GtkButton *button, gpointer user_data) {
    AppWidgets *widgets = (AppWidgets *)user_data;

    //Save Matrixes
    helperSave(widgets);

    //Matrix Transpose
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            widgets->matrixSecAns[i][j] = (double)widgets->matrixBase[j][i];            
            char result[10];
            snprintf(result, sizeof(result), "%.2f", widgets->matrixSecAns[i][j]);
            gtk_entry_set_text(GTK_ENTRY(widgets->entriesSecAns[i][j]), result);
        }
    }
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window, *grid, *buttonReset, *labelA, *labelB, *labelAns, *label, *labelNum, *labelSecAns;
    GtkWidget *buttonAdd, *buttonSub, *buttonMult, *buttonScal, *buttonTran, *buttonInv;
    AppWidgets *widgets = g_new(AppWidgets, 1);

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Matrix Mathematics");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 600);

    grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Labels for the matrices
    labelA = gtk_label_new("Matrix A");
    gtk_grid_attach(GTK_GRID(grid), labelA, 0, 0, 3, 1);

    labelB = gtk_label_new("Matrix B");
    gtk_grid_attach(GTK_GRID(grid), labelB, 4, 0, 3, 1);

    labelAns = gtk_label_new("Matrix Solution");
    gtk_grid_attach(GTK_GRID(grid), labelAns, 20, 0, 3, 1);

    //Labels for other half
    label = gtk_label_new("Matrix");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 20, 3, 1);

    labelNum = gtk_label_new("Scalar Variable");
    gtk_grid_attach(GTK_GRID(grid), labelNum, 4, 20, 3, 1);

    labelSecAns = gtk_label_new("Matrix Solution");
    gtk_grid_attach(GTK_GRID(grid), labelSecAns, 20, 20, 3, 1);

    // Entries for Matrix A
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            widgets->entriesA[i][j] = gtk_entry_new();
            gtk_entry_set_width_chars(GTK_ENTRY(widgets->entriesA[i][j]), 5);
            gtk_grid_attach(GTK_GRID(grid), widgets->entriesA[i][j], j, i + 1, 1, 1);
        }
    }

    // Entries for Matrix B
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            widgets->entriesB[i][j] = gtk_entry_new();
            gtk_entry_set_width_chars(GTK_ENTRY(widgets->entriesB[i][j]), 5);
            gtk_grid_attach(GTK_GRID(grid), widgets->entriesB[i][j], j + 4, i + 1, 1, 1);
        }
    }

    // Entries for Matrix Answer
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            widgets->entriesAns[i][j] = gtk_entry_new();
            gtk_entry_set_width_chars(GTK_ENTRY(widgets->entriesAns[i][j]), 5);
            gtk_grid_attach(GTK_GRID(grid), widgets->entriesAns[i][j], j + 20, i + 1, 1, 1);
        }
    }

    // Entries for Matrix Base
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            widgets->entriesBase[i][j] = gtk_entry_new();
            gtk_entry_set_width_chars(GTK_ENTRY(widgets->entriesBase[i][j]), 5);
            gtk_grid_attach(GTK_GRID(grid), widgets->entriesBase[i][j], j, i + 22, 1, 1);
        }
    }

    // Entries for Matrix SecondAnswer
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            widgets->entriesSecAns[i][j] = gtk_entry_new();
            gtk_entry_set_width_chars(GTK_ENTRY(widgets->entriesSecAns[i][j]), 5);
            gtk_grid_attach(GTK_GRID(grid), widgets->entriesSecAns[i][j], j + 20, i + 22, 1, 1);
        }
    }

    widgets->entryScalar = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(widgets->entryScalar), 5);
    gtk_grid_attach(GTK_GRID(grid), widgets->entryScalar, 4, 23, 3, 1);

    //Matrix Addition Button
    buttonAdd = gtk_button_new_with_label("Matrix Addition");
    gtk_grid_attach(GTK_GRID(grid), buttonAdd, 7, 1, 2, 1);
    g_signal_connect(buttonAdd, "clicked", G_CALLBACK(addition_clicked), widgets);

    //Matrix Subtraction Button
    buttonSub = gtk_button_new_with_label("Matrix Subtraction");
    gtk_grid_attach(GTK_GRID(grid), buttonSub, 7, 2, 2, 1);
    g_signal_connect(buttonSub, "clicked", G_CALLBACK(subtraction_clicked), widgets);

    //Matrix Multiplication Button
    buttonMult = gtk_button_new_with_label("Matrix Multiplication");
    gtk_grid_attach(GTK_GRID(grid), buttonMult, 7, 3, 2, 1);
    g_signal_connect(buttonMult, "clicked", G_CALLBACK(multiplication_clicked), widgets);

    //Matrix Scalar Multiplication Button
    buttonScal = gtk_button_new_with_label("Scalar Multiplication");
    gtk_grid_attach(GTK_GRID(grid), buttonScal, 7, 22, 2, 1);
    g_signal_connect(buttonScal, "clicked", G_CALLBACK(scalar_multiplication_clicked), widgets);

    //Matrix Inverse button
    buttonInv = gtk_button_new_with_label("Matrix Inverse");
    gtk_grid_attach(GTK_GRID(grid), buttonInv, 7, 23, 2, 1);
    g_signal_connect(buttonInv, "clicked", G_CALLBACK(inverse_clicked), widgets);

    // Matrix Transpose Button
    buttonTran = gtk_button_new_with_label("Matrix Transpose");
    gtk_grid_attach(GTK_GRID(grid), buttonTran, 7, 24, 2, 1);
    g_signal_connect(buttonTran, "clicked", G_CALLBACK(transpose_clicked), widgets);

    // Reset Button
    buttonReset = gtk_button_new_with_label("Reset Matrices");
    gtk_grid_attach(GTK_GRID(grid), buttonReset, 0, 7, 7, 1);
    g_signal_connect(buttonReset, "clicked", G_CALLBACK(reset_clicked), widgets);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.MatrixApp", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
