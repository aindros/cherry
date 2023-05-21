/* See LICENSE file for copyright and license details. */

#ifndef __CHERRY_EVENT_H__
#define __CHERRY_EVENT_H__

#include <X11/Xlib.h>

enum Events {
	WINDOW_DELETED,
	WINDOW_EXPOSED,
	MOUSE_BUTTON_PRESSED,
	KEY_PRESSED
};

typedef struct CherryEvent {
	Display *display;
	Window   window;
	int      event_id;
	int      x, y;
	XKeyEvent xkey;
};

#endif /* __CHERRY_EVENT_H__ */
