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
	w->x = 0;
	w->y = 0;
	w->listener = NULL;

	CherryApplication *app = cherry_application_get_running_app();

	int offset = 10;
	int border_width = 5;
	XSizeHints hints;
	hints.x      = w->x + offset;
	hints.y      = w->y + offset;
	cherry_window_get_position(window, &hints.x, &hints.y);
	cherry_window_get_dimension(window, &hints.width, &hints.height);
	hints.flags  = PPosition|PSize;

	XSetWindowAttributes attributes;
/*	attributes.background_pixel = XWhitePixel(app->display, app->screen); */
	attributes.background_pixel = RGB(100, 10, 10);

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

	/* window manager properties (yes, use of StdProp is obsolete) */
	XSetStandardProperties(app->display,
	                       w->window_handler,
	                       window_name,
	                       icon_name,
	                       None, NULL, 0,
	                       &hints);

	/* allow receiving mouse events */
	XSelectInput(app->display,
	             w->window_handler,
	             ButtonPressMask | KeyPressMask | ExposureMask);

	Atom wmDelete = XInternAtom(app->display, "WM_DELETE_WINDOW", True);
	XSetWMProtocols(app->display, w->window_handler, &wmDelete, 1);

	Atom wmDispose = XInternAtom(app->display, "CHERRY_DISPOSE_ON_EXIT", True);
	XSetWMProtocols(app->display, w->window_handler, &wmDelete, 1);

	w->gc = XCreateGC(app->display, w->window_handler, 0, 0);
	XSetBackground(app->display, w->gc, WhitePixel(app->display, app->screen));
	XSetForeground(app->display, w->gc, BlackPixel(app->display, app->screen));
/*	XSetForeground(app->display, w->gc, RGB(255,0,127)); */
	cherry_widget_get_dimension((CherryWidget *) window, &width, &height);
	cherry_widget_set_dimension((CherryWidget *) window, width + offset, height + offset);

	clist_add(&(app->windows), w);
	XSaveContext(app->display, w->window_handler, app->context, (XPointer) w);

	return w;
}

void
cherry_window_dispose_on_exit(CherryWindow *w)
{
	CherryApplication *app = cherry_application_get_running_app();

	XEvent evt;
	evt.xclient.type = ClientMessage;
	evt.xclient.serial = 0;
	evt.xclient.send_event = 1;
	evt.xclient.message_type = XInternAtom(app->display, "WM_PROTOCOLS", 0);
	evt.xclient.format = 32;
	evt.xclient.window = w->window_handler;
	evt.xclient.data.l[0] = XInternAtom(app->display, "CHERRY_DISPOSE_ON_EXIT", 0);

	XSendEvent(app->display, w->window_handler, 0, NoEventMask, &evt);
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
cherry_window_get_dimension(CherryWindow *window, int *width, int *height)
{
	CherryWidget *widget = (CherryWidget *) window;
	cherry_widget_get_dimension(widget, width, height);
}

void
cherry_window_set_dimension(CherryWindow *window, int width, int height)
{
	CherryWidget *widget = (CherryWidget *) window;
	cherry_widget_set_dimension(widget, width, height);

	if (cherry_widget_is_visible(widget)) {
		int x, y;
		CherryApplication *app = cherry_application_get_running_app();
		XMoveResizeWindow(app->display, window->window_handler,
		                  x, y,
		                  width, height);
	}
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
                           int (*listener)(struct CherryWindow *, CherryEvent))
{
	w->listener = listener;
}
