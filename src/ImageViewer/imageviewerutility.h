#ifndef _IMAGEVIEWER_IMAGEVIEWERUTILITY_H
#define _IMAGEVIEWER_IMAGEVIEWERUTILITY_H
void set_active_window(GtkWidget *window, GdkPixbuf *image);
void clear_active_window();
GtkWidget *get_active_window();
GdkPixbuf *get_active_image();
#endif
