/* See LICENSE file for copyright and license details. */

#include <stdlib.h>
#include "widget.h"

CherryWidget *
cherry_widget_new(void)
{
	CherryWidget *comp = malloc(sizeof(*comp));
	comp->x = 0;
	comp->y = 0;
	comp->components = clist_create();
	comp->draw = NULL;
	comp->dimension = cherry_dimension_new();

	return comp;
}

CherryDimension *
cherry_widget_get_dimension(CherryWidget *comp) {
	return comp->dimension;
}

void
cherry_widget_add_component(CherryWidget *parent, CherryWidget *child)
{
	clist_add(&parent->components, child);
}
