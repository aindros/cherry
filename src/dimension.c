/* See LICENSE file for copyright and license details. */

#include <stdlib.h>
#include "dimension.h"

CherryDimension *
cherry_dimension_new(void)
{
	CherryDimension *dim = malloc(sizeof(*dim));
	if (dim == NULL) return NULL;

	cherry_dimension_set_width(dim, 0);
	cherry_dimension_set_height(dim, 0);

	return dim;
}

void
cherry_dimension_set_width(CherryDimension *d, int width)
{
	d->width = width;
}

void
cherry_dimension_set_height(CherryDimension *d, int height)
{
	d->height = height;
}
