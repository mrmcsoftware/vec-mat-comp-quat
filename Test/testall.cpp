/*********************************************************
   Simple program to test all functions of all classes.
   (Some things not tested here because they are tested in
    other test programs.)
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

#define EPSILONCOMP .00003

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

int main(int argc,char *argv[])
{
int i;
quat q1(1.0,2.0,3.5,4.0);
quat q2(vec3(3.0,2.0,1.0));
quat q3(2.0,3.5,4.0,5.0);
quat q4(1.0,0.0,0.0,0.0);
vec3 v1(0.0,0.0,1.0),v2;
vec3 qaxis(1.0,0.0,0.0);
vec3 qpt(1.0,2.0,3.0),qpt2;

printf("--------  comp  --\n");
float arr2[2]={5.0,6.5};
comp carr(arr2);
cout << "carr: " << carr << endl;
cout << "4.0+carr: " << 4.0+carr << endl;
cout << "carr+4.0: " << carr+4.0 << endl;
cout << "4.0-carr: " << 4.0-carr << endl;
cout << "carr-4.0: " << carr-4.0 << endl;
cout << "carr+=4.0: " << (carr+=4.0) << endl;
cout << "carr-=4.0: " << (carr-=4.0) << endl;
printf("--------  quat  --\n");
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
quat q8(vec3(q1.yaw(),q1.pitch(),q1.roll()));
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
cout << "q1 dot q1: " << q1.dot() << endl;
quat q6(4.0,3.0,2.0,1.0);
cout << "***** q1: " << q1 << " q6: " << q6 << endl;
cout << "q1 dot q6: " << q1.dot(q6) << endl;
cout << "q1 []'s: " << q1[0] << "," << q1[1] << "," << q1[2] << "," << q1[3] << endl;
q1[0]=q1[0]*2.0; q1[1]*=3.0; q1[2]=q1[2]*4.0; q1[3]*=5.0;
cout << "q1 []'s * (2,3,4,5): " << q1 << endl;
quat qvars[6];
for (i=0;i<6;i++) { qvars[i][0]=(float)(i)*1.5; qvars[i][1]=(float)(i)*2.0; qvars[i][2]=(float)(i)*2.5; qvars[i][3]=(float)(i)*3.0; }
//for (i=0;i<6;i++) { qvars[i]=quat((float)(i)*1.5,(float)(i)*2.0,(float)(i)*2.5,(float)(i)*3.0); }
cout << "qvars[0]: " << qvars[0] <<" ("<< qvars[0][0] <<","<<qvars[0][1]<<","<<qvars[0][2]<<","<<qvars[0][3]<<")"<<endl;
cout << "qvars[1]: " << qvars[1] <<" ("<< qvars[1][0] <<","<<qvars[1][1]<<","<<qvars[1][2]<<","<<qvars[1][3]<<")"<<endl;
cout << "qvars[2]: " << qvars[2] <<" ("<< qvars[2][0] <<","<<qvars[2][1]<<","<<qvars[2][2]<<","<<qvars[2][3]<<")"<<endl;
cout << "qvars[3]: " << qvars[3] <<" ("<< qvars[3][0] <<","<<qvars[3][1]<<","<<qvars[3][2]<<","<<qvars[3][3]<<")"<<endl;
cout << "qvars[4]: " << qvars[4] <<" ("<< qvars[4][0] <<","<<qvars[4][1]<<","<<qvars[4][2]<<","<<qvars[4][3]<<")"<<endl;
cout << "qvars[5]: " << qvars[5] <<" ("<< qvars[5][0] <<","<<qvars[5][1]<<","<<qvars[5][2]<<","<<qvars[5][3]<<")"<<endl;
cout << "***** q1: " << q1 << " q6: " << q6 << endl;
cout << "q1+q6: " << q1+q6 << endl;
cout << "q1-q6: " << q1-q6 << endl;
cout << "q1*q6: " << q1*q6 << endl;
cout << "cross(q1,q6): " << cross(q1,q6) << endl;
cout << "q1/q6: " << q1/q6 << endl;
cout << "-q1: " << -q1 << endl;
cout << "3.0*q1: " << 3.0*q1 << endl;
cout << "q1*3.0: " << q1*3.0 << endl;
vec3 v5(1.2,2.3,3.4);
cout << "q1*vec3(1.2,2.3,3.4): " << q1*v5 << endl;
cout << "q1/2.0: " << q1/2.0 << endl;
cout << "q1+=q6: " << (q1+=q6) << endl;
cout << "q1-=q6: " << (q1-=q6) << endl;
cout << "q1*=q6: " << (q1*=q6) << endl;
cout << "q1/=q6: " << (q1/=q6) << endl;
cout << "q1*=2.0: " << (q1*=2.0) << endl;
cout << "q1/=2.0: " << (q1/=2.0) << endl;
cout << "***** q1: " << q1 << " q6: " << q6 << endl;
cout << "q1 equals (1,2,3.5,4)?: " << (q1==quat(1.0,2.0,3.5,4.0)) << endl;
cout << "q1 notequals (1,2,3.5,4)?: " << (q1!=quat(1.0,2.0,3.5,4.0)) << endl;
cout << "q1 equals (2,6,14,20)?: " << (q1==quat(2.0,6.0,14.0,20.0)) << endl;
cout << "q1 notequals (2,6,14,20)?: " << (q1!=quat(2.0,6.0,14.0,20.0)) << endl;
printf("--------  vec4  --\n");
//float arr4[4]={5.0,6.5,7.2,8.3};
vec4 v4arr(arr4);
cout << "v4arr: " << v4arr << endl;
cout << "4.0+v4arr: " << 4.0+v4arr << endl;
cout << "v4arr+4.0: " << v4arr+4.0 << endl;
cout << "4.0-v4arr: " << 4.0-v4arr << endl;
cout << "v4arr-4.0: " << v4arr-4.0 << endl;
vec4 v4a(1.0,2.0,3.5,4.0);
vec4 v4b(4.0,3.0,2.0,1.0);
cout << "***** v4a: " << v4a << " v4b: " << v4b << endl;
cout << "v4a.xy(): " << v4a.xy() << endl;
cout << "v4a.xyz(): " << v4a.xyz() << endl;
cout << "v4a dot v4a: " << v4a.dot() << endl;
cout << "v4a dot v4b: " << v4a.dot(v4b) << endl;
cout << "v4a length: " << v4a.length() << endl;
cout << "v4a normalized: " << v4a.normalized() << " v4a: " << v4a << endl;
cout << "v4a normalized (mag): " << v4a.normalize() << " v4a: " << v4a << endl;
v4a=vec4(1.0,2.0,3.5,4.0);
cout << "reset and v4a []'s: " << v4a[0] << "," << v4a[1] << "," << v4a[2] << "," << v4a[3] << endl;
v4a[0]=v4a[0]*2.0; v4a[1]*=3.0; v4a[2]=v4a[2]*4.0; v4a[3]*=5.0;
cout << "v4a []'s * (2,3,4,5): " << v4a << " and reset" << endl;
v4a=vec4(1.0,2.0,3.5,4.0);
cout << "v4a+v4b: " << v4a+v4b << endl;
cout << "v4a-v4b: " << v4a-v4b << endl;
cout << "v4a*v4b: " << v4a*v4b << endl;
cout << "v4a/v4b: " << v4a/v4b << endl;
cout << "-v4a: " << -v4a << endl;
cout << "v4a+4.0: " << v4a+4.0 << endl;
cout << "v4a-4.0: " << v4a-4.0 << endl;
cout << "v4a*4.0: " << v4a*4.0 << endl;
cout << "4.0*v4a: " << 4.0*v4a << endl;
cout << "v4a/4.0: " << v4a/4.0 << endl;
cout << "v4a+=v4b: " << (v4a+=v4b) << endl;
cout << "v4a-=v4b: " << (v4a-=v4b) << endl;
cout << "v4a*=v4b: " << (v4a*=v4b) << endl;
cout << "v4a/=v4b: " << (v4a/=v4b) << endl;
cout << "v4a*=4.0: " << (v4a*=4.0) << endl;
cout << "v4a/=4.0: " << (v4a/=4.0) << endl;
cout << "v4a+=4.0: " << (v4a+=4.0) << endl;
cout << "v4a-=4.0: " << (v4a-=4.0) << endl;
cout << "v4a++: " << (v4a++) << " v4a: " << v4a << endl;
cout << "v4a--: " << (v4a--) << " v4a: " << v4a << endl;
cout << "++v4a: " << (++v4a) << " v4a: " << v4a << endl;
cout << "--v4a: " << (--v4a) << " v4a: " << v4a << endl;
printf("--------  vec3  --\n");
float arr3[3]={5.0,6.5,7.2};
vec3 v3arr(arr3);
cout << "v3arr: " << v3arr << endl;
cout << "4.0+v3arr: " << 4.0+v3arr << endl;
cout << "v3arr+4.0: " << v3arr+4.0 << endl;
cout << "4.0-v3arr: " << 4.0-v3arr << endl;
cout << "v3arr-4.0: " << v3arr-4.0 << endl;
vec3 v3a(1.0,2.0,3.5);
vec3 v3b(4.0,3.0,2.0);
cout << "***** v3a: " << v3a << " v3b: " << v3b << endl;
cout << "v3a.xy(): " << v3a.xy() << endl;
cout << "v3a dot v3a: " << v3a.dot() << endl;
cout << "v3a dot v3b: " << v3a.dot(v3b) << endl;
cout << "v3a cross v3b: " << v3a.cross(v3b) << endl;
cout << "v3a length: " << v3a.length() << endl;
cout << "v3a normalized: " << v3a.normalized() << " v3a: " << v3a << endl;
cout << "v3a normalized (mag): " << v3a.normalize() << " v3a: " << v3a << endl;
v3a=vec3(1.0,2.0,3.5);
//cout << "4th element: " << v3a[3] << endl; // this will cause abort
cout << "reset and v3a []'s: " << v3a[0] << "," << v3a[1] << "," << v3a[2] << endl;
v3a[0]=v3a[0]*2.0; v3a[1]*=3.0; v3a[2]=v3a[2]*4.0;
cout << "v3a []'s * (2,3,4): " << v3a << " and reset" << endl;
v3a=vec3(1.0,2.0,3.5);
cout << "v3a+v3b: " << v3a+v3b << endl;
cout << "v3a-v3b: " << v3a-v3b << endl;
cout << "v3a*v3b: " << v3a*v3b << endl;
cout << "v3a/v3b: " << v3a/v3b << endl;
cout << "-v3a: " << -v3a << endl;
cout << "v3a+4.0: " << v3a+4.0 << endl;
cout << "v3a-4.0: " << v3a-4.0 << endl;
cout << "v3a*4.0: " << v3a*4.0 << endl;
cout << "4.0*v3a: " << 4.0*v3a << endl;
cout << "v3a/4.0: " << v3a/4.0 << endl;
cout << "v3a+=v3b: " << (v3a+=v3b) << endl;
cout << "v3a-=v3b: " << (v3a-=v3b) << endl;
cout << "v3a*=v3b: " << (v3a*=v3b) << endl;
cout << "v3a/=v3b: " << (v3a/=v3b) << endl;
cout << "v3a*=4.0: " << (v3a*=4.0) << endl;
cout << "v3a/=4.0: " << (v3a/=4.0) << endl;
cout << "v3a+=4.0: " << (v3a+=4.0) << endl;
cout << "v3a-=4.0: " << (v3a-=4.0) << endl;
cout << "v3a++: " << (v3a++) << " v3a: " << v3a << endl;
cout << "v3a--: " << (v3a--) << " v3a: " << v3a << endl;
cout << "++v3a: " << (++v3a) << " v3a: " << v3a << endl;
cout << "--v3a: " << (--v3a) << " v3a: " << v3a << endl;
printf("--------  vec2  --\n");
//float arr2[2]={5.0,6.5};
vec2 v2arr(arr2);
cout << "v2arr: " << v2arr << endl;
cout << "4.0+v2arr: " << 4.0+v2arr << endl;
cout << "v2arr+4.0: " << v2arr+4.0 << endl;
cout << "4.0-v2arr: " << 4.0-v2arr << endl;
cout << "v2arr-4.0: " << v2arr-4.0 << endl;
vec2 v2a(1.0,2.0);
vec2 v2b(4.0,3.0);
cout << "***** v2a: " << v2a << " v2b: " << v2b << endl;
cout << "v2a dot v2a: " << v2a.dot() << endl;
cout << "v2a dot v2b: " << v2a.dot(v2b) << endl;
cout << "v2a length: " << v2a.length() << endl;
cout << "v2a normalized: " << v2a.normalized() << " v2a: " << v2a << endl;
cout << "v2a normalized (mag): " << v2a.normalize() << " v2a: " << v2a << endl;
v2a=vec2(1.0,2.0);
cout << "reset and v2a []'s: " << v2a[0] << "," << v2a[1] << endl;
v2a[0]=v2a[0]*2.0; v2a[1]*=3.0;
cout << "v2a []'s * (2,3): " << v2a << " and reset" << endl;
v2a=vec2(1.0,2.0);
cout << "v2a+v2b: " << v2a+v2b << endl;
cout << "v2a-v2b: " << v2a-v2b << endl;
cout << "v2a*v2b: " << v2a*v2b << endl;
cout << "v2a/v2b: " << v2a/v2b << endl;
cout << "-v2a: " << -v2a << endl;
cout << "v2a+4.0: " << v2a+4.0 << endl;
cout << "v2a-4.0: " << v2a-4.0 << endl;
cout << "v2a*4.0: " << v2a*4.0 << endl;
cout << "4.0*v2a: " << 4.0*v2a << endl;
cout << "v2a/4.0: " << v2a/4.0 << endl;
cout << "v2a+=v2b: " << (v2a+=v2b) << endl;
cout << "v2a-=v2b: " << (v2a-=v2b) << endl;
cout << "v2a*=v2b: " << (v2a*=v2b) << endl;
cout << "v2a/=v2b: " << (v2a/=v2b) << endl;
cout << "v2a*=4.0: " << (v2a*=4.0) << endl;
cout << "v2a/=4.0: " << (v2a/=4.0) << endl;
cout << "v2a+=4.0: " << (v2a+=4.0) << endl;
cout << "v2a-=4.0: " << (v2a-=4.0) << endl;
cout << "v2a++: " << (v2a++) << " v2a: " << v2a << endl;
cout << "v2a--: " << (v2a--) << " v2a: " << v2a << endl;
cout << "++v2a: " << (++v2a) << " v2a: " << v2a << endl;
cout << "--v2a: " << (--v2a) << " v2a: " << v2a << endl;
printf("--------  mat2  --\n");
mat2 m2a(1.0,2.0,3.5,4.0);
mat2 m2b(4.1,3.2,2.0,1.0);
cout << "m2a: ";
cout << m2a;
cout << "m2b: " << endl;
m2b.print();
cout << "m2a transpose: ";
cout << m2a.transpose();
cout << "m2a determinant: " << m2a.determinant() << endl;
cout << "m2a inverse: " << endl;
m2a.inverse().print();
cout << "m2a+m2b: ";
cout << (m2a+m2b);
cout << "m2a-m2b: ";
cout << (m2a-m2b);
cout << "-m2a: ";
cout << (-m2a);
vec2 v6(3.4,2.6);
cout << "m2a*vec2(3.4,2.6): " << (m2a*v6) << endl;
cout << "vec2(3.4,2.6)*m2a: " << (v6*m2a) << endl;
cout << "m2a*4.0: ";
cout << (m2a*4.0);
cout << "4.0*m2a: ";
cout << (4.0f*m2a);
cout << "m2a*m2b: ";
cout << (m2a*m2b);
cout << "m2a/4.0: ";
cout << (m2a/4.0);
cout << "m2a/m2b: ";
cout << (m2a/m2b);
cout << "m2a+=m2b: ";
cout << (m2a+=m2b);
cout << "m2a-=m2b: ";
cout << (m2a-=m2b);
cout << "m2a*=m2b: ";
cout << (m2a*=m2b);
cout << "m2a/=m2b: ";
cout << (m2a/=m2b);
cout << "m2a*=4.0: ";
cout << (m2a*=4.0);
cout << "m2a/=4.0: ";
cout << (m2a/=4.0);
cout << "m2a equals (1,2)?: " << (m2a==mat2(1.0,2.0)) << endl;
cout << "m2a notequals (1,2)?: " << (m2a!=mat2(1.0,2.0)) << endl;
cout << "m2a equals (2,6)?: " << (m2a==mat2(2.0,6.0)) << endl;
cout << "m2a notequals (2,6)?: " << (m2a!=mat2(2.0,6.0)) << endl;
printf("--------  mat3  --\n");
mat3 m3a(1.0,2.0,3.5,4.0,5.0,6.0,7.5,8.0,9.0);
mat3 m3b(4.1,3.2,2.0,1.0,7.0,8.0,9.0,2.0,3.0);
cout << "m3a: ";
cout << m3a;
cout << "m3b: " << endl;
m3b.print();
cout << "m3a transpose: ";
cout << m3a.transpose();
cout << "m3a determinant: " << m3a.determinant() << endl;
cout << "m3a inverse: " << endl;
m3a.inverse().print();
cout << "m3a+m3b: ";
cout << (m3a+m3b);
cout << "m3a-m3b: ";
cout << (m3a-m3b);
cout << "-m3a: ";
cout << (-m3a);
vec3 v7(3.4,2.6,4.2);
cout << "m3a*vec3(3.4,2.6,4.2): " << (m3a*v7) << endl;
cout << "vec3(3.4,2.6,4.2)*m3a: " << (v7*m3a) << endl;
cout << "m3a*4.0: ";
cout << (m3a*4.0);
cout << "4.0*m3a: ";
cout << (4.0f*m3a);
cout << "m3a*m3b: ";
cout << (m3a*m3b);
cout << "m3a/4.0: ";
cout << (m3a/4.0);
cout << "m3a/m3b: ";
cout << (m3a/m3b);
cout << "m3a+=m3b: ";
cout << (m3a+=m3b);
cout << "m3a-=m3b: ";
cout << (m3a-=m3b);
cout << "m3a*=m3b: ";
cout << (m3a*=m3b);
cout << "m3a/=m3b: ";
cout << (m3a/=m3b);
cout << "m3a*=4.0: ";
cout << (m3a*=4.0);
cout << "m3a/=4.0: ";
cout << (m3a/=4.0);
cout << "m3a equals (1,2,3.5,...)?: " << (m3a==mat3(1.0,2.0,3.5,4.0,5.0,6.0,7.5,8.0,9.0)) << endl;
cout << "m3a notequals (1,2,3.5,...)?: " << (m3a!=mat3(1.0,2.0,3.5,4.0,5.0,6.0,7.5,8.0,9.0)) << endl;
cout << "m3a equals (2,6,14,...)?: " << (m3a==mat3(2.0,6.0,14.0,4.0,5.0,6.0,7.5,8.0,9.0)) << endl;
cout << "m3a notequals (2,6,14,...)?: " << (m3a!=mat3(2.0,6.0,14.0,4.0,5.0,6.0,7.5,8.0,9.0)) << endl;
printf("--------  mat4  --\n");
mat4 m4a(1.0,2.0,3.5,4.0,5.0,6.0,7.5,8.0,9.1,10.2,11.3,12.5,13.6,14.7,15.8,16.5);
mat4 m4b(4.1,3.2,2.0,1.0,7.0,8.0,9.0,2.0,3.0,10.5,11.5,12.0,13.5,14.5,15.5,16.0);
cout << "m4a: ";
cout << m4a;
cout << "m4b: " << endl;
m4b.print();
cout << "m4a transpose: ";
cout << m4a.transpose();
cout << "m4a determinant: " << m4a.determinant() << endl;
cout << "m4a inverse: " << endl;
m4a.inverse().print();
cout << "m4a+m4b: ";
cout << (m4a+m4b);
cout << "m4a-m4b: ";
cout << (m4a-m4b);
cout << "-m4a: ";
cout << (-m4a);
vec4 v3(3.4,2.6,4.2,1.3);
cout << "m4a*vec4(3.4,2.6,4.2,1.3): " << (m4a*v3) << endl;
cout << "vec4(3.4,2.6,4.2,1.3)*m4a: " << (v3*m4a) << endl;
cout << "m4a*4.0: ";
cout << (m4a*4.0);
cout << "4.0*m4a: ";
cout << (4.0f*m4a);
cout << "m4a*m4b: ";
cout << (m4a*m4b);
cout << "m4a/4.0: ";
cout << (m4a/4.0);
cout << "m4a/m4b: ";
cout << (m4a/m4b);
cout << "m4a+=m4b: ";
cout << (m4a+=m4b);
cout << "m4a-=m4b: ";
cout << (m4a-=m4b);
cout << "m4a*=m4b: ";
cout << (m4a*=m4b);
cout << "m4a/=m4b: ";
cout << (m4a/=m4b);
cout << "m4a*=4.0: ";
cout << (m4a*=4.0);
cout << "m4a/=4.0: ";
cout << (m4a/=4.0);
cout << "m4a equals (1,2,3.5,...)?: " << (m4a==mat4(1.0,2.0,3.5,4.0,5.0,6.0,7.5,8.0,9.1,10.2,11.3,12.5,13.6,14.7,15.8,16.5)) << endl;
cout << "m4a notequals (1,2,3.5,...)?: " << (m4a!=mat4(1.0,2.0,3.5,4.0,5.0,6.0,7.5,8.0,9.1,10.2,11.3,12.5,13.6,14.7,15.8,16.5)) << endl;
cout << "m4a equals (2,6,14,...)?: " << (m4a==mat4(2.0,6.0,14.0,4.0,5.0,6.0,7.5,8.0,9.0,10.0,11.0,12.5,13.0,14.0,15.0,16.5)) << endl;
cout << "m4a notequals (2,6,14,...)?: " << (m4a!=mat4(2.0,6.0,14.0,4.0,5.0,6.0,7.5,8.0,9.0,10.0,11.0,12.5,13.0,14.0,15.0,16.5)) << endl;
return(0);
}
