/* See LICENSE file for copyright and license details. */

#include <stdlib.h>
#include "widget.h"

CherryWidget *
cherry_widget_new(void)
{
	CherryWidget *widget = malloc(sizeof(*widget));
	widget->x = 0;
	widget->y = 0;
	widget->widgets = clist_create();
	widget->draw = NULL;
	widget->dimension = cherry_dimension_new();

	return widget;
}

CherryDimension *
cherry_widget_get_dimension(CherryWidget *comp) {
	return comp->dimension;
}

void
cherry_widget_add_component(CherryWidget *parent, CherryWidget *child)
{
	clist_add(&parent->widgets, child);
}
