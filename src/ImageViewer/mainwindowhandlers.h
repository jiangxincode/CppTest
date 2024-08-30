#ifndef __IMAGEVIEWER_MAINWINDOWHANDLERS_H
#define __IMAGEVIEWER_MAINWINDOWHANDLERS_H
gboolean check_user_exit();
void file_open_handler(GtkMenuItem *item, gpointer data);
void file_close_handler(GtkMenuItem *item, gpointer data);
void file_exit_item_handler(GtkMenuItem *item, gpointer data);
void rotate_handler(GtkButton *button, gpointer data);
void flip_handler(GtkButton *button, gpointer data);
void help_about_handler(GtkMenuItem *item, gpointer data);
#endif
