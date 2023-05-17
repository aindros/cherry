/* See LICENSE file for copyright and license details. */

#ifndef __CHERRY_DIMENSION_H__
#define __CHERRY_DIMENSION_H__

typedef struct {
	int width;
	int height;
} CherryDimension;

CherryDimension *cherry_dimension_new(void);
void             cherry_dimension_set_width(CherryDimension *, int);
void             cherry_dimension_set_height(CherryDimension *, int);

#endif /* __CHERRY_DIMENSION_H__ */
