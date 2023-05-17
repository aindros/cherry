/* See LICENSE file for copyright and license details. */

#ifndef __CHERRY_WINDOW_H__
#define __CHERRY_WINDOW_H__

#include "dimension.h"

typedef struct CherryWindow {
	char            *title;
	CherryDimension *dimension;
	int x, y;
	int visible;

	/* Xlib stuff */
	Window window_handler;
	GC     gc;

	int (*listener)(struct CherryWindow *, int);
} CherryWindow;

CherryWindow *cherry_window_new(void);
void          cherry_window_dispose_on_exit(CherryWindow *);
char         *cherry_window_get_title(CherryWindow *);
void          cherry_window_set_title(CherryWindow *, char *);
void          cherry_window_set_dimension(CherryWindow *, int, int);
void          cherry_window_set_position(CherryWindow *, int, int);
void          cherry_window_set_visible(CherryWindow *, int);
void          cherry_window_set_listener(CherryWindow *, int (*listener)(struct CherryWindow *, int));

#endif /* __CHERRY_WINDOW_H__ */
