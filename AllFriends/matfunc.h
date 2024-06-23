/*********************************************************
   Various 3d transformation functions using matrices
   Copyright © 2021 Mark Craig

   https://www.youtube.com/MrMcSoftware
**********************************************************/

#ifndef _MATFUNC_H
#define _MATFUNC_H

#include "vec3.h"
#include "mat4.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#if _MSC_VER == 1200
using ::sin;
using ::cos;
using ::sqrt;
#else
using std::sin;
using std::cos;
using std::sqrt;
#endif

mat4 Translate(const vec3 &t)
{
mat4 r(1.0);

r.m[3][0]=t.x;
r.m[3][1]=t.y;
r.m[3][2]=t.z;
return(r);
}

mat4 Scale(const vec3 &s)
{
mat4 r(1.0);

r.m[0][0]=s.x;
r.m[1][1]=s.y;
r.m[2][2]=s.z;
return(r);
}

mat4 Rotate(const float ang,const int type)
{
float c,s;
mat4 r(1.0);

//ang*=M_PI/180.0;
c=cos(ang);
s=sin(ang);
switch (type)
	{
	case 0:
		r.m[1][1]=c;
		r.m[2][2]=c;
		r.m[1][2]=s;
		r.m[2][1]=-s;
		break;
	case 1:
		r.m[0][0]=c;
		r.m[2][2]=c;
		r.m[2][0]=s;
		r.m[0][2]=-s;
		break;
	case 2:
		r.m[0][0]=c;
		r.m[1][1]=c;
		r.m[0][1]=s;
		r.m[1][0]=-s;
		break;
	}	
return(r);
}

mat4 View(const vec3 &e,const vec3 &a,const vec3 &u)
{
float b,ab;
vec3 n;
mat4 r(1.0);

n=a-e;
n.normalize();
b=u.x*n.x+u.y*n.y+u.z*n.z;
ab=sqrt(1.0-b*b);
r.m[0][2]=n.x;
r.m[1][2]=n.y;
r.m[2][2]=n.z;
r.m[0][1]=(u.x-b*n.x)/ab;
r.m[1][1]=(u.y-b*n.y)/ab;
r.m[2][1]=(u.z-b*n.z)/ab;
r.m[0][0]=r.m[1][2]*r.m[2][1]-r.m[1][1]*r.m[2][2];
r.m[1][0]=r.m[2][2]*r.m[0][1]-r.m[2][1]*r.m[0][2];
r.m[2][0]=r.m[0][2]*r.m[1][1]-r.m[0][1]*r.m[1][2];
mat4 r2=Translate(-e);
r=r2*r;
return(r);
}

mat4 PerspectiveProj(const float &ang,const float &zn,const float &zf)
{
float angle,c,s,q;
mat4 r(1.0);

angle=ang*M_PI/360.0;
c=cos(angle);
s=sin(angle);
if (zf==-1.0) { q=s; }
else { q=s/(1.0-zn/zf); }
r.m[0][0]=c;
r.m[1][1]=c;
r.m[2][2]=q;
r.m[2][3]=s;
r.m[3][2]=-q*zn;
r.m[3][3]=0.0;
return(r);
}

mat4 ParallelProj(const float &xl,const float &xr,const float &yb,const float &yt,const float &zn,const float &zf)
{
mat4 r(1.0);

r.m[0][0]=2.0/(xr-xl);
r.m[1][1]=2.0/(yt-yb);
if (zf==-1.0) { r.m[2][2]=0.0; }
else { r.m[2][2]=1.0/(zf-zn); }
r.m[3][0]=-xl*r.m[0][0]-1.0;
r.m[3][1]=-yb*r.m[1][1]-1.0;
r.m[3][2]=-zn*r.m[2][2];
return(r);
}

#endif
