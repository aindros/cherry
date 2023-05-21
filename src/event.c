/* See LICENSE file for copyright and license details. */

#include "window.h"

CherryEvent
cherry_event_create(Display *display, Window wnd, int event_id)
{
	CherryEvent evt;

	evt.display  = display;
	evt.window   = wnd;
	evt.event_id = event_id;

	return evt;
}

CherryEvent
cherry_event_mouse_create(Display *display, Window wnd, int event_id, int x, int y)
{
	CherryEvent evt;
	CherryEventMouse mouse;

	evt = cherry_event_create(display, wnd, event_id);
	mouse.x = x;
	mouse.y = y;
	evt.mouse = mouse;

	return evt;
}

CherryEvent
cherry_event_key_create(int event_id, XKeyEvent xkey)
{
	CherryEvent evt;
	CherryEventKey key;

	evt.event_id = event_id;
	key.xkey = xkey;
	evt.key = key;

	return evt;
}

int
cherry_event_id(CherryEvent evt)
{
	return evt.event_id;
}
