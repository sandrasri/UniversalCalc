// conversionView.c
#include "conversionView.h"
#include "view.h"
#include "sampleModel.h"
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern GtkWidget *stack;
const char *selected_from_conversion = NULL;
const char *selected_to_conversion = NULL;
const char *selected_to_conversionNum = NULL;
const char *selected_from_conversionNum = NULL;
const double selectedValue;

typedef struct {
    const char *type;
    GtkWidget *item_label;
} MenuSignalData;

// Callback function for dropdown menu items
void on_menu_item_clicked(GtkMenuItem *menuitem, gpointer user_data) {
    MenuSignalData *data = (MenuSignalData*) user_data;
    const char *text = gtk_menu_item_get_label(menuitem);

    if (strcmp(data->type, "from") == 0) {
        selected_from_conversion = text;
    } else if (strcmp(data->type, "to") == 0) {
        selected_to_conversion = text;
    } else if (strcmp(data->type, "toNum") == 0) {
        selected_to_conversionNum = text;
    } else if (strcmp(data->type, "fromNum") == 0) {
        selected_from_conversionNum = text;
    }

    gtk_menu_item_set_label(GTK_MENU_ITEM(data->item_label), text);
}

void on_numconvert_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget **widgets = (GtkWidget**) user_data;
    GtkWidget *entryNum = widgets[0];
    GtkWidget *label_Numresult = widgets[1];

    const gchar *input_numtext = gtk_entry_get_text(GTK_ENTRY(entryNum));
    if (!selected_from_conversionNum || !selected_to_conversionNum || strlen(input_numtext) == 0) {
        gtk_label_set_text(GTK_LABEL(label_Numresult), "Please select both conversions and enter a value.");
        return;
    }
    
    int value = atof(input_numtext);
    const char* result = compute_numconversion(selected_from_conversionNum, selected_to_conversionNum, value);
    
    char result_str[100];
    if (strcmp(result, "0.0") != 0) {
        snprintf(result_str, sizeof(result_str), "%.2d %s = %s %s", value, selected_from_conversionNum, result, selected_to_conversionNum);
        gtk_label_set_text(GTK_LABEL(label_Numresult), result_str);
    }
    else {
        snprintf(result_str, sizeof(result_str), "Cannot convert values");
        gtk_label_set_text(GTK_LABEL(label_Numresult), result_str);
    }
}

void on_convert_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget **widgets = (GtkWidget**) user_data;
    GtkWidget *entry = widgets[0];
    GtkWidget *label_result = widgets[1];

    const gchar *input_text = gtk_entry_get_text(GTK_ENTRY(entry));
    if (!selected_from_conversion || !selected_to_conversion || strlen(input_text) == 0) {
        gtk_label_set_text(GTK_LABEL(label_result), "Please select both conversions and enter a value.");
        return;
    }

    double value = atof(input_text);
    double result = perform_conversion(selected_from_conversion, selected_to_conversion, value);
    
    char result_str[100];
    if (result != 0) {
        snprintf(result_str, sizeof(result_str), "%.2f %s = %.2f %s", value, selected_from_conversion, result, selected_to_conversion);
        gtk_label_set_text(GTK_LABEL(label_result), result_str);
    }
    else {
        snprintf(result_str, sizeof(result_str), "Cannot convert values");
        gtk_label_set_text(GTK_LABEL(label_result), result_str);
    }
    
}

GtkWidget* create_conversion_calculator_view() {
    GtkWidget *basic, *vbox, *secondbox;
    GtkCssProvider *cssProvider;

    basic = gtk_grid_new();
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    secondbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);

    // Load CSS for styling
    cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(cssProvider,
        "#frameTop { background-color: #e0f7fa; padding: 20px; border-radius: 10px; }"
        "#frameBottom { background-color: #f1f8e9; padding: 20px; border-radius: 10px; }"
        "menubar {"
        "    background-color: #c8e6c9;"
        "    padding: 5px;"
        "    border-radius: 4px;"
        "}"
        "menuitem {"
        "    font-size: 14px;"
        "    padding: 6px 12px;"
        "}"
        "menuitem:hover {"
        "    background-color: #a5d6a7;"
        "}"
    , -1, NULL);

    // These will be reused in signal connections
    GtkWidget *fromItem = gtk_menu_item_new_with_label("From Conversion");
    MenuSignalData *from_data = g_new(MenuSignalData, 1);
    from_data->type = "from";
    from_data->item_label = fromItem;
    
    GtkWidget *toItem = gtk_menu_item_new_with_label("To Conversion");
    MenuSignalData *to_data = g_new(MenuSignalData, 1);
    to_data->type = "to";
    to_data->item_label = toItem; 

    GtkWidget *fromItemNum = gtk_menu_item_new_with_label("From Conversion Num");
    MenuSignalData *from_dataNum = g_new(MenuSignalData, 1);
    from_dataNum->type = "fromNum";
    from_dataNum->item_label = fromItemNum;
    
    GtkWidget *toItemNum = gtk_menu_item_new_with_label("To Conversion Num");
    MenuSignalData *to_dataNum = g_new(MenuSignalData, 1);
    to_dataNum->type = "toNum";
    to_dataNum->item_label = toItemNum; 

    // Create "From Conversion" menu
    GtkWidget *menubar = gtk_menu_bar_new();
    GtkWidget *fromMenu = gtk_menu_new();
    GtkWidget *lb_from = gtk_menu_item_new_with_label("lb");
    GtkWidget *gram_from = gtk_menu_item_new_with_label("gram");
    GtkWidget *celsius_from = gtk_menu_item_new_with_label("celsius");
    GtkWidget *fahrenheit_from = gtk_menu_item_new_with_label("fahrenheit");
    GtkWidget *kilogram_from = gtk_menu_item_new_with_label("kilogram");
    GtkWidget *kilometer_from = gtk_menu_item_new_with_label("kilometer");
    GtkWidget *centimeter_from = gtk_menu_item_new_with_label("centimeter");
    GtkWidget *inches_from = gtk_menu_item_new_with_label("inches");
    GtkWidget *miles_from = gtk_menu_item_new_with_label("miles");
    GtkWidget *meter_from = gtk_menu_item_new_with_label("meter");
    GtkWidget *feet_from = gtk_menu_item_new_with_label("feet");
    GtkWidget *litre_from = gtk_menu_item_new_with_label("litre");
    GtkWidget *gallon_from = gtk_menu_item_new_with_label("gallon");
    GtkWidget *ounce_from = gtk_menu_item_new_with_label("ounce");
    GtkWidget *millilitre_from = gtk_menu_item_new_with_label("millilitre");
    GtkWidget *kelvin_from = gtk_menu_item_new_with_label("kelvin");
    
    GtkWidget *label_conversion = gtk_label_new("Select units and enter a value to convert");
    GtkWidget *entry_value = gtk_entry_new();
    GtkWidget *button_convert = gtk_button_new_with_label("Convert");
    GtkWidget *label_result = gtk_label_new("Result will appear here");

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(fromItem), fromMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(fromMenu), lb_from);
    gtk_menu_shell_append(GTK_MENU_SHELL(fromMenu), gram_from);
    gtk_menu_shell_append(GTK_MENU_SHELL(fromMenu), celsius_from);
    gtk_menu_shell_append(GTK_MENU_SHELL(fromMenu), fahrenheit_from);
    gtk_menu_shell_append(GTK_MENU_SHELL(fromMenu), kilogram_from);
    gtk_menu_shell_append(GTK_MENU_SHELL(fromMenu), centimeter_from);
    gtk_menu_shell_append(GTK_MENU_SHELL(fromMenu), inches_from);
    gtk_menu_shell_append(GTK_MENU_SHELL(fromMenu), miles_from);
    gtk_menu_shell_append(GTK_MENU_SHELL(fromMenu), meter_from);
    gtk_menu_shell_append(GTK_MENU_SHELL(fromMenu), feet_from);
    gtk_menu_shell_append(GTK_MENU_SHELL(fromMenu), kilometer_from);
    gtk_menu_shell_append(GTK_MENU_SHELL(fromMenu), litre_from);
    gtk_menu_shell_append(GTK_MENU_SHELL(fromMenu), gallon_from);
    gtk_menu_shell_append(GTK_MENU_SHELL(fromMenu), ounce_from);
    gtk_menu_shell_append(GTK_MENU_SHELL(fromMenu), millilitre_from);
    gtk_menu_shell_append(GTK_MENU_SHELL(fromMenu), kelvin_from);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), fromItem);

    // Connect signals for "From Conversion" menu items
    g_signal_connect(lb_from, "activate", G_CALLBACK(on_menu_item_clicked), from_data);
    g_signal_connect(gram_from, "activate", G_CALLBACK(on_menu_item_clicked), from_data);
    g_signal_connect(celsius_from, "activate", G_CALLBACK(on_menu_item_clicked), from_data);
    g_signal_connect(fahrenheit_from, "activate", G_CALLBACK(on_menu_item_clicked), from_data);
    g_signal_connect(kilogram_from, "activate", G_CALLBACK(on_menu_item_clicked), from_data);
    g_signal_connect(centimeter_from, "activate", G_CALLBACK(on_menu_item_clicked), from_data);
    g_signal_connect(inches_from, "activate", G_CALLBACK(on_menu_item_clicked), from_data);
    g_signal_connect(miles_from, "activate", G_CALLBACK(on_menu_item_clicked), from_data);
    g_signal_connect(meter_from, "activate", G_CALLBACK(on_menu_item_clicked), from_data);
    g_signal_connect(feet_from, "activate", G_CALLBACK(on_menu_item_clicked), from_data);
    g_signal_connect(kilometer_from, "activate", G_CALLBACK(on_menu_item_clicked), from_data);
    g_signal_connect(litre_from, "activate", G_CALLBACK(on_menu_item_clicked), from_data);
    g_signal_connect(gallon_from, "activate", G_CALLBACK(on_menu_item_clicked), from_data);
    g_signal_connect(ounce_from, "activate", G_CALLBACK(on_menu_item_clicked), from_data);
    g_signal_connect(millilitre_from, "activate", G_CALLBACK(on_menu_item_clicked), from_data);
    g_signal_connect(kelvin_from, "activate", G_CALLBACK(on_menu_item_clicked), from_data);

    // Create "To Conversion" menu
    GtkWidget *toMenu = gtk_menu_new();
    GtkWidget *lb_to = gtk_menu_item_new_with_label("lb");
    GtkWidget *gram_to = gtk_menu_item_new_with_label("gram");
    GtkWidget *celsius_to = gtk_menu_item_new_with_label("celsius");
    GtkWidget *fahrenheit_to = gtk_menu_item_new_with_label("fahrenheit");
    GtkWidget *kilogram_to = gtk_menu_item_new_with_label("kilogram");
    GtkWidget *kilometer_to = gtk_menu_item_new_with_label("kilometer");
    GtkWidget *centimeter_to = gtk_menu_item_new_with_label("centimeter");
    GtkWidget *inches_to = gtk_menu_item_new_with_label("inches");
    GtkWidget *miles_to = gtk_menu_item_new_with_label("miles");
    GtkWidget *meter_to = gtk_menu_item_new_with_label("meter");
    GtkWidget *feet_to = gtk_menu_item_new_with_label("feet");
    GtkWidget *litre_to = gtk_menu_item_new_with_label("litre");
    GtkWidget *gallon_to = gtk_menu_item_new_with_label("gallon");
    GtkWidget *ounce_to = gtk_menu_item_new_with_label("ounce");
    GtkWidget *millilitre_to = gtk_menu_item_new_with_label("millilitre");
    GtkWidget *kelvin_to = gtk_menu_item_new_with_label("kelvin");

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(toItem), toMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(toMenu), lb_to);
    gtk_menu_shell_append(GTK_MENU_SHELL(toMenu), gram_to);
    gtk_menu_shell_append(GTK_MENU_SHELL(toMenu), celsius_to);
    gtk_menu_shell_append(GTK_MENU_SHELL(toMenu), fahrenheit_to);
    gtk_menu_shell_append(GTK_MENU_SHELL(toMenu), kilogram_to);
    gtk_menu_shell_append(GTK_MENU_SHELL(toMenu), centimeter_to);
    gtk_menu_shell_append(GTK_MENU_SHELL(toMenu), inches_to);
    gtk_menu_shell_append(GTK_MENU_SHELL(toMenu), miles_to);
    gtk_menu_shell_append(GTK_MENU_SHELL(toMenu), meter_to);
    gtk_menu_shell_append(GTK_MENU_SHELL(toMenu), gallon_to);
    gtk_menu_shell_append(GTK_MENU_SHELL(toMenu), ounce_to);
    gtk_menu_shell_append(GTK_MENU_SHELL(toMenu), litre_to);
    gtk_menu_shell_append(GTK_MENU_SHELL(toMenu), feet_to);
    gtk_menu_shell_append(GTK_MENU_SHELL(toMenu), kilometer_to);
    gtk_menu_shell_append(GTK_MENU_SHELL(toMenu), millilitre_to);
    gtk_menu_shell_append(GTK_MENU_SHELL(toMenu), kelvin_to);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), toItem);

    // Connect signals for "To Conversion" menu items
    g_signal_connect(lb_to, "activate", G_CALLBACK(on_menu_item_clicked), to_data);
    g_signal_connect(gram_to, "activate", G_CALLBACK(on_menu_item_clicked), to_data);
    g_signal_connect(celsius_to, "activate", G_CALLBACK(on_menu_item_clicked), to_data);
    g_signal_connect(fahrenheit_to, "activate", G_CALLBACK(on_menu_item_clicked), to_data);
    g_signal_connect(kilogram_to, "activate", G_CALLBACK(on_menu_item_clicked), to_data);
    g_signal_connect(centimeter_to, "activate", G_CALLBACK(on_menu_item_clicked), to_data);
    g_signal_connect(inches_to, "activate", G_CALLBACK(on_menu_item_clicked), to_data);
    g_signal_connect(miles_to, "activate", G_CALLBACK(on_menu_item_clicked), to_data);
    g_signal_connect(meter_to, "activate", G_CALLBACK(on_menu_item_clicked), to_data);
    g_signal_connect(feet_to, "activate", G_CALLBACK(on_menu_item_clicked), to_data);
    g_signal_connect(litre_to, "activate", G_CALLBACK(on_menu_item_clicked), to_data);
    g_signal_connect(gallon_to, "activate", G_CALLBACK(on_menu_item_clicked), to_data);
    g_signal_connect(ounce_to, "activate", G_CALLBACK(on_menu_item_clicked), to_data);
    g_signal_connect(kilometer_to, "activate", G_CALLBACK(on_menu_item_clicked), to_data);
    g_signal_connect(millilitre_to, "activate", G_CALLBACK(on_menu_item_clicked), to_data);
    g_signal_connect(kelvin_to, "activate", G_CALLBACK(on_menu_item_clicked), to_data);   

    gtk_box_pack_start(GTK_BOX(vbox), menubar, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), label_conversion, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_value, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button_convert, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), label_result, FALSE, FALSE, 0);
    gtk_grid_attach(GTK_GRID(basic), vbox, 1, 0, 10, 10);

    //Create Numerical Conversion Menu
    // Create "From Conversion Num" menu
    GtkWidget *numericalmenu = gtk_menu_bar_new();
    GtkWidget *frommenu_num = gtk_menu_new();
    GtkWidget *decimal_from = gtk_menu_item_new_with_label("decimal");
    GtkWidget *binary_from = gtk_menu_item_new_with_label("binary");
    GtkWidget *hexadecimal_from = gtk_menu_item_new_with_label("hexadecimal");

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(fromItemNum), frommenu_num);
    gtk_menu_shell_append(GTK_MENU_SHELL(frommenu_num), decimal_from);
    gtk_menu_shell_append(GTK_MENU_SHELL(frommenu_num), binary_from);
    gtk_menu_shell_append(GTK_MENU_SHELL(frommenu_num), hexadecimal_from);
    gtk_menu_shell_append(GTK_MENU_SHELL(numericalmenu), fromItemNum);

    g_signal_connect(binary_from, "activate", G_CALLBACK(on_menu_item_clicked), from_dataNum);
    g_signal_connect(decimal_from, "activate", G_CALLBACK(on_menu_item_clicked), from_dataNum);
    g_signal_connect(hexadecimal_from, "activate", G_CALLBACK(on_menu_item_clicked), from_dataNum);

    GtkWidget *label_numconversion = gtk_label_new("Select units and enter a value to convert");
    GtkWidget *entry_numvalue = gtk_entry_new();
    GtkWidget *button_numconvert = gtk_button_new_with_label("Convert");
    GtkWidget *label_numresult = gtk_label_new("Result will appear here");

    // Create "To Conversion Num" menu
    GtkWidget *tomenu_num = gtk_menu_new();
    GtkWidget *decimal_to = gtk_menu_item_new_with_label("decimal");
    GtkWidget *binary_to = gtk_menu_item_new_with_label("binary");
    GtkWidget *hexadecimal_to = gtk_menu_item_new_with_label("hexadecimal");

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(toItemNum), tomenu_num);
    gtk_menu_shell_append(GTK_MENU_SHELL(tomenu_num), decimal_to);
    gtk_menu_shell_append(GTK_MENU_SHELL(tomenu_num), binary_to);
    gtk_menu_shell_append(GTK_MENU_SHELL(tomenu_num), hexadecimal_to);
    gtk_menu_shell_append(GTK_MENU_SHELL(numericalmenu), toItemNum);

    g_signal_connect(binary_to, "activate", G_CALLBACK(on_menu_item_clicked), to_dataNum);
    g_signal_connect(decimal_to, "activate", G_CALLBACK(on_menu_item_clicked), to_dataNum);
    g_signal_connect(hexadecimal_to, "activate", G_CALLBACK(on_menu_item_clicked), to_dataNum);

    gtk_box_pack_start(GTK_BOX(secondbox), numericalmenu, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(secondbox), label_numconversion, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(secondbox), entry_numvalue, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(secondbox), button_numconvert, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(secondbox), label_numresult, FALSE, FALSE, 0);
    gtk_grid_attach(GTK_GRID(basic), secondbox, 30, 0, 10, 10);

    // Home button to return to the main menu
    GtkWidget *button_home = gtk_button_new_with_label("Home");
    g_signal_connect(button_home, "clicked", G_CALLBACK(on_button_home_clicked), NULL);
    gtk_grid_attach(GTK_GRID(basic), button_home, 10, 10, 2, 1);

    GtkWidget **widget_refs = g_new(GtkWidget*, 2);
    widget_refs[0] = entry_value;
    widget_refs[1] = label_result;

    GtkWidget **widget_numrefs = g_new(GtkWidget*, 2);
    widget_numrefs[0] = entry_numvalue;
    widget_numrefs[1] = label_numresult;

    g_signal_connect(button_convert, "clicked", G_CALLBACK(on_convert_button_clicked), widget_refs);
    g_signal_connect(button_numconvert, "clicked", G_CALLBACK(on_numconvert_button_clicked), widget_numrefs);

    // Apply CSS styling to the window and children
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    return basic;
}
