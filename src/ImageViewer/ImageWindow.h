/**
 * ImageWindow .h
 *
 * Header to declare functions to work on 七he image window
 */
#ifndef __IMAGEVIEWER_IMAGEWINDOW_H
#define __IMAGEVIEWER_IMAGEWINDOW_H
void ShowImage(gchar * filename);
void RotateImage();
void CloseActiveImage();
void FlipImage(gboolean horizontal);
#endif
