/**
 * ImageWindow .h
 *
 * Header to declare functions to work on 七he image window
 */
#ifndef __IMAGEVIEWER_IMAGEWINDOW_H
#define __IMAGEVIEWER_IMAGEWINDOW_H
void Showimage(gchar * filename);
void RotateImage();
void CloseActiveimage();
void Flipimage(gboolean horizontal);
#endif
