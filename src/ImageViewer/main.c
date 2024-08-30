#include <gtk/gtk.h>
#include "mainwindow.h"

static gchar app_name[] = {"ImageViewer"};

static gchar app_version[] = {"1.0"};

gint main(gint argc, gchar *argv[])
{
    gtk_init(&argc, &argv);
    build_main_window(app_name, app_version);
    gtk_main();
    return 0;
}
