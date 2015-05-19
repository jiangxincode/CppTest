#include<gtk/gtk.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
/*
Initial the numbers!
*/
gdouble Income = 0;
gdouble PackMon = 0;
gdouble TaxPayment = 0;
gdouble IncoAfterTax = 0;

/*
Declare the input!
*/
GtkWidget *entry1;
GtkWidget *entry2;
GtkWidget *entry3;
GtkWidget *entry4;

/*
Declare the parameters!
*/
GtkWidget *window;
GtkWidget *table;
GtkWidget *button1;
GtkWidget *button2;
GtkWidget *label1;
GtkWidget *label2;
GtkWidget *label3;
GtkWidget *label4;

/*
Calculate the tax payment and return the result!!
*/
gdouble calculating(gdouble temp)
{
	if( temp <= 3500)
		return 0;
	else if(temp <= 5000)
		return (temp - 3500) * 0.03;
	else if(temp <= 8000)
		return (temp - 3500) * 0.1;
	else if(temp <= 12500)
		return (temp -3500) * 0.2;
	else if(temp <= 25000)
		return (temp - 3500) * 0.25;
	else if(temp <= 40000)
		return (temp -3500) *0.3;
	else
		return (temp - 3500) *0.4;
}
void on_submitting_clicked(GtkButton *button,gpointer data)
{
	/*
	Declare three variable to get the context from the two entry controls!
	*/
	const char *strincome = gtk_entry_get_text(GTK_ENTRY(entry1));
	const char *strpackmon = gtk_entry_get_text(GTK_ENTRY(entry2));

	/*
	Converse the two char variable into gdouble number!
	*/
	Income = g_ascii_strtod(gtk_entry_get_text(GTK_ENTRY(entry1)),NULL);
    PackMon = g_ascii_strtod(gtk_entry_get_text(GTK_ENTRY(entry2)),NULL);
	TaxPayment = calculating(Income - PackMon);       //Use the function to get the taxpayment!

	IncoAfterTax = Income - PackMon - TaxPayment;

	gchar out[8];   //Declare this variable to get the conversed number variable of TaxPayment and IncoAfterTax!
	gchar out2[8];
	/*
	Converse the gdouble number into text to show!
	*/
    gchar *result1 = g_ascii_dtostr(out,8,IncoAfterTax);
	gchar *result2 = g_ascii_dtostr(out2,8,TaxPayment);

	gtk_entry_set_text(GTK_ENTRY(entry3),result2);
	gtk_entry_set_text(GTK_ENTRY(entry4),result1);   //Assign the two empty entry control as the conversed value of IncoAfterTax and TaxPayment!
}

/*
Clear all the context and number which used to calculate
by assigning the entry controls  as null and the number as 0!
*/
void on_another_clicked(GtkButton *button,gpointer data)
{
	gtk_entry_set_text(GTK_ENTRY(entry1),"");
	gtk_entry_set_text(GTK_ENTRY(entry2),"");
	gtk_entry_set_text(GTK_ENTRY(entry3),"");
	gtk_entry_set_text(GTK_ENTRY(entry4),"");
	Income = 0;
	PackMon = 0;
	IncoAfterTax = 0;
	TaxPayment = 0;
}


int main0001(int argc, char *argv[])
{
	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

	gtk_window_set_title(GTK_WINDOW(window), "A Small TaxPayment Calculator!");

	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	table = gtk_table_new(5, 2, FALSE);

	gtk_container_add(GTK_CONTAINER(window), table);

	label1 = gtk_label_new("Income:");
	label2 = gtk_label_new("CompreInsuPkg:");
	label3 = gtk_label_new("TaxPayment:");
	label4 = gtk_label_new("IncoAfterTax:");

	button1 = gtk_button_new_with_label("Submitting");
	button2 = gtk_button_new_with_label("Another");

	/*Put the controls to its position!*/
	gtk_table_attach(GTK_TABLE(table), label1, 0, 1, 0, 1,GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

	gtk_table_attach(GTK_TABLE(table), label2, 0, 1, 1, 2,GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

	gtk_table_attach(GTK_TABLE(table), label3, 0, 1, 2, 3,GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

	gtk_table_attach(GTK_TABLE(table), label4, 0, 1, 3, 4,GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

	gtk_table_attach(GTK_TABLE(table), button1, 0, 1, 4, 5,GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

	gtk_table_attach(GTK_TABLE(table), button2, 0, 2, 4, 6,GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

	entry2 = gtk_entry_new_with_max_length(6);

	entry1 = gtk_entry_new_with_max_length(7);

	entry3 = gtk_entry_new_with_max_length(5);

	entry4 = gtk_entry_new_with_max_length(8);

	/*Like the follow!*/
	gtk_table_attach(GTK_TABLE(table), entry1, 1, 2, 0, 1,GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

	gtk_table_attach(GTK_TABLE(table), entry2, 1, 2, 1, 2,GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

	gtk_table_attach(GTK_TABLE(table), entry3, 1, 2, 2, 3,GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

	gtk_table_attach(GTK_TABLE(table), entry4, 1, 2, 3, 4,GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

	gtk_widget_show(table);

	gtk_widget_show(label1);

	gtk_widget_show(label2);

	gtk_widget_show(label3);

	gtk_widget_show(label4);

	gtk_widget_show(button1);

	gtk_widget_show(button2);

	gtk_widget_show(entry1);

	gtk_widget_show(entry2);

	gtk_widget_show(entry3);

	gtk_widget_show(entry4);

	/*Get the clicked event to do the special function!*/
	g_signal_connect(G_OBJECT(button1),"clicked",G_CALLBACK(on_submitting_clicked),NULL);

	g_signal_connect(G_OBJECT(button2),"clicked",G_CALLBACK(on_another_clicked),NULL);
	gtk_widget_show(window);

	g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit), NULL);

	gtk_main();

	return 0;
}

