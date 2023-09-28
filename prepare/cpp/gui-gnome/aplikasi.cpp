#include <gtk/gtk.h>
#include <cairo.h>
#include <math.h>

const double PI = 3.14159265358979323846;
const int WINDOW_WIDTH = 300;
const int WINDOW_HEIGHT = 300;
const int CLOCK_RADIUS = 100;

gboolean drawClock(GtkWidget* widget, cairo_t* cr, gpointer data)
{
    int width, height;
    gtk_window_get_size(GTK_WINDOW(widget), &width, &height);

    cairo_translate(cr, width / 2.0, height / 2.0);
    cairo_scale(cr, CLOCK_RADIUS, CLOCK_RADIUS);
    cairo_set_line_width(cr, 0.05);

    // Draw clock circle
    cairo_arc(cr, 0, 0, 1, 0, 2 * PI);
    cairo_stroke(cr);

    // Draw hour hand
    double hour = fmod(gtk_adjustment_get_value(GTK_ADJUSTMENT(data)), 12);
    double hourAngle = (hour - 3) * (PI / 6);
    cairo_move_to(cr, 0, 0);
    cairo_line_to(cr, 0.4 * cos(hourAngle), 0.4 * sin(hourAngle));
    cairo_stroke(cr);

    // Draw minute hand
    double minute = fmod(gtk_adjustment_get_value(GTK_ADJUSTMENT(data)), 60);
    double minuteAngle = (minute - 15) * (PI / 30);
    cairo_move_to(cr, 0, 0);
    cairo_line_to(cr, 0.6 * cos(minuteAngle), 0.6 * sin(minuteAngle));
    cairo_stroke(cr);

    // Draw second hand
    double second = fmod(gtk_adjustment_get_value(GTK_ADJUSTMENT(data)), 60);
    double secondAngle = (second - 15) * (PI / 30);
    cairo_move_to(cr, 0, 0);
    cairo_line_to(cr, 0.8 * cos(secondAngle), 0.8 * sin(secondAngle));
    cairo_stroke(cr);

    return FALSE;
}

gboolean updateClock(gpointer data)
{
    GtkWidget* widget = GTK_WIDGET(data);
    if (gtk_widget_get_visible(widget))
    {
        gtk_widget_queue_draw(widget);
        return TRUE;
    }
    return FALSE;
}

int main(int argc, char** argv)
{
    GtkWidget* window;
    GtkWidget* drawingArea;
    GtkAdjustment* adjustment;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Analog Clock");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    drawingArea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), drawingArea);
    g_signal_connect(drawingArea, "draw", G_CALLBACK(drawClock), NULL);

    adjustment = GTK_ADJUSTMENT(gtk_adjustment_new(0, 0, 60, 1, 1, 0));
    g_timeout_add_seconds(1, updateClock, drawingArea);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
