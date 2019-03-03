#include "gEmail.h"

int main0000(int argc, char *argv[])
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

