/**
 * main.c
 *
 * This is the main entry source for ImageViewer, responsible for
 * pieceing together the user interface of the application.
 * User interface signals are responded to in their own source files
 **/
#include <gnome.h>
#include "mainwindow.h"

/** Statics for application name and version **/
static gchar app_name[] = { "imageviewer" };
static gchar app_version[] = { "1.0" };

/** The ubiquitous main ( ) function **/
gint main(gint argc, gchar * argv[]) {
	gnome_init(app_name, app_version, argc, argv);
	BuildMainWindow(app_name, app_version);
	gtk_main();
	return 0;
}

