/*********************************************************
   2d vector class
   Copyright © 2021 Mark Craig

   https://www.youtube.com/MrMcSoftware
**********************************************************/

#ifndef _VEC2_H
#define _VEC2_H

#include <cmath>
#include <iostream>
#include <cassert>
#ifdef VEC_USE_SWIZZLE
#define VEC_USE_SWIZZLE_SETTING
#undef VEC_USE_SWIZZLE
#endif
#ifdef VEC_USE_MAT
#include "mat2.h"

class mat2;
#endif

// Warning: anonymous unions and structs are not guaranteed to work in every
//          compiler/C++ version

class vec2
	{
	public:
		union
			{
			struct { float x,y; };
			struct { float s,t; };
			struct { float u,v; };
			struct { float V[2]; };
			};

		vec2() { x=y=0; }

		vec2(float cx, float cy) { x=cx; y=cy; }

		vec2(float cx) { x=y=cx; }

		vec2(const vec2 &v) { x=v.x; y=v.y; }

		vec2(float v[2]) { x=v[0]; y=v[1]; }

#ifndef VEC_USE_SWIZZLE
		inline vec2 yx() const
			{
			return(vec2(y,x));
			}
#endif

		inline float dot() const
			{
			float r=x*x+y*y;
			return(r);
			}

		inline float dot(const vec2 &q) const
			{
			float r=x*q.x+y*q.y;
			return(r);
			}

		inline float length() const
			{
			float r=sqrt(x*x+y*y);
			return(r);
			}

		inline vec2 const normalized() const
			{
			float mag=sqrt(x*x+y*y);
			if (mag!=0.0)
				{
				vec2 r;
				r.x=x/mag; r.y=y/mag;
				return(r);
				}
			return(vec2(0.0,0.0));
			}

		inline float normalize()
			{
			float mag=sqrt(x*x+y*y);
			if (mag!=0.0) { x/=mag; y/=mag; }
			else { x=y=0.0; }
			return(mag);
			}

		inline float operator[] (int i) const
			{
			assert((i>=0)&&(i<2));
			return(V[i]);
			}

		inline float& operator[] (int i)
			{
			assert((i>=0)&&(i<2));
			return(V[i]);
			}
	};

vec2 operator+ (const vec2 &L, const vec2 &R)
	{
	vec2 c; c.x=L.x+R.x; c.y=L.y+R.y; return(c);
	}

vec2 operator+ (const vec2 &L, const float &R)
	{
	vec2 c; c.x=L.x+R; c.y=L.y+R; return(c);
	}

vec2 operator+ (const float &L, const vec2 &R)
	{
	vec2 c; c.x=L+R.x; c.y=L+R.y; return(c);
	}

vec2 operator- (const vec2 &R)
	{
	vec2 c; c.x=-R.x; c.y=-R.y; return(c);
	}

vec2 operator- (const vec2 &L, const vec2 &R)
	{
	vec2 c; c.x=L.x-R.x; c.y=L.y-R.y; return(c);
	}

vec2 operator- (const vec2 &L, const float &R)
	{
	vec2 c; c.x=L.x-R; c.y=L.y-R; return(c);
	}

vec2 operator- (const float &L, const vec2 &R)
	{
	vec2 c; c.x=L-R.x; c.y=L-R.y; return(c);
	}

vec2 operator* (const vec2 &L, const vec2 &R)
	{
	vec2 c;
	c.x=R.x*L.x; c.y=R.y*L.y;
	return(c);
	}

vec2 operator* (const float &L, const vec2 &R)
	{
	vec2 c;
	c.x=R.x*L; c.y=R.y*L;
	return(c);
	}

vec2 operator* (const vec2 &L, const float &R)
	{
	return(R*L);
	}

vec2 operator/ (const vec2 &L, const vec2 &R)
	{
	vec2 c;
	c.x=L.x/R.x; c.y=L.y/R.y;
	return(c);
	}

vec2 operator/ (const vec2 &L, const float &R)
	{
	vec2 c;
	c.x=L.x/R; c.y=L.y/R;
	return(c);
	}

vec2& operator+= (vec2 &L, const vec2 &R)
	{
	L.x+=R.x; L.y+=R.y;
	return(L);
	}

vec2& operator+= (vec2 &L, const float &R)
	{
	L.x+=R; L.y+=R;
	return(L);
	}

vec2& operator-= (vec2 &L, const vec2 &R)
	{
	L.x-=R.x; L.y-=R.y;
	return(L);
	}

vec2& operator-= (vec2 &L, const float &R)
	{
	L.x-=R; L.y-=R;
	return(L);
	}

vec2& operator*= (vec2 &L, const vec2 &R)
	{
	L.x*=R.x; L.y*=R.y;
	return(L);
	}

vec2& operator*= (vec2 &L, const float &R)
	{
	L.x*=R; L.y*=R;
	return(L);
	}

#ifdef VEC_USE_MAT
vec2& operator*= (vec2 &L, const mat2 &R)
	{
	L=L*R;
	return(L);
	}
#endif

vec2& operator/= (vec2 &L, const vec2 &R)
	{
	L.x/=R.x; L.y/=R.y;
	return(L);
	}

vec2& operator/= (vec2 &L, const float &R)
	{
	L.x/=R; L.y/=R;
	return(L);
	}

vec2& operator++ (vec2 &R)
	{
	++R.x; ++R.y;
	return(R);
	}

vec2 operator++ (vec2 &L, int)
	{
	vec2 c=L;
	L.x++; L.y++;
	return(c);
	}

vec2& operator-- (vec2 &R)
	{
	--R.x; --R.y;
	return(R);
	}

vec2 operator-- (vec2 &L, int)
	{
	vec2 c=L;
	L.x--; L.y--;
	return(c);
	}

#ifdef EPSILONCOMP
#ifdef EPSILONCOMPREL
#ifndef VMCQ_NEEDMAX
#define eq(a,b) (fabs(a-(b))<EPSILONCOMP*std::max(fabs(a),fabs(b)))
#define ne(a,b) (fabs(a-(b))>=EPSILONCOMP*std::max(fabs(a),fabs(b)))
#else
#define eq(a,b) (fabs(a-(b))<EPSILONCOMP*((fabs(a)>fabs(b))?fabs(a):fabs(b)))
#define ne(a,b) (fabs(a-(b))>=EPSILONCOMP*((fabs(a)>fabs(b))?fabs(a):fabs(b)))
#endif
#else
#define eq(a,b) (fabs(a-(b))<EPSILONCOMP)
#define ne(a,b) (fabs(a-(b))>=EPSILONCOMP)
#endif

bool operator== (const vec2 &L, const vec2 &R)
	{
	return((eq(L.x,R.x))&&(eq(L.y,R.y)));
	}

bool operator!= (const vec2 &L, const vec2 &R)
	{
	return((ne(L.x,R.x))||(ne(L.y,R.y)));
	}

#undef eq
#undef ne

#else

bool operator== (const vec2 &L, const vec2 &R)
	{
	return((L.x==R.x)&&(L.y==R.y));
	}

bool operator!= (const vec2 &L, const vec2 &R)
	{
	return((L.x!=R.x)||(L.y!=R.y));
	}

#endif

std::ostream& operator<< (std::ostream &os, const vec2 &R)
	{
	os << "(" << R.x << "," << R.y << ")";
	return(os);
	}

#define bvec2 vec2

#ifdef VEC_USE_SWIZZLE_SETTING
#define VEC_USE_SWIZZLE
#undef VEC_USE_SWIZZLE_SETTING
#endif
#endif
