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

#include "vmcq.h"

using namespace vmcq;

#define _TWOPI 6.283185307179586476925286766559
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define rad2deg(x) (x*180.0/M_PI)
#define deg2rad(x) (x*M_PI/180.0)

#ifdef VMCQ_NEEDMAX
#define C(a,b) (fabs(a-(b))<=.00006*((fabs(a)>fabs(b))?fabs(a):fabs(b)))
#else
#define C(a,b) (fabs(a-(b))<=.00006*std::max(fabs(a),fabs(b)))
#endif

#define PF passfail[p]++; cout << pf[p];

int main(int argc,char *argv[])
{
int i,passfail[2]={0,0},p;
char pf[2][16]={"   Fail\n","   Pass\n"};
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
cout << "carr: " << carr;
p=(C(carr.r,5.0)&&C(carr.i,6.5)); PF
cout << "4.0+carr: " << 4.0+carr;
comp ctemp=4.0+carr; p=(C(ctemp.r,9.0)&&C(ctemp.i,6.5)); PF
cout << "carr+4.0: " << carr+4.0;
ctemp=carr+4.0; p=(C(ctemp.r,9.0)&&C(ctemp.i,6.5)); PF
cout << "4.0-carr: " << 4.0-carr;
ctemp=4.0-carr; p=(C(ctemp.r,-1.0)&&C(ctemp.i,-6.5)); PF
cout << "carr-4.0: " << carr-4.0;
ctemp=carr-4.0; p=(C(ctemp.r,1.0)&&C(ctemp.i,6.5)); PF
cout << "carr+=4.0: " << (carr+=4.0);
p=(C(carr.r,9.0)&&C(carr.i,6.5)); PF;
cout << "carr-=4.0: " << (carr-=4.0);
p=(C(carr.r,5.0)&&C(carr.i,6.5)); PF;
printf("--------  quat  --\n");
float arr4[4]={5.0,6.5,7.2,8.3};
quat qarr(arr4);
cout << "qarr: " << qarr;
p=(C(qarr.w,5.0)&&(qarr.x,6.5)&&C(qarr.y,7.2)&&C(qarr.z,8.3)); PF
quat qr=rotate(q4,(float)(deg2rad(90.0)),qaxis);
quat qr2=rotate(q4,(float)(deg2rad(180.0)),qaxis);
cout << "qr: " << qr;
p=(C(qr.w,.707107)&&C(qr.x,.707107)&&C(qr.y,0.0)&&C(qr.z,0.0)); PF
vec3 q2axis;
float q2theta;
Quat2AxisAngle(qr,q2axis,q2theta);
cout << "q2axis: " << q2axis << " q2theta: " << q2theta;
p=(C(q2axis.x,1.0)&&C(q2axis.y,0.0)&&C(q2axis.z,0.0)&&C(q2theta,1.5708)); PF
quat q0=slerp(qr,qr2,.5);
cout << "slerp(qr,qr2): " << q0;
p=(C(q0.w,.382683)&&C(q0.x,.92388)&&C(q0.y,0.0)&&C(q0.z,0.0)); PF
quat q7=lerp(qr,qr2,.5);
cout << "lerp(qr,qr2): " << q7;
p=(C(q7.w,.353553)&&C(q7.x,.853553)&&C(q7.y,0.0)&&C(q7.z,0.0)); PF
quat q5=mix(qr,qr2,.5);
cout << "mix(qr,qr2): " << q5;
p=(C(q5.w,.382683)&&C(q5.x,.92388)&&C(q5.y,0.0)&&C(q5.z,0.0)); PF
Quat2AxisAngle(q0,q2axis,q2theta);
cout << "slerp q2axis: " << q2axis << " q2theta: " << q2theta;
p=(C(q2axis.x,1.0)&&C(q2axis.y,0.0)&&C(q2axis.z,0.0)&&C(q2theta,2.35619)); PF
quat qpt3=qr*quat(0.0,qpt.x,qpt.y,qpt.z)*qr.conjugate();
vec3 rr(qpt3.x,qpt3.y,qpt3.z);
cout << "rot0: " << rr;
p=(C(rr.x,1.0)&&C(rr.y,-3.0)&&C(rr.z,2.0)); PF
qpt2=rotatept(qpt,(float)(deg2rad(90.0)),qaxis);
cout << "rot: " << qpt2;
p=(C(qpt2.x,1.0)&&C(qpt2.y,-3.0)&&C(qpt2.z,2.0)); PF
qr2=rotate(qr,(float)(deg2rad(90.0)),qaxis);
cout << "qr2: " << qr2;
p=(C(qr2.w,0.0)&&C(qr2.x,1.0)&&C(qr2.y,0.0)&&C(qr2.z,0.0)); PF
quat qpt3n=qr2*quat(0.0,qpt.x,qpt.y,qpt.z)*qr2.conjugate();
vec3 rr2(qpt3n.x,qpt3n.y,qpt3n.z);
cout << "rot2: " << rr2;
p=(C(rr2.x,1.0)&&C(rr2.y,-2.0)&&C(rr2.z,-3.0)); PF
v2=cross(q3,v1);
cout << "cross: " << v2;
p=(C(v2.x,51.0)&&C(v2.y,26.0)&&C(v2.z,-55.5)); PF
cout << "quatofcross: " << quat(v2);
quat qtemp; qtemp=quat(v2);
p=(C(qtemp.w,-.657626)&&C(qtemp.x,-.554603)&&C(qtemp.y,-.478378)&&C(qtemp.z,-.176346)); PF
v2=cross(v1,q3);
cout << "cross: " << v2;
p=(C(v2.x,.00579699)&&C(v2.y,.0164757)&&C(v2.z,.982762)); PF
cout << "quatofcross: " << quat(v2);
qtemp=quat(v2);
p=(C(qtemp.w,.881637)&&C(qtemp.x,.471847)&&C(qtemp.y,.00644237)&&C(qtemp.z,.00589545)); PF
cout << "q1: " << q1;
p=(C(q1.w,1.0)&&C(q1.x,2.0)&&C(q1.y,3.5)&&C(q1.z,4.0)); PF
q1.normalize();
cout << "q1 norm: " << q1;
p=(C(q1.w,.173422)&&C(q1.x,.346844)&&C(q1.y,.606977)&&C(q1.z,.693688)); PF
printf("R quat->euler yaw=%f pitch=%f roll=%f",q1.yaw(),q1.pitch(),q1.roll());
p=(C(q1.yaw(),-2.772259)&&C(q1.pitch(),.723023)&&C(q1.roll(),-1.844964)); PF
printf("D quat->euler yaw=%f pitch=%f roll=%f",rad2deg(q1.yaw()),rad2deg(q1.pitch()),rad2deg(q1.roll()));
p=(C(rad2deg(q1.yaw()),-158.838740)&&C(rad2deg(q1.pitch()),41.426146)&&C(rad2deg(q1.roll()),-105.708638)); PF
quat q8(vec3(q1.yaw(),q1.pitch(),q1.roll()));
cout << "euler->quat q8: " << q8;
p=(C(q8.w,-.173422)&&C(q8.x,-.346844)&&C(q8.y,-.606977)&&C(q8.z,-.693688)); PF
cout << "euler(1,2,3)->quat (norm) q2: " << q2;
p=(C(q2.w,-.368871)&&C(q2.x,.754934)&&C(q2.y,.501509)&&C(q2.z,-.206149)); PF
cout << "1,2,3.5,4 squared: " << q1.square();
qtemp=q1.square();
p=(C(qtemp.w,-.93985)&&C(qtemp.x,.120301)&&C(qtemp.y,.210526)&&C(qtemp.z,.240602)); PF
cout << "1,2,3.5,4*2,3,4,5: " << q1*quat(2,3,4,5);
qtemp=q1*quat(2,3,4,5);
p=(C(qtemp.w,-6.59004)&&C(qtemp.x,1.47409)&&C(qtemp.y,2.25449)&&C(qtemp.z,1.82093)); PF
cout << "conj q1: " << q1.conjugate();
qtemp=q1.conjugate();
p=(C(qtemp.w,.173422)&&C(qtemp.x,-.346844)&&C(qtemp.y,-.606977)&&C(qtemp.z,-.693688)); PF
cout << "inverse q1: " << q1.inverse();
qtemp=q1.inverse();
p=(C(qtemp.w,.173422)&&C(qtemp.x,-.346844)&&C(qtemp.y,-.606977)&&C(qtemp.z,-.693688)); PF
cout << "norm q1: " << q1.normalized();
qtemp=q1.normalized();
p=(C(qtemp.w,.173422)&&C(qtemp.x,.346844)&&C(qtemp.y,.606977)&&C(qtemp.z,.693688)); PF
q1=quat(1.0,2.0,3.5,4.0);
cout << "reset q1 back to 1,2,3.5,4): " << q1;
p=(C(q1.w,1.0)&&C(q1.x,2.0)&&(q1.y,3.5)&&C(q1.z,4.0)); PF
cout << "mag q1: " << q1.length();
p=C(q1.length(),5.76628); PF
cout << "q1 dot q1: " << q1.dot();
p=C(q1.dot(),33.25); PF
quat q6(4.0,3.0,2.0,1.0);
cout << "***** q1: " << q1 << " q6: " << q6 << endl;
cout << "q1 dot q6: " << q1.dot(q6);
p=C(q1.dot(q6),21.0); PF
cout << "q1 []'s: " << q1[0] << "," << q1[1] << "," << q1[2] << "," << q1[3];
p=(C(q1[0],1.0)&&C(q1[1],2.0)&&C(q1[2],3.5)&&C(q1[3],4.0)); PF
q1[0]=q1[0]*2.0; q1[1]*=3.0; q1[2]=q1[2]*4.0; q1[3]*=5.0;
cout << "q1 []'s * (2,3,4,5): " << q1;
p=(C(q1.w,2.0)&&C(q1.x,6.0)&&C(q1.y,14.0)&&C(q1.z,20.0)); PF
quat qvars[6];
for (i=0;i<6;i++) { qvars[i][0]=(float)(i)*1.5; qvars[i][1]=(float)(i)*2.0; qvars[i][2]=(float)(i)*2.5; qvars[i][3]=(float)(i)*3.0; }
//for (i=0;i<6;i++) { qvars[i]=quat((float)(i)*1.5,(float)(i)*2.0,(float)(i)*2.5,(float)(i)*3.0); }
cout << "qvars[0]: " << qvars[0] <<" ("<< qvars[0][0] <<","<<qvars[0][1]<<","<<qvars[0][2]<<","<<qvars[0][3]<<")";
p=(C(qvars[0].w,0.0)&&C(qvars[0].x,0.0)&&C(qvars[0].y,0.0)&&C(qvars[0].z,0.0)&&C(qvars[0][0],0.0)&&C(qvars[0][1],0.0)&&C(qvars[0][2],0.0)&&C(qvars[0][3],0.0)); PF
cout << "qvars[1]: " << qvars[1] <<" ("<< qvars[1][0] <<","<<qvars[1][1]<<","<<qvars[1][2]<<","<<qvars[1][3]<<")";
p=(C(qvars[1].w,1.5)&&C(qvars[1].x,2.0)&&C(qvars[1].y,2.5)&&C(qvars[1].z,3.0)&&C(qvars[1][0],1.5)&&C(qvars[1][1],2.0)&&C(qvars[1][2],2.5)&&C(qvars[1][3],3.0)); PF
cout << "qvars[2]: " << qvars[2] <<" ("<< qvars[2][0] <<","<<qvars[2][1]<<","<<qvars[2][2]<<","<<qvars[2][3]<<")";
p=(C(qvars[2].w,3.0)&&C(qvars[2].x,4.0)&&C(qvars[2].y,5.0)&&C(qvars[2].z,6.0)&&C(qvars[2][0],3.0)&&C(qvars[2][1],4.0)&&C(qvars[2][2],5.0)&&C(qvars[2][3],6.0)); PF
cout << "qvars[3]: " << qvars[3] <<" ("<< qvars[3][0] <<","<<qvars[3][1]<<","<<qvars[3][2]<<","<<qvars[3][3]<<")";
p=(C(qvars[3].w,4.5)&&C(qvars[3].x,6.0)&&C(qvars[3].y,7.5)&&C(qvars[3].z,9.0)&&C(qvars[3][0],4.5)&&C(qvars[3][1],6.0)&&C(qvars[3][2],7.5)&&C(qvars[3][3],9.0)); PF
cout << "qvars[4]: " << qvars[4] <<" ("<< qvars[4][0] <<","<<qvars[4][1]<<","<<qvars[4][2]<<","<<qvars[4][3]<<")";
p=(C(qvars[4].w,6.0)&&C(qvars[4].x,8.0)&&C(qvars[4].y,10.0)&&C(qvars[4].z,12.0)&&C(qvars[4][0],6.0)&&C(qvars[4][1],8.0)&&C(qvars[4][2],10.0)&&C(qvars[4][3],12.0)); PF
cout << "qvars[5]: " << qvars[5] <<" ("<< qvars[5][0] <<","<<qvars[5][1]<<","<<qvars[5][2]<<","<<qvars[5][3]<<")";
p=(C(qvars[5].w,7.5)&&C(qvars[5].x,10.0)&&C(qvars[5].y,12.5)&&C(qvars[5].z,15.0)&&C(qvars[5][0],7.5)&&C(qvars[5][1],10.0)&&C(qvars[5][2],12.5)&&C(qvars[5][3],15.0)); PF
cout << "***** q1: " << q1 << " q6: " << q6 << endl;
cout << "q1+q6: " << q1+q6;
qtemp=q1+q6;
p=(C(qtemp.w,6.0)&&C(qtemp.x,9.0)&&C(qtemp.y,16.0)&&C(qtemp.z,21.0)); PF
cout << "q1-q6: " << q1-q6;
qtemp=q1-q6;
p=(C(qtemp.w,-2.0)&&C(qtemp.x,3.0)&&C(qtemp.y,12.0)&&C(qtemp.z,19.0)); PF
cout << "q1*q6: " << q1*q6;
qtemp=q1*q6;
p=(C(qtemp.w,-58.0)&&C(qtemp.x,4.0)&&C(qtemp.y,114.0)&&C(qtemp.z,52.0)); PF
cout << "cross(q1,q6): " << cross(q1,q6);
qtemp=cross(q1,q6);
p=(C(qtemp.w,-58.0)&&C(qtemp.x,4.0)&&C(qtemp.y,114.0)&&C(qtemp.z,52.0)); PF
cout << "q1/q6: " << q1/q6;
qtemp=q1/q6;
p=(C(qtemp.w,2.46667)&&C(qtemp.x,1.46667)&&C(qtemp.y,-.0666666)&&C(qtemp.z,3.6)); PF
cout << "-q1: " << -q1;
qtemp=-q1;
p=(C(qtemp.w,-2.0)&&C(qtemp.x,-6.0)&&C(qtemp.y,-14.0)&&C(qtemp.z,-20.0)); PF
cout << "3.0*q1: " << 3.0*q1;
qtemp=3.0*q1;
p=(C(qtemp.w,6.0)&&C(qtemp.x,18.0)&&C(qtemp.y,42.0)&&C(qtemp.z,60.0)); PF
cout << "q1*3.0: " << q1*3.0;
qtemp=q1*3.0;
p=(C(qtemp.w,6.0)&&C(qtemp.x,18.0)&&C(qtemp.y,42.0)&&C(qtemp.z,60.0)); PF
vec3 v5(1.2,2.3,3.4);
cout << "q1*vec3(1.2,2.3,3.4): " << q1*v5;
vec3 v3temp; v3temp=q1*v5;
p=(C(v3temp.x,-220.4)&&C(v3temp.y,116.7)&&C(v3temp.z,-10.2001)); PF
cout << "q1/2.0: " << q1/2.0;
qtemp=q1/2.0;
p=(C(qtemp.w,1.0)&&C(qtemp.x,3.0)&&C(qtemp.y,7.0)&&C(qtemp.z,10.0)); PF
cout << "q1+=q6: " << (q1+=q6);
p=(C(q1.w,6.0)&&C(q1.x,9.0)&&C(q1.y,16.0)&&C(q1.z,21.0)); PF
cout << "q1-=q6: " << (q1-=q6);
p=(C(q1.w,2.0)&&C(q1.x,6.0)&&C(q1.y,14.0)&&C(q1.z,20.0)); PF
cout << "q1*=q6: " << (q1*=q6);
p=(C(q1.w,-58.0)&&C(q1.x,4.0)&&C(q1.y,114.0)&&C(q1.z,52.0)); PF
cout << "q1/=q6: " << (q1/=q6);
p=(C(q1.w,2.0)&&C(q1.x,6.0)&&C(q1.y,14.0)&&C(q1.z,20.0)); PF
cout << "q1*=2.0: " << (q1*=2.0);
p=(C(q1.w,4.0)&&C(q1.x,12.0)&&C(q1.y,28.0)&&C(q1.z,40.0)); PF
cout << "q1/=2.0: " << (q1/=2.0);
p=(C(q1.w,2.0)&&C(q1.x,6.0)&&C(q1.y,14.0)&&C(q1.z,20.0)); PF
cout << "***** q1: " << q1 << " q6: " << q6 << endl;
cout << "q1 equals (1,2,3.5,4)?: " << (q1==quat(1.0,2.0,3.5,4.0));
p=(q1==quat(1.0,2.0,3.5,4.0)); p=!p; PF
cout << "q1 notequals (1,2,3.5,4)?: " << (q1!=quat(1.0,2.0,3.5,4.0));
p=(q1!=quat(1.0,2.0,3.5,4.0)); PF
cout << "q1 equals (2,6,14,20)?: " << (q1==quat(2.0,6.0,14.0,20.0));
p=(q1==quat(2.0,6.0,14.0,20.0)); PF
cout << "q1 notequals (2,6,14,20)?: " << (q1!=quat(2.0,6.0,14.0,20.0));
p=(q1!=quat(2.0,6.0,14.0,20.0)); p=!p; PF
printf("--------  vec4  --\n");
//float arr4[4]={5.0,6.5,7.2,8.3};
vec4 v4arr(arr4);
cout << "v4arr: " << v4arr;
p=(C(v4arr.x,5.0)&&C(v4arr.y,6.5)&&C(v4arr.z,7.2)&&C(v4arr.w,8.3)); PF
cout << "4.0+v4arr: " << 4.0+v4arr;
vec4 v4temp; v4temp=4.0+v4arr;
p=(C(v4temp.x,9.0)&&C(v4temp.y,10.5)&&C(v4temp.z,11.2)&&C(v4temp.w,12.3)); PF
cout << "v4arr+4.0: " << v4arr+4.0;
v4temp=v4arr+4.0;
p=(C(v4temp.x,9.0)&&C(v4temp.y,10.5)&&C(v4temp.z,11.2)&&C(v4temp.w,12.3)); PF
cout << "4.0-v4arr: " << 4.0-v4arr;
v4temp=4.0-v4arr;
p=(C(v4temp.x,-1.0)&&C(v4temp.y,-2.5)&&C(v4temp.z,-3.2)&&C(v4temp.w,-4.3)); PF
cout << "v4arr-4.0: " << v4arr-4.0;
v4temp=v4arr-4.0;
p=(C(v4temp.x,1.0)&&C(v4temp.y,2.5)&&C(v4temp.z,3.2)&&C(v4temp.w,4.3)); PF
vec4 v4a(1.0,2.0,3.5,4.0);
vec4 v4b(4.0,3.0,2.0,1.0);
cout << "***** v4a: " << v4a << " v4b: " << v4b << endl;
vec2 v2temp;
#ifdef VEC_USE_SWIZZLE
// Some compilers need the next "throwaway" statement to instantiate vec2
//  (since this is the first time vec2 is used in this program)
vec2 throwaway;
cout << "v4a.xy: " << vec2(v4a.xy);
v2temp=v4a.xy;
p=(C(v2temp.x,1.0)&&C(v2temp.y,2.0)); PF
cout << "v4a.xyz: " << vec3(v4a.xyz);
v3temp=v4a.xyz;
p=(C(v3temp.x,1.0)&&C(v3temp.y,2.0)&&C(v3temp.z,3.5)); PF
// or you could do:
/*
cout << "v4a.xy: " << vec2(v4a.xy);
cout << "v4a.xyz: " << vec3(v4a.xyz);
*/
#else
cout << "v4a.xy(): " << v4a.xy();
v2temp=v4a.xy();
p=(C(v2temp.x,1.0)&&C(v2temp.y,2.0)); PF
cout << "v4a.xyz(): " << v4a.xyz();
v3temp=v4a.xyz();
p=(C(v3temp.x,1.0)&&C(v3temp.y,2.0)&&C(v3temp.z,3.5)); PF
#endif
cout << "v4a dot v4a: " << v4a.dot();
p=C(v4a.dot(),33.25); PF
cout << "v4a dot v4b: " << v4a.dot(v4b);
p=C(v4a.dot(v4b),21.0); PF
cout << "v4a length: " << v4a.length();
p=C(v4a.length(),5.76628); PF
cout << "v4a normalized: " << v4a.normalized() << " v4a: " << v4a;
v4temp=v4a.normalized();
p=(C(v4temp.x,.173422)&&C(v4temp.y,.346844)&&C(v4temp.z,.606977)&&C(v4temp.w,.693688)); PF
float v4mag;
v4mag=v4a.normalize();
cout << "v4a normalized (mag): " << v4mag << " v4a: " << v4a;
p=(C(v4mag,5.76628)&&C(v4a.x,.173422)&&C(v4a.y,.346844)&&C(v4a.z,.606977)&&C(v4a.w,.693688)); PF
v4a=vec4(1.0,2.0,3.5,4.0);
cout << "reset and v4a []'s: " << v4a[0] << "," << v4a[1] << "," << v4a[2] << "," << v4a[3];
p=(C(v4a[0],1.0)&&C(v4a[1],2.0)&&C(v4a[2],3.5)&&C(v4a[3],4.0)); PF
v4a[0]=v4a[0]*2.0; v4a[1]*=3.0; v4a[2]=v4a[2]*4.0; v4a[3]*=5.0;
cout << "v4a []'s * (2,3,4,5): " << v4a << " and reset";
p=(C(v4a[0],2.0)&&C(v4a[1],6.0)&&C(v4a[2],14.0)&&C(v4a[3],20.0)); PF
v4a=vec4(1.0,2.0,3.5,4.0);
cout << "v4a+v4b: " << v4a+v4b;
v4temp=v4a+v4b;
p=(C(v4temp.x,5.0)&&C(v4temp.y,5.0)&&C(v4temp.z,5.5)&&C(v4temp.w,5.0)); PF
cout << "v4a-v4b: " << v4a-v4b;
v4temp=v4a-v4b;
p=(C(v4temp.x,-3.0)&&C(v4temp.y,-1.0)&&C(v4temp.z,1.5)&&C(v4temp.w,3.0)); PF
cout << "v4a*v4b: " << v4a*v4b;
v4temp=v4a*v4b;
p=(C(v4temp.x,4.0)&&C(v4temp.y,6.0)&&C(v4temp.z,7.0)&&C(v4temp.w,4.0)); PF
cout << "v4a/v4b: " << v4a/v4b;
v4temp=v4a/v4b;
p=(C(v4temp.x,.25)&&C(v4temp.y,.666667)&&C(v4temp.z,1.75)&&C(v4temp.w,4.0)); PF
cout << "-v4a: " << -v4a;
v4temp=-v4a;
p=(C(v4temp.x,-1.0)&&C(v4temp.y,-2.0)&&C(v4temp.z,-3.5)&&C(v4temp.w,-4.0)); PF
cout << "v4a+4.0: " << v4a+4.0;
v4temp=v4a+4.0;
p=(C(v4temp.x,5.0)&&C(v4temp.y,6.0)&&C(v4temp.z,7.5)&&C(v4temp.w,8.0)); PF
cout << "v4a-4.0: " << v4a-4.0;
v4temp=v4a-4.0;
p=(C(v4temp.x,-3.0)&&C(v4temp.y,-2.0)&&C(v4temp.z,-.5)&&C(v4temp.w,0.0)); PF
cout << "v4a*4.0: " << v4a*4.0;
v4temp=v4a*4.0;
p=(C(v4temp.x,4.0)&&C(v4temp.y,8.0)&&C(v4temp.z,14.0)&&C(v4temp.w,16.0)); PF
cout << "4.0*v4a: " << 4.0*v4a;
v4temp=4.0*v4a;
p=(C(v4temp.x,4.0)&&C(v4temp.y,8.0)&&C(v4temp.z,14.0)&&C(v4temp.w,16.0)); PF
cout << "v4a/4.0: " << v4a/4.0;
v4temp=v4a/4.0;
p=(C(v4temp.x,.25)&&C(v4temp.y,.5)&&C(v4temp.z,.875)&&C(v4temp.w,1.0)); PF
cout << "v4a+=v4b: " << (v4a+=v4b);
p=(C(v4a.x,5.0)&&C(v4a.y,5.0)&&C(v4a.z,5.5)&&C(v4a.w,5.0)); PF
cout << "v4a-=v4b: " << (v4a-=v4b);
p=(C(v4a.x,1.0)&&C(v4a.y,2.0)&&C(v4a.z,3.5)&&C(v4a.w,4.0)); PF
cout << "v4a*=v4b: " << (v4a*=v4b);
p=(C(v4a.x,4.0)&&C(v4a.y,6.0)&&C(v4a.z,7.0)&&C(v4a.w,4.0)); PF
cout << "v4a/=v4b: " << (v4a/=v4b);
p=(C(v4a.x,1.0)&&C(v4a.y,2.0)&&C(v4a.z,3.5)&&C(v4a.w,4.0)); PF
cout << "v4a*=4.0: " << (v4a*=4.0);
p=(C(v4a.x,4.0)&&C(v4a.y,8.0)&&C(v4a.z,14.0)&&C(v4a.w,16.0)); PF
cout << "v4a/=4.0: " << (v4a/=4.0);
p=(C(v4a.x,1.0)&&C(v4a.y,2.0)&&C(v4a.z,3.5)&&C(v4a.w,4.0)); PF
cout << "v4a+=4.0: " << (v4a+=4.0);
p=(C(v4a.x,5.0)&&C(v4a.y,6.0)&&C(v4a.z,7.5)&&C(v4a.w,8.0)); PF
cout << "v4a-=4.0: " << (v4a-=4.0);
p=(C(v4a.x,1.0)&&C(v4a.y,2.0)&&C(v4a.z,3.5)&&C(v4a.w,4.0)); PF
cout << "v4a++: " << (v4a++) << " v4a: " << v4a;
p=(C(v4a.x,2.0)&&C(v4a.y,3.0)&&C(v4a.z,4.5)&&C(v4a.w,5.0)); PF
cout << "v4a--: " << (v4a--) << " v4a: " << v4a;
p=(C(v4a.x,1.0)&&C(v4a.y,2.0)&&C(v4a.z,3.5)&&C(v4a.w,4.0)); PF
cout << "++v4a: " << (++v4a) << " v4a: " << v4a;
p=(C(v4a.x,2.0)&&C(v4a.y,3.0)&&C(v4a.z,4.5)&&C(v4a.w,5.0)); PF
cout << "--v4a: " << (--v4a) << " v4a: " << v4a;
p=(C(v4a.x,1.0)&&C(v4a.y,2.0)&&C(v4a.z,3.5)&&C(v4a.w,4.0)); PF
printf("--------  vec3  --\n");
float arr3[3]={5.0,6.5,7.2};
vec3 v3arr(arr3);
cout << "v3arr: " << v3arr;
p=(C(v3arr.x,5.0)&&C(v3arr.y,6.5)&&C(v3arr.z,7.2)); PF
cout << "4.0+v3arr: " << 4.0+v3arr;
v3temp=4.0+v3arr;
p=(C(v3temp.x,9.0)&&C(v3temp.y,10.5)&&C(v3temp.z,11.2)); PF
cout << "v3arr+4.0: " << v3arr+4.0;
v3temp=v3arr+4.0;
p=(C(v3temp.x,9.0)&&C(v3temp.y,10.5)&&C(v3temp.z,11.2)); PF
cout << "4.0-v3arr: " << 4.0-v3arr;
v3temp=4.0-v3arr;
p=(C(v3temp.x,-1.0)&&C(v3temp.y,-2.5)&&C(v3temp.z,-3.2)); PF
cout << "v3arr-4.0: " << v3arr-4.0;
v3temp=v3arr-4.0;
p=(C(v3temp.x,1.0)&&C(v3temp.y,2.5)&&C(v3temp.z,3.2)); PF
vec3 v3a(1.0,2.0,3.5);
vec3 v3b(4.0,3.0,2.0);
cout << "***** v3a: " << v3a << " v3b: " << v3b << endl;
#ifdef VEC_USE_SWIZZLE
cout << "v3a.xy: " << vec2(v3a.xy);
v2temp=v3a.xy;
p=(C(v2temp.x,1.0)&&C(v2temp.y,2.0)); PF
#else
cout << "v3a.xy(): " << v3a.xy();
v2temp=v3a.xy();
p=(C(v2temp.x,1.0)&&C(v2temp.y,2.0)); PF
#endif
cout << "v3a dot v3a: " << v3a.dot();
p=C(v3a.dot(),17.25); PF
cout << "v3a dot v3b: " << v3a.dot(v3b);
p=C(v3a.dot(v3b),17.0); PF
cout << "v3a cross v3b: " << v3a.cross(v3b);
v3temp=v3a.cross(v3b);
p=(C(v3temp.x,-6.5)&&C(v3temp.y,12.0)&&C(v3temp.z,-5.0)); PF
cout << "v3a length: " << v3a.length();
p=C(v3a.length(),4.15331); PF
cout << "v3a normalized: " << v3a.normalized() << " v3a: " << v3a;
v3temp=v3a.normalized();
p=(C(v3temp.x,.240772)&&C(v3temp.y,.481543)&&C(v3temp.z,.842701)); PF
float v3mag;
v3mag=v3a.normalize();
cout << "v3a normalized (mag): " << v3mag << " v3a: " << v3a;
p=(C(v3mag,4.15331)&&C(v3a.x,.240772)&&C(v3a.y,.481543)&&C(v3a.z,.842701)); PF
v3a=vec3(1.0,2.0,3.5);
//cout << "4th element: " << v3a[3] << endl; // this will cause abort
cout << "reset and v3a []'s: " << v3a[0] << "," << v3a[1] << "," << v3a[2];
p=(C(v3a[0],1.0)&&C(v3a[1],2.0)&&C(v3a[2],3.5)); PF
v3a[0]=v3a[0]*2.0; v3a[1]*=3.0; v3a[2]=v3a[2]*4.0;
cout << "v3a []'s * (2,3,4): " << v3a << " and reset";
p=(C(v3a[0],2.0)&&C(v3a[1],6.0)&&C(v3a[2],14.0)); PF
v3a=vec3(1.0,2.0,3.5);
cout << "v3a+v3b: " << v3a+v3b;
v3temp=v3a+v3b;
p=(C(v3temp.x,5.0)&&C(v3temp.y,5.0)&&C(v3temp.z,5.5)); PF
cout << "v3a-v3b: " << v3a-v3b;
v3temp=v3a-v3b;
p=(C(v3temp.x,-3.0)&&C(v3temp.y,-1.0)&&C(v3temp.z,1.5)); PF
cout << "v3a*v3b: " << v3a*v3b;
v3temp=v3a*v3b;
p=(C(v3temp.x,4.0)&&C(v3temp.y,6.0)&&C(v3temp.z,7.0)); PF
cout << "v3a/v3b: " << v3a/v3b;
v3temp=v3a/v3b;
p=(C(v3temp.x,.25)&&C(v3temp.y,.666667)&&C(v3temp.z,1.75)); PF
cout << "-v3a: " << -v3a;
v3temp=-v3a;
p=(C(v3temp.x,-1.0)&&C(v3temp.y,-2.0)&&C(v3temp.z,-3.5)); PF
cout << "v3a+4.0: " << v3a+4.0;
v3temp=v3a+4.0;
p=(C(v3temp.x,5.0)&&C(v3temp.y,6.0)&&C(v3temp.z,7.5)); PF
cout << "v3a-4.0: " << v3a-4.0;
v3temp=v3a-4.0;
p=(C(v3temp.x,-3.0)&&C(v3temp.y,-2.0)&&C(v3temp.z,-.5)); PF
cout << "v3a*4.0: " << v3a*4.0;
v3temp=v3a*4.0;
p=(C(v3temp.x,4.0)&&C(v3temp.y,8.0)&&C(v3temp.z,14.0)); PF
cout << "4.0*v3a: " << 4.0*v3a;
v3temp=4.0*v3a;
p=(C(v3temp.x,4.0)&&C(v3temp.y,8.0)&&C(v3temp.z,14.0)); PF
cout << "v3a/4.0: " << v3a/4.0;
v3temp=v3a/4.0;
p=(C(v3temp.x,.25)&&C(v3temp.y,.5)&&C(v3temp.z,.875)); PF
cout << "v3a+=v3b: " << (v3a+=v3b);
p=(C(v3a.x,5.0)&&C(v3a.y,5.0)&&C(v3a.z,5.5)); PF
cout << "v3a-=v3b: " << (v3a-=v3b);
p=(C(v3a.x,1.0)&&C(v3a.y,2.0)&&C(v3a.z,3.5)); PF
cout << "v3a*=v3b: " << (v3a*=v3b);
p=(C(v3a.x,4.0)&&C(v3a.y,6.0)&&C(v3a.z,7.0)); PF
cout << "v3a/=v3b: " << (v3a/=v3b);
p=(C(v3a.x,1.0)&&C(v3a.y,2.0)&&C(v3a.z,3.5)); PF
cout << "v3a*=4.0: " << (v3a*=4.0);
p=(C(v3a.x,4.0)&&C(v3a.y,8.0)&&C(v3a.z,14.0)); PF
cout << "v3a/=4.0: " << (v3a/=4.0);
p=(C(v3a.x,1.0)&&C(v3a.y,2.0)&&C(v3a.z,3.5)); PF
cout << "v3a+=4.0: " << (v3a+=4.0);
p=(C(v3a.x,5.0)&&C(v3a.y,6.0)&&C(v3a.z,7.5)); PF
cout << "v3a-=4.0: " << (v3a-=4.0);
p=(C(v3a.x,1.0)&&C(v3a.y,2.0)&&C(v3a.z,3.5)); PF
cout << "v3a++: " << (v3a++) << " v3a: " << v3a;
p=(C(v3a.x,2.0)&&C(v3a.y,3.0)&&C(v3a.z,4.5)); PF
cout << "v3a--: " << (v3a--) << " v3a: " << v3a;
p=(C(v3a.x,1.0)&&C(v3a.y,2.0)&&C(v3a.z,3.5)); PF
cout << "++v3a: " << (++v3a) << " v3a: " << v3a;
p=(C(v3a.x,2.0)&&C(v3a.y,3.0)&&C(v3a.z,4.5)); PF
cout << "--v3a: " << (--v3a) << " v3a: " << v3a;
p=(C(v3a.x,1.0)&&C(v3a.y,2.0)&&C(v3a.z,3.5)); PF
printf("--------  vec2  --\n");
//float arr2[2]={5.0,6.5};
vec2 v2arr(arr2);
cout << "v2arr: " << v2arr;
p=(C(v2arr.x,5.0)&&C(v2arr.y,6.5)); PF
cout << "4.0+v2arr: " << 4.0+v2arr;
v2temp=4.0+v2arr;
p=(C(v2temp.x,9.0)&&C(v2temp.y,10.5)); PF
cout << "v2arr+4.0: " << v2arr+4.0;
v2temp=v2arr+4.0;
p=(C(v2temp.x,9.0)&&C(v2temp.y,10.5)); PF
cout << "4.0-v2arr: " << 4.0-v2arr;
v2temp=4.0-v2arr;
p=(C(v2temp.x,-1.0)&&C(v2temp.y,-2.5)); PF
cout << "v2arr-4.0: " << v2arr-4.0;
v2temp=v2arr-4.0;
p=(C(v2temp.x,1.0)&&C(v2temp.y,2.5)); PF
vec2 v2a(1.0,2.0);
vec2 v2b(4.0,3.0);
cout << "***** v2a: " << v2a << " v2b: " << v2b << endl;
#ifdef VEC_USE_SWIZZLE
cout << "v2a.yx: " << vec2(v2a.yx);
v2temp=v2a.yx;
p=(C(v2temp.x,2.0)&&C(v2temp.y,1.0)); PF
#else
cout << "v2a.yx(): " << v2a.yx();
v2temp=v2a.yx();
p=(C(v2temp.x,2.0)&&C(v2temp.y,1.0)); PF
#endif
cout << "v2a dot v2a: " << v2a.dot();
p=C(v2a.dot(),5.0); PF
cout << "v2a dot v2b: " << v2a.dot(v2b);
p=C(v2a.dot(v2b),10.0); PF
cout << "v2a length: " << v2a.length();
p=C(v2a.length(),2.23607); PF
cout << "v2a normalized: " << v2a.normalized() << " v2a: " << v2a;
v2temp=v2a.normalized();
p=(C(v2temp.x,.447214)&&C(v2temp.y,.894427)); PF
float v2mag;
v2mag=v2a.normalize();
cout << "v2a normalized (mag): " << v2mag << " v2a: " << v2a;
p=(C(v2mag,2.23607)&&C(v2a.x,.447214)&&C(v2a.y,.894427)); PF
v2a=vec2(1.0,2.0);
cout << "reset and v2a []'s: " << v2a[0] << "," << v2a[1];
p=(C(v2a[0],1.0)&&C(v2a[1],2.0)); PF
v2a[0]=v2a[0]*2.0; v2a[1]*=3.0;
cout << "v2a []'s * (2,3): " << v2a << " and reset";
p=(C(v2a[0],2.0)&&C(v2a[1],6.0)); PF
v2a=vec2(1.0,2.0);
cout << "v2a+v2b: " << v2a+v2b;
v2temp=v2a+v2b;
p=(C(v2temp.x,5.0)&&C(v2temp.y,5.0)); PF
cout << "v2a-v2b: " << v2a-v2b;
v2temp=v2a-v2b;
p=(C(v2temp.x,-3.0)&&C(v2temp.y,-1.0)); PF
cout << "v2a*v2b: " << v2a*v2b;
v2temp=v2a*v2b;
p=(C(v2temp.x,4.0)&&C(v2temp.y,6.0)); PF
cout << "v2a/v2b: " << v2a/v2b;
v2temp=v2a/v2b;
p=(C(v2temp.x,.25)&&C(v2temp.y,.666667)); PF
cout << "-v2a: " << -v2a;
v2temp=-v2a;
p=(C(v2temp.x,-1.0)&&C(v2temp.y,-2.0)); PF
cout << "v2a+4.0: " << v2a+4.0;
v2temp=v2a+4.0;
p=(C(v2temp.x,5.0)&&C(v2temp.y,6.0)); PF
cout << "v2a-4.0: " << v2a-4.0;
v2temp=v2a-4.0;
p=(C(v2temp.x,-3.0)&&C(v2temp.y,-2.0)); PF
cout << "v2a*4.0: " << v2a*4.0;
v2temp=v2a*4.0;
p=(C(v2temp.x,4.0)&&C(v2temp.y,8.0)); PF
cout << "4.0*v2a: " << 4.0*v2a;
v2temp=4.0*v2a;
p=(C(v2temp.x,4.0)&&C(v2temp.y,8.0)); PF
cout << "v2a/4.0: " << v2a/4.0;
v2temp=v2a/4.0;
p=(C(v2temp.x,.25)&&C(v2temp.y,.5)); PF
cout << "v2a+=v2b: " << (v2a+=v2b);
p=(C(v2a.x,5.0)&&C(v2a.y,5.0)); PF
cout << "v2a-=v2b: " << (v2a-=v2b);
p=(C(v2a.x,1.0)&&C(v2a.y,2.0)); PF
cout << "v2a*=v2b: " << (v2a*=v2b);
p=(C(v2a.x,4.0)&&C(v2a.y,6.0)); PF
cout << "v2a/=v2b: " << (v2a/=v2b);
p=(C(v2a.x,1.0)&&C(v2a.y,2.0)); PF
cout << "v2a*=4.0: " << (v2a*=4.0);
p=(C(v2a.x,4.0)&&C(v2a.y,8.0)); PF
cout << "v2a/=4.0: " << (v2a/=4.0);
p=(C(v2a.x,1.0)&&C(v2a.y,2.0)); PF
cout << "v2a+=4.0: " << (v2a+=4.0);
p=(C(v2a.x,5.0)&&C(v2a.y,6.0)); PF
cout << "v2a-=4.0: " << (v2a-=4.0);
p=(C(v2a.x,1.0)&&C(v2a.y,2.0)); PF
cout << "v2a++: " << (v2a++) << " v2a: " << v2a;
p=(C(v2a.x,2.0)&&C(v2a.y,3.0)); PF
cout << "v2a--: " << (v2a--) << " v2a: " << v2a;
p=(C(v2a.x,1.0)&&C(v2a.y,2.0)); PF
cout << "++v2a: " << (++v2a) << " v2a: " << v2a;
p=(C(v2a.x,2.0)&&C(v2a.y,3.0)); PF
cout << "--v2a: " << (--v2a) << " v2a: " << v2a;
p=(C(v2a.x,1.0)&&C(v2a.y,2.0)); PF
printf("--------  mat2  --\n");
mat2 m2a(1.0,2.0,3.5,4.0);
mat2 m2b(4.1,3.2,2.0,1.0);
cout << "m2a: ";
cout << m2a;
cout << "m2b: " << endl;
m2b.print();
m2b.latex();
cout << "m2a transpose: ";
cout << m2a.transpose();
mat2 mt=m2a.transpose();
p=(C(mt.m[0][0],1.0)&&C(mt.m[0][1],2.0)&&C(mt.m[1][0],3.5)&&C(mt.m[1][1],4.0)); PF
cout << "m2a determinant: " << m2a.determinant();
p=C(m2a.determinant(),-3.0); PF
cout << "m2a inverse: " << endl;
m2a.inverse().print();
mt=m2a.inverse();
p=(C(mt.m[0][0],-1.333333)&&C(mt.m[0][1],1.166667)&&C(mt.m[1][0],.666667)&&C(mt.m[1][1],-.333333)); PF
cout << "m2a+m2b: ";
cout << (m2a+m2b);
mt=m2a+m2b;
p=(C(mt.m[0][0],5.1)&&C(mt.m[0][1],5.5)&&C(mt.m[1][0],5.2)&&C(mt.m[1][1],5.0)); PF
cout << "m2a-m2b: ";
cout << (m2a-m2b);
mt=m2a-m2b;
p=(C(mt.m[0][0],-3.1)&&C(mt.m[0][1],1.5)&&C(mt.m[1][0],-1.2)&&C(mt.m[1][1],3.0)); PF
cout << "-m2a: ";
cout << (-m2a);
mt=-m2a;
p=(C(mt.m[0][0],-1.0)&&C(mt.m[0][1],-3.5)&&C(mt.m[1][0],-2.0)&&C(mt.m[1][1],-4.0)); PF
vec2 v6(3.4,2.6);
cout << "m2a*vec2(3.4,2.6): " << (m2a*v6);
v2temp=m2a*v6;
p=(C(v2temp.x,12.5)&&C(v2temp.y,17.2)); PF
cout << "vec2(3.4,2.6)*m2a: " << (v6*m2a);
v2temp=v6*m2a;
p=(C(v2temp.x,8.6)&&C(v2temp.y,22.3)); PF
cout << "m2a*4.0: ";
cout << (m2a*4.0);
mt=m2a*4.0;
p=(C(mt.m[0][0],4.0)&&C(mt.m[0][1],14.0)&&C(mt.m[1][0],8.0)&&C(mt.m[1][1],16.0)); PF
cout << "4.0*m2a: ";
cout << (4.0f*m2a);
mt=4.0f*m2a;
p=(C(mt.m[0][0],4.0)&&C(mt.m[0][1],14.0)&&C(mt.m[1][0],8.0)&&C(mt.m[1][1],16.0)); PF
cout << "m2a*m2b: ";
cout << (m2a*m2b);
mt=m2a*m2b;
p=(C(mt.m[0][0],15.3)&&C(mt.m[0][1],5.5)&&C(mt.m[1][0],21.0)&&C(mt.m[1][1],8.0)); PF
cout << "m2a/4.0: ";
cout << (m2a/4.0);
mt=m2a/4.0;
p=(C(mt.m[0][0],.25)&&C(mt.m[0][1],.875)&&C(mt.m[1][0],.5)&&C(mt.m[1][1],1.0)); PF
cout << "m2a/m2b: ";
cout << (m2a/m2b);
mt=m2a/m2b;
p=(C(mt.m[0][0],4.434783)&&C(mt.m[0][1],-5.369565)&&C(mt.m[1][0],4.695652)&&C(mt.m[1][1],-5.391304)); PF
cout << "m2a+=m2b: ";
cout << (m2a+=m2b);
p=(C(m2a.m[0][0],5.1)&&C(m2a.m[0][1],5.5)&&C(m2a.m[1][0],5.2)&&C(m2a.m[1][1],5.0)); PF
cout << "m2a-=m2b: ";
cout << (m2a-=m2b);
p=(C(m2a.m[0][0],1.0)&&C(m2a.m[0][1],3.5)&&C(m2a.m[1][0],2.0)&&C(m2a.m[1][1],4.0)); PF
cout << "m2a*=m2b: ";
cout << (m2a*=m2b);
p=(C(m2a.m[0][0],15.3)&&C(m2a.m[0][1],5.5)&&C(m2a.m[1][0],21.0)&&C(m2a.m[1][1],8.0)); PF
cout << "m2a/=m2b: ";
cout << (m2a/=m2b);
p=(C(m2a.m[0][0],1.0)&&C(m2a.m[0][1],3.5)&&C(m2a.m[1][0],2.0)&&C(m2a.m[1][1],4.0)); PF
cout << "m2a*=4.0: ";
cout << (m2a*=4.0);
p=(C(m2a.m[0][0],4.0)&&C(m2a.m[0][1],14.0)&&C(m2a.m[1][0],8.0)&&C(m2a.m[1][1],16.0)); PF
cout << "m2a/=4.0: ";
cout << (m2a/=4.0);
p=(C(m2a.m[0][0],1.0)&&C(m2a.m[0][1],3.5)&&C(m2a.m[1][0],2.0)&&C(m2a.m[1][1],4.0)); PF
cout << "m2a equals (1,2,3.5,4)?: " << (m2a==mat2(1.0,2.0,3.5,4.0));
p=(m2a==mat2(1.0,2.0,3.5,4.0)); p=p; PF
cout << "m2a notequals (1,2,3.5,4)?: " << (m2a!=mat2(1.0,2.0,3.5,4.0));
p=(m2a!=mat2(1.0,2.0,3.5,4.0)); p=!p; PF
cout << "m2a equals (2,6,14,4)?: " << (m2a==mat2(2.0,6.0,14.0,4.0));
p=(m2a==mat2(2.0,6.0,14.0,4.0)); p=!p; PF
cout << "m2a notequals (2,6,14,4)?: " << (m2a!=mat2(2.0,6.0,14.0,4.0));
p=(m2a!=mat2(2.0,6.0,14.0,4.0)); p=p; PF
//Mat2<int> mint2(1,-2,3,4);
//mint2.latex(); // Works but won't compile with NoTemplates version
mat2 mfloat2(1.2,-2.3,3.4,4.5);
mfloat2.latex(1,true,std::cerr);
mfloat2/=2.3456;
mfloat2.latex();
mfloat2.latex(1,false);
printf("--------  mat3  --\n");
mat3 m3a(1.0,2.0,3.5,4.0,5.0,6.0,7.5,8.0,9.0);
mat3 m3b(4.1,3.2,2.0,1.0,7.0,8.0,9.0,2.0,3.0);
cout << "m3a: ";
cout << m3a;
cout << "m3b: " << endl;
m3b.print();
m3b.latex();
cout << "m3a transpose: ";
cout << m3a.transpose();
mat3 M=m3a.transpose();
p=(C(M.m[0][0],1.0)&&C(M.m[0][1],2.0)&&C(M.m[0][2],3.5)&&C(M.m[1][0],4.0)&&C(M.m[1][1],5.0)&&C(M.m[1][2],6.0)&&C(M.m[2][0],7.5)&&C(M.m[2][1],8.0)&&C(M.m[2][2],9.0)); PF
cout << "m3a determinant: " << m3a.determinant();
p=C(m3a.determinant(),-4.25); PF
cout << "m3a inverse: " << endl;
m3a.inverse().print();
M=m3a.inverse();
p=(C(M.m[0][0],.705882)&&C(M.m[0][1],-2.117647)&&C(M.m[0][2],1.294118)&&C(M.m[1][0],-2.352941)&&C(M.m[1][1],4.058824)&&C(M.m[1][2],-1.647059)&&C(M.m[2][0],1.294118)&&C(M.m[2][1],-1.882353)&&C(M.m[2][2],.705882)); PF
cout << "m3a+m3b: ";
cout << (m3a+m3b);
M=m3a+m3b;
p=(C(M.m[0][0],5.1)&&C(M.m[0][1],5.0)&&C(M.m[0][2],16.5)&&C(M.m[1][0],5.2)&&C(M.m[1][1],12.0)&&C(M.m[1][2],10.0)&&C(M.m[2][0],5.5)&&C(M.m[2][1],14.0)&&C(M.m[2][2],12.0)); PF
cout << "m3a-m3b: ";
cout << (m3a-m3b);
M=m3a-m3b;
p=(C(M.m[0][0],-3.1)&&C(M.m[0][1],3.0)&&C(M.m[0][2],-1.5)&&C(M.m[1][0],-1.2)&&C(M.m[1][1],-2.0)&&C(M.m[1][2],6.0)&&C(M.m[2][0],1.5)&&C(M.m[2][1],-2.0)&&C(M.m[2][2],6.0)); PF
cout << "-m3a: ";
cout << (-m3a);
M=-m3a;
p=(C(M.m[0][0],-1.0)&&C(M.m[0][1],-4.0)&&C(M.m[0][2],-7.5)&&C(M.m[1][0],-2.0)&&C(M.m[1][1],-5.0)&&C(M.m[1][2],-8.0)&&C(M.m[2][0],-3.5)&&C(M.m[2][1],-6.0)&&C(M.m[2][2],-9.0)); PF
vec3 v7(3.4,2.6,4.2);
cout << "m3a*vec3(3.4,2.6,4.2): " << (m3a*v7);
v3temp=m3a*v7;
p=(C(v3temp.x,45.3)&&C(v3temp.y,53.4)&&C(v3temp.z,65.3)); PF
cout << "vec3(3.4,2.6,4.2)*m3a: " << (v7*m3a);
v3temp=v7*m3a;
p=(C(v3temp.x,23.3)&&C(v3temp.y,51.8)&&C(v3temp.z,84.1)); PF
cout << "m3a*4.0: ";
cout << (m3a*4.0);
M=m3a*4.0;
p=(C(M.m[0][0],4.0)&&C(M.m[0][1],16.0)&&C(M.m[0][2],30.0)&&C(M.m[1][0],8.0)&&C(M.m[1][1],20.0)&&C(M.m[1][2],32.0)&&C(M.m[2][0],14.0)&&C(M.m[2][1],24.0)&&C(M.m[2][2],36.0)); PF
cout << "4.0*m3a: ";
cout << (4.0f*m3a);
M=4.0f*m3a;
p=(C(M.m[0][0],4.0)&&C(M.m[0][1],16.0)&&C(M.m[0][2],30.0)&&C(M.m[1][0],8.0)&&C(M.m[1][1],20.0)&&C(M.m[1][2],32.0)&&C(M.m[2][0],14.0)&&C(M.m[2][1],24.0)&&C(M.m[2][2],36.0)); PF
cout << "m3a*m3b: ";
cout << (m3a*m3b);
M=m3a*m3b;
p=(C(M.m[0][0],31.9)&&C(M.m[0][1],89.0)&&C(M.m[0][2],39.5)&&C(M.m[1][0],40.2)&&C(M.m[1][1],101.0)&&C(M.m[1][2],52.0)&&C(M.m[2][0],51.55)&&C(M.m[2][1],117.5)&&C(M.m[2][2],70.5)); PF
cout << "m3a/4.0: ";
cout << (m3a/4.0);
M=m3a/4.0;
p=(C(M.m[0][0],.25)&&C(M.m[0][1],1.0)&&C(M.m[0][2],1.875)&&C(M.m[1][0],.5)&&C(M.m[1][1],1.25)&&C(M.m[1][2],2.0)&&C(M.m[2][0],.875)&&C(M.m[2][1],1.5)&&C(M.m[2][2],2.25)); PF
cout << "m3a/m3b: ";
cout << (m3a/m3b);
M=m3a/m3b;
p=(C(M.m[0][0],.583403)&&C(M.m[0][1],-1.549036)&&C(M.m[0][2],1.782481)&&C(M.m[1][0],.626991)&&C(M.m[1][1],-1.147527)&&C(M.m[1][2],1.550712)&&C(M.m[2][0],.740151)&&C(M.m[2][1],-.585918)&&C(M.m[2][2],1.170159)); PF
cout << "m3a+=m3b: ";
cout << (m3a+=m3b);
p=(C(m3a.m[0][0],5.1)&&C(m3a.m[0][1],5.0)&&C(m3a.m[0][2],16.5)&&C(m3a.m[1][0],5.2)&&C(m3a.m[1][1],12.0)&&C(m3a.m[1][2],10.0)&&C(m3a.m[2][0],5.5)&&C(m3a.m[2][1],14.0)&&C(m3a.m[2][2],12.0)); PF
cout << "m3a-=m3b: ";
cout << (m3a-=m3b);
p=(C(m3a.m[0][0],1.0)&&C(m3a.m[0][1],4.0)&&C(m3a.m[0][2],7.5)&&C(m3a.m[1][0],2.0)&&C(m3a.m[1][1],5.0)&&C(m3a.m[1][2],8.0)&&C(m3a.m[2][0],3.5)&&C(m3a.m[2][1],6.0)&&C(m3a.m[2][2],9.0)); PF
cout << "m3a*=m3b: ";
cout << (m3a*=m3b);
p=(C(m3a.m[0][0],31.9)&&C(m3a.m[0][1],89.0)&&C(m3a.m[0][2],39.5)&&C(m3a.m[1][0],40.2)&&C(m3a.m[1][1],101.0)&&C(m3a.m[1][2],52.0)&&C(m3a.m[2][0],51.55)&&C(m3a.m[2][1],117.5)&&C(m3a.m[2][2],70.5)); PF
cout << "m3a/=m3b: ";
cout << (m3a/=m3b);
p=(C(m3a.m[0][0],1.0)&&C(m3a.m[0][1],4.0)&&C(m3a.m[0][2],7.5)&&C(m3a.m[1][0],2.0)&&C(m3a.m[1][1],5.0)&&C(m3a.m[1][2],8.0)&&C(m3a.m[2][0],3.5)&&C(m3a.m[2][1],6.0)&&C(m3a.m[2][2],9.0)); PF
cout << "m3a*=4.0: ";
cout << (m3a*=4.0);
p=(C(m3a.m[0][0],4.0)&&C(m3a.m[0][1],16.0)&&C(m3a.m[0][2],30.0)&&C(m3a.m[1][0],8.0)&&C(m3a.m[1][1],20.0)&&C(m3a.m[1][2],32.0)&&C(m3a.m[2][0],14.0)&&C(m3a.m[2][1],24.0)&&C(m3a.m[2][2],36.0)); PF
cout << "m3a/=4.0: ";
cout << (m3a/=4.0);
p=(C(m3a.m[0][0],1.0)&&C(m3a.m[0][1],4.0)&&C(m3a.m[0][2],7.5)&&C(m3a.m[1][0],2.0)&&C(m3a.m[1][1],5.0)&&C(m3a.m[1][2],8.0)&&C(m3a.m[2][0],3.5)&&C(m3a.m[2][1],6.0)&&C(m3a.m[2][2],9.0)); PF
cout << "m3a equals (1,2,3.5,...)?: " << (m3a==mat3(1.0,2.0,3.5,4.0,5.0,6.0,7.5,8.0,9.0));
p=(m3a==mat3(1.0,2.0,3.5,4.0,5.0,6.0,7.5,8.0,9.0)); p=p; PF
cout << "m3a notequals (1,2,3.5,...)?: " << (m3a!=mat3(1.0,2.0,3.5,4.0,5.0,6.0,7.5,8.0,9.0));
p=(m3a!=mat3(1.0,2.0,3.5,4.0,5.0,6.0,7.5,8.0,9.0)); p=!p; PF
cout << "m3a equals (2,6,14,...)?: " << (m3a==mat3(2.0,6.0,14.0,4.0,5.0,6.0,7.5,8.0,9.0));
p=(m3a==mat3(2.0,6.0,14.0,4.0,5.0,6.0,7.5,8.0,9.0)); p=!p; PF
cout << "m3a notequals (2,6,14,...)?: " << (m3a!=mat3(2.0,6.0,14.0,4.0,5.0,6.0,7.5,8.0,9.0));
p=(m3a!=mat3(2.0,6.0,14.0,4.0,5.0,6.0,7.5,8.0,9.0)); p=p; PF
//Mat3<int> mint3(1,-2,3,4,5,-6,7,8,9);
//mint3.latex(); // Works but won't compile with NoTemplates version
mat3 mfloat3(1.2,-2.3,3.4,4.5,5.6,-6.7,7.8,8.9,9.10);
mfloat3.latex(1,true,std::cerr);
mfloat3/=2.3456;
mfloat3.latex();
mfloat3.latex(1,false);
printf("--------  mat4  --\n");
mat4 m4a(1.0,2.0,3.5,4.0,5.0,6.0,7.5,8.0,9.1,10.2,11.3,12.5,13.6,14.7,15.8,16.5);
mat4 m4b(4.1,3.2,2.0,1.0,7.0,8.0,9.0,2.0,3.0,10.5,11.5,12.0,13.5,14.5,15.5,16.0);
cout << "m4a: ";
cout << m4a;
cout << "m4b: " << endl;
m4b.print();
m4b.latex();
cout << "m4a transpose: ";
cout << m4a.transpose();
mat4 F=m4a.transpose();
p=(C(F.m[0][0],1.0)&&C(F.m[0][1],2.0)&&C(F.m[0][2],3.5)&&C(F.m[0][3],4.0)&&C(F.m[1][0],5.0)&&C(F.m[1][1],6.0)&&C(F.m[1][2],7.5)&&C(F.m[1][3],8.0)&&C(F.m[2][0],9.1)&&C(F.m[2][1],10.2)&&C(F.m[2][2],11.3)&&C(F.m[2][3],12.5)&&C(F.m[3][0],13.6)&&C(F.m[3][1],14.7)&&C(F.m[3][2],15.8)&&C(F.m[3][3],16.5)); PF
cout << "m4a determinant: " << m4a.determinant();
p=C(m4a.determinant(),-1.1); PF
cout << "m4a inverse: " << endl;
m4a.inverse().print();
F=m4a.inverse();
p=(C(F.m[0][0],-9.068)&&C(F.m[0][1],13.113939)&&C(F.m[0][2],-2.045514)&&C(F.m[0][3],-2.250046)&&C(F.m[1][0],11.068)&&C(F.m[1][1],-17.114)&&C(F.m[1][2],4.045557)&&C(F.m[1][3],2.250048)&&C(F.m[2][0],1.818225)&&C(F.m[2][1],-2.363692)&&C(F.m[2][2],-1.454575)&&C(F.m[2][3],2.000043)&&C(F.m[3][0],-4.54556)&&C(F.m[3][1],6.909255)&&C(F.m[3][2],-.36365)&&C(F.m[3][3],-2.000043)); PF
cout << "m4a+m4b: ";
cout << (m4a+m4b);
F=m4a+m4b;
p=(C(F.m[0][0],5.1)&&C(F.m[0][1],12.0)&&C(F.m[0][2],12.1)&&C(F.m[0][3],27.1)&&C(F.m[1][0],5.2)&&C(F.m[1][1],14.0)&&C(F.m[1][2],20.7)&&C(F.m[1][3],29.2)&&C(F.m[2][0],5.5)&&C(F.m[2][1],16.5)&&C(F.m[2][2],22.8)&&C(F.m[2][3],31.3)&&C(F.m[3][0],5.0)&&C(F.m[3][1],10.0)&&C(F.m[3][2],24.5)&&C(F.m[3][3],32.5)); PF
cout << "m4a-m4b: ";
cout << (m4a-m4b);
F=m4a-m4b;
p=(C(F.m[0][0],-3.1)&&C(F.m[0][1],-2.0)&&C(F.m[0][2],6.1)&&C(F.m[0][3],.1)&&C(F.m[1][0],-1.2)&&C(F.m[1][1],-2.0)&&C(F.m[1][2],-.3)&&C(F.m[1][3],.2)&&C(F.m[2][0],1.5)&&C(F.m[2][1],-1.5)&&C(F.m[2][2],-.2)&&C(F.m[2][3],.3)&&C(F.m[3][0],3.0)&&C(F.m[3][1],6.0)&&C(F.m[3][2],.5)&&C(F.m[3][3],.5)); PF
cout << "-m4a: ";
cout << (-m4a);
F=-m4a;
p=(C(F.m[0][0],-1.0)&&C(F.m[0][1],-5.0)&&C(F.m[0][2],-9.1)&&C(F.m[0][3],-13.6)&&C(F.m[1][0],-2.0)&&C(F.m[1][1],-6.0)&&C(F.m[1][2],-10.2)&&C(F.m[1][3],-14.7)&&C(F.m[2][0],-3.5)&&C(F.m[2][1],-7.5)&&C(F.m[2][2],-11.3)&&C(F.m[2][3],-15.8)&&C(F.m[3][0],-4.0)&&C(F.m[3][1],-8.0)&&C(F.m[3][2],-12.5)&&C(F.m[3][3],-16.5)); PF
vec4 v3(3.4,2.6,4.2,1.3);
cout << "m4a*vec4(3.4,2.6,4.2,1.3): " << (m4a*v3);
v4temp=m4a*v3;
p=(C(v4temp.x,72.3)&&C(v4temp.y,84.35)&&C(v4temp.z,99.4)&&C(v4temp.w,108.35)); PF
cout << "vec4(3.4,2.6,4.2,1.3)*m4a: " << (v3*m4a);
v4temp=v3*m4a;
p=(C(v4temp.x,28.5)&&C(v4temp.y,74.5)&&C(v4temp.z,121.17)&&C(v4temp.w,172.27)); PF
cout << "m4a*4.0: ";
cout << (m4a*4.0);
F=m4a*4.0;
p=(C(F.m[0][0],4.0)&&C(F.m[0][1],20.0)&&C(F.m[0][2],36.4)&&C(F.m[0][3],54.4)&&C(F.m[1][0],8.0)&&C(F.m[1][1],24.0)&&C(F.m[1][2],40.8)&&C(F.m[1][3],58.8)&&C(F.m[2][0],14.0)&&C(F.m[2][1],30.0)&&C(F.m[2][2],45.2)&&C(F.m[2][3],63.2)&&C(F.m[3][0],16.0)&&C(F.m[3][1],32.0)&&C(F.m[3][2],50.0)&&C(F.m[3][3],66.0)); PF
cout << "4.0*m4a: ";
cout << (4.0f*m4a);
F=4.0f*m4a;
p=(C(F.m[0][0],4.0)&&C(F.m[0][1],20.0)&&C(F.m[0][2],36.4)&&C(F.m[0][3],54.4)&&C(F.m[1][0],8.0)&&C(F.m[1][1],24.0)&&C(F.m[1][2],40.8)&&C(F.m[1][3],58.8)&&C(F.m[2][0],14.0)&&C(F.m[2][1],30.0)&&C(F.m[2][2],45.2)&&C(F.m[2][3],63.2)&&C(F.m[3][0],16.0)&&C(F.m[3][1],32.0)&&C(F.m[3][2],50.0)&&C(F.m[3][3],66.0)); PF
cout << "m4a*m4b: ";
cout << (m4a*m4b);
F=m4a*m4b;
p=(C(F.m[0][0],51.9)&&C(F.m[0][1],156.1)&&C(F.m[0][2],323.35)&&C(F.m[0][3],444.65)&&C(F.m[1][0],62.5)&&C(F.m[1][1],183.2)&&C(F.m[1][2],362.7)&&C(F.m[1][3],507.3)&&C(F.m[2][0],76.75)&&C(F.m[2][1],217.8)&&C(F.m[2][2],408.8)&&C(F.m[2][3],583.95)&&C(F.m[3][0],83.5)&&C(F.m[3][1],237.5)&&C(F.m[3][2],437.75)&&C(F.m[3][3],627.75)); PF
cout << "m4a/4.0: ";
cout << (m4a/4.0);
F=m4a/4.0;
p=(C(F.m[0][0],.25)&&C(F.m[0][1],1.25)&&C(F.m[0][2],2.275)&&C(F.m[0][3],3.4)&&C(F.m[1][0],.5)&&C(F.m[1][1],1.5)&&C(F.m[1][2],2.55)&&C(F.m[1][3],3.675)&&C(F.m[2][0],.875)&&C(F.m[2][1],1.875)&&C(F.m[2][2],2.825)&&C(F.m[2][3],3.95)&&C(F.m[3][0],1.0)&&C(F.m[3][1],2.0)&&C(F.m[3][2],3.125)&&C(F.m[3][3],4.125)); PF
cout << "m4a/m4b: ";
cout << (m4a/m4b);
F=m4a/m4b;
p=(C(F.m[0][0],.168509)&&C(F.m[0][1],-.539359)&&C(F.m[0][2],.813037)&&C(F.m[0][3],.408984)&&C(F.m[1][0],.100791)&&C(F.m[1][1],.160714)&&C(F.m[1][2],.372761)&&C(F.m[1][3],.326947)&&C(F.m[2][0],.019288)&&C(F.m[2][1],1.19251)&&C(F.m[2][2],-.276974)&&C(F.m[2][3],.158831)&&C(F.m[3][0],-.096297)&&C(F.m[3][1],1.683589)&&C(F.m[3][2],-.56186)&&C(F.m[3][3],.131049)); PF
cout << "m4a+=m4b: ";
cout << (m4a+=m4b);
p=(C(m4a.m[0][0],5.1)&&C(m4a.m[0][1],12.0)&&C(m4a.m[0][2],12.1)&&C(m4a.m[0][3],27.1)&&C(m4a.m[1][0],5.2)&&C(m4a.m[1][1],14.0)&&C(m4a.m[1][2],20.7)&&C(m4a.m[1][3],29.2)&&C(m4a.m[2][0],5.5)&&C(m4a.m[2][1],16.5)&&C(m4a.m[2][2],22.8)&&C(m4a.m[2][3],31.3)&&C(m4a.m[3][0],5.0)&&C(m4a.m[3][1],10.0)&&C(m4a.m[3][2],24.5)&&C(m4a.m[3][3],32.5)); PF
cout << "m4a-=m4b: ";
cout << (m4a-=m4b);
p=(C(m4a.m[0][0],1.0)&&C(m4a.m[0][1],5.0)&&C(m4a.m[0][2],9.1)&&C(m4a.m[0][3],13.6)&&C(m4a.m[1][0],2.0)&&C(m4a.m[1][1],6.0)&&C(m4a.m[1][2],10.2)&&C(m4a.m[1][3],14.7)&&C(m4a.m[2][0],3.5)&&C(m4a.m[2][1],7.5)&&C(m4a.m[2][2],11.3)&&C(m4a.m[2][3],15.8)&&C(m4a.m[3][0],4.0)&&C(m4a.m[3][1],8.0)&&C(m4a.m[3][2],12.5)&&C(m4a.m[3][3],16.5)); PF
cout << "m4a*=m4b: ";
cout << (m4a*=m4b);
p=(C(m4a.m[0][0],51.9)&&C(m4a.m[0][1],156.1)&&C(m4a.m[0][2],323.35)&&C(m4a.m[0][3],444.65)&&C(m4a.m[1][0],62.5)&&C(m4a.m[1][1],183.2)&&C(m4a.m[1][2],362.7)&&C(m4a.m[1][3],507.3)&&C(m4a.m[2][0],76.75)&&C(m4a.m[2][1],217.8)&&C(m4a.m[2][2],408.8)&&C(m4a.m[2][3],583.95)&&C(m4a.m[3][0],83.5)&&C(m4a.m[3][1],237.5)&&C(m4a.m[3][2],437.75)&&C(m4a.m[3][3],627.75)); PF
cout << "m4a/=m4b: ";
cout << (m4a/=m4b);
p=(C(m4a.m[0][0],1.0)&&C(m4a.m[0][1],5.0)&&C(m4a.m[0][2],9.1)&&C(m4a.m[0][3],13.6)&&C(m4a.m[1][0],2.0)&&C(m4a.m[1][1],6.0)&&C(m4a.m[1][2],10.2)&&C(m4a.m[1][3],14.7)&&C(m4a.m[2][0],3.5)&&C(m4a.m[2][1],7.5)&&C(m4a.m[2][2],11.3)&&C(m4a.m[2][3],15.8)&&C(m4a.m[3][0],4.0)&&C(m4a.m[3][1],8.0)&&C(m4a.m[3][2],12.5)&&C(m4a.m[3][3],16.5)); PF
cout << "m4a*=4.0: ";
cout << (m4a*=4.0);
p=(C(m4a.m[0][0],4.0)&&C(m4a.m[0][1],20.0)&&C(m4a.m[0][2],36.4)&&C(m4a.m[0][3],54.4)&&C(m4a.m[1][0],8.0)&&C(m4a.m[1][1],24.0)&&C(m4a.m[1][2],40.8)&&C(m4a.m[1][3],58.8)&&C(m4a.m[2][0],14.0)&&C(m4a.m[2][1],30.0)&&C(m4a.m[2][2],45.2)&&C(m4a.m[2][3],63.2)&&C(m4a.m[3][0],16.0)&&C(m4a.m[3][1],32.0)&&C(m4a.m[3][2],50.0)&&C(m4a.m[3][3],66.0)); PF
cout << "m4a/=4.0: ";
cout << (m4a/=4.0);
p=(C(m4a.m[0][0],1.0)&&C(m4a.m[0][1],5.0)&&C(m4a.m[0][2],9.1)&&C(m4a.m[0][3],13.6)&&C(m4a.m[1][0],2.0)&&C(m4a.m[1][1],6.0)&&C(m4a.m[1][2],10.2)&&C(m4a.m[1][3],14.7)&&C(m4a.m[2][0],3.5)&&C(m4a.m[2][1],7.5)&&C(m4a.m[2][2],11.3)&&C(m4a.m[2][3],15.8)&&C(m4a.m[3][0],4.0)&&C(m4a.m[3][1],8.0)&&C(m4a.m[3][2],12.5)&&C(m4a.m[3][3],16.5)); PF
cout << "m4a equals (1,2,3.5,...)?: " << (m4a==mat4(1.0,2.0,3.5,4.0,5.0,6.0,7.5,8.0,9.1,10.2,11.3,12.5,13.6,14.7,15.8,16.5));
p=(m4a==mat4(1.0,2.0,3.5,4.0,5.0,6.0,7.5,8.0,9.1,10.2,11.3,12.5,13.6,14.7,15.8,16.5)); p=p; PF
cout << "m4a notequals (1,2,3.5,...)?: " << (m4a!=mat4(1.0,2.0,3.5,4.0,5.0,6.0,7.5,8.0,9.1,10.2,11.3,12.5,13.6,14.7,15.8,16.5));
p=(m4a!=mat4(1.0,2.0,3.5,4.0,5.0,6.0,7.5,8.0,9.1,10.2,11.3,12.5,13.6,14.7,15.8,16.5)); p=!p; PF
cout << "m4a equals (2,6,14,...)?: " << (m4a==mat4(2.0,6.0,14.0,4.0,5.0,6.0,7.5,8.0,9.0,10.0,11.0,12.5,13.0,14.0,15.0,16.5));
p=(m4a==mat4(2.0,6.0,14.0,4.0,5.0,6.0,7.5,8.0,9.0,10.0,11.0,12.5,13.0,14.0,15.0,16.5)); p=!p; PF
cout << "m4a notequals (2,6,14,...)?: " << (m4a!=mat4(2.0,6.0,14.0,4.0,5.0,6.0,7.5,8.0,9.0,10.0,11.0,12.5,13.0,14.0,15.0,16.5));
p=(m4a!=mat4(2.0,6.0,14.0,4.0,5.0,6.0,7.5,8.0,9.0,10.0,11.0,12.5,13.0,14.0,15.0,16.5)); p=p; PF
//Mat4<int> mint4(1,-2,3,4,5,-6,7,8,9,10,11,12,13,14,15,16);
//mint4.latex(); // Works but won't compile with NoTemplates version
mat4 mfloat4(1.2,-2.3,3.4,4.5,5.6,-6.7,7.8,8.9,9.10,10.11,11.12,12.13,13.14,14.15,15.16,16.17);
mfloat4.latex(1,true,std::cerr);
mfloat4/=2.3456;
mfloat4.latex();
mfloat4.latex(1,false);
printf("-------------------------------\n");
#ifdef VEC_USE_MAT
printf("--------  vec2*=mat2  --\n");
cout << v2b << " *= " << m2b << " = "; v2b*=m2b; cout << v2b;
p=(C(v2b.x,26.0)&&C(v2b.y,11.0)); PF
printf("--------  vec3*=mat3  --\n");
cout << v3b << " *= " << m3b << " = "; v3b*=m3b; cout << v3b;
p=(C(v3b.x,30.0)&&C(v3b.y,41.0)&&C(v3b.z,48.0)); PF
printf("--------  vec4*=mat4  --\n");
cout << v4b << " *= " << m4b << " = "; v4b*=m4b; cout << v4b;
p=(C(v4b.x,31.0)&&C(v4b.y,72.0)&&C(v4b.z,78.5)&&C(v4b.w,144.5)); PF
printf("-------------------------------\n");
#endif
printf("Results: Pass: %d    Fail: %d\n",passfail[1],passfail[0]);
return(0);
}
