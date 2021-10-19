/*********************************************************
   Simple program to test various functions of the
   quaternion number class.
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

int main(int argc,char *argv[])
{
quat q1(1.0,2.0,3.5,4.0);
//quat q1(.7071,.7071,0.0,0.0);
quat q2(vec3(3.0,2.0,1.0));
quat q3(2.0,3.5,4.0,5.0);
quat q4(1.0,0.0,0.0,0.0);
vec3 v1(0.0,0.0,1.0),v2;
vec3 qaxis(1.0,0.0,0.0);
vec3 qpt(1.0,2.0,3.0),qpt2;
quat q6(2.3,vec3(.123,.456,.789));
quat q9(5.2);

float arr4[4]={5.0,6.5,7.2,8.3};
quat qarr(arr4);
cout << "qarr: " << qarr << endl;
quat qr=rotate(q4,(float)(deg2rad(90.0)),qaxis);
quat qr2=rotate(q4,(float)(deg2rad(180.0)),qaxis);
cout << "qr: " << qr << endl;
vec3 q2axis;
float q2theta;
Quat2AxisAngle(qr,q2axis,q2theta);
cout << "q2axis: " << q2axis << " q2theta: " << q2theta << endl;
quat q0=slerp(qr,qr2,.5);
cout << "slerp(qr,qr2): " << q0 << endl;
quat q7=lerp(qr,qr2,.5);
cout << "lerp(qr,qr2): " << q7 << endl;
quat q5=mix(qr,qr2,.5);
cout << "mix(qr,qr2): " << q5 << endl;
Quat2AxisAngle(q0,q2axis,q2theta);
cout << "slerp q2axis: " << q2axis << " q2theta: " << q2theta << endl;
quat qpt3=qr*quat(0.0,qpt.x,qpt.y,qpt.z)*qr.conjugate();
vec3 rr(qpt3.x,qpt3.y,qpt3.z);
cout << "rot0: " << rr << endl;
qpt2=rotatept(qpt,(float)(deg2rad(90.0)),qaxis);
cout << "rot: " << qpt2 << endl;
qr2=rotate(qr,(float)(deg2rad(90.0)),qaxis);
cout << "qr2: " << qr2 << endl;
quat qpt3n=qr2*quat(0.0,qpt.x,qpt.y,qpt.z)*qr2.conjugate();
vec3 rr2(qpt3n.x,qpt3n.y,qpt3n.z);
cout << "rot2: " << rr2 << endl;
v2=cross(q3,v1);
cout << "cross: " << v2 << endl;
cout << "quatofcross: " << quat(v2) << endl;
v2=cross(v1,q3);
cout << "cross: " << v2 << endl;
cout << "quatofcross: " << quat(v2) << endl;
cout << "q1: " << q1 << endl;
q1.normalize();
cout << "q1 norm: " << q1 << endl;
printf("R quat->euler yaw=%f pitch=%f roll=%f\n",q1.yaw(),q1.pitch(),q1.roll());
printf("D quat->euler yaw=%f pitch=%f roll=%f\n",rad2deg(q1.yaw()),rad2deg(q1.pitch()),rad2deg(q1.roll()));
#if EULER2QUAT_METHOD==0
quat q8(vec3(q1.yaw(),q1.pitch(),q1.roll()));
#elif EULER2QUAT_METHOD==2
quat q8(vec3(q1.yaw(),q1.roll(),q1.pitch()));
#else
quat q8(vec3(q1.roll(),q1.yaw(),q1.pitch()));
#endif
cout << "euler->quat q8: " << q8 << endl;
cout << "euler(1,2,3)->quat (norm) q2: " << q2 << endl;
cout << "1,2,3.5,4 squared: " << q1.square() << endl;
cout << "1,2,3.5,4*2,3,4,5: " << q1*quat(2,3,4,5) << endl;
cout << "conj q1: " << q1.conjugate() << endl;
cout << "inverse q1: " << q1.inverse() << endl;
cout << "norm q1: " << q1.normalized() << endl;
q1=quat(1.0,2.0,3.5,4.0);
cout << "reset q1 back to 1,2,3.5,4): " << q1 << endl;
cout << "mag q1: " << q1.length() << endl;
cout << "q6: " << q6 << endl;
cout << "q9: " << q9 << endl;
mat4 rmat=Quat2Mat4(qr);
cout << "qr to mat4: " << rmat << endl;
mat4 rmat2=Rotate(deg2rad(90.0),0);
cout << "Rotate mat: " << rmat2 << endl;
return(0);
}
