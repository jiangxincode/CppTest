/**
 * mainwindowhandlers.h
 *
 * Prototypes for the signal handlers
 **/
#ifndef __IMAGEVIEWER_MAINWINDOWHANDLERS_H
#define __IMAGEVIEWER_MAINWINDOWHANDLERS_H
gboolean CheckUserExit();
void FileOpenHandler(GtkMenuItem * item, gpointer data);
void FileCloseHandler(GtkMenuItem * item, gpointer data);
void FileExitItemHandler(GtkMenuItem * item, gpointer data);
void RotateHandler(GtkButton * button, gpointer data);
void FlipHandler(GtkButton * button, gpointer data);
void HelpAboutHandler(GtkMenuItem * item, gpointer data);
#endif
