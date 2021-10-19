/*********************************************************
   Simple program to test various matrix functions,
   3d transformation/projection functions, and Euler and
   quaternion rotation functions.
   Copyright © 2021 Mark Craig

   https://www.youtube.com/MrMcSoftware
**********************************************************/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

//#define EULER2QUAT_METHOD 0
//#define EULER2QUAT_METHOD 1
//#define EULER2QUAT_METHOD 2

//#define DONT_SWAP_YAW_PITCH

using std::cout;
using std::endl;

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat2.h"
#include "mat3.h"
#include "mat4.h"
#include "quat.h"
#include "comp.h"

#define _TWOPI 6.283185307179586476925286766559
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define rad2deg(x) (x*180.0/M_PI)
#define deg2rad(x) (x*M_PI/180.0)

#include "matfunc.h"

vec3 yaw(vec3 &v, const float &ang, int axis=1) // axis=2 for T-B angles
{
vec4 v2;
vec4 v1(v,1.0);
mat4 matr=Rotate(deg2rad(ang),axis);
v2=v1*matr;
cout << "yaw(" << ang << "): " << v2.xyz() << endl;
return(v2.xyz());
}

vec3 pitch(vec3 &v, const float &ang, int axis=2) // axis=1 for T-B angles
{
vec4 v2;
vec4 v1(v,1.0);
mat4 matr=Rotate(deg2rad(ang),axis);
v2=v1*matr;
cout << "pitch(" << ang << "): " << v2.xyz() << endl;
return(v2.xyz());
}

vec3 roll(vec3 &v, const float &ang)
{
vec4 v2;
vec4 v1(v,1.0);
mat4 matr=Rotate(deg2rad(ang),0);
v2=v1*matr;
cout << "roll(" << ang << "): " << v2.xyz() << endl;
return(v2.xyz());
}

int main(int argc,char *argv[])
{
vec4 v1c(5.2,1.2,2.3,1.0);
vec4 v2c;
mat4 matr,matrv,matrp,matrt;
vec3 ve(0.0,4.0,12.0);
vec3 va(0.0,0.0,0.0);
vec3 vu(0.0,1.0,0.0);

vec3 tr(1.4,2.5,3.8);
matr=Rotate(deg2rad(90.0),0);
v2c=v1c*matr;
cout << "v2c: " << v2c << endl;
matrt=mat4(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);
matrv=mat4(17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32);
matrt=matrt*matrv;
cout << "matrt: " << endl;
matrt.print();
matrt=mat4(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);
cout << "reset matrt and mult. by .5: " << endl;
matrt*=.5;
matrt.print();
matrt=mat4(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);
matrt*=matrv;
cout << "matrt (should be same as previous calc. matrt): " << endl;
matrt.print();
matrv=View(ve,va,vu);
cout << "view: " << endl;
matrv.print();
matrp=PerspectiveProj(45.0,6.2,11.8);
cout << "pers: " << endl;
matrp.print();
matr=ParallelProj(-1.2,1.3,-2.4,2.5,6.2,11.8);
cout << "para: " << endl;
matr.print();
matr=matrv*matrp;
cout << "view&pers: " << endl;
matr.print();
cout << "v&p coutv: " << matr ;
vec3 pt(1.2,2.0,3.0);
cout << "initial pt: " << pt << endl;
float rolla=65.0;
float pitcha=35.0;
float yawa=23.0;
//rolla=pitcha=yawa=90.0;
#if EULER2QUAT_METHOD==0
pt=roll(pt,rolla);
pt=pitch(pt,pitcha);
pt=yaw(pt,yawa);
cout << "final pt: " << pt << endl;
vec3 euler(deg2rad(yawa),deg2rad(pitcha),deg2rad(rolla));
#elif EULER2QUAT_METHOD==2
pt=roll(pt,rolla);
pt=yaw(pt,yawa);
pt=pitch(pt,pitcha);
cout << "final pt: " << pt << endl;
vec3 euler(deg2rad(yawa),deg2rad(rolla),deg2rad(pitcha));
#else
#ifndef DONT_SWAP_YAW_PITCH
pt=roll(pt,rolla);
pt=yaw(pt,yawa);
pt=pitch(pt,pitcha);
cout << "final pt: " << pt << endl;
vec3 euler(deg2rad(rolla),deg2rad(yawa),deg2rad(pitcha));
#else
pt=roll(pt,rolla);
pt=pitch(pt,pitcha,1);
pt=yaw(pt,yawa,2);
cout << "final pt: " << pt << endl;
vec3 euler(deg2rad(rolla),deg2rad(pitcha),deg2rad(yawa));
#endif
#endif
quat q1(euler);
pt=vec3(1.2,2.0,3.0);
quat P(0.0,pt.x,pt.y,pt.z);
quat qn=q1*P*q1.conjugate();
vec3 pt2(qn.x,qn.y,qn.z);
cout << "result from quats: " << pt2 << endl;
cout << "quat2euler: yaw: " << rad2deg(q1.yaw()) << " pitch: " << rad2deg(q1.pitch()) << " roll: " << rad2deg(q1.roll()) << endl;
return(0);
}
