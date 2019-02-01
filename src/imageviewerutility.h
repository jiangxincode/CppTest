/**
 * imageviewerutility.h
 *
 * Function prototypes for the imageviewer utility functions
 **/
#ifndef _IMAGEVIEWER_IMAGEVIEWERUTILITY_H
#define _IMAGEVIEWER_IMAGEVIEWERUTILITY_H
void SetActiveWindow(GtkWidget* window, GdkImlibImage * image);
void ClearActiveWindow();
GtkWidget *GetActiveWindow();
GdkImlibImage *GetActiveimage();
#endif
