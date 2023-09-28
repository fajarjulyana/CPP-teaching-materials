#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <gtk/gtk.h>

// Struktur untuk data pengguna
struct User {
    std::string username;
    std::string password;
};

// Variabel global untuk menyimpan data pengguna
std::vector<User> users;

// Fungsi untuk membaca data pengguna dari file
void readUsersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file) {
        users.clear();
        std::string line;
        while (std::getline(file, line)) {
            size_t separatorPos = line.find(':');
            if (separatorPos != std::string::npos) {
                std::string username = line.substr(0, separatorPos);
                std::string password = line.substr(separatorPos + 1);
                users.push_back({username, password});
            }
        }
        file.close();
    }
}

// Fungsi untuk menulis data pengguna ke file
void writeUsersToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file) {
        for (const User& user : users) {
            file << user.username << ':' << user.password << '\n';
        }
        file.close();
    }
}

// Fungsi untuk mengecek keberadaan pengguna berdasarkan username
bool isUserExists(const std::string& username) {
    for (const User& user : users) {
        if (user.username == username) {
            return true;
        }
    }
    return false;
}

// Fungsi callback saat tombol Login diklik
void onLoginButtonClicked(GtkButton* button, gpointer data) {
    // Dapatkan username dan password dari entry
    GtkEntry* usernameEntry = GTK_ENTRY(data);
    GtkEntry* passwordEntry = GTK_ENTRY(gtk_bin_get_child(GTK_BIN(data)));

    const gchar* username = gtk_entry_get_text(usernameEntry);
    const gchar* password = gtk_entry_get_text(passwordEntry);

    // Cek keberadaan pengguna
    if (isUserExists(username)) {
        // Cek kecocokan password
        for (const User& user : users) {
            if (user.username == username && user.password == password) {
                // Login berhasil, tampilkan jendela utama dan sembunyikan jendela login
                GtkWidget* mainWindow = static_cast<GtkWidget*>(g_object_get_data(G_OBJECT(button), "mainWindow"));
                gtk_widget_hide(GTK_WIDGET(gtk_widget_get_parent(GTK_WIDGET(button))));
                gtk_widget_show_all(mainWindow);
                return;
            }
        }
    }

    // Jika login gagal, tampilkan pesan kesalahan
    GtkWidget* dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,
                                               "Login failed. Invalid username or password.");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

// Fungsi callback saat tombol Logout diklik
void onLogoutButtonClicked(GtkButton* button, gpointer data) {
    // Tampilkan jendela login dan sembunyikan jendela utama
    GtkWidget* loginWindow = static_cast<GtkWidget*>(g_object_get_data(G_OBJECT(button), "loginWindow"));
    GtkWidget* mainWindow = static_cast<GtkWidget*>(g_object_get_data(G_OBJECT(button), "mainWindow"));
    gtk_widget_hide(mainWindow);
    gtk_widget_show_all(loginWindow);
}

int main(int argc, char* argv[]) {
    // Inisialisasi GTK
    gtk_init(&argc, &argv);

    // Baca data pengguna dari file
    readUsersFromFile("users.txt");

    // Buat jendela login
    GtkWidget* loginWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(loginWindow), "Login");
    gtk_container_set_border_width(GTK_CONTAINER(loginWindow), 10);

    GtkWidget* loginBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(loginWindow), loginBox);

    GtkWidget* usernameEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(usernameEntry), "Username");
    gtk_box_pack_start(GTK_BOX(loginBox), usernameEntry, FALSE, FALSE, 0);

    GtkWidget* passwordEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(passwordEntry), "Password");
    gtk_entry_set_visibility(GTK_ENTRY(passwordEntry), FALSE);
    gtk_box_pack_start(GTK_BOX(loginBox), passwordEntry, FALSE, FALSE, 0);

    GtkWidget* loginButton = gtk_button_new_with_label("Login");
    gtk_box_pack_start(GTK_BOX(loginBox), loginButton, FALSE, FALSE, 0);

    g_signal_connect(loginButton, "clicked", G_CALLBACK(onLoginButtonClicked), passwordEntry);

    gtk_widget_show_all(loginWindow);

    // Buat jendela utama
    GtkWidget* mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(mainWindow), "Nama Acak");
    gtk_container_set_border_width(GTK_CONTAINER(mainWindow), 10);
    gtk_window_set_default_size(GTK_WINDOW(mainWindow), 300, 200);

    GtkWidget* mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(mainWindow), mainBox);

    GtkWidget* nameLabel = gtk_label_new("Nama Acak");
    gtk_box_pack_start(GTK_BOX(mainBox), nameLabel, TRUE, TRUE, 0);

    GtkWidget* generateButton = gtk_button_new_with_label("Generate");
    gtk_box_pack_start(GTK_BOX(mainBox), generateButton, TRUE, TRUE, 0);

    GtkWidget* logoutButton = gtk_button_new_with_label("Logout");
    gtk_box_pack_end(GTK_BOX(mainBox), logoutButton, TRUE, TRUE, 0);

    g_signal_connect(logoutButton, "clicked", G_CALLBACK(onLogoutButtonClicked), NULL);

    g_signal_connect(mainWindow, "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    // Simpan pointer jendela login dan jendela utama sebagai data pada tombol
    g_object_set_data(G_OBJECT(loginButton), "loginWindow", loginWindow);
    g_object_set_data(G_OBJECT(loginButton), "mainWindow", mainWindow);
    g_object_set_data(G_OBJECT(logoutButton), "loginWindow", loginWindow);
    g_object_set_data(G_OBJECT(logoutButton), "mainWindow", mainWindow);

    gtk_widget_hide(mainWindow);

    // Jalankan GTK main loop
    gtk_main();

    // Tulis data pengguna ke file sebelum keluar
    writeUsersToFile("users.txt");

    return 0;
}
