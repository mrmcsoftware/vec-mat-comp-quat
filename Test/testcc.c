/*********************************************************
   Simple program to test various functions of the C
   complex number capability (complex.h).
   Copyright © 2021 Mark Craig

   https://www.youtube.com/MrMcSoftware
**********************************************************/

#define _GNU_SOURCE

#include <stdio.h>
#include <math.h>
#include <complex.h>
 
typedef double complex cplx;
 
void print(cplx v)
{
printf("(%f+j%f)\n",creal(v),cimag(v));
}

int main()
{
cplx v8c,v9c,v10c,cV1av,r;
float po=3.5;
v8c=2.0+3.0*I;
v9c=1.5+4.5*I;
cV1av=5.0+6.5*I;

printf("cV1av=%f %f\n",creal(cV1av),cimag(cV1av)); r=v8c;
r=4.0+cV1av;
printf("4.0+cV1av=%f %f\n",creal(r),cimag(r)); r=v8c;
r=cV1av+4.0;
printf("cV1av+4.0=%f %f\n",creal(r),cimag(r)); r=v8c;
r=4.0-cV1av;
printf("4.0-cV1av=%f %f\n",creal(r),cimag(r)); r=v8c;
r=cV1av-4.0;
printf("cV1av-4.0=%f %f\n",creal(r),cimag(r));
cV1av+=4.0;
printf("cV1av+=4.0=%f %f\n",creal(cV1av),cimag(cV1av));
cV1av-=4.0;
printf("cV1av-=4.0=%f %f\n",creal(cV1av),cimag(cV1av));
printf("v8c="); print(v8c);
printf("v9c="); print(v9c);
v10c=v8c+v9c;
printf("add="); print(v10c);
v10c=v8c-v9c;
printf("sub="); print(v10c);
v10c=v8c*v9c;
printf("mul="); print(v10c);
v10c=v8c/v9c;
printf("div="); print(v10c);
printf("-----------\n");
v10c=v8c+v9c;
printf("add="); print(v10c);
v10c=v8c-v9c;
printf("sub="); print(v10c);
v10c=v8c*v9c;
printf("mul="); print(v10c);
v10c=v8c/v9c;
printf("div="); print(v10c);
v10c=v8c*v8c;
printf("sqr(kinda)="); print(v10c);
float cab=cabs(v8c);
printf("abs=%f\n",cab);
v10c=ccos(v8c);
printf("cos="); print(v10c);
v10c=csin(v8c);
printf("sin="); print(v10c);
v10c=cpow(v8c,v8c);
printf("ztoz="); print(v10c);
v10c=cpow(v8c,po);
printf("pow="); print(v10c);
v10c=cexp(v8c);
printf("exp="); print(v10c);
v10c=ccosh(v8c);
printf("cosh="); print(v10c);
v10c=csinh(v8c);
printf("sinh="); print(v10c);
/* cab=cmag(v8c);
printf("cmag=%f\n",cab); */
printf("cmag=abs????\n");
cab=carg(v8c);
printf("carg=%f\n",cab);
v10c=clog(v8c);
printf("log="); print(v10c);
v10c=clog10(v8c);
printf("log10="); print(v10c);
/* v10c=clog2(v8c); // not in lucy's compiler
printf("log2="); print(v10c); */
v10c=cacos(v8c);
printf("acos="); print(v10c);
v10c=casin(v8c);
printf("asin="); print(v10c);
v10c=catan(v8c);
printf("atan="); print(v10c);
v10c=ctan(v8c);
printf("tan="); print(v10c);
v10c=cacosh(v8c);
printf("acosh="); print(v10c);
v10c=casinh(v8c);
printf("asinh="); print(v10c);
v10c=catanh(v8c);
printf("atanh="); print(v10c);
v10c=ctanh(v8c);
printf("tanh="); print(v10c);
v10c=csqrt(v8c);
printf("sqrt="); print(v10c);
v10c=conj(v8c);
printf("conj="); print(v10c);
v10c=cproj(v8c);
printf("proj="); print(v10c);
v10c=cproj(INFINITY+I*3.0);
printf("cproj(Inf,3i)="); print(v10c);
v10c=cproj(INFINITY-I*3.0);
printf("cproj(Inf,-3i)="); print(v10c);
v10c=cproj(2.0+I*INFINITY);
printf("cproj(2,Infi)="); print(v10c);
v10c=cproj(2.0-I*INFINITY);
printf("cproj(2,-Infi)="); print(v10c);
}
