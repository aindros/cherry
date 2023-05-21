/* See LICENSE file for copyright and license details. */

#ifndef __CHERRY_APPLICATION_H__
#define __CHERRY_APPLICATION_H__

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <utils.h>

typedef struct CherryApplication {
	char *name;

	/* Xlib stuff */
	Display *display;
	int      screen;
	int      depth;
	Visual  *visual;
	XContext context;

	void (*listener_activate)(struct CherryApplication *, void *);
	void *listener_activate_data;

	void (*listener_deactivate)(struct CherryApplication *, void *);
	void *listener_deactivate_data;

	list_t windows;
} CherryApplication;

CherryApplication *cherry_application_new(const char *);
int                cherry_application_run(CherryApplication *, int, char **);
CherryApplication *cherry_application_get_running_app(void);

/* LISTENERS */
void cherry_application_set_activated_listener(CherryApplication *, void (*f)(struct CherryApplication *, void *), void *);
void cherry_application_set_deactivated_listener(CherryApplication *, void (*f)(struct CherryApplication *, void *), void *);

#endif /* __CHERRY_APPLICATION_H__ */
