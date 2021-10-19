/*********************************************************
   Simple program to test various functions of the complex
   number class.
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

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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

int main(int argc,char *argv[])
{
comp c1(2.0,3.0),c2(1.5,4.5),c3,c4(5.0,6.5);
float po=3.5;

cout << "c4: " << c4 << endl;
cout << "4.0+c4: " << 4.0+c4 << endl;
cout << "c4+4.0: " << c4+4.0 << endl;
cout << "4.0-c4: " << 4.0-c4 << endl;
cout << "c4-4.0: " << c4-4.0 << endl;
cout << "c4+=4.0: " << (c4+=4.0) << endl;
cout << "c4-=4.0: " << (c4-=4.0) << endl;
cout << "c1: " << c1 << endl;
cout << "c2: " << c2 << endl;
c3=c1+c2;
cout << "add: " << c3 << endl;
c3=c1-c2;
cout << "sub: " << c3 << endl;
c3=c1*c2;
cout << "mul: " << c3 << endl;
quat q1(2.0,3.0,0.0,0.0);
quat q2(1.5,4.5,0.0,0.0);
cout << "mulq: " << q1*q2 << endl;
c3=c1/c2;
cout << "div: " << c3 << endl;
cout << "c1 dot c1: " << c1.dot() << endl;
cout << "c1 dot c2: " << c1.dot(c2) << endl;
cout << "c1 normalized: " << c1.normalized() << " c1: " << c1 << endl;
cout << "c1 normalized mag: " << c1.normalize() << " c1: " << c1 << endl;
c1=comp(2.0,3.0);
cout << "c1 []'s: " << c1[0] << "," << c1[1] << endl;
c1[0]=c1[0]*4.0; c1[1]*=5.0;
cout << "c1 []'s * (4,5): " << c1 << endl;
c1=comp(2.0,3.0);
cout << "reset c1 and -c1: " << -c1 << endl;
cout << "c1*4.0: " << c1*4.0 << endl;
cout << "4.0*c1: " << 4.0*c1 << endl;
cout << "c1/4.0: " << c1/4.0 << endl;
cout << "c1+=c2: " << (c1+=c2) << endl;
cout << "c1-=c2: " << (c1-=c2) << endl;
cout << "c1*=c2: " << (c1*=c2) << endl;
cout << "c1/=c2: " << (c1/=c2) << endl;
cout << "c1*=4.0: " << (c1*=4.0) << endl;
cout << "c1/=4.0: " << (c1/=4.0) << endl;
c3=MagPhase2Complex(c1.mag(),c1.phase());
cout << "MagPhase2Complex: " << c3 << endl;
printf("-----------\n");
c3=c1+c2;
cout << "add: " << c3 << endl;
c3=c1-c2;
cout << "sub: " << c3 << endl;
c3=c1*c2;
cout << "mul: " << c3 << endl;
c3=c1/c2;
cout << "div: " << c3 << endl;
c3=c1.square();
cout << "sqr: " << c3 << endl;
float cabs=abs(c1);
cout << "abs: " << cabs << endl;
c3=cos(c1);
cout << "cos: " << c3 << endl;
c3=sin(c1);
cout << "sin: " << c3 << endl;
c3=ztoz(c1);
cout << "ztoz: " << c3 << endl;
c3=cpow(c1,po);
cout << "cpow: " << c3 << endl;
c3=exp(c1);
cout << "exp: " << c3 << endl;
c3=cosh(c1);
cout << "cosh: " << c3 << endl;
c3=sinh(c1);
cout << "sinh: " << c3 << endl;
cabs=c1.mag();
printf("cmag=%f\n",cabs);
cabs=c1.phase();
printf("carg=%f\n",cabs);
c3=log(c1);
cout << "log: " << c3 << endl;
c3=log10(c1);
cout << "log10: " << c3 << endl;
c3=log2(c1);
cout << "log2: " << c3 << endl;
c3=acos(c1);
cout << "acos: " << c3 << endl;
c3=asin(c1);
cout << "asin: " << c3 << endl;
c3=atan(c1);
cout << "atan: " << c3 << endl;
c3=tan(c1);
cout << "tan: " << c3 << endl;
c3=acosh(c1);
cout << "acosh: " << c3 << endl;
c3=asinh(c1);
cout << "asinh: " << c3 << endl;
c3=atanh(c1);
cout << "atanh: " << c3 << endl;
c3=tanh(c1);
cout << "tanh: " << c3 << endl;
c3=sqrt(c1);
cout << "sqrt: " << c3 << endl;
c3=c1.conjugate();
cout << "conj: " << c3 << endl;
#ifdef INFINITY
c3=cproj(c1);
cout << "cproj: " << c3 << endl;
c3=cproj(comp(INFINITY,3.0));
cout << "cproj(Inf,3i): " << c3 << endl;
c3=cproj(comp(INFINITY,-3.0));
cout << "cproj(Inf,-3i): " << c3 << endl;
c3=cproj(comp(2.0,INFINITY));
cout << "cproj(2,Infi): " << c3 << endl;
c3=cproj(comp(2.0,-INFINITY));
cout << "cproj(2,-Infi): " << c3 << endl;
#endif
cout << "polar(2.0,1.35): " << polar(2.0,1.35) << endl;
cout << "cpow(c1,c2): " << cpow(c1,c2) << endl;
cout << "cpow(3.5,c2): " << cpow(po,c2) << endl;
#if _MSC_VER == 1200
c3=cpow(2.71828182845904523536f,comp(0.0,M_PI))+1.0;
#else
c3=cpow(2.71828182845904523536,comp(0.0,M_PI))+1.0;
#endif
cout << "e^{i(pi)}+1=0 (using cpow): " << c3 << endl;
c3=exp(comp(0.0,M_PI))+1.0;
cout << "e^{i(pi)}+1=0 (using exp): " << c3 << endl;
return(0);
}
