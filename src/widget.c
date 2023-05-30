/* See LICENSE file for copyright and license details. */

#include <stdio.h>
#include <stdlib.h>
#include "widget.h"

static void
cherry_widget_draw(CherryWidget *widget)
{
	if (cherry_widget_is_visible(*widget) == 0) return;
	widget->drawn = 1;
}

CherryWidget
cherry_widget_new(void)
{
	CherryWidget widget;
	widget.x = 0;
	widget.y = 0;
	widget.widgets = clist_create();
	widget.width = 0;
	widget.height = 0;
	widget.visible = 0;
	widget.drawn = 0;
	widget.draw = cherry_widget_draw;

	return widget;
}

void
cherry_widget_get_dimension(CherryWidget *widget, int *width, int *height) {
	*width = widget->width;
	*height = widget->height;
}

void
cherry_widget_set_dimension(CherryWidget *widget, int width, int height)
{
	widget->width = width;
	widget->height = height;
}

void
cherry_widget_add_component(CherryWidget *parent, CherryWidget *child)
{
	clist_add(&parent->widgets, child);
	if (cherry_widget_is_visible(parent) && parent->drawn) {
		child->draw(child);
	}
}

int
cherry_widget_is_visible(CherryWidget *widget)
{
	return widget->visible;
}

void
cherry_widget_set_visible(CherryWidget *widget, int visible)
{
	widget->visible = visible;

	if (visible && widget->drawn == 0)
		widget->draw(widget);
}

void
cherry_widget_get_position(CherryWidget *widget, int *x, int *y)
{
	*x = widget->x;
	*y = widget->y;
}

void
cherry_widget_set_position(CherryWidget *widget, int x, int y)
{
	widget->x = x;
	widget->y = y;
}
