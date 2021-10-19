/***********************************************************************
   Sample vector graphics program to test and demonstrate matfunc.h's
   functions, etc. (all by Mark Craig).  This program is based on Mark's
   solution to a homework assignment for Dr. Shoaff's graphics class.
   Copyright © 2021 Mark Craig

   https://www.youtube.com/MrMcSoftware
************************************************************************/

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"
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

using std::cout;
using std::endl;

typedef struct
	{
	vec3 v[4];
	} Square;

typedef struct
	{
	vec3 v[3];
	} Triangle;

typedef struct
	{
	vec3 c;
	float r;
	} Circle;

	/* Linux GUI variables */

GC gc;						/* XWindow Graphic Context */
Display *dpy;				/* Connection to the X server */
Window win;					/* Window handle */
Atom wmDeleteMessage;		/* Message sent when user clicks "x" close button */
int width, height;			/* Window client area dimensions */

void graphinit(), graphterm(), ProcessEvents(char *key);
void ClearScreen(), setcolor(int r, int g, int b);

std::vector<mat4> v;
float angle = 0.0;			// Rotation angle of animation
float angle2 = 0.0;			// Rotation angle (another axis) of animation
float hscale = 1.0;			// Scale of house
float xrange, xrangeh;		// adjust to aspect ratio
int delay = 15, dinc = 2;	// Control the speed of animation
int display = 2;			// 0 = Perspective, 1 = Parallel, 2 = Both
bool pauseit = false;		// To pause animation, press SPACE
bool centerit = false;		// To center rotation axis

void tran(float tx, float ty, float tz)
{
mat4 t = Translate(vec3(tx,ty,tz)) * (v[v.size()-1]);
v[v.size()-1] = t;
}

void scale(float sx, float sy, float sz)
{
mat4 t = Scale(vec3(sx,sy,sz)) * (v[v.size()-1]);
v[v.size()-1] = t;
}

void rot(float ang, int axis)
{
mat4 t = Rotate(deg2rad(ang),axis-1) * (v[v.size()-1]);
v[v.size()-1] = t;
}

void para(float xl, float xr, float yb, float yt, float zn, float zf)
{
mat4 t = ParallelProj(xl,xr,yb,yt,zn,zf) * (v[v.size()-1]);
v[v.size()-1] = t;
}

void pers(float ang, float zn, float zf)
{
mat4 t = PerspectiveProj(ang,zn,zf) * (v[v.size()-1]);
v[v.size()-1] = t;
}

void view(vec3 e, vec3 a, vec3 u)
{
mat4 t = View(e,a,u) * (v[v.size()-1]);
v[v.size()-1] = t;
}

void square(Square &sq)
{
sq.v[0].x = 0; sq.v[0].y = 0; sq.v[0].z = 0;
sq.v[1].x = 1; sq.v[1].y = 0; sq.v[1].z = 0;
sq.v[2].x = 1; sq.v[2].y = 1; sq.v[2].z = 0;
sq.v[3].x = 0; sq.v[3].y = 1; sq.v[3].z = 0;
}

void triangle(Triangle &tr)
{
tr.v[0].x = 0; tr.v[0].y = 0; tr.v[0].z = 0;
tr.v[1].x = 1; tr.v[1].y = 0; tr.v[1].z = 0;
tr.v[2].x = 1; tr.v[2].y = 1; tr.v[2].z = 0;
}

void circle(Circle &ci)
{
ci.c.x = 0; ci.c.y = 0; ci.c.z = 0;
ci.r = 1;
}

void push()
{
v.push_back(mat4(1.0));
}

void pop()
{
v.pop_back();
}

void print_stack()
{
struct matrices *sptr;

cout << "Begin print_stack\n";
for (std::vector<mat4>::reverse_iterator i = v.rbegin(); i != v.rend(); i++)
	{
	cout << *i;
	}
cout << endl;
cout << "End print_stack\n";
}

void print()
{
mat4 m(1.0);

for (std::vector<mat4>::reverse_iterator i = v.rbegin(); i != v.rend(); i++)
	{
	m *= (*i);
	}
cout << m;
}

void global()
{
push();
}

mat4 combine_matrices()
{
mat4 m(1.0);

for (std::vector<mat4>::reverse_iterator i = v.rbegin(); i != v.rend(); i++)
	{
	m *= (*i);
	}
return(m);
}

void draw_square()
{
Square sq;
vec4 c[4];
vec2 p[4];
int i;

mat4 m = combine_matrices();
square(sq);
c[0] = vec4(sq.v[0],1.0)*m;
c[1] = vec4(sq.v[1],1.0)*m;
c[2] = vec4(sq.v[2],1.0)*m;
c[3] = vec4(sq.v[3],1.0)*m;
for (i=0; i<4; i++)
	{
	p[i].x = (xrangeh+c[i].x/c[i].w)*float(width)/xrange;
	p[i].y = float(height)-(1.0+c[i].y/c[i].w)*float(height)/2.0;
	}
XDrawLine(dpy, win, gc, p[0].x, p[0].y, p[1].x, p[1].y);
XDrawLine(dpy, win, gc, p[1].x, p[1].y, p[2].x, p[2].y);
XDrawLine(dpy, win, gc, p[2].x, p[2].y, p[3].x, p[3].y);
XDrawLine(dpy, win, gc, p[3].x, p[3].y, p[0].x, p[0].y);
}

void draw_triangle()
{
Triangle tr;
vec4 c[3];
vec2 p[3];
int i;

mat4 m = combine_matrices();
triangle(tr);
c[0] = vec4(tr.v[0],1.0)*m;
c[1] = vec4(tr.v[1],1.0)*m;
c[2] = vec4(tr.v[2],1.0)*m;
for (i=0; i<3; i++)
	{
	p[i].x = (xrangeh+c[i].x/c[i].w)*float(width)/xrange;
	p[i].y = float(height)-(1.0+c[i].y/c[i].w)*float(height)/2.0;
	}
XDrawLine(dpy, win, gc, p[0].x, p[0].y, p[1].x, p[1].y);
XDrawLine(dpy, win, gc, p[1].x, p[1].y, p[2].x, p[2].y);
XDrawLine(dpy, win, gc, p[2].x, p[2].y, p[0].x, p[0].y);
}

void scene()
{
static int count = 0;
vec3 e,a,u;

e = vec3(70.0,120.0,-100.0);
a = vec3(0.0,0.0,0.0);
u = vec3(0.0,1.0,0.0);
global();
switch (display)
	{
	case 0:
		pers(15.0,0.0,100.0); setcolor(255,255,255);
		if (!pauseit) { angle++; }
		ClearScreen();
		break;
	case 1:
		para(-20.0,20.0,-20.0,20.0,0.0,100.0); setcolor(0,255,0);
		if (!pauseit) { angle++; }
		ClearScreen();
		break;
	case 2:
		if (count%2) { pers(15.0,0.0,100.0); setcolor(255,255,255); }
		else
			{
			para(-20.0,20.0,-20.0,20.0,0.0,100.0); setcolor(0,255,0);
			if (!pauseit) { angle++; }
			ClearScreen();
			}
		count++;
		break;
	}
view(e,a,u); 
scale(hscale,hscale,-hscale);
rot(angle2,1);
rot(angle,2);
if (centerit) { tran(-5.0,0.0,-10.0); }
push();				/* Floor */
scale(10.0,0.0,20.0);
rot(90.0,1);
draw_square();
pop();
push();				/* Front */
scale(10.0,10.0,0.0);
draw_square();
pop();
push();				/* Front Door */
tran(3.5,0.0,0.0);
scale(3.0,6.0,0.0);
draw_square();
pop();
push();				/* Back */
tran(0.0,0.0,20.0);
scale(10.0,10.0,0.0);
draw_square();
pop();
push();				/* Roof1 */
tran(0.0,10.0,0.0);
rot(45.0,3);
scale(7.07107,0.0,20.0);
rot(90.0,1);
draw_square();
pop();
push();				/* Roof2 */
tran(5.0,15.0,0.0);
rot(-45.0,3);
scale(7.07107,0.0,20.0);
rot(90.0,1);
draw_square();
pop();
push();				/* Gable1 */
tran(5.0,10.0,0.0);
scale(7.07107,7.07107,0.0);
tran(0.707107,0.0,0.0);
rot(135.0,3);
draw_triangle();
pop();
push();				/* Gable2 */
tran(5.0,10.0,20.0);
scale(7.07107,7.07107,0.0);
tran(0.707107,0.0,0.0);
rot(135.0,3);
draw_triangle();
pop();
pop();
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

graphinit();
// Wait for window to popup
//  Some X11 systems will crash if the window hasn't been mapped yet, so wait
//  for MapNotify event rather than Expose
do { XNextEvent(dpy, &event); } while (event.type != MapNotify);
//do { XNextEvent(dpy, &event); } while (event.type != Expose);
XFlush(dpy);
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
XStoreName(dpy, win, "Mark's Vector Graphics program to test matfunc.h (Linux)");
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
		case 111: hscale+=.1; scene(); break; // up
		case 116: hscale-=.1; if (hscale < .01) { hscale+=.1; } scene(); // down
		}
	key[0] = string[0];
	switch (string[0])
		{
		case 'q': graphterm(); return; break;
		case '1': display = 0; if (!pauseit) { angle--; } scene(); break;
		case '2': display = 1; if (!pauseit) { angle--; } scene(); break;
		case '3': display = 2; if (!pauseit) { angle--; } scene(); break;
		case ' ': pauseit = !pauseit; break;
		case 13: angle++; scene(); break;
		case 8: angle--; scene(); break;
		case 'r': angle = angle2 = 0; hscale = 1.0; scene(); break;
		case 'c': centerit = !centerit; scene(); break;
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
		angle = e->x/float(width)*360.0; drag = true;
		angle2 = e->y/float(height)*360.0;
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
		angle = e->x/float(width)*360.0;
		angle2 = e->y/float(height)*360.0; scene();
		}
	}
}
