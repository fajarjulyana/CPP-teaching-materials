#include <gtk/gtk.h>

// Callback function for the "clicked" signal of the button
static void button_clicked(GtkWidget* widget, gpointer data) {
    g_print("Button clicked!\n");
}

int main(int argc, char** argv) {
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Hello World");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 200, 100);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a button
    GtkWidget* button = gtk_button_new_with_label("Click Me");
    g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), NULL);

    // Add the button to the main window
    gtk_container_add(GTK_CONTAINER(window), button);

    // Show all the widgets
    gtk_widget_show_all(window);

    // Start the main loop
    gtk_main();

    return 0;
}