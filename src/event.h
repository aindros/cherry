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

typedef struct CherryEventMouse {
	int x;
	int y;
} CherryEventMouse;

typedef struct CherryEventKey {
	XKeyEvent xkey;
} CherryEventKey;

typedef struct CherryEvent {
	Display *display;
	Window   window;
	int      event_id;
	CherryEventKey   key;
	CherryEventMouse mouse;
} CherryEvent;

CherryEvent cherry_event_create(Display *, Window, int);
CherryEvent cherry_event_mouse_create(Display *, Window, int, int x, int y);
CherryEvent cherry_event_key_create(int, XKeyEvent);
int         cherry_event_id(CherryEvent);

#endif /* __CHERRY_EVENT_H__ */
