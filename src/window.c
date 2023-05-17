/* See LICENSE file for copyright and license details. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "application.h"
#include "window.h"
#include "color.h"

CherryWindow *
cherry_window_new(void)
{
	CherryWindow *w = malloc(sizeof(*w));
	w->title = NULL;
	w->dimension = cherry_dimension_new();
	w->x = 0;
	w->y = 0;
	w->listener = NULL;

	CherryApplication *app = cherry_application_get_running_app();

	int offset = 10;
	int border_width = 5;
	XSizeHints hints;
	hints.x      = w->x + offset;
	hints.y      = w->y + offset;
	hints.width  = w->dimension->width  + offset;
	hints.height = w->dimension->height + offset;
	hints.flags  = PPosition|PSize;

	XSetWindowAttributes attributes;
	attributes.background_pixel = XWhitePixel(app->display, app->screen);

	w->window_handler = XCreateWindow(app->display,
	                                  XRootWindow(app->display, app->screen),
	                                  hints.x,     hints.y,
	                                  hints.width, hints.height,
	                                  border_width,
	                                  app->depth,
	                                  InputOutput,
	                                  app->visual,
	                                  CWBackPixel,
	                                  &attributes);
	char window_name[] = "";
	char icon_name[]   = "";
	XSetStandardProperties(app->display,
	                       w->window_handler,
	                       window_name,
	                       icon_name,
	                       None, NULL, 0,
	                       &hints);

	clist_add(&(app->windows), w, sizeof(*w));

	w->gc = XCreateGC(app->display, w->window_handler, 0, 0);
	XSetBackground(app->display, w->gc, WhitePixel(app->display, app->screen));
	XSetForeground(app->display, w->gc, BlackPixel(app->display, app->screen));


	return w;
}

char *
cherry_window_get_title(CherryWindow *w)
{
	char *wnd_name;
	CherryApplication *app = cherry_application_get_running_app();
	XFetchName(app->display, w->window_handler, &wnd_name);

	return wnd_name;
}

void
cherry_window_set_title(CherryWindow *w, char *title)
{
	w->title = strdup(title);

	CherryApplication *app = cherry_application_get_running_app();
	XStoreName(app->display, w->window_handler, w->title);
}

void
cherry_window_set_dimension(CherryWindow *w, int width, int height)
{
	w->dimension->width  = width;
	w->dimension->height = height;

	CherryApplication *app = cherry_application_get_running_app();
	XMoveResizeWindow(app->display, w->window_handler,
	                  w->x, w->y,
	                  w->dimension->width, w->dimension->height);
}

void
cherry_window_set_position(CherryWindow *w, int x, int y)
{
	w->x = x;
	w->y = y;

	CherryApplication *app = cherry_application_get_running_app();
	XMoveResizeWindow(app->display, w->window_handler,
	                  w->x, w->y,
	                  w->dimension->width, w->dimension->height);
}

void
cherry_window_set_visible(CherryWindow *w, int visible)
{
	CherryApplication *app = cherry_application_get_running_app();

	if (visible) {
		XMapRaised(app->display, w->window_handler);
	}
}

void
cherry_window_set_listener(CherryWindow *w,
                           int (*listener)(struct CherryWindow *, int))
{
	w->listener = listener;
}
