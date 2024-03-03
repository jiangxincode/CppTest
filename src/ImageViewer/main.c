/**
 * main.c
 *
 * This is the main entry source for ImageViewer, responsible for
 * piecing together the user interface of the application.
 * User interface signals are responded to in their own source files
 **/

#include <gtk/gtk.h>
#include "mainwindow.h"

/** Statics for application name and version **/
static gchar app_name[] =
{ "ImageViewer" };

static gchar app_version[] =
{ "1.0" };

/** The ubiquitous main() function **/
gint main(gint argc, gchar * argv[])
{
	gtk_init(&argc, &argv);
    BuildMainWindow(app_name, app_version);
	gtk_main();
	return 0;
}

