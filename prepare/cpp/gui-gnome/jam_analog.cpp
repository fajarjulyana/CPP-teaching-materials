#include <gtk/gtk.h>
#include <math.h>

// Fungsi untuk menggambar jam analog
static gboolean draw_clock(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    gint width, height;
    gtk_widget_get_size_request(widget, &width, &height);

    // Mengatur ukuran jendela
    gtk_window_set_default_size(GTK_WINDOW(widget), 400, 400);

    // Mengatur titik pusat lingkaran jam
    gint center_x = width / 2;
    gint center_y = height / 2;
    gint radius = MIN(center_x, center_y) - 10;

    // Menggambar lingkaran jam
    cairo_set_source_rgb(cr, 1, 1, 1); // Warna latar belakang putih
    cairo_paint(cr);

    cairo_set_line_width(cr, 5);
    cairo_set_source_rgb(cr, 0, 0, 0); // Warna garis hitam

    // Menggambar lingkaran jam
    cairo_arc(cr, center_x, center_y, radius, 0, 2 * M_PI);
    cairo_stroke(cr);

    // Menggambar jarum jam
    gint hour = g_date_time_get_hour(g_date_time_new_now_local());
    gint minute = g_date_time_get_minute(g_date_time_new_now_local());
    gint second = g_date_time_get_second(g_date_time_new_now_local());

    gint hour_x = center_x + 0.4 * radius * sin((hour % 12 + minute / 60.0) * (M_PI / 6.0));
    gint hour_y = center_y - 0.4 * radius * cos((hour % 12 + minute / 60.0) * (M_PI / 6.0));

    gint minute_x = center_x + 0.6 * radius * sin(minute * (M_PI / 30.0));
    gint minute_y = center_y - 0.6 * radius * cos(minute * (M_PI / 30.0));

    gint second_x = center_x + 0.8 * radius * sin(second * (M_PI / 30.0));
    gint second_y = center_y - 0.8 * radius * cos(second * (M_PI / 30.0));

    cairo_set_line_width(cr, 5);
    cairo_set_source_rgb(cr, 0, 0, 1); // Warna jarum jam biru

    // Menggambar jarum jam
    cairo_move_to(cr, center_x, center_y);
   
    cairo_line_to(cr, hour_x, hour_y);
    cairo_stroke(cr);

    cairo_set_line_width(cr, 3);
    cairo_set_source_rgb(cr, 0, 1, 0); // Warna jarum menit hijau

    cairo_move_to(cr, center_x, center_y);
    cairo_line_to(cr, minute_x, minute_y);
    cairo_stroke(cr);

    cairo_set_line_width(cr, 2);
    cairo_set_source_rgb(cr, 1, 0, 0); // Warna jarum detik merah

    cairo_move_to(cr, center_x, center_y);
    cairo_line_to(cr, second_x, second_y);
    cairo_stroke(cr);

    return FALSE;
}

int main(int argc, char *argv[])
{
    // Inisialisasi GTK
    gtk_init(&argc, &argv);

    // Membuat jendela
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Analog Clock");
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Membuat area menggambar
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), drawing_area);
    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(draw_clock), NULL);

    // Menampilkan semua elemen
    gtk_widget_show_all(window);

    // Menjalankan main loop GTK
    gtk_main();

    return 0;
}
