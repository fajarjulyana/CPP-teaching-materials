#include <gtk/gtk.h>
#include <iostream>
#include <string>
//#include <SerialStream.h>

using namespace std;
//using namespace LibSerial;

GtkWidget *window;
GtkWidget *buttonForward;
GtkWidget *buttonBackward;
GtkWidget *buttonLeft;
GtkWidget *buttonRight;
GtkWidget *buttonStop;

//SerialStream serialPort;
/*
void sendCommand(GtkWidget *widget, gpointer data) {
  const string command = static_cast<const char*>(data);
  serialPort << command << flush;
}
*/
int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);

  // Create the main window
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Bluetooth Control Car");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  // Create buttons
  buttonForward = gtk_button_new_with_label("Forward");
  buttonBackward = gtk_button_new_with_label("Backward");
  buttonLeft = gtk_button_new_with_label("Left");
  buttonRight = gtk_button_new_with_label("Right");
  buttonStop = gtk_button_new_with_label("Stop");
/*
  // Connect button signals to callbacks
  g_signal_connect(buttonForward, "clicked", G_CALLBACK(sendCommand), (gpointer)"F");
  g_signal_connect(buttonBackward, "clicked", G_CALLBACK(sendCommand), (gpointer)"B");
  g_signal_connect(buttonLeft, "clicked", G_CALLBACK(sendCommand), (gpointer)"L");
  g_signal_connect(buttonRight, "clicked", G_CALLBACK(sendCommand), (gpointer)"R");
  g_signal_connect(buttonStop, "clicked", G_CALLBACK(sendCommand), (gpointer)"S");

  // Create a vertical box layout and add buttons
  GtkWidget *vbox = gtk_vbox_new(TRUE, 5);
  gtk_box_pack_start(GTK_BOX(vbox), buttonForward, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), buttonBackward, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), buttonLeft, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), buttonRight, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), buttonStop, TRUE, TRUE, 0);

  // Add the layout to the main window and show all widgets
  gtk_container_add(GTK_CONTAINER(window), vbox);
  gtk_widget_show_all(window);

  // Open the serial port
  serialPort.Open("/dev/ttyACM0");
  if (!serialPort.good()) {
    cerr << "Error opening serial port" << endl;
    return 1;
  }

  // Configure the serial port settings
  serialPort.SetBaudRate(SerialStreamBuf::BAUD_9600);
  serialPort.SetCharSize(SerialStreamBuf::CHAR_SIZE_8);
  serialPort.SetNumOfStopBits(1);
  serialPort.SetParity(SerialStreamBuf::PARITY_NONE);
  serialPort.SetFlowControl(SerialStreamBuf::FLOW_CONTROL_NONE);

  gtk_main();

  // Close the serial port
  serialPort.Close();
*/
  return 0;

}
