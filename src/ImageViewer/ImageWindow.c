/**
 * ImageWindow .c
 *
 * All the code to work with an image in a window
 */
#include<gtk/gtk.h>
#include "imageviewerutility.h"

/**
 * DestroyWindow()
 *
 * Callback triggered when the image window is destroyed .
 * A pointer to the image on display i s passed into the handler
 * i-n order that the image can be killed, preventing a memory
 * leak from occurring. The Active window pointer is also cleared .
 */
void DestroyWindow(GtkWidget* window, gpointer imagedata)
{
	g_object_unref((GdkPixbuf *) imagedata);
	ClearActiveWindow();
}
/**
 * GotFocus ( )
 *
 * Callback triggered when image window gets focus. It then
 * stores a pointer to it self and its image as the active window
 * and image, in order that main window GUI can work with the
 * correct window
 */
void GotFocus(GtkWidget * window, GdkEvent * event, gpointer imagedata)
{
	SetActiveWindow(window, (GdkPixbuf *) imagedata);
}

/**
 * SetImageintoWindow()
 *
 * A utility function that takes a GdkPixbuf image and puts it into
 * a specified window
 */
void SetImageIntoWindow(GtkWidget * window, GdkPixbuf * image)
{
	GtkWidget *pixmap;
	/* Check to see if there is already a child in the window */
	if (gtk_bin_get_child(GTK_BIN(window)) != NULL)
	{
		/* Destroy the child if there is one */
		gtk_widget_destroy(gtk_bin_get_child(GTK_BIN(window)));
	}
	/* Create a new pixmap from the passed in image */
	pixmap = gtk_image_new_from_pixbuf(image);
	/* Add the pixmap into the window and show it*/
	gtk_container_add(GTK_CONTAINER(window), pixmap);
	gtk_widget_show(pixmap);
	SetActiveWindow(window, image);
}

/**
 * FlipImage ( )
 *
 * Utility function to flip an image about an axis . The second
 * parameter dictates whether the calling code wants the image
 * to be flipped horizontally, or vertically
 */
void FlipImage(gboolean horizontal)
{
	GtkWidget *window;
	GdkPixbuf *image;
	/* Grab the active window pointer */

	window = GetActiveWindow();
	/* check the pointer isn't null before continuing */
	if (window != NULL)
	{
		/* grab the image and perform the flip */
		image = GetActiveImage();
		if (horizontal)
		{
			image = gdk_pixbuf_flip(image, TRUE);
		}
		else
		{
			image = gdk_pixbuf_flip(image, FALSE);
		}
		/* Set the flipped image into the active window */
		SetImageIntoWindow(window, image);
	}
}

/**
 * RotateImage()
 *
 * Utility to rotate an image 90 degrees .
 */
void RotateImage(gboolean clockwise)
{
	GtkWidget *window;
	GdkPixbuf *image;
	/* Grab the active window */
	window = GetActiveWindow();
	/* Check that the active window is valid before continuing */
	if (window != NULL)
	{
		/* Grab the active image */
		image = GetActiveImage();
		/* Rotate the image - second parameter is ignored at the moment*/
		if (clockwise)
		{
			image = gdk_pixbuf_rotate_simple(image, GDK_PIXBUF_ROTATE_CLOCKWISE);
		}
		else
		{
			image = gdk_pixbuf_rotate_simple(image, GDK_PIXBUF_ROTATE_COUNTERCLOCKWISE);
		}
		/* Set the new image into the window */
		SetImageIntoWindow(window, image);
	}
}

/**
 * CloseActiveimage ( )
 *
 * Utility function to close down the last active window .
 */
void CloseActiveImage()
{
	/* Grab the last active window pointer */
	GtkWidget *window = GetActiveWindow();
	/* If the pointer is valid, destroy the window */
	if (window != NULL)
		gtk_widget_destroy(window);
}
/**
 * ShowImage ( )
 *
 * The main entry function for the image window.

 * It takes the passed in filename and attempts to
 * load it up as an image
 **/
void ShowImage(gchar * filename)
{
	GdkPixbuf *image;
	GtkWidget *window;
	GtkWidget *messagebox;
	/* Attempt to load up 吐e specified image */
	image = gdk_pixbuf_new_from_file(filename, NULL);
	/* If the resulting image is NULL, then the load failed ....
	 * tell the user */
	if (image == NULL)
	{
		//TODO
		return;
	}
	/* Create a window in the usual way, with the filename as the title */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), filename);
	/* Set the newly loaded image into the window */
	SetImageIntoWindow(window, image);
	/* Connect up the window's signal handlers */
	g_signal_connect(G_OBJECT (window ), "destroy", G_CALLBACK (DestroyWindow ), image);
	g_signal_connect(G_OBJECT (window ), "focus_in_event", G_CALLBACK (GotFocus ), image);
	/* Finally, show the window */
	gtk_widget_show(window);
}

