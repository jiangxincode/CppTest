/**
 * mainwindow.c
 *
 * Responsible for building the main window of the application
 * and handling its signals, and those of its user interface.
 **/

#include <gtk/gtk.h>
#include "mainwindow.h"
#include "mainwindowhandlers.h"
#include "imageviewerutility.h"
#include "fileselect.h"
#include "ImageWindow.h"

/* Declare the window widget itself */
GtkWidget *mainwindow;

GtkWidget *createMenuBar()
{
    GtkWidget *menu_bar = gtk_menu_bar_new();

    GtkWidget *file_menu = gtk_menu_new();
    GtkWidget *file_menu_item = gtk_menu_item_new_with_mnemonic("_File");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_menu_item), file_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), file_menu_item);

    GtkWidget *open = gtk_menu_item_new_with_label("Open");
    g_signal_connect(G_OBJECT(open), "activate", G_CALLBACK(FileOpenHandler), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), open);

    GtkWidget *close = gtk_menu_item_new_with_label("Close");
    g_signal_connect(G_OBJECT(close), "activate", G_CALLBACK(FileCloseHandler), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), close);

    GtkWidget *exit = gtk_menu_item_new_with_label("Exit");
    g_signal_connect(G_OBJECT(exit), "activate", G_CALLBACK(FileExitItemHandler), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), exit);

    GtkWidget *help_menu = gtk_menu_new();
    GtkWidget *help_menu_item = gtk_menu_item_new_with_mnemonic("_Help");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(help_menu_item), help_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), help_menu_item);

    GtkWidget *about = gtk_menu_item_new_with_label("About");
    g_signal_connect(G_OBJECT(about), "activate", G_CALLBACK(HelpAboutHandler), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), about);

    return menu_bar;
}

GtkWidget *createToolBar()
{
    GtkWidget *tool_bar = gtk_toolbar_new();

    GtkToolItem *openButton = gtk_tool_button_new(NULL, "Open");
    gtk_tool_button_set_icon_name(GTK_TOOL_BUTTON(openButton), "document-open");
    gtk_tool_item_set_tooltip_text(openButton, "Load up a graphic");
    g_signal_connect(G_OBJECT(openButton), "clicked", G_CALLBACK(FileOpenHandler), NULL);
    gtk_toolbar_insert(GTK_TOOLBAR(tool_bar), openButton, -1);

    GtkToolItem *closeButton = gtk_tool_button_new(NULL, "Close");
    gtk_tool_button_set_icon_name(GTK_TOOL_BUTTON(closeButton), "document-close");
    gtk_tool_item_set_tooltip_text(closeButton, "Close the current graphic");
    g_signal_connect(G_OBJECT(closeButton), "clicked", G_CALLBACK(FileCloseHandler), NULL);
    gtk_toolbar_insert(GTK_TOOLBAR(tool_bar), closeButton, -1);

    GtkToolItem *rotate1Button = gtk_tool_button_new(NULL, "Rotate");
    gtk_tool_button_set_icon_name(GTK_TOOL_BUTTON(rotate1Button), "edit-redo");
    gtk_tool_item_set_tooltip_text(rotate1Button, "Rotate image clockwise");
    g_signal_connect(G_OBJECT(rotate1Button), "clicked", G_CALLBACK(RotateHandler), GINT_TO_POINTER(0));
    gtk_toolbar_insert(GTK_TOOLBAR(tool_bar), rotate1Button, -1);

    GtkToolItem *rotate2Button = gtk_tool_button_new(NULL, "Rotate");
    gtk_tool_button_set_icon_name(GTK_TOOL_BUTTON(rotate2Button), "edit-undo");
    gtk_tool_item_set_tooltip_text(rotate2Button, "Rotate image counter clockwise");
    g_signal_connect(G_OBJECT(rotate2Button), "clicked", G_CALLBACK(RotateHandler), GINT_TO_POINTER(1));
    gtk_toolbar_insert(GTK_TOOLBAR(tool_bar), rotate2Button, -1);

    GtkToolItem *flip1Button = gtk_tool_button_new(NULL, "Flip");
    gtk_tool_button_set_icon_name(GTK_TOOL_BUTTON(flip1Button), "go-previous");
    gtk_tool_item_set_tooltip_text(flip1Button, "Flip image horizontally");
    g_signal_connect(G_OBJECT(flip1Button), "clicked", G_CALLBACK(FlipHandler), GINT_TO_POINTER(0));
    gtk_toolbar_insert(GTK_TOOLBAR(tool_bar), flip1Button, -1);

    GtkToolItem *flip2Button = gtk_tool_button_new(NULL, "Flip");
    gtk_tool_button_set_icon_name(GTK_TOOL_BUTTON(flip2Button), "go-down");
    gtk_tool_item_set_tooltip_text(flip2Button, "Flip image vertically");
    g_signal_connect(G_OBJECT(flip2Button), "clicked", G_CALLBACK(FlipHandler), GINT_TO_POINTER(1));
    gtk_toolbar_insert(GTK_TOOLBAR(tool_bar), flip2Button, -1);

    GtkToolItem *exitButton = gtk_tool_button_new(NULL, "Exit");
    gtk_tool_button_set_icon_name(GTK_TOOL_BUTTON(exitButton), "application-exit");
    gtk_tool_item_set_tooltip_text(exitButton, "Quit the app");
    g_signal_connect(G_OBJECT(exitButton), "clicked", G_CALLBACK(FileExitItemHandler), NULL);
    gtk_toolbar_insert(GTK_TOOLBAR(tool_bar), exitButton, -1);

    return tool_bar;
}

/**=== MAINWINDOW USER INTERFACE HANDLERS ====**/
/**
 * FileExititemHandler ( )
 *
 * Callback triggered when user hits Exit on the File menu - shuts the
 * application down after first checking with the user that that is what
 * they want to do
 **/
void FileExitItemHandler(GtkMenuItem *item, gpointer data)
{
    if (CheckUserExit())
        gtk_widget_destroy(mainwindow);
}

/** FileCloseHandler ( )
 *
 * CallbackTriggered when user hits Close on the File menu - shuts the
 * last selected window down .
 **/
void FileCloseHandler(GtkMenuItem *item, gpointer data)
{
    CloseActiveImage();
}

/**
 * HelpAboutHandler ( )
 *
 * Callback triggered when user hits About on the Help menu . Displays the
 * about box .
 **/
void HelpAboutHandler(GtkMenuItem *item, gpointer data)
{
    GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
    GtkWidget *aboutdialog = gtk_message_dialog_new(NULL, flags, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", "ImageViewer 1.0 (C) 2019,JiangXin(Aloys)");
    gtk_dialog_run(GTK_DIALOG(aboutdialog));
    gtk_widget_destroy(aboutdialog);
}

/**
 * FileOpenHandler ( )
 *
 * Callback triggered when user hits open on the File menu - get s the
 * user to choose a file, and then loads up the image viewer form
 * with the image loaded inside .
 **/
void FileOpenHandler(GtkMenuItem *item, gpointer data)
{
    gchar *filename = ChooseFile();
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
void RotateHandler(GtkButton *button, gpointer data)
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
void FlipHandler(GtkButton *button, gpointer data)
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
gboolean QueryShutdown(GtkWidget *widget, GdkEvent *event, gpointer data)
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
void CloseTheApp(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

/** ====== MAINWINDOW UTILITY FUNCT工ONS ======**/
/**
 * BuildMainwindow
 *
 * Builds up the main window and it ' s user interface
 **/
void BuildMainWindow(gchar *appname, gchar *appversion)
{
    mainwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(mainwindow), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(mainwindow), 600, 200);
    gtk_window_set_title(GTK_WINDOW(mainwindow), "Image Viewer");

    g_signal_connect(G_OBJECT(mainwindow), "delete_event", G_CALLBACK(QueryShutdown), NULL);
    g_signal_connect(G_OBJECT(mainwindow), "destroy", G_CALLBACK(CloseTheApp), NULL);

    GtkWidget *menu_bar = createMenuBar();
    GtkWidget *tool_bar = createToolBar();

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(vbox), menu_bar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), tool_bar, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(mainwindow), vbox);

    gtk_widget_show_all(mainwindow);

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
    GtkWidget *dialog = gtk_dialog_new_with_buttons(
        "Are you sure you want to quit？",
        NULL, GTK_DIALOG_MODAL, "gtk-ok", GTK_RESPONSE_OK,
        "gtk-cancel", GTK_RESPONSE_CANCEL, NULL);
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    /* If the user clicked on the first button ( the YES button), return TRUE */
    if (result == GTK_RESPONSE_OK)
    {
        return TRUE;
    }
    return FALSE;
}
