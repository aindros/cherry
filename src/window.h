/* See LICENSE file for copyright and license details. */

#ifndef __CHERRY_WINDOW_H__
#define __CHERRY_WINDOW_H__

#include "dimension.h"

typedef struct {
	char            *title;
	CherryDimension *dimension;
	int x, y;
	int visible;

	/* Xlib stuff */
	Window window_handler;
} CherryWindow;

CherryWindow *cherry_window_new(void);
void          cherry_window_set_title(CherryWindow *, char *);
void          cherry_window_set_dimension(CherryWindow *, int, int);
void          cherry_window_set_position(CherryWindow *, int, int);
void          cherry_window_set_visible(CherryWindow *, int);

#endif /* __CHERRY_WINDOW_H__ */
