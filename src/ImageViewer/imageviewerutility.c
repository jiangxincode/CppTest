/**
 *
 * Utility functions for image viewer application .
 **/
#include <gtk/gtk.h>

/* Setup pointers to keep track of the last window and image used */
GtkWidget *lastwindow;
GdkPixbuf *lastimage;

/**
 *
 * Used when a window becomes active. Stores its pointer so
 * the main window GUI can work with it.
 **/
void set_active_window(GtkWidget *window, GdkPixbuf *image)
{
    lastimage = image;
    lastwindow = window;
}

/**
 *
 * Used when a window deactivates. Clears the last window
 * pointer. Normally another window comes active afterwards,
 * so last window is later checked out as NULL, there are no
 * graphics loaded .
 **/
void clear_active_window()
{
    lastimage = NULL;
    lastwindow = NULL;
}

/**
 *
 * Returns a painter t0 the last active window . Called from the
 * main window GUI in order for the GU工to work with the right
 * window .
 **/
GtkWidget *get_active_window()
{
    return lastwindow;
}

/**
 *
 * Returns a pointer to the last active image .
 */
GdkPixbuf *get_active_image()
{
    return lastimage;
}
