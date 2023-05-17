/* See LICENSE file for copyright and license details. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <utils.h>
#include <log.h>
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

static void
dispatch_event(CherryApplication *app, Window wnd, int event_id) {
	iterator_t it = clist_iterator(&app->windows);
	while (clist_iterator_has_next(it)) {
		CherryWindow *w = clist_iterator_next(&it);
		if (w->window_handler == wnd) {
			if (w->listener != NULL) {
				w->listener(w, event_id);
			} else {
				return;
			}
		}
	}
}

static void
cherry_application_main_loop(CherryApplication *app)
{
	XEvent event;
	int finish = 0;
	char *atom_name;

	while (finish == 0) {
		XNextEvent(app->display, &event);

		switch (event.type) {
			case ClientMessage:
				atom_name = XGetAtomName(app->display, (Atom) event.xclient.data.l[0]);

				if (strcmp("CHERRY_DISPOSE_ON_EXIT", atom_name) == 0) {
					/* Exit from loop */
					finish = 1;
				} else if (strcmp("WM_DELETE_WINDOW", atom_name) == 0) {
					dispatch_event(app, event.xclient.window, DELETE_WINDOW);
				}

				XFree(atom_name);
				break;
			case Expose:
				break;
			case MappingNotify:
				break;
			case ButtonPress:
				break;
			case KeyPress:
				break;
		}
	}
}

static void
print_log(Log *log, char *fmt, char *attr)
{
	char *message = calloc(strlen(fmt) + strlen(attr) + 1, sizeof(char));
	sprintf(message, fmt, attr);
	log_debug(log, message);

	free(message);
}

int
cherry_application_run(CherryApplication *app, int argc, char **argv)
{
	Log *log = log_create("cherry_application_run");

	if (app == NULL) exit(1);

	/* setup display/screen */
	app->display = XOpenDisplay(NULL);
	app->screen  = DefaultScreen(app->display);
	app->depth   = DefaultDepth(app->display, app->screen);
	app->visual  = DefaultVisual(app->display, app->screen);

	if (app->listener_activate != NULL)
		app->listener_activate(app, app->listener_activate_data);

	cherry_application_main_loop(app);

	/* finalization */
	iterator_t it = clist_iterator(&app->windows);
	while (clist_iterator_has_next(it)) {
		CherryWindow *w = clist_iterator_next(&it);

		char *wnd_name = cherry_window_get_title(w);
		print_log(log, "Destroying window: %s", wnd_name);
		XFree(wnd_name);

		XFreeGC(app->display, w->gc);
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
