/**
 * fileselect.c
 *
 * Simplifies use of the GtkFileSelection dialog
 */
#include <gtk/gtk.h>

gchar *selectedfile;

/**
 * CloseTheDialog()
 *
 * Callback triggered when dialog closes down.
 */
void CloseTheDialog(GtkWidget * widget, gpointer data)
{
	gtk_main_quit();
}

/**
 * OKClicked()
 *
 * Callback triggered when the user clicks on the OK button in
 * the dialog. It duplicates the filename selected within the dialog and
 * stores a pointer to the duplicated string in 'selectedfile', ready to
 * be returned
 */
void OKClicked(GtkWidget * dialog, gpointer data)
{
	/* we need to duplicate the filename selected, since the widget is
	 * about to be destroyed, and can take the string with it */
    selectedfile = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
	gtk_widget_destroy(dialog);
}

/**
 * CancelClicked()
 *
 * Callback triggered when the user clicks on the Cancel button in the
 * dialog. Does nothing more than destroy the dialog.
 */
void CancelClicked(GtkWidget * dialog, gpointer data)
{
	gtk_widget_destroy(dialog);
}

/**
 * ChooseFile()
 *
 * Pops open the GtkFileSelection dialog, and returns the name of
 * the file selected when the dialog closes down, assuming the user actually
 * chooses something. Otherwise, it just returns FALSE.
 */
gchar* ChooseFile()
{
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    dialog = gtk_file_chooser_dialog_new("Choose an image to load",
                                         NULL,
                                         action,
                                         "Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         "Open",
                                         GTK_RESPONSE_ACCEPT,
                                         NULL);

    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
        OKClicked(dialog, NULL);
    } else if (res == GTK_RESPONSE_CANCEL) {
        CancelClicked(dialog, NULL);
    }
	return selectedfile;
}
