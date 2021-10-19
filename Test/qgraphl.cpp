/***********************************************************************
   Sample quaternion rotation vector graphics program to test and
   demonstrate quaternion rotations (all by Mark Craig).
   Copyright © 2021 Mark Craig

   https://www.youtube.com/MrMcSoftware
************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"
#include "quat.h"
#include <X11/Xlib.h>
#include <X11/X.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>		/* Not needed if include string.h */
 
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define rad2deg(x) (x*180.0/M_PI)
#define deg2rad(x) (x*M_PI/180.0)

#include "matfunc.h"

	/* Linux GUI variables */

GC gc;						/* XWindow Graphic Context */
Display *dpy;				/* Connection to the X server */
Window win;					/* Window handle */
Atom wmDeleteMessage;		/* Message sent when user clicks "x" close button */
int width, height;			/* Window client area dimensions */

void graphinit(), graphterm(), ProcessEvents(char *key);
void ClearScreen(), setcolor(int r, int g, int b);

mat4 mproj(1.0);			// 3d projection matrix
int axescontrol = 0;		// Mouse controls which axes
float angleXYZ = 0.0;		// Rotation angle of animation around XYZ axis
float angleZ = 0.0;			// Rotation angle of animation around Z axis
float angleY = 0.0;			// Rotation angle of animation around Y axis
float angleX = 0.0;			// Rotation angle of animation around X axis
float scale = 1.0;			// scale of scene
float xrange, xrangeh;		// adjust to aspect ratio
int delay = 15, dinc = 2;	// Control the speed of animation
int method = 0;				// Rotation method: 0=all quat, 1=quat then mat4
bool pauseit = false;		// To pause animation, press SPACE

void pers(float ang, float zn, float zf)
{
mproj = PerspectiveProj(ang,zn,zf) * mproj;
}

void view(vec3 e, vec3 a, vec3 u)
{
mproj = View(e,a,u) * mproj;
}

vec3 obj[8]={vec3(-5.0,-5.0,-5.0),vec3(5.0,-5.0,-5.0),
	vec3(-5.0,5.0,-5.0),vec3(5.0,5.0,-5.0),
	vec3(-5.0,-5.0,5.0),vec3(5.0,-5.0,5.0),
	vec3(-5.0,5.0,5.0),vec3(5.0,5.0,5.0)};
vec3 obja[4]={vec3(0.0,0.0,0.0),vec3(15.0,0.0,0.0),
	vec3(0.0,15.0,0.0),vec3(0.0,0.0,15.0)};

void scene()
{
vec4 c[8], c2[4];
vec2 p[8], p2[4];
quat q(1.0,0.0,0.0,0.0);
quat P, qn;
int i;
mat4 m;

if (angleXYZ!=0.0) { q=rotate(q, deg2rad(angleXYZ), vec3(1.0,1.0,1.0).normalized()); }
if (angleZ!=0.0) { q=rotate(q, deg2rad(angleZ), vec3(0.0,0.0,1.0)); }
q=rotate(q, deg2rad(angleX), vec3(1.0,0.0,0.0));
q=rotate(q, deg2rad(angleY), vec3(0.0,1.0,0.0));
if (method) { m=Quat2Mat4(q); m*=mproj; if (scale!=0.0) { m=Scale(vec3(scale))*m; } }
else { if (scale!=0.0) { q*=sqrt(scale); } }
for (i=0; i<8; i++)
	{
	if (method==0) // Do rotation completely with quats (mat4 only for proj.)
		{
		P = quat(0.0,obj[i]);
		qn = q * P * q.conjugate();
		c[i] = vec4(qn.x,qn.y,qn.z,1.0) * mproj;
		}
	else { c[i] = vec4(obj[i].x,obj[i].y,obj[i].z,1.0) * m; }
	p[i].x = (xrangeh+c[i].x/c[i].w)*float(width)/xrange;
	p[i].y = float(height)-(1.0+c[i].y/c[i].w)*float(height)/2.0;
	if (i<4)
		{
		if (method==0)
			{
			P = quat(0.0,obja[i]);
			qn = q * P * q.conjugate();
			c2[i] = vec4(qn.x,qn.y,qn.z,1.0) * mproj;
			}
		else { c2[i] = vec4(obja[i].x,obja[i].y,obja[i].z,1.0) * m; }
		p2[i].x = (1.0+c2[i].x/c2[i].w)*float(width)/2.0;
		p2[i].y = float(height)-(1.0+c2[i].y/c2[i].w)*float(height)/2.0;
		}
	}
ClearScreen();
if (method) { setcolor(50,255,255); } else { setcolor(255,255,255); }
XDrawLine(dpy, win, gc, p[0].x, p[0].y, p[1].x, p[1].y);
XDrawLine(dpy, win, gc, p[2].x, p[2].y, p[3].x, p[3].y);
XDrawLine(dpy, win, gc, p[4].x, p[4].y, p[5].x, p[5].y);
XDrawLine(dpy, win, gc, p[6].x, p[6].y, p[7].x, p[7].y);
XDrawLine(dpy, win, gc, p[0].x, p[0].y, p[4].x, p[4].y);
XDrawLine(dpy, win, gc, p[1].x, p[1].y, p[5].x, p[5].y);
XDrawLine(dpy, win, gc, p[2].x, p[2].y, p[6].x, p[6].y);
XDrawLine(dpy, win, gc, p[3].x, p[3].y, p[7].x, p[7].y);
setcolor(255,255,0);
XDrawLine(dpy, win, gc, p[0].x, p[0].y, p[2].x, p[2].y);
XDrawLine(dpy, win, gc, p[1].x, p[1].y, p[3].x, p[3].y);
XDrawLine(dpy, win, gc, p[4].x, p[4].y, p[6].x, p[6].y);
XDrawLine(dpy, win, gc, p[5].x, p[5].y, p[7].x, p[7].y);
setcolor(255,0,0); XDrawLine(dpy, win, gc, p2[0].x, p2[0].y, p2[1].x, p2[1].y);
setcolor(0,255,0); XDrawLine(dpy, win, gc, p2[0].x, p2[0].y, p2[2].x, p2[2].y);
setcolor(0,0,255); XDrawLine(dpy, win, gc, p2[0].x, p2[0].y, p2[3].x, p2[3].y);
if (!pauseit) { angleY++; if (angleY>=360.0) { angleY-=360.0; angleX+=5.0; } }
}

	/* Linux / XWindows GUI stuff */

void ClearScreen()
{
XClearWindow(dpy, win);
}

int main(int argc, char *argv[])
{
char str[8];
XEvent event;
vec3 e,a,u;

graphinit();
// Wait for window to popup
//  Some X11 systems will crash if the window hasn't been mapped yet, so wait
//  for MapNotify event rather than Expose
do { XNextEvent(dpy, &event); } while (event.type != MapNotify);
//do { XNextEvent(dpy, &event); } while (event.type != Expose);
XFlush(dpy);
e = vec3(70.0,120.0,-100.0);
a = vec3(0.0,0.0,0.0);
u = vec3(0.0,1.0,0.0);
pers(15.0,0.0,100.0);
view(e,a,u); 
setcolor(255,255,255);
scene();
while (1)
	{
	/* trying to be nice on CPU - only continuously run while loop when
	   rotating, otherwise, use XPeekEvent which waits for event */
	if (!pauseit)
		{
		if (delay > 0) { usleep(delay*500); }
		scene();
		if (XPending(dpy)) { ProcessEvents(str); } 
		}
	else { if (XPeekEvent(dpy, &event)) { ProcessEvents(str); } }
	if (str[0] == 'q') { break; }
	}
}

void setcolor(int r, int g, int b)
{
unsigned long c;

c=((unsigned long)(r)<<16)|((unsigned long)(g)<<8)|((unsigned long)(b));
XSetForeground(dpy, gc, c);
}

void graphinit()
{
XGCValues gcvalues;
XSizeHints hints;
XWMHints wm_hints;
Visual *visual;
XVisualInfo vis;
XSetWindowAttributes wa;
int depth = 24;
int border_width = 0;
int screen_num;
unsigned int wclass;
unsigned long valuemask;
char *display_name = NULL;

/* I copied this routine from some other code I wrote.  I took out the
   unneeded (in this project) code I saw, but there still might be some more */
 
if ((dpy = XOpenDisplay(display_name)) == NULL)
	{
	printf("Cannot connect to X server %s\n", XDisplayName(display_name));
	exit(1);
	}
screen_num = DefaultScreen(dpy);
depth = DefaultDepth(dpy, screen_num);
width = 640;
height = 480;
xrange = 2.0*width/height; xrangeh=xrange/2.0;
if (depth > 8)
	{
	//visual = DefaultVisual(dpy, screen_num);
	vis.depth = depth;
	XMatchVisualInfo(dpy, screen_num, vis.depth, TrueColor, &vis);
	visual = vis.visual;
	valuemask = CWColormap | CWBackPixel | CWBorderPixel;
	wa.background_pixel = BlackPixel(dpy, screen_num);
	wa.border_pixel = BlackPixel(dpy, screen_num);
	wclass = InputOutput;
	wa.colormap = XCreateColormap(dpy, RootWindow(dpy, screen_num), visual, AllocNone);
	win = XCreateWindow(dpy, RootWindow(dpy, screen_num),
		0, 0, width, height, border_width, vis.depth, wclass,
		visual, valuemask, &wa);
	wmDeleteMessage = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(dpy, win, &wmDeleteMessage, 1);
	}
hints.flags = PPosition | PSize;
hints.x = hints.y = 0;
hints.width = width;
hints.height = height;
XSetNormalHints(dpy, win, &hints);
XStoreName(dpy, win, "Mark's Quaternion Vector Graphics program to test quat.h (Linux)");
XSetInputFocus(dpy, PointerRoot, RevertToNone, CurrentTime);
wm_hints.initial_state = NormalState;
wm_hints.input = True;
wm_hints.flags = StateHint | InputHint;
XSetWMHints(dpy, win, &wm_hints);
XSelectInput(dpy, win, ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask | StructureNotifyMask | PointerMotionMask);
XMapWindow(dpy, win);
gc = XCreateGC(dpy, win, 0L, &gcvalues);
XSetForeground(dpy, gc, WhitePixel(dpy, 0));
}

void graphterm()
{
static int term = 0;

if (term) { return; }
XFlush(dpy);
XFreeGC(dpy, gc);
XDestroyWindow(dpy, win);
XCloseDisplay(dpy);
term = 1;
}

void mouseAngles(int x, int y)
{
switch (axescontrol)
	{
	case 0:
		angleY = x/float(width)*360.0;
		angleX = y/float(height)*360.0;
		break;
	case 1:
		angleX = x/float(width)*360.0;
		break;
	case 2:
		angleY = x/float(width)*360.0;
		break;
	case 3:
		angleZ = x/float(width)*360.0;
		break;
	case 4:
		angleXYZ = x/float(width)*360.0;
		break;
	}
}

void ProcessEvents(char *key)
{
XEvent event;
char string[128];
static bool drag = false;
static bool pausestatus;

key[0] = string[0] = '\0';
//if (XCheckTypedWindowEvent(dpy, win, Expose, &event)) { }
if (XCheckTypedWindowEvent(dpy, win, ClientMessage, &event))
	{
	if (event.xclient.data.l[0] == wmDeleteMessage)
		{
		key[0] = 'q'; graphterm(); return;
		}
	}
if (XCheckTypedWindowEvent(dpy, win, KeyPress, &event))
	{
	XLookupString(&event.xkey, string, 128, NULL, NULL);
	switch (event.xkey.keycode)
		{
		case 113: delay-=dinc; if (delay < 0) { delay = 0; } break; // left
		case 114: delay+=dinc; break; // right
		case 111: scale+=.1; scene(); break; // up
		case 116: scale-=.1; if (scale < .01) { scale+=.1; } scene(); // down
		}
	key[0] = string[0];
	switch (string[0])
		{
		case 'q': graphterm(); return; break;
		case ' ': pauseit = !pauseit; break;
		case 13: angleY++; scene(); break;
		case 8: angleY-=2; scene(); break;
		case 'r': angleY = angleX = angleZ = angleXYZ = 0; scale = 1.0; scene();
			break;
		case 'x': axescontrol = 1; break;
		case 'y': axescontrol = 2; break;
		case 'z': axescontrol = 3; break;
		case 'a': axescontrol = 4; break;
		case 'n': axescontrol = 0; break;
		case '1': method = 0; scene(); break;
		case '2': method = 1; scene(); break;
		}
	}
if (XCheckTypedWindowEvent(dpy, win, ConfigureNotify, &event))
	{
	if ((event.xconfigure.width != width)||(event.xconfigure.height != height))
		{
		width = event.xconfigure.width;
		height = event.xconfigure.height;
		xrange = 2.0*width/height; xrangeh=xrange/2.0;
		}
	}
if (XCheckTypedWindowEvent(dpy, win, ButtonPress, &event))
	{
	XButtonEvent *e = (XButtonEvent *)&event;
	if (e->button == 1)
		{
		mouseAngles(e->x, e->y); drag = true;
		pausestatus = pauseit; pauseit = true; scene();
		}
	}
if (XCheckTypedWindowEvent(dpy, win, ButtonRelease, &event))
	{
	XButtonEvent *e = (XButtonEvent *)&event;
	if (e->button == 1) { drag = false; pauseit = pausestatus; }
	}
if (XCheckTypedWindowEvent(dpy, win, MotionNotify, &event))
	{
	XMotionEvent *e = (XMotionEvent *)&event;
	if (drag)
		{
		mouseAngles(e->x, e->y);
		scene();
		}
	}
}
