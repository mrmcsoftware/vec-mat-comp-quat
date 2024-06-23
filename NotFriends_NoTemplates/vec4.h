/*********************************************************
   4d vector class
   Copyright © 2021 Mark Craig

   https://www.youtube.com/MrMcSoftware
**********************************************************/

#ifndef _VEC4_H
#define _VEC4_H

#include <cmath>
#include <iostream>
#include <cassert>
#ifdef VEC_USE_SWIZZLE
#define VEC_USE_SWIZZLE_SETTING
#undef VEC_USE_SWIZZLE
#endif
#include "vec2.h"
#include "vec3.h"
#ifdef VEC_USE_MAT
#include "mat4.h"

class mat4;
#endif

class vec4
	{
	public:
		union
			{
			struct { float x,y,z,w; };
			struct { float r,g,b,a; };
			struct { float V[4]; };
			};

		vec4() { x=y=z=w=0; }

		vec4(float cx, float cy, float cz, float cw) { x=cx; y=cy; z=cz; w=cw; }

		vec4(float cx) { x=y=z=w=cx; }

		vec4(vec3 v, float cw) { x=v.x; y=v.y; z=v.z; w=cw; }

		vec4(const vec4 &v) { x=v.x; y=v.y; z=v.z; w=v.w; }

		vec4(float v[4]) { x=v[0]; y=v[1]; z=v[2]; w=v[3]; }

#ifndef VEC_USE_SWIZZLE
		inline vec2 xy() const
			{
			return(vec2(x,y));
			}

		inline vec3 xyz() const
			{
			return(vec3(x,y,z));
			}
#endif

		inline float dot() const
			{
			float r=x*x+y*y+z*z+w*w;
			return(r);
			}

		inline float dot(const vec4 &q) const
			{
			float r=x*q.x+y*q.y+z*q.z+w*q.w;
			return(r);
			}

		inline float length() const
			{
			float r=sqrt(x*x+y*y+z*z+w*w);
			return(r);
			}

		inline vec4 const normalized() const
			{
			float mag=sqrt(x*x+y*y+z*z+w*w);
			if (mag!=0.0)
				{
				vec4 r;
				r.x=x/mag; r.y=y/mag; r.z=z/mag; r.w=w/mag;
				return(r);
				}
			return(vec4(0.0,0.0,0.0,0.0));
			}

		inline float normalize()
			{
			float mag=sqrt(x*x+y*y+z*z+w*w);
			if (mag!=0.0) { x/=mag; y/=mag; z/=mag; w/=mag; }
			else { x=y=z=w=0.0; }
			return(mag);
			}

	inline float operator[] (int i) const { return(V[i]); }

	inline float& operator[] (int i) { return(V[i]); }
	};

vec4 operator+ (const vec4 &L, const vec4 &R)
	{
	vec4 c; c.x=L.x+R.x; c.y=L.y+R.y; c.z=L.z+R.z; c.w=L.w+R.w; return(c);
	}

vec4 operator+ (const vec4 &L, const float &R)
	{
	vec4 c; c.x=L.x+R; c.y=L.y+R; c.z=L.z+R; c.w=L.w+R; return(c);
	}

vec4 operator+ (const float &L, const vec4 &R)
	{
	vec4 c; c.x=L+R.x; c.y=L+R.y; c.z=L+R.z; c.w=L+R.w; return(c);
	}

vec4 operator- (const vec4 &R)
	{
	vec4 c; c.x=-R.x; c.y=-R.y; c.z=-R.z; c.w=-R.w; return(c);
	}

vec4 operator- (const vec4 &L, const vec4 &R)
	{
	vec4 c; c.x=L.x-R.x; c.y=L.y-R.y; c.z=L.z-R.z; c.w=L.w-R.w; return(c);
	}

vec4 operator- (const vec4 &L, const float &R)
	{
	vec4 c; c.x=L.x-R; c.y=L.y-R; c.z=L.z-R; c.w=L.w-R; return(c);
	}

vec4 operator- (const float &L, const vec4 &R)
	{
	vec4 c; c.x=L-R.x; c.y=L-R.y; c.z=L-R.z; c.w=L-R.w; return(c);
	}

vec4 operator* (const vec4 &L, const vec4 &R)
	{
	vec4 c;
	c.x=R.x*L.x; c.y=R.y*L.y; c.z=R.z*L.z; c.w=R.w*L.w;
	return(c);
	}

vec4 operator* (const float &L, const vec4 &R)
	{
	vec4 c;
	c.x=R.x*L; c.y=R.y*L; c.z=R.z*L; c.w=R.w*L;
	return(c);
	}

vec4 operator* (const vec4 &L, const float &R)
	{
	return(R*L);
	}

vec4 operator/ (const vec4 &L, const vec4 &R)
	{
	vec4 c;
	c.x=L.x/R.x; c.y=L.y/R.y; c.z=L.z/R.z; c.w=L.w/R.w;
	return(c);
	}

vec4 operator/ (const vec4 &L, const float &R)
	{
	vec4 c;
	c.x=L.x/R; c.y=L.y/R; c.z=L.z/R; c.w=L.w/R;
	return(c);
	}

vec4& operator+= (vec4 &L, const vec4 &R)
	{
	L.x+=R.x; L.y+=R.y; L.z+=R.z; L.w+=R.w;
	return(L);
	}

vec4& operator+= (vec4 &L, const float &R)
	{
	L.x+=R; L.y+=R; L.z+=R; L.w+=R;
	return(L);
	}

vec4& operator-= (vec4 &L, const vec4 &R)
	{
	L.x-=R.x; L.y-=R.y; L.z-=R.z; L.w-=R.w;
	return(L);
	}

vec4& operator-= (vec4 &L, const float &R)
	{
	L.x-=R; L.y-=R; L.z-=R; L.w-=R;
	return(L);
	}

vec4& operator*= (vec4 &L, const vec4 &R)
	{
	L.x*=R.x; L.y*=R.y; L.z*=R.z; L.w*=R.w;
	return(L);
	}

vec4& operator*= (vec4 &L, const float &R)
	{
	L.x*=R; L.y*=R; L.z*=R; L.w*=R;
	return(L);
	}

#ifdef VEC_USE_MAT
vec4& operator*= (vec4 &L, const mat4 &R)
	{
	L=L*R;
	return(L);
	}
#endif

vec4& operator/= (vec4 &L, const vec4 &R)
	{
	L.x/=R.x; L.y/=R.y; L.z/=R.z; L.w/=R.w;
	return(L);
	}

vec4& operator/= (vec4 &L, const float &R)
	{
	L.x/=R; L.y/=R; L.z/=R; L.w/=R;
	return(L);
	}

vec4& operator++ (vec4 &R)
	{
	++R.x; ++R.y; ++R.z; ++R.w;
	return(R);
	}

vec4 operator++ (vec4 &L, int)
	{
	vec4 c=L;
	L.x++; L.y++; L.z++; L.w++;
	return(c);
	}

vec4& operator-- (vec4 &R)
	{
	--R.x; --R.y; --R.z; --R.w;
	return(R);
	}

vec4 operator-- (vec4 &L, int)
	{
	vec4 c=L;
	L.x--; L.y--; L.z--; L.w--;
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

bool operator== (const vec4 &L, const vec4 &R)
	{
	return((eq(L.x,R.x))&&(eq(L.y,R.y))&&(eq(L.z,R.z))&&(eq(L.w,R.w)));
	}

bool operator!= (const vec4 &L, const vec4 &R)
	{
	return((ne(L.x,R.x))||(ne(L.y,R.y))||(ne(L.z,R.z))||(ne(L.w,R.w)));
	}

#undef eq
#undef ne

#else

bool operator== (const vec4 &L, const vec4 &R)
	{
	return((L.x==R.x)&&(L.y==R.y)&&(L.z==R.z)&&(L.w==R.w));
	}

bool operator!= (const vec4 &L, const vec4 &R)
	{
	return((L.x!=R.x)||(L.y!=R.y)||(L.z!=R.z)||(L.w!=R.w));
	}

#endif

std::ostream& operator<< (std::ostream &os, const vec4 &R)
	{
	os << "(" << R.x << "," << R.y << "," << R.z << "," << R.w << ")";
	return(os);
	}

#ifdef VEC_USE_SWIZZLE_SETTING
#define VEC_USE_SWIZZLE
#undef VEC_USE_SWIZZLE_SETTING
#endif
#endif
