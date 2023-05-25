/* See LICENSE file for copyright and license details. */

#ifndef __CHERRY_WIDGET_H__
#define __CHERRY_WIDGET_H__

#include <stdlib.h> /* used bu utils.h until I'll fix that */
#include <utils.h>
#include "dimension.h"

/* The parent of all widgets */
typedef struct CherryWidget {
	int x, y;
	CherryDimension *dimension;
	int visible;
	list_t components;

	/* Xlib stuff */
//	XSizeHints hints;
//	GC         gc;
//	Window     wnd;

	void (*draw)(struct CherryWidget *);
} CherryWidget;

CherryWidget    *cherry_widget_new(void);
CherryDimension *cherry_widget_get_dimension(CherryWidget *);

#endif /* __CHERRY_WIDGET_H__ */
