/***********************************************************************
   Sample vector graphics program to test and demonstrate matfunc.h's
   functions, etc. (all by Mark Craig).  This program is based on Mark's
   solution to a homework assignment for Dr. Shoaff's graphics class.
   Copyright © 2021 Mark Craig

   https://www.youtube.com/MrMcSoftware
************************************************************************/

#include <windows.h>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"
 
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

	/* Windows GUI variables */

HINSTANCE hin;					/* instance handle */
WNDCLASS wc;					/* window class */
HWND w = NULL;					/* window */
HDC hdc;						/* window DC handle */
HPEN pens[2];					/* color pens for line drawing */
int width = 640, height = 480;	/* Window client area dimensions */

void ClearScreen();

std::vector<mat4> v;
float angle = 0.0;			// Rotation angle of animation
float angle2 = 0.0;			// Rotation angle (another axis) of animation
float hscale = 1.0;			// Scale of house
float xrange, xrangeh;		// adjust to aspect ratio
int delay = 7, dinc = 1;	// Control the speed of animation
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
MoveToEx(hdc, p[0].x, p[0].y, NULL);
LineTo(hdc, p[1].x, p[1].y);
LineTo(hdc, p[2].x, p[2].y);
LineTo(hdc, p[3].x, p[3].y);
LineTo(hdc, p[0].x, p[0].y);
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
MoveToEx(hdc, p[0].x, p[0].y, NULL);
LineTo(hdc, p[1].x, p[1].y);
LineTo(hdc, p[2].x, p[2].y);
LineTo(hdc, p[0].x, p[0].y);
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
		pers(15.0,0.0,100.0); SelectObject(hdc,pens[0]);
		if (!pauseit) { angle++; }
		ClearScreen();
		break;
	case 1:
		para(-20.0,20.0,-20.0,20.0,0.0,100.0); SelectObject(hdc,pens[1]);
		if (!pauseit) { angle++; }
		ClearScreen();
		break;
	case 2:
		if (count%2) { pers(15.0,0.0,100.0); SelectObject(hdc,pens[0]); }
		else
			{
			para(-20.0,20.0,-20.0,20.0,0.0,100.0); SelectObject(hdc,pens[1]);
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

	/* Windows GUI stuff */

void QuitProgram()
{
if (w) { DestroyWindow(w); w = NULL; }
}

void ClearScreen()
{
SelectObject(hdc, wc.hbrBackground);
PatBlt(hdc, 0, 0, width, height, PATCOPY);
}

long FAR PASCAL WindowProcedure(HWND w, unsigned msg, WPARAM wp, LPARAM lp)
{
RECT rc;
WORD wplow;
POINTS pt;
static bool drag = false;
static bool pausestatus;

switch (msg)
	{
	case WM_CREATE:
		hdc = GetDC(w);
		pens[0] = CreatePen(PS_SOLID,1,RGB(255,255,255));
		pens[1] = CreatePen(PS_SOLID,1,RGB(0,255,0));
		break;
	case WM_SIZING:
	case WM_SIZE:
		GetClientRect(w,&rc);
		width = rc.right-rc.left;
		height = rc.bottom-rc.top;
		xrange = 2.0*width/height; xrangeh=xrange/2.0;
		pausestatus = pauseit; pauseit = true; scene(); pauseit = pausestatus;
		break;
	case WM_KEYDOWN:
		wplow = LOWORD(wp);
		switch (wplow)
			{
			case VK_LEFT: delay-=dinc; if (delay < 0) { delay = 0; } break;
			case VK_RIGHT: delay+=dinc; break;
			case VK_UP: hscale+=.1; scene(); break;
			case VK_DOWN: hscale-=.1; if (hscale < .01) { hscale+=.1; } scene();
				break;
			case 'Q': DestroyWindow(w); w = NULL; break;
			case '1': display = 0; if (!pauseit) { angle--; } scene(); break;
			case '2': display = 1; if (!pauseit) { angle--; } scene(); break;
			case '3': display = 2; if (!pauseit) { angle--; } scene(); break;
			case ' ': pauseit = !pauseit; break;
			case 13: angle++; scene(); break;
			case 8: angle--; scene(); break;
			case 'R': angle = angle2 = 0; hscale = 1.0; scene(); break;
			case 'C': centerit = !centerit; scene(); break;
			}
		break;
	case WM_MOUSEMOVE:
		if (drag)
			{
			pt = MAKEPOINTS(lp);
			angle = pt.x/float(width)*360.0;
			angle2 = pt.y/float(height)*360.0; scene();
			}
		return(FALSE);
	case WM_LBUTTONDOWN:
		pt = MAKEPOINTS(lp);
		angle = pt.x/float(width)*360.0; drag = true;
		angle2 = pt.y/float(height)*360.0;
		pausestatus = pauseit; pauseit = true; scene();
		break;
	case WM_LBUTTONUP:
		drag = false; pauseit = pausestatus;
		break;
	case WM_CLOSE: DestroyWindow(w); w = NULL; break;
	case WM_DESTROY: PostQuitMessage(0); break;
	default: return(DefWindowProc(w, msg, wp, lp));
	}
return(0L);
}

int PASCAL WinMain(HINSTANCE hi, HINSTANCE hpi, LPSTR cmd, int scmd)
{
MSG msg;
DWORD dwStyle = WS_OVERLAPPEDWINDOW;
RECT rc={0, 0, width, height};

wc.style = 0;
wc.lpfnWndProc = (WNDPROC)WindowProcedure;
wc.cbClsExtra = 0; wc.cbWndExtra = 0; wc.hInstance = hi;
wc.hCursor = LoadCursor(NULL, IDC_ARROW);
wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
wc.lpszMenuName = NULL;
wc.lpszClassName = "FractClass";
if (!RegisterClass(&wc)) { QuitProgram(); }
hin=hi;
AdjustWindowRect(&rc, dwStyle, FALSE);
w = CreateWindow("FractClass",
	"Mark's Vector Graphics program to test matfunc.h (Windows)", dwStyle,
	50, 50, (rc.right-rc.left), (rc.bottom-rc.top), NULL, NULL, hi, NULL);
if (!w) { QuitProgram(); }
ShowWindow(w, scmd);
UpdateWindow(w);
scene();
while (1)
	{
    /* trying to be nice on CPU - only continuously run while loop when
       rotating, otherwise, use GetMessage which waits for event */
	if (!pauseit)
		{
		if (delay > 0) { Sleep(delay); }
		scene();
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) == TRUE)
			{
			if (GetMessage(&msg, NULL, 0, 0))
				{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				}
			else { return(TRUE); }
			}
		}
	else if (GetMessage(&msg, NULL, 0, 0))
		{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}
	else { return(TRUE); }
	}
QuitProgram();
}
