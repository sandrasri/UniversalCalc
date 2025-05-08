// statisticalView.c
#include "statisticalView.h"
#include "view.h"
#include "sampleModel.h"
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern GtkWidget *stack;
GtkWidget *entryBox, *resultBox;

typedef struct {
    double numList[100];
    int count;
} Result;

Result helperOrderFunction(const char *current_text) { 
    //Split up the string into numList
    Result result;
    char *text_copy = strdup(current_text);
    char *token = strtok(text_copy, ",");
    result.count = 0;
    while (token != NULL) {
        result.numList[result.count++] = atof(token);
        token = strtok(NULL, ",");
    }
    return result;
}

void on_button_stat_clicked(GtkButton *button, gpointer data) {
    const char *current_text = gtk_entry_get_text(GTK_ENTRY(entryBox));
    const char *function = gtk_button_get_label(GTK_BUTTON(button));
    if (strlen(current_text) == 0) return;

    Result result = helperOrderFunction(current_text);
    double value = 0.0;
    char stat_label[50];

    if (strcmp(function, "Median") == 0) {
        value = calculateMedian(result.numList, result.count);
        strcpy(stat_label, "Median");
    } else if (strcmp(function, "Mean") == 0) {
        value = calculateMean(result.numList, result.count);
        strcpy(stat_label, "Mean");
    } else if (strcmp(function, "Mode") == 0) {
        value = calculateMode(result.numList, result.count);
        strcpy(stat_label, "Mode");
    } else if (strcmp(function, "StandardDev") == 0) {
        value = calculateStd(result.numList, result.count);
        strcpy(stat_label, "StandardDev");
    } else if (strcmp(function, "Variance") == 0) {
        value = calculateVariance(result.numList, result.count);
        strcpy(stat_label, "Variance");
    }

    char formatted[128];
    sprintf(formatted, "%s: %.2f", stat_label, value);

    const char *existing_text = gtk_entry_get_text(GTK_ENTRY(resultBox));
    char *updated = g_strdup_printf("%s%s%s", 
        strlen(existing_text) > 0 ? existing_text : "",
        strlen(existing_text) > 0 ? " | " : "",
        formatted);

    gtk_entry_set_text(GTK_ENTRY(resultBox), updated);
    g_free(updated);
}

void on_button_reset_clicked(GtkButton *button, gpointer user_data) {
    gtk_entry_set_text(GTK_ENTRY(entryBox), "");
    gtk_entry_set_text(GTK_ENTRY(resultBox), "");
}

GtkWidget* create_statistics_calculator_view() {
    GtkWidget *panel;
    GtkWidget *button_mean, *button_median, *button_mode, *button_std, *button_variance, *button_reset;
    GtkCssProvider *cssProvider;

    panel = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(panel), 10);
    gtk_grid_set_column_spacing(GTK_GRID(panel), 10);
    gtk_widget_set_name(panel, "mainPanel");

    // Entry Box (Input)
    entryBox = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryBox), "Enter numbers separated by commas");
    gtk_widget_set_name(entryBox, "entryBox");
    gtk_grid_attach(GTK_GRID(panel), entryBox, 0, 0, 6, 1);

    // Result Box (Output)
    resultBox = gtk_entry_new();
    gtk_editable_set_editable(GTK_EDITABLE(resultBox), FALSE);
    gtk_widget_set_name(resultBox, "resultBox");
    gtk_grid_attach(GTK_GRID(panel), resultBox, 0, 1, 6, 1);

    // Buttons (Horizontal layout)
    button_mean = gtk_button_new_with_label("Mean");
    button_median = gtk_button_new_with_label("Median");
    button_mode = gtk_button_new_with_label("Mode");
    button_std = gtk_button_new_with_label("StandardDev");
    button_variance = gtk_button_new_with_label("Variance");
    button_reset = gtk_button_new_with_label("Reset");

    gtk_grid_attach(GTK_GRID(panel), button_mean, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(panel), button_median, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(panel), button_mode, 2, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(panel), button_std, 3, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(panel), button_variance, 4, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(panel), button_reset, 5, 2, 1, 1);

    // Signal connections
    g_signal_connect(button_mean, "clicked", G_CALLBACK(on_button_stat_clicked), (gpointer)"Mean");
    g_signal_connect(button_median, "clicked", G_CALLBACK(on_button_stat_clicked), (gpointer)"Median");
    g_signal_connect(button_mode, "clicked", G_CALLBACK(on_button_stat_clicked), (gpointer)"Mode");
    g_signal_connect(button_std, "clicked", G_CALLBACK(on_button_stat_clicked), (gpointer)"Std Dev");
    g_signal_connect(button_variance, "clicked", G_CALLBACK(on_button_stat_clicked), (gpointer)"Variance");
    g_signal_connect(button_reset, "clicked", G_CALLBACK(on_button_reset_clicked), NULL);

    // Home button to return to the main menu
    GtkWidget *button_home = gtk_button_new_with_label("Home");
    g_signal_connect(button_home, "clicked", G_CALLBACK(on_button_home_clicked), NULL);
    gtk_grid_attach(GTK_GRID(panel), button_home, 2, 10, 1, 1);

    // CSS Styling
    cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(cssProvider,
        "#mainPanel { padding: 15px; background-color: #f8f8f8; }"
        "#entryBox, #resultBox { font-size: 16px; padding: 5px; border-radius: 5px; }"
        "button { font-weight: bold; padding: 8px 10px; border-radius: 8px; background: #e0f7fa; }"
        "button:hover { background: #b2ebf2; }"
    , -1, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    return panel;
}
