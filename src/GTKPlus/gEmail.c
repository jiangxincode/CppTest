/**
 * 在Linux上有一个很古老等电子邮件收发工具——mail命令行工具，gEmail利用GTK+为mail实现了一个简单等前端。用户可调用次工具来收发邮件。
 */
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

int main(int argc, char *argv[])
{
        GtkWidget *window;
        GtkWidget *vbox, *hbox1, *hbox2;
        GtkWidget *label, *button, *view;
        gtk_init(&argc, &argv);
        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(window), "gEmail");
        gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
        gtk_container_set_border_width(GTK_CONTAINER(window), 10);

        vbox = gtk_vbox_new(FALSE, 0);
        gtk_container_add(GTK_CONTAINER(window), vbox);

        hbox1 = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox), hbox1, FALSE, FALSE, 5);

        label = gtk_label_new("Email To:");
        gtk_box_pack_start(GTK_BOX(hbox1), label, FALSE, FALSE, 5);

        to_entry = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox1), to_entry, TRUE, TRUE, 5);

        button = gtk_button_new_with_label("Send");
        gtk_box_pack_start(GTK_BOX(hbox1), button, FALSE, FALSE, 5);

        hbox2 = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox), hbox2, FALSE, FALSE, 5);

        label = gtk_label_new("Theme:");
        gtk_box_pack_start(GTK_BOX(hbox2), label, FALSE, FALSE, 5);

        sub_entry = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox2), sub_entry, TRUE, TRUE, 5);

        view = gtk_scrolled_window_new(NULL, NULL);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(view), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

        text = gtk_text_view_new();
        buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text));
        gtk_container_add(GTK_CONTAINER(view), text);
        gtk_box_pack_start(GTK_BOX(vbox), view, TRUE, TRUE, 5);

        view = gtk_viewport_new(NULL, NULL);
        gtk_box_pack_start(GTK_BOX(vbox), view, FALSE, FALSE, 5);

        mlabel = gtk_label_new("Promote:Fill up the information and Send");
        gtk_container_add(GTK_CONTAINER(view), mlabel);

        g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(gtk_main_quit), NULL);
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_send), NULL);

        gtk_widget_show_all(window);
        gtk_main();
        return 0;
}

void on_send(GtkButton *button, gpointer data)
{
    GtkTextIter start, end;
    const char *to, *sub;
    char *buf;

    to = gtk_entry_get_text(GTK_ENTRY(to_entry));
    sub = gtk_entry_get_text(GTK_ENTRY(sub_entry));
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    buf = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);

    if(send_email(to,sub,buf))
    {
        create_message_dialog(GTK_MESSAGE_INFO, "Success");
    }
    else
    {
        create_message_dialog(GTK_MESSAGE_INFO,"Failed");
    }
}

gboolean send_email(const char *to, const char *sub, gchar *text)
{
    FILE *fp;
    char command[1024];
    fp = fopen("./letter","w");
    if(fp == NULL)
    {
        gtk_label_set_text(GTK_LABEL(mlabel), "Promote:Error in open the file");
        return FALSE;
    }
    fputs(text,fp);
    fclose(fp);
    sprintf(command, "mail %s -s %s < letter", to, sub);
    system(command);
    return TRUE;
}

void create_message_dialog(GtkMessageType type, const gchar *message)
{
    GtkWidget *dialogx;
    GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
    dialogx = gtk_message_dialog_new(NULL, flags, type, GTK_BUTTONS_OK, "%s", message);
    gtk_dialog_run(GTK_DIALOG(dialogx));
    gtk_widget_destroy(dialogx);
}


