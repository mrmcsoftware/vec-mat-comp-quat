/*********************************************************
   2x2 matrix class
   Copyright © 2021 Mark Craig

   https://www.youtube.com/MrMcSoftware
**********************************************************/

#ifndef _MAT2_H
#define _MAT2_H

#include <cstdio>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "vec2.h"

class mat2
	{
	public:
		union
			{
			struct { float m[2][2]; };
			struct { float M[4]; };
			struct { float x0,x1,y0,y1; };
			};

		mat2() { x0=y0=x1=y1=0; }

		mat2(float X0) { y0=x1=0; x0=y1=X0; }

		mat2(float X0, float Y0, float X1, float Y1) { x0=X0; y0=Y0; x1=X1; y1=Y1; }

		mat2(vec2 v1, vec2 v2) { x0=v1.x; y0=v1.y; x1=v2.x; y1=v2.y; }

		mat2(const mat2 &v) { x0=v.x0; y0=v.y0; x1=v.x1; y1=v.y1; }

		inline mat2 const transpose() const
			{
			mat2 trans;
			trans.m[0][0]=m[0][0]; trans.m[1][0]=m[0][1];
			trans.m[0][1]=m[1][0]; trans.m[1][1]=m[1][1];
			return(trans);
			}

		inline float const determinant() const
			{
			return(m[0][0]*m[1][1]-m[1][0]*m[0][1]);
			}

		inline mat2 const inverse() const
			{
			float invdet=1.0/(m[0][0]*m[1][1]-m[1][0]*m[0][1]);
			mat2 inv;
			inv.m[0][0]=m[1][1]*invdet;
			inv.m[1][0]=-m[1][0]*invdet;
			inv.m[0][1]=-m[0][1]*invdet;
			inv.m[1][1]=m[0][0]*invdet;
			return(inv);
			}

		inline void const print(int nl=1) const
			{
			printf("| %9.4f %9.4f |\n",m[0][0],m[0][1]);
			printf("| %9.4f %9.4f |\n",m[1][0],m[1][1]);
			if (nl) { printf("\n"); }
			}
	};

mat2 operator+ (const mat2 &L, const mat2 &R)
	{
	mat2 c;
	c.m[0][0]=L.m[0][0]+R.m[0][0]; c.m[1][0]=L.m[1][0]+R.m[1][0];
	c.m[0][1]=L.m[0][1]+R.m[0][1]; c.m[1][1]=L.m[1][1]+R.m[1][1];
	return(c);
	}

mat2 operator- (const mat2 &R)
	{
	mat2 c;
	c.x0=-R.x0; c.y0=-R.y0;
	c.x1=-R.x1; c.y1=-R.y1;
	return(c);
	}

mat2 operator- (const mat2 &L, const mat2 &R)
	{
	mat2 c;
	c.m[0][0]=L.m[0][0]-R.m[0][0]; c.m[1][0]=L.m[1][0]-R.m[1][0];
	c.m[0][1]=L.m[0][1]-R.m[0][1]; c.m[1][1]=L.m[1][1]-R.m[1][1];
	return(c);
	}

vec2 operator* (const mat2 &L, const vec2 &R)
	{
	vec2 c;
	c.x=R.x*L.x0+R.y*L.x1;
	c.y=R.x*L.y0+R.y*L.y1;
	return(c);
	}

vec2 operator* (const vec2 &L, const mat2 &R)
	{
	vec2 c;
	c.x=L.x*R.x0+L.y*R.y0;
	c.y=L.x*R.x1+L.y*R.y1;
	return(c);
	}

mat2 operator* (const mat2 &L, const float &R)
	{
	mat2 c;
	c.m[0][0]=L.m[0][0]*R; c.m[1][0]=L.m[1][0]*R;
	c.m[0][1]=L.m[0][1]*R; c.m[1][1]=L.m[1][1]*R;
	return(c);
	}

mat2 operator* (const float &L, const mat2 &R)
	{
	return(R*L);
	}

mat2 operator* (const mat2 &L, const mat2 &R)
	{
	mat2 c;
	c.m[0][0]=R.m[0][0]*L.m[0][0]+R.m[1][0]*L.m[0][1];
	c.m[1][0]=R.m[0][0]*L.m[1][0]+R.m[1][0]*L.m[1][1];
	c.m[0][1]=R.m[0][1]*L.m[0][0]+R.m[1][1]*L.m[0][1];
	c.m[1][1]=R.m[0][1]*L.m[1][0]+R.m[1][1]*L.m[1][1];
	return(c);
	}

mat2 operator/ (const mat2 &L, const float &R)
	{
	mat2 c;
	c.m[0][0]=L.m[0][0]/R; c.m[1][0]=L.m[1][0]/R;
	c.m[0][1]=L.m[0][1]/R; c.m[1][1]=L.m[1][1]/R;
	return(c);
	}

mat2 operator/ (const mat2 &L, const mat2 &R)
	{
	return(L*R.inverse());
	}

mat2& operator+= (mat2 &L, const mat2 &R)
	{
	L=L+R;
	return(L);
	}

mat2& operator-= (mat2 &L, const mat2 &R)
	{
	L=L-R;
	return(L);
	}

mat2& operator*= (mat2 &L, const mat2 &R)
	{
	L=L*R;
	return(L);
	}

mat2& operator*= (mat2 &L, const float &R)
	{
	L=L*R;
	return(L);
	}

mat2& operator/= (mat2 &L, const mat2 &R)
	{
	L=L/R;
	return(L);
	}

mat2& operator/= (mat2 &L, const float &R)
	{
	L=L/R;
	return(L);
	}

#ifdef EPSILONCOMP

#define eq(a,b) (fabs(a-b)<EPSILONCOMP)
#define ne(a,b) (fabs(a-b)>=EPSILONCOMP)

bool operator== (const mat2 &L, const mat2 &R)
	{
	return((eq(L.M[0],R.M[0]))&&(eq(L.M[1],R.M[1]))
		&&(eq(L.M[2],R.M[2]))&&(eq(L.M[3],R.M[3])));
	}

bool operator!= (const mat2 &L, const mat2 &R)
	{
	return((ne(L.M[0],R.M[0]))||(ne(L.M[1],R.M[1]))
		||(ne(L.M[2],R.M[2]))||(ne(L.M[3],R.M[3])));
	}

#undef eq
#undef ne

#else

bool operator== (const mat2 &L, const mat2 &R)
	{
	return((L.M[0]==R.M[0])&&(L.M[1]==R.M[1])&&(L.M[2]==R.M[2])
		&&(L.M[3]==R.M[3]));
	}

bool operator!= (const mat2 &L, const mat2 &R)
	{
	return((L.M[0]!=R.M[0])||(L.M[1]!=R.M[1])||(L.M[2]!=R.M[2])
		||(L.M[3]!=R.M[3]));
	}

#endif

#define FORM std::setprecision(4) << std::setw(9)

std::ostream& operator<< (std::ostream &os, const mat2 &R)
	{
	std::ios_base::fmtflags f = os.flags();
	os << std::fixed;
	os << std::endl;
	os << "| " << FORM << R.x0 << " " << FORM << R.x1 << " |" << std::endl;
	os << "| " << FORM << R.y0 << " " << FORM << R.y1 << " |" << std::endl;
	os.flags(f);
	return(os);
	}

#endif
