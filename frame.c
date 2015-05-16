#include "frame.h"

void close_door(GtkWidget *widget, gpointer label)
{
        if(strcmp(gtk_label_get_text(GTK_LABEL(label)) , "Open")==0)
        {
                gtk_label_set_text(GTK_LABEL(label), "Closed");
        }
}

void open_door(GtkWidget *widget, gpointer label)
{
        if(strcmp(gtk_label_get_text(GTK_LABEL(label)) , "Closed")==0)
        {
                gtk_label_set_text(GTK_LABEL(label), "Open");
        }
}


void click_directory(GtkWidget *widget, gpointer seq)
{
        GdkRGBA *color;
        color = (GdkRGBA *)malloc(sizeof(GdkRGBA));
        color->red = 1.0;
        color->green = 0.0;
        color->blue = 0.0;
        color->alpha = 1.0;
        if(((*(gint *)seq)++)%2==0)
        {
                gtk_widget_override_color(widget, GTK_STATE_FLAG_NORMAL, color);
        }
        else
        {
                gtk_widget_override_color(widget, GTK_STATE_FLAG_NORMAL, NULL);
        }
}


