/* See LICENSE file for copyright and license details. */

#include <stdio.h>
#include <stdlib.h>
#include "widget.h"

static void
cherry_widget_draw(CherryWidget *widget)
{
	widget->drawn = 1;
}

CherryWidget *
cherry_widget_new(void)
{
	CherryWidget *widget = malloc(sizeof(*widget));
	widget->x = 0;
	widget->y = 0;
	widget->widgets = clist_create();
	widget->width = 0;
	widget->height = 0;
	widget->visible = 0;
	widget->draw = cherry_widget_draw;

	return widget;
}

void
cherry_widget_get_dimension(CherryWidget *widget, int *width, int *height) {
	*width = widget->width;
	*height = widget->height;
}

void
cherry_widget_add_component(CherryWidget *parent, CherryWidget *child)
{
	clist_add(&parent->widgets, child);
}
