/**
 * mainwindow.c
 *
 * Responsible for building the main window of the application
 * and handling its signals, and those of its user interface.
 **/

#include <gnome.h>
#include "mainwindow.h"
#include "mainwindowhandlers.h"
#include "imageviewerutility.h"
#include "fileselect.h"
#include "ImageWindow.h"

/* Declare the window widget itself */
GtkWidget *mainwindow;

/** ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ MENUS ===================== **/
static GnomeUIInfo file_menu[] =
{
GNOMEUIINFO_MENU_OPEN_ITEM ( FileOpenHandler, NULL ),
GNOMEUIINFO_MENU_CLOSE_ITEM ( FileCloseHandler, NULL ),
GNOMEUIINFO_SEPARATOR,
GNOMEUIINFO_MENU_EXIT_ITEM ( FileExitItemHandler, NULL ),
GNOMEUIINFO_END };

static GnomeUIInfo help_menu[] =
{
GNOMEUIINFO_MENU_ABOUT_ITEM ( HelpAboutHandler, NULL ),
GNOMEUIINFO_END };

static GnomeUIInfo menu_bar[] =
{
GNOMEUIINFO_SUBTREE ( "_File ", file_menu ),
GNOMEUIINFO_SUBTREE ( "_Help ", help_menu ),
GNOMEUIINFO_END };

/**================ TOOLBARS =====================**/
static GnomeUIInfo toolbar_icons[] =
{
{ GNOME_APP_UI_ITEM, "Open", "Load up a graphic ", FileOpenHandler, NULL, NULL,
		GNOME_APP_PIXMAP_STOCK, GNOME_STOCK_PIXMAP_OPEN },
{ GNOME_APP_UI_ITEM, "Close ", "Close the current graphic ", FileCloseHandler,
NULL, NULL, GNOME_APP_PIXMAP_STOCK, GNOME_STOCK_PIXMAP_CLOSE },
GNOMEUIINFO_SEPARATOR,
{ GNOME_APP_UI_ITEM, "Rotate ", "Rotate image clockwise", RotateHandler, GINT_TO_POINTER(0), NULL,
		GNOME_APP_PIXMAP_STOCK,
		GNOME_STOCK_PIXMAP_REDO },
{ GNOME_APP_UI_ITEM, "Rotate ", "Rotate image counter clockwise", RotateHandler, GINT_TO_POINTER(1), NULL,
		GNOME_APP_PIXMAP_STOCK,
		GNOME_STOCK_PIXMAP_UNDO },
{ GNOME_APP_UI_ITEM, "Flip", "Flip image horizontally", FlipHandler,
		GINT_TO_POINTER(0), NULL, GNOME_APP_PIXMAP_STOCK,
		GNOME_STOCK_PIXMAP_BACK },
{ GNOME_APP_UI_ITEM, "Flip", "Flip image vertically", FlipHandler,
		GINT_TO_POINTER(1), NULL, GNOME_APP_PIXMAP_STOCK,
		GNOME_STOCK_PIXMAP_DOWN },
GNOMEUIINFO_SEPARATOR,
{ GNOME_APP_UI_ITEM, "Exit", "Quit the app", FileExitItemHandler, NULL, NULL,
		GNOME_APP_PIXMAP_STOCK,
		GNOME_STOCK_PIXMAP_EXIT },
GNOMEUIINFO_END };

/**=== MAINWINDOW USER INTERFACE HANDLERS ====**/
/**
 * FileExititemHandler ( )
 *
 * Callback triggered when user hits Exit on the File menu - shuts the
 * application down after first checking with the user that that is what
 * they want to do
 **/
void FileExitItemHandler(GtkMenuItem * item, gpointer data)
{
	if (CheckUserExit())
		gtk_widget_destroy(mainwindow);
}

/** FileCloseHandler ( )
 *
 * CallbackTriggered when user hits Close on the File menu - shuts the
 * last selected window down .
 **/
void FileCloseHandler(GtkMenuItem * item, gpointer data)
{
	CloseActiveImage();
}

/**
 * HelpAboutHandler ( )
 *
 * Callback triggered when user hits About on the Help menu . Displays the
 * about box .
 **/
void HelpAboutHandler(GtkMenuItem * item, gpointer data)
{
	GtkWidget *aboutdialog;
	const gchar *authors[] =
	{ "Aloys", NULL };
	const gchar *documenters[] =
	{ "Welcome to ImageViewer - an easy image viewer build on GTK+" };
	aboutdialog = gnome_about_new("ImageViewer", " 1.0 ",
			"(C) 2019,JiangXin(Aloys)", "",
			(const gchar * *) authors, (const gchar * *) documenters,
			NULL, NULL);
	gtk_widget_show(aboutdialog);
}

/**
 * FileOpenHandler ( )
 *
 * Callback triggered when user hits open on the File menu - get s the
 * user to choose a file, and then loads up the image viewer form
 * with the image loaded inside .
 **/
void FileOpenHandler(GtkMenuItem * item, gpointer data)
{
	gchar* filename = ChooseFile();
	if (filename != NULL)
	{
		ShowImage(filename);
		g_free(filename);
	}
}

/**
 * RotateHandler ( )
 *
 * Callback triggered when user hits the Rotate button on the toolbar .
 * The code calls the image window ' s rotate code to rotate the image
 **/
void RotateHandler(GtkButton * button, gpointer data)
{
	if (GPOINTER_TO_INT(data) == 0)
	{
		RotateImage(TRUE);
	}
	else
	{
		RotateImage(FALSE);
	}
}

/**
 * FlipHandler ( )
 *
 * Callback triggered when the user hits either of the flip buttons on
 * the toolbar. The data parameter i s converted to an integer, o for
 * horizontal flip, 1 for a vertical flip, before the appropriate code
 * is called.
 **/
void FlipHandler(GtkButton * button, gpointer data)
{
	if (GPOINTER_TO_INT(data) == 0)
	{
		FlipImage(TRUE);
	}
	else
	{
		FlipImage(FALSE);
	}
}

/**=============================== MAINWINDOW SIGNAL HANDLERS ========= **/
/**
 * QueryShutdown
 *
 * When the user tries to close down the main application window, this
 * callback checks whether or notthe user is sure about what they want to
 * do . Assuming they are, the signal is allowed to be handler by GTK which
 * will destroy the window in the usual manner
 **/
gboolean QueryShutdown(GtkWidget * widget, GdkEvent * event, gpointer data)
{
	return (!CheckUserExit());
}

/**
 * CloseTheApp ( }
 *
 * Stops the application from running when the main window is destroyed .
 * This can only happen after the user has been queried as to whether or
 * not they are sure they want to quit the app
 **/
void CloseTheApp(GtkWidget * widget, gpointer data)
{
	gtk_main_quit();
}

/** ====== MAINWINDOW UTILITY FUNCT工ONS ======**/
/**
 * BuildMainwindow
 *
 * Builds up the main window and it ' s user interface
 **/
void BuildMainWindow(gchar * appname, gchar * appversion)
{

	/* Create the GnomeApp widget and set it up at the top of the screen */
	mainwindow = gnome_app_new(appname, "Image Viewer");
	gtk_window_set_default_size(GTK_WINDOW(mainwindow),
			gdk_screen_width() - 100, 80);
	gtk_widget_set_uposition(mainwindow, 0, 0);
	/* Next, connect up the main window signal handlers */
	gtk_signal_connect(GTK_OBJECT (mainwindow), "delete_event",
			GTK_SIGNAL_FUNC (QueryShutdown), NULL);
	gtk_signal_connect(GTK_OBJECT (mainwindow), "destroy",
			GTK_SIGNAL_FUNC (CloseTheApp ), NULL);
	/** Build up the menu bar **/
	gnome_app_create_menus(GNOME_APP(mainwindow), menu_bar);
	/** Build up the tool bar **/
	gnome_app_create_toolbar(GNOME_APP(mainwindow), toolbar_icons);
	/* Finally, show the window */
	gtk_widget_show(mainwindow);
	/* Clear the active window pointer, since the app just got going */
	ClearActiveWindow();
}
/**
 * CheckUserExit（）
 *
 * Puts up a message box asking the user if they really want to quit .
 * Returns TRUE if they do .
 **/
gboolean CheckUserExit()
{
	GtkWidget* msgbox;
	msgbox = gnome_message_box_new("Are you sure you want to quit？",
	GNOME_MESSAGE_BOX_QUESTION, GNOME_STOCK_BUTTON_YES,
	GNOME_STOCK_BUTTON_NO, NULL);
	/* If the user clicked on the first button ( the YES button), return
	 * TRUE */
	return (gnome_dialog_run_and_close(GNOME_DIALOG(msgbox)) == 0);
}
