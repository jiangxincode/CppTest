#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

GtkWidget *from_entry, *to_entry;
GtkWidget *sub_entry, *mlabel;
GtkWidget *text;
GtkTextBuffer *buffer;

void create_message_dialog(GtkMessageType type, const gchar *message);
gboolean send_email(const char *to, const char *sub, gchar *text);
void on_send(GtkButton *button, gpointer data);
