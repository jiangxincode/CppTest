#include "gEmail.h"

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
