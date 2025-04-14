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
    GtkWidget *window, *grid, *mainBox;
    GtkCssProvider *cssProvider;
    GtkStyleContext *context;

    AppWidgets *widgets = g_new(AppWidgets, 1);

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Matrix Mathematics");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 700);

    // Load CSS for styling
    cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(cssProvider,
        "#frameTop { background-color: #e0f7fa; padding: 20px; border-radius: 10px; }"
        "#frameBottom { background-color: #f1f8e9; padding: 20px; border-radius: 10px; }"
        "button { margin: 4px; padding: 6px 12px; font-weight: bold; }",
        -1, NULL
    );

    mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_add(GTK_CONTAINER(window), mainBox);

    // ----- Top Frame -----
    GtkWidget *frameTop = gtk_frame_new(NULL);
    gtk_widget_set_name(frameTop, "frameTop");
    gtk_box_pack_start(GTK_BOX(mainBox), frameTop, TRUE, TRUE, 10);

    GtkWidget *topGrid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(topGrid), 5);
    gtk_grid_set_row_spacing(GTK_GRID(topGrid), 5);
    gtk_container_add(GTK_CONTAINER(frameTop), topGrid);

    GtkWidget *labelA = gtk_label_new("Matrix A");
    gtk_grid_attach(GTK_GRID(topGrid), labelA, 0, 0, 3, 1);

    GtkWidget *labelB = gtk_label_new("Matrix B");
    gtk_grid_attach(GTK_GRID(topGrid), labelB, 4, 0, 3, 1);

    GtkWidget *labelAns = gtk_label_new("Matrix Solution");
    gtk_grid_attach(GTK_GRID(topGrid), labelAns, 20, 0, 3, 1);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            widgets->entriesA[i][j] = gtk_entry_new();
            gtk_grid_attach(GTK_GRID(topGrid), widgets->entriesA[i][j], j, i + 1, 1, 1);

            widgets->entriesB[i][j] = gtk_entry_new();
            gtk_grid_attach(GTK_GRID(topGrid), widgets->entriesB[i][j], j + 4, i + 1, 1, 1);

            widgets->entriesAns[i][j] = gtk_entry_new();
            gtk_grid_attach(GTK_GRID(topGrid), widgets->entriesAns[i][j], j + 20, i + 1, 1, 1);
        }
    }

    GtkWidget *buttonAdd = gtk_button_new_with_label("Matrix Addition");
    gtk_grid_attach(GTK_GRID(topGrid), buttonAdd, 7, 1, 2, 1);
    g_signal_connect(buttonAdd, "clicked", G_CALLBACK(addition_clicked), widgets);

    GtkWidget *buttonSub = gtk_button_new_with_label("Matrix Subtraction");
    gtk_grid_attach(GTK_GRID(topGrid), buttonSub, 7, 2, 2, 1);
    g_signal_connect(buttonSub, "clicked", G_CALLBACK(subtraction_clicked), widgets);

    GtkWidget *buttonMult = gtk_button_new_with_label("Matrix Multiplication");
    gtk_grid_attach(GTK_GRID(topGrid), buttonMult, 7, 3, 2, 1);
    g_signal_connect(buttonMult, "clicked", G_CALLBACK(multiplication_clicked), widgets);

    GtkWidget *buttonReset = gtk_button_new_with_label("Reset Matrices");
    gtk_grid_attach(GTK_GRID(topGrid), buttonReset, 0, 7, 7, 1);
    g_signal_connect(buttonReset, "clicked", G_CALLBACK(reset_clicked), widgets);

    // ----- Bottom Frame -----
    GtkWidget *frameBottom = gtk_frame_new(NULL);
    gtk_widget_set_name(frameBottom, "frameBottom");
    gtk_box_pack_start(GTK_BOX(mainBox), frameBottom, TRUE, TRUE, 10);

    GtkWidget *bottomGrid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(bottomGrid), 5);
    gtk_grid_set_row_spacing(GTK_GRID(bottomGrid), 5);
    gtk_container_add(GTK_CONTAINER(frameBottom), bottomGrid);

    GtkWidget *label = gtk_label_new("Matrix");
    gtk_grid_attach(GTK_GRID(bottomGrid), label, 0, 0, 3, 1);

    GtkWidget *labelNum = gtk_label_new("Scalar Variable");
    gtk_grid_attach(GTK_GRID(bottomGrid), labelNum, 4, 0, 3, 1);

    GtkWidget *labelSecAns = gtk_label_new("Matrix Solution");
    gtk_grid_attach(GTK_GRID(bottomGrid), labelSecAns, 20, 0, 3, 1);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            widgets->entriesBase[i][j] = gtk_entry_new();
            gtk_grid_attach(GTK_GRID(bottomGrid), widgets->entriesBase[i][j], j, i + 1, 1, 1);

            widgets->entriesSecAns[i][j] = gtk_entry_new();
            gtk_grid_attach(GTK_GRID(bottomGrid), widgets->entriesSecAns[i][j], j + 20, i + 1, 1, 1);
        }
    }

    widgets->entryScalar = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(bottomGrid), widgets->entryScalar, 4, 2, 3, 1);

    GtkWidget *buttonScal = gtk_button_new_with_label("Scalar Multiplication");
    gtk_grid_attach(GTK_GRID(bottomGrid), buttonScal, 7, 1, 2, 1);
    g_signal_connect(buttonScal, "clicked", G_CALLBACK(scalar_multiplication_clicked), widgets);

    GtkWidget *buttonInv = gtk_button_new_with_label("Matrix Inverse");
    gtk_grid_attach(GTK_GRID(bottomGrid), buttonInv, 7, 2, 2, 1);
    g_signal_connect(buttonInv, "clicked", G_CALLBACK(inverse_clicked), widgets);

    GtkWidget *buttonTran = gtk_button_new_with_label("Matrix Transpose");
    gtk_grid_attach(GTK_GRID(bottomGrid), buttonTran, 7, 3, 2, 1);
    g_signal_connect(buttonTran, "clicked", G_CALLBACK(transpose_clicked), widgets);

    // Apply CSS styling to the window and children
    context = gtk_widget_get_style_context(window);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

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
