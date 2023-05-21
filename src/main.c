/* See LICENSE file for copyright and license details. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "application.h"
#include "event.h"
#include "window.h"

static void
app_deactivated(CherryApplication *app, void *data)
{
	printf("Deactivated\n");
}

int
listener1(CherryWindow *w, CherryEvent evt)
{
	char hello[] = "Example 1";
	char hi[] = "Hi!";

	KeySym mykey;
	char text[10];
	int i;

	switch (evt.event_id) {
		case WINDOW_DELETED:
			printf("Listener1\n");
			cherry_window_dispose_on_exit(w);
			break;
		case WINDOW_EXPOSED:
			XDrawImageString(evt.display,
			                 evt.window,
			                 w->gc,
			                 50, 50,
			                 hello, strlen(hello));
			break;
		case MOUSE_BUTTON_PRESSED:
			XDrawImageString(evt.display,
			                 evt.window,
			                 w->gc,
			                 evt.mouse.x, evt.mouse.y,
			                 hi, strlen(hi));
			break;
		case KEY_PRESSED:
			i = XLookupString(&evt.key.xkey, text, 10, &mykey, 0);
			if (i == 1 && text[0] == 'q') cherry_window_dispose_on_exit(w);
			break;
	}

	return 0;
}

  int
listener2(CherryWindow *w, CherryEvent evt)
{
	switch (evt.event_id) {
		case WINDOW_DELETED:
			printf("Listener2\n");
			break;
	}

	return 0;
}

static void
app_activated(CherryApplication *app, void *data)
{
	CherryWindow *w = cherry_window_new();
	cherry_window_set_title(w, "Hello from another World!");
	cherry_window_set_dimension(w, 350, 250);
	cherry_window_set_position(w, 200, 300);
	cherry_window_set_listener(w, listener1);

	CherryWindow *w2 = cherry_window_new();
	cherry_window_set_title(w2, "The second window");
	cherry_window_set_dimension(w2, 350, 250);
	cherry_window_set_position(w2, 500, 300);
	cherry_window_set_listener(w2, listener2);

	/* show up window */
	cherry_window_set_visible(w, 1);
	cherry_window_set_visible(w2, 1);
}

int
main(int argc, char **argv)
{
	CherryApplication *app = cherry_application_new("Just a test!");
	cherry_application_set_activated_listener(app, app_activated, NULL);
	cherry_application_set_deactivated_listener(app, app_deactivated, NULL);

	return cherry_application_run(app, argc, argv);
}
