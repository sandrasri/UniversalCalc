// conversionView.c
#include "conversionView.h"
#include "view.h"
#include "sampleModel.h"
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern GtkWidget *stack;

GtkWidget* create_conversion_calculator_view() {
    GtkWidget *basic, *vbox;
   // GtkWidget *to_conversion, *from_conversion;

    GtkCssProvider *cssProvider;

    basic = gtk_grid_new();
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);

    // Load CSS for styling
    cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(cssProvider,
        "#frameTop { background-color: #e0f7fa; padding: 20px; border-radius: 10px; }"
        "#frameBottom { background-color: #f1f8e9; padding: 20px; border-radius: 10px; }"
        "button { margin: 4px; padding: 6px 12px; font-weight: bold; }",
        -1, NULL
    );

    GtkWidget *menubar = gtk_menu_bar_new();
    GtkWidget *fileMenu = gtk_menu_new();
    GtkWidget *fileMi = gtk_menu_item_new_with_label("File");
    GtkWidget *quitMi = gtk_menu_item_new_with_label("Quit");

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMi), fileMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quitMi);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), fileMi);
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);
    gtk_grid_attach(GTK_GRID(basic), vbox, 0, 0, 1, 5);

    // Home button to return to the main menu
    GtkWidget *button_home = gtk_button_new_with_label("Home");
    g_signal_connect(button_home, "clicked", G_CALLBACK(on_button_home_clicked), NULL);
    gtk_grid_attach(GTK_GRID(basic), button_home, 10, 10, 2, 1);

   // Apply CSS styling to the window and children
   gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

   return basic;
}
