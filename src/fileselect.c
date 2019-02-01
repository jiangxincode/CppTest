/**
 * fileselect.c
 *
 * Simplifies use of the GtkFileSelection dialog
 */
#include <gnome.h>

/* Declare pointers to the dialog and the selected filename string */
GtkWidget* dialog;
gchar * selectedfile;

/**
 * CloseTheDialog ( )
 *
 * Callback triggered when dialog closes down .
 */
void CloseTheDialog(GtkWidget * widget, gpointer data) {
	gtk_main_quit();
}

/**
 * OKClicked ( )
 *
 * Callback triggered when the user clicks on the OK button in
 * the dialog . It duplicates the filename selected within the dialog and
 * stores a pointer to the duplicated string in ' selected file ' , ready to
 * be returned
 */
void OKClicked(GtkButton * button, gpointer data) {
	/* we need to duplicate the filename selected, since the widget is
	 * about to be destroyed, and can take the string with it */
	selectedfile = g_strdup(
			gtk_file_selection_get_filename(GTK_FILE_SELECTION(dialog)));
	gtk_widget_destroy(dialog);
}

/**
 * Cancel Clicked ( )
 *
 * Callback triggered when the user clicks on the Cancel button in the
 * dialog . Does nothing more than destroy the dialog .
 */
void CancelClicked(GtkButton * button, gpointer data) {
	gtk_widget_destroy(dialog);
}

/**
 * Choose File ()
 *
 * Pops open the GtkFileSelection dialog, and returns the name of
 * the file selected when the dialog closes down , assuming the user actually
 * chooses something . Otherwise , it j ust returns FALSE .
 */
gchar * ChooseFile() {

	/* Reset filename to NULL to prevent false returns */
	selectedfile = NULL;
	/* Create the dialog */
	dialog = gtk_file_selection_new("Choose an image to load");
	/** Connect up the signal handlers for the default buttons on the
	 *dialog **/
	gtk_signal_connect(GTK_OBJECT ( GTK_FILE_SELECTION ( dialog ) ->ok_button ),
			"clicked", GTK_SIGNAL_FUNC (OKClicked ), NULL);
	gtk_signal_connect(
			GTK_OBJECT ( GTK_FILE_SELECTION (dialog )-> cancel_button ),
			"clicked", GTK_SIGNAL_FUNC ( CancelClicked ), NULL);
	gtk_signal_connect(GTK_OBJECT (dialog ), "destroy",
			GTK_SIGNAL_FUNC (CloseTheDialog ), NULL);
	/* Show the dialog , then start up the gtk_main () loop again . The dialog
	 * quits this */
	gtk_widget_show(dialog);
	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
	gtk_main();
	return selectedfile;
}
