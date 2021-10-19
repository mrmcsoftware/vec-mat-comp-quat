/***********************************************************************
   Sample vector graphics program to test and demonstrate matfunc.h's
   functions, etc. (all by Mark Craig).  This program is based on Mark's
   solution to a homework assignment for Dr. Shoaff's graphics class.
   Copyright © 2021 Mark Craig

   https://www.youtube.com/MrMcSoftware
************************************************************************/

#include <windows.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"
#include "quat.h"
 
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define rad2deg(x) (x*180.0/M_PI)
#define deg2rad(x) (x*M_PI/180.0)

#include "matfunc.h"

	/* Windows GUI variables */

HINSTANCE hin;					/* instance handle */
WNDCLASS wc;					/* window class */
HWND w = NULL;					/* window */
HDC hdc;						/* window DC handle */
HPEN pens[6];					/* color pens for line drawing */
int width = 640, height = 480;	/* Window client area dimensions */

void ClearScreen();

mat4 mproj(1.0);			// 3d projection matrix
int axescontrol = 0;		// Mouse controls which axes
float angleXYZ = 0.0;		// Rotation angle of animation around XYZ axis
float angleZ = 0.0;			// Rotation angle of animation around Z axis
float angleY = 0.0;			// Rotation angle of animation around Y axis
float angleX = 0.0;			// Rotation angle of animation around X axis
float scale = 1.0;			// scale of scene
float xrange, xrangeh;		// adjust to aspect ratio
int delay = 7, dinc = 1;	// Control the speed of animation
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
SelectObject(hdc,pens[method*5]);
MoveToEx(hdc, p[0].x, p[0].y, NULL); LineTo(hdc, p[1].x, p[1].y);
MoveToEx(hdc, p[2].x, p[2].y, NULL); LineTo(hdc, p[3].x, p[3].y);
MoveToEx(hdc, p[4].x, p[4].y, NULL); LineTo(hdc, p[5].x, p[5].y);
MoveToEx(hdc, p[6].x, p[6].y, NULL); LineTo(hdc, p[7].x, p[7].y);
MoveToEx(hdc, p[0].x, p[0].y, NULL); LineTo(hdc, p[4].x, p[4].y);
MoveToEx(hdc, p[1].x, p[1].y, NULL); LineTo(hdc, p[5].x, p[5].y);
MoveToEx(hdc, p[2].x, p[2].y, NULL); LineTo(hdc, p[6].x, p[6].y);
MoveToEx(hdc, p[3].x, p[3].y, NULL); LineTo(hdc, p[7].x, p[7].y);
SelectObject(hdc,pens[1]);
MoveToEx(hdc, p[0].x, p[0].y, NULL); LineTo(hdc, p[2].x, p[2].y);
MoveToEx(hdc, p[1].x, p[1].y, NULL); LineTo(hdc, p[3].x, p[3].y);
MoveToEx(hdc, p[4].x, p[4].y, NULL); LineTo(hdc, p[6].x, p[6].y);
MoveToEx(hdc, p[5].x, p[5].y, NULL); LineTo(hdc, p[7].x, p[7].y);
SelectObject(hdc,pens[2]);
MoveToEx(hdc, p2[0].x, p2[0].y, NULL); LineTo(hdc, p2[1].x, p2[1].y);
SelectObject(hdc,pens[3]);
MoveToEx(hdc, p2[0].x, p2[0].y, NULL); LineTo(hdc, p2[2].x, p2[2].y);
SelectObject(hdc,pens[4]);
MoveToEx(hdc, p2[0].x, p2[0].y, NULL); LineTo(hdc, p2[3].x, p2[3].y);
if (!pauseit) { angleY++; if (angleY>=360.0) { angleY-=360.0; angleX+=5.0; } }
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
//BitBlt(hdc, 0, 0, width, height, NULL, 0, 0, BLACKNESS);
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
		pens[1] = CreatePen(PS_SOLID,1,RGB(255,255,0));
		pens[2] = CreatePen(PS_SOLID,1,RGB(255,0,0));
		pens[3] = CreatePen(PS_SOLID,1,RGB(0,255,0));
		pens[4] = CreatePen(PS_SOLID,1,RGB(0,0,255));
		pens[5] = CreatePen(PS_SOLID,1,RGB(50,255,255));
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
			case VK_UP: scale+=.1; scene(); break;
			case VK_DOWN: scale-=.1; if (scale < .01) { scale+=.1; } scene();
				break;
			case 'Q': DestroyWindow(w); w = NULL; break;
			case ' ': pauseit = !pauseit; break;
			case 13: angleY++; scene(); break;
			case 8: angleY-=2; scene(); break;
			case 'R': angleY = angleX = angleZ = angleXYZ = 0; scale = 1.0;
				scene(); break;
			case 'X': axescontrol = 1; break;
			case 'Y': axescontrol = 2; break;
			case 'Z': axescontrol = 3; break;
			case 'A': axescontrol = 4; break;
			case 'N': axescontrol = 0; break;
			case '1': method = 0; scene(); break;
			case '2': method = 1; scene(); break;
			}
		break;
	case WM_MOUSEMOVE:
		if (drag)
			{
			pt = MAKEPOINTS(lp);
			mouseAngles(pt.x, pt.y);
			scene();
			}
		return(FALSE);
	case WM_LBUTTONDOWN:
		pt = MAKEPOINTS(lp);
		mouseAngles(pt.x, pt.y); drag = true;
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
vec3 e,a,u;

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
	"Mark's Quaternion Vector Graphics program to test quat.h (Windows)",
	dwStyle, 50, 50, (rc.right-rc.left), (rc.bottom-rc.top), NULL, NULL, hi,
	NULL);
if (!w) { QuitProgram(); }
ShowWindow(w, scmd);
UpdateWindow(w);
e = vec3(70.0,120.0,-100.0);
a = vec3(0.0,0.0,0.0);
u = vec3(0.0,1.0,0.0);
pers(15.0,0.0,100.0);
view(e,a,u); 
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
