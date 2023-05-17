/* See LICENSE file for copyright and license details. */

#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <utils.h>
#include "application.h"
#include "event.h"
#include "window.h"

static CherryApplication *_app = NULL;

CherryApplication *
cherry_application_new(const char *name)
{
	if (_app != NULL)
		return _app;

	CherryApplication *app = malloc(sizeof(*app));
	app->name = strdup(name);
	app->display = NULL;
	app->windows = clist_create();

	app->listener_activate = NULL;
	app->listener_activate_data = NULL;

	app->listener_deactivate = NULL;
	app->listener_deactivate_data = NULL;

	_app = app;

	return app;
}

int
cherry_application_run(CherryApplication *app, int argc, char **argv)
{
	if (app == NULL) exit(1);

	/* setup display/screen */
	app->display = XOpenDisplay(NULL);
	app->screen  = DefaultScreen(app->display);
	app->depth   = DefaultDepth(app->display, app->screen);
	app->visual  = DefaultVisual(app->display, app->screen);

	if (app->listener_activate != NULL)
		app->listener_activate(app, app->listener_activate_data);

	/* finalization */
	iterator_t it = clist_iterator(&app->windows);
	while (clist_iterator_has_next(it)) {
		CherryWindow *w = clist_iterator_next(&it);
		char *wnd_name = cherry_window_get_title(w);
		printf("Destroying window: %s\n", wnd_name);
		XFree(wnd_name);
		XDestroyWindow(app->display, w->window_handler);
	}

	XCloseDisplay(app->display);

	if (app->listener_deactivate != NULL)
		app->listener_deactivate(app, app->listener_deactivate_data);

	return EXIT_SUCCESS;
}

void
cherry_application_set_activated_listener(CherryApplication *app,
                                          void (*listener_activate)(CherryApplication *, void *),
                                          void *data)
{
	if (app == NULL) return;

	app->listener_activate = listener_activate;
	app->listener_activate_data = data;
}

void
cherry_application_set_deactivated_listener(CherryApplication *app,
                                            void (*listener_deactivate)(CherryApplication *, void *),
                                            void *data)
{
	if (app == NULL) return;

	app->listener_deactivate = listener_deactivate;
	app->listener_deactivate_data = data;
}

CherryApplication *
cherry_application_get_running_app(void)
{
	return _app;
}
