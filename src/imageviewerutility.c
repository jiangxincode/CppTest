/**
 * imageviewerutility.c
 *
 * Utility functions for imageviewer app .
 **/
#include <gnome.h>

/* Setup pointers to keep track of the last window and image used */
GtkWidget *lastwindow;
GdkPixbuf * lastimage;

/**
 * SetActiveWindow ( )
 *
 * Used when a window becomes active . Stores its pointer so
 * the main window GUI can work with it .
 **/
void SetActiveWindow(GtkWidget * window, GdkPixbuf * image)
{
	lastimage = image;
	lastwindow = window;
}

/**
 * ClearActiveWindow ( )
 *
 * Used when a window deactivates . Clears the last window
 * pointer . Normally another window comes active afterwards ,
 * so last window is later checked out as NULL , there are no
 * graphics loaded .
 **/
void ClearActiveWindow()
{
	lastimage = NULL;
	lastwindow = NULL;
}

/**
 * GetActiveWindow ()
 *
 * Returns a painter t0 the last active window . Called from the
 * main window GUI in order for the GU工to work with the right
 * window .
 **/
GtkWidget *GetActiveWindow()
{
	return lastwindow;
}

/**
 * GetActive image ()
 *
 * Returns a pointer to the last active image .
 */
GdkPixbuf * GetActiveImage()
{
	return lastimage;
}
