/*********************************************************
   Simple program to test various functions of the C++
   standard library complex number class.
   Copyright © 2021 Mark Craig

   https://www.youtube.com/MrMcSoftware
**********************************************************/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>
#include <complex>

using namespace std;

int main(int argc,char *argv[])
{
complex<float> c1(2.0,3.0),c2(1.5,4.5),c3,c4(5.0,6.5);
float po=3.5;

cout << "c4: " << c4 << endl;
cout << "4.0+c4: " << 4.0f+c4 << endl;
cout << "c4+4.0: " << c4+4.0f << endl;
cout << "4.0-c4: " << 4.0f-c4 << endl;
cout << "c4-4.0: " << c4-4.0f << endl;
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
c3=c1/c2;
cout << "div: " << c3 << endl;
c1=complex<float>(2.0,3.0);
cout << "reset c1 and -c1: " << -c1 << endl;
cout << "c1*4.0: " << c1*4.0f << endl;
cout << "4.0*c1: " << 4.0f*c1 << endl;
cout << "c1/4.0: " << c1/4.0f << endl;
cout << "c1+=c2: " << (c1+=c2) << endl;
cout << "c1-=c2: " << (c1-=c2) << endl;
cout << "c1*=c2: " << (c1*=c2) << endl;
cout << "c1/=c2: " << (c1/=c2) << endl;
cout << "c1*=4.0: " << (c1*=4.0) << endl;
cout << "c1/=4.0: " << (c1/=4.0) << endl;
printf("-----------\n");
c3=c1+c2;
cout << "add: " << c3 << endl;
c3=c1-c2;
cout << "sub: " << c3 << endl;
c3=c1*c2;
cout << "mul: " << c3 << endl;
c3=c1/c2;
cout << "div: " << c3 << endl;
float cabs=abs(c1);
cout << "abs: " << cabs << endl;
c3=cos(c1);
cout << "cos: " << c3 << endl;
c3=sin(c1);
cout << "sin: " << c3 << endl;
cout << "ztoz: " << pow(c1,c1) << endl;
c3=pow(c1,po);
cout << "cpow: " << c3 << endl;
c3=exp(c1);
cout << "exp: " << c3 << endl;
c3=cosh(c1);
cout << "cosh: " << c3 << endl;
c3=sinh(c1);
cout << "sinh: " << c3 << endl;
cabs=abs(c1);
printf("cmag=%f\n",cabs);
cabs=arg(c1);
printf("carg=%f\n",cabs);
c3=log(c1);
cout << "log: " << c3 << endl;
c3=log10(c1);
cout << "log10: " << c3 << endl;
//  These functions were added in C++11
#if __cplusplus >= 201103L
c3=acos(c1);
cout << "acos: " << c3 << endl;
c3=asin(c1);
cout << "asin: " << c3 << endl;
c3=atan(c1);
cout << "atan: " << c3 << endl;
#endif
c3=tan(c1);
cout << "tan: " << c3 << endl;
#if __cplusplus >= 201103L
c3=acosh(c1);
cout << "acosh: " << c3 << endl;
c3=asinh(c1);
cout << "asinh: " << c3 << endl;
c3=atanh(c1);
cout << "atanh: " << c3 << endl;
#endif
c3=tanh(c1);
cout << "tanh: " << c3 << endl;
c3=sqrt(c1);
cout << "sqrt: " << c3 << endl;
c3=conj(c1);
cout << "conj: " << c3 << endl;
#ifdef INFINITY
#if __cplusplus >= 201103L
c3=proj(c1);
cout << "cproj: " << c3 << endl;
c3=proj(complex<float>(INFINITY,3.0));
cout << "cproj(Inf,3i): " << c3 << endl;
c3=proj(complex<float>(INFINITY,-3.0));
cout << "cproj(Inf,-3i): " << c3 << endl;
c3=proj(complex<float>(2.0,INFINITY));
cout << "cproj(2,Infi): " << c3 << endl;
c3=proj(complex<float>(2.0,-INFINITY));
cout << "cproj(2,-Infi): " << c3 << endl;
#endif
#endif
cout << "polar(2.0,1.35): " << polar(2.0,1.35) << endl;
cout << "cpow(c1,c2): " << pow(c1,c2) << endl;
cout << "cpow(3.5,c2): " << pow(po,c2) << endl;
}
