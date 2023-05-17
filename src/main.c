/* See LICENSE file for copyright and license details. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "application.h"
#include "window.h"

static void
app_deactivated(CherryApplication *app, void *data)
{
	printf("Deactivated\n");
}

static void
app_activated(CherryApplication *app, void *data)
{
	char hello[] = "Hello World!";

	CherryWindow *w = cherry_window_new();
	cherry_window_set_title(w, "Hello from another World!");
	cherry_window_set_dimension(w, 350, 250);
	cherry_window_set_position(w, 200, 300);
	cherry_window_set_visible(w, 1);


  char hi[] = "hi!";

  Window  mywindow;

  GC      mygc;

  XEvent myevent;
  KeySym mykey;

  XSizeHints myhint;

  unsigned long myforeground, mybackground;
  int i;
  char text[10];
  int done;

	Display *mydisplay = app->display;
	int      myscreen  = app->screen;
	int      depth     = app->depth;
	Visual  *visual    = app->visual;




  XSetWindowAttributes attributes;
  attributes.background_pixel      = XWhitePixel(mydisplay, myscreen);

  /* drawing contexts for an window */
  myforeground = BlackPixel(mydisplay, myscreen);
  mybackground = WhitePixel(mydisplay, myscreen);
  myhint.x = 200;
  myhint.y = 300;
  myhint.width = 350;
  myhint.height = 250;
  myhint.flags = PPosition|PSize;

  /* create window */
//  mywindow = XCreateSimpleWindow(mydisplay, DefaultRootWindow(mydisplay),
//                                 myhint.x, myhint.y,
//                                 myhint.width, myhint.height,
//                                 5, myforeground, mybackground);

	mywindow = XCreateWindow(mydisplay, XRootWindow(mydisplay, myscreen),
	                         myhint.x, myhint.y, myhint.width, myhint.height, 5, depth,  InputOutput,
	                         visual ,CWBackPixel, &attributes);

	/* window manager properties (yes, use of StdProp is obsolete) */
	XSetStandardProperties(mydisplay, mywindow, hello, hello,
	                       None, NULL, 0, &myhint);

  /* graphics context */
  mygc = XCreateGC(mydisplay, mywindow, 0, 0);
  XSetBackground(mydisplay, mygc, mybackground);
  XSetForeground(mydisplay, mygc, myforeground);

  /* allow receiving mouse events */
  XSelectInput(mydisplay,mywindow,
               ButtonPressMask|KeyPressMask|ExposureMask);

  /* show up window */
  XMapRaised(mydisplay, mywindow);

	Atom wmDelete=XInternAtom(app->display, "WM_DELETE_WINDOW", True);
	XSetWMProtocols(app->display, mywindow, &wmDelete, 1);

  /* event loop */
  done = 0;
  while(done==0){

    /* fetch event */
    XNextEvent(mydisplay, &myevent);

    switch(myevent.type){
		case ClientMessage:
			printf("Closed window\n");
			done = 1;
			break;

    case Expose:
      /* Window was showed. */
      if(myevent.xexpose.count==0)
        XDrawImageString(myevent.xexpose.display,
                         myevent.xexpose.window,
                         mygc,
                         50, 50,
                         hello, strlen(hello));
      break;
    case MappingNotify:
      /* Modifier key was up/down. */
      XRefreshKeyboardMapping(&myevent.xmapping);
      break;
    case ButtonPress:
      /* Mouse button was pressed. */
      XDrawImageString(myevent.xbutton.display,
                       myevent.xbutton.window,
                       mygc,
                       myevent.xbutton.x, myevent.xbutton.y,
                       hi, strlen(hi));
      break;
    case KeyPress:
      /* Key input. */
      i = XLookupString(&myevent.xkey, text, 10, &mykey, 0);
      if(i==1 && text[0]=='q') done = 1;
      break;
    }
  }

  /* finalization */
  XFreeGC(mydisplay,mygc);
	XDestroyWindow(mydisplay, mywindow);
//	XCloseDisplay(app->display);
}

int
main(int argc, char **argv)
{
	CherryApplication *app = cherry_application_new("Just a test!");
	cherry_application_set_activated_listener(app, app_activated, NULL);
	cherry_application_set_deactivated_listener(app, app_deactivated, NULL);

	return cherry_application_run(app, argc, argv);
}
