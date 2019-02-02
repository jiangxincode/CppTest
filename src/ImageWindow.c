/**
 * ImageWindow .c
 *
 * All the code to work with an image in a window
 */
#include <gnome.h>
#include "imageviewerutility.h"

/**
 * DestroyWindow ( )
 *
 * Callback triggered when the image window is destroyed .
 * A pointer to the image on display i s passed into the handler
 * i-n order that the image can be killed , preventing a memory
 * leak from occuring. The Active window pointer is also cleared .
 */
void DestroyWindow(GtkWidget* window, gpointer imagedata)
{
	gdk_imlib_kill_image((GdkImlibImage *) imagedata);
	ClearActiveWindow();
}
/**
 * GotFocus ( )
 *
 * Callback triggered when image window gets focus . It then
 * stores a pointer to it self and its image as the act ive window
 * and image , in order that main window gui can work with the
 * correct window
 */
void GotFocus(GtkWidget * window, GdkEvent * event, gpointer imagedata)
{
	SetActiveWindow(window, (GdkImlibImage *) imagedata);
}

/**
 * Set imageintoWindow ( )
 *
 * A utility function that takes a GdkimLib image and puts it into
 * a specified window
 */
void SetImageintoWindow(GtkWidget * window, GdkImlibImage * image)
{
	GtkWidget *pixmap;
	/* Check to see if there is already a child in the window */
	if (gtk_bin_get_child(GTK_BIN(window)) != NULL)
		/* Destroy the child if there is one */
		gtk_widget_destroy(gtk_bin_get_child(GTK_BIN(window)));
	/* Create a new GnomePixmap from the passed in image */
	pixmap = gnome_pixmap_new_from_imlib(image);
	/* Add the GnomePixmap into the window and show it*/
	gtk_container_add(GTK_CONTAINER(window), pixmap);
	gtk_widget_show(pixmap);
}

/**
 * Flipimage ( )
 *
 * Utility function to flip an image about an axis . The second
 * parameter dictates whether the calling code wants the image
 * to be flipped horizontally, or vertically
 */
void Flipimage(gboolean horizontal)
{
	GtkWidget *window;
	GdkImlibImage * image;
	/* Grab the active window pointer */

	window = GetActiveWindow();
	/* check the pointer isn ' t null before continuing */
	if (window != NULL)
	{
		/* grab the image and perform the flip */
		image = GetActiveimage();
		if (horizontal)
			gdk_imlib_flip_image_horizontal(image);
		else
			gdk_imlib_flip_image_vertical(image);
		/* Set the flipped image into the active window */
		SetimageintoWindow(window, image);
	}
}
/**
 * RotateImage ( )
 *
 * Utility to rotate an image 90 degrees .
 */
void Rotateimage()
{
	GtkWidget *window;
	GdkImlibImage * image;
	/* Grab the active window * /
	 window = GetActiveWindow ( ) ;
	 /* Check that the active window is valid before continuing */
	if (window != NULL)
	{
		/* Grab the active image */
		image = GetActiveImage();
		/* Rotate the image - second parameter is ignored at the moment*/
		gdk_imlib_rotate_image(image, 0);
		/* Set the new image into the window */
		SetImageintoWindow(window, image);
	}
}

/**
 * CloseActiveimage ( )
 *
 * Utility function to close down the last active window .
 */
void CloseActiveimage()
{
	/* Grab the last active window pointer */
	GtkWidget *window = GetActiveWindow();
	/* If the pointer is valid, destroy the window */
	if (window != NULL)
		gtk_widget_destroy(window);
}
/**
 * Showimage ( )
 *
 * The main entry function for the image window.

 * It takes the passed in filename and attempts to
 * load it up as an image
 **/
void Showlmage(gchar * filename)
{
	GdkImlibImage * image;
	GtkWidget *window;
	GtkWidget *messagebox;
	/* Attempt to load up 吐e specified image */
	image = gdk_imlib_load_image(filename);
	/* If the resulting image is NULL , then the load failed ....
	 * tell the user */
	if (image == NULL)
	{
		messagebox = gnome_message_box_new(
				"Sorry , you specified an invalid file",
				GNOME_MESSAGE_BOX_ERROR,
				GNOME_STOCK_BUTTON_OK, NULL);
		gnome_dialog_run_and_close(GNOME_DIALOG(messagebox));
		return;
	}
	/* Create a window in the usual way, with the filename as the title */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), filename);
	/* Setthe newly loaded image into the window */
	SetImageintoWindow(window, image);
	/* Connect up the wi ndow 's signal handlers */
	gtk_signal_connect(GTK_OBJECT (window ), "destroy",
			GTK_SIGNAL_FUNC (DestroyWindow ), image);
	gtk_signal_connect(GTK_OBJECT (window ), "focus_in_event",
			GTK_SIGNAL_FUNC (GotFocus ), image);
	/* Finally, show the window */
	gtk_widget_show(window);
}

