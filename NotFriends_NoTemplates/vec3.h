/*********************************************************
   3d vector class
   Copyright © 2021 Mark Craig

   https://www.youtube.com/MrMcSoftware
**********************************************************/

#ifndef _VEC3_H
#define _VEC3_H

#include <cmath>
#include <iostream>
#include <cassert>
#ifdef VEC_USE_SWIZZLE
#define VEC_USE_SWIZZLE_SETTING
#undef VEC_USE_SWIZZLE
#endif
#include "vec2.h"
#ifdef VEC_USE_MAT
#include "mat3.h"

class mat3;
#endif

class vec3
	{
	public:
		union
			{
			struct { float x,y,z; };
			struct { float r,g,b; };
			struct { float V[3]; };
			};

		vec3() { x=y=z=0; }

		vec3(float cx, float cy, float cz) { x=cx; y=cy; z=cz; }

		vec3(float cx) { x=y=z=cx; }

		vec3(vec2 v, float cz) { x=v.x; y=v.y; z=cz; }

		vec3(const vec3 &v) { x=v.x; y=v.y; z=v.z; }

		vec3(float v[3]) { x=v[0]; y=v[1]; z=v[2]; }

#ifndef VEC_USE_SWIZZLE
		inline vec2 xy() const
			{
			return(vec2(x,y));
			}
#endif

		inline float dot() const
			{
			float r=x*x+y*y+z*z;
			return(r);
			}

		inline float dot(const vec3 &q) const
			{
			float r=x*q.x+y*q.y+z*q.z;
			return(r);
			}

		inline vec3 cross(const vec3 &q) const
			{
			vec3 v1;
			v1.x=y*q.z-z*q.y;
			v1.y=z*q.x-x*q.z;
			v1.z=x*q.y-y*q.x;
			return(v1);
			}

		inline float length() const
			{
			float r=sqrt(x*x+y*y+z*z);
			return(r);
			}

		inline vec3 const normalized() const
			{
			float mag=sqrt(x*x+y*y+z*z);
			if (mag!=0.0)
				{
				vec3 r;
				r.x=x/mag; r.y=y/mag; r.z=z/mag;
				return(r);
				}
			return(vec3(0.0,0.0,0.0));
			}

		inline float normalize()
			{
			float mag=sqrt(x*x+y*y+z*z);
			if (mag!=0.0) { x/=mag; y/=mag; z/=mag; }
			else { x=y=z=0.0; }
			return(mag);
			}

		// this one used if "const vec3 variable" or sometimes if "var1=var2[2]"
		//    Note: apparently, T& will also work
		inline float operator[] (int i) const
			{
			assert((i>=0)&&(i<3));
			return(V[i]);
			}

		// this one used if "var1=var2[2]" or if "var2[2]=var1"
		inline float& operator[] (int i)
			{
			assert((i>=0)&&(i<3));
			return(V[i]);
			}
	};

vec3 operator+ (const vec3 &L, const vec3 &R)
	{
	vec3 c; c.x=L.x+R.x; c.y=L.y+R.y; c.z=L.z+R.z; return(c);
	}

vec3 operator+ (const vec3 &L, const float &R)
	{
	vec3 c; c.x=L.x+R; c.y=L.y+R; c.z=L.z+R; return(c);
	}

vec3 operator+ (const float &L, const vec3 &R)
	{
	vec3 c; c.x=L+R.x; c.y=L+R.y; c.z=L+R.z; return(c);
	}

vec3 operator- (const vec3 &R)
	{
	vec3 c; c.x=-R.x; c.y=-R.y; c.z=-R.z; return(c);
	}

vec3 operator- (const vec3 &L, const vec3 &R)
	{
	vec3 c; c.x=L.x-R.x; c.y=L.y-R.y; c.z=L.z-R.z; return(c);
	}

vec3 operator- (const vec3 &L, const float &R)
	{
	vec3 c; c.x=L.x-R; c.y=L.y-R; c.z=L.z-R; return(c);
	}

vec3 operator- (const float &L, const vec3 &R)
	{
	vec3 c; c.x=L-R.x; c.y=L-R.y; c.z=L-R.z; return(c);
	}

vec3 operator* (const vec3 &L, const vec3 &R)
	{
	vec3 c;
	c.x=R.x*L.x; c.y=R.y*L.y; c.z=R.z*L.z;
	return(c);
	}

vec3 operator* (const float &L, const vec3 &R)
	{
	vec3 c;
	c.x=R.x*L; c.y=R.y*L; c.z=R.z*L;
	return(c);
	}

vec3 operator* (const vec3 &L, const float &R)
	{
	return(R*L);
	}

vec3 operator/ (const vec3 &L, const vec3 &R)
	{
	vec3 c;
	c.x=L.x/R.x; c.y=L.y/R.y; c.z=L.z/R.z;
	return(c);
	}

vec3 operator/ (const vec3 &L, const float &R)
	{
	vec3 c;
	c.x=L.x/R; c.y=L.y/R; c.z=L.z/R;
	return(c);
	}

vec3& operator+= (vec3 &L, const vec3 &R)
	{
	L.x+=R.x; L.y+=R.y; L.z+=R.z;
	return(L);
	}

vec3& operator+= (vec3 &L, const float &R)
	{
	L.x+=R; L.y+=R; L.z+=R;
	return(L);
	}

vec3& operator-= (vec3 &L, const vec3 &R)
	{
	L.x-=R.x; L.y-=R.y; L.z-=R.z;
	return(L);
	}

vec3& operator-= (vec3 &L, const float &R)
	{
	L.x-=R; L.y-=R; L.z-=R;
	return(L);
	}

vec3& operator*= (vec3 &L, const vec3 &R)
	{
	L.x*=R.x; L.y*=R.y; L.z*=R.z;
	return(L);
	}

vec3& operator*= (vec3 &L, const float &R)
	{
	L.x*=R; L.y*=R; L.z*=R;
	return(L);
	}

#ifdef VEC_USE_MAT
vec3& operator*= (vec3 &L, const mat3 &R)
	{
	L=L*R;
	return(L);
	}
#endif

vec3& operator/= (vec3 &L, const vec3 &R)
	{
	L.x/=R.x; L.y/=R.y; L.z/=R.z;
	return(L);
	}

vec3& operator/= (vec3 &L, const float &R)
	{
	L.x/=R; L.y/=R; L.z/=R;
	return(L);
	}

vec3& operator++ (vec3 &R)
	{
	++R.x; ++R.y; ++R.z;
	return(R);
	}

vec3 operator++ (vec3 &L, int)
	{
	vec3 c=L;
	L.x++; L.y++; L.z++;
	return(c);
	}

vec3& operator-- (vec3 &R)
	{
	--R.x; --R.y; --R.z;
	return(R);
	}

vec3 operator-- (vec3 &L, int)
	{
	vec3 c=L;
	L.x--; L.y--; L.z--;
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

bool operator== (const vec3 &L, const vec3 &R)
	{
	return((eq(L.x,R.x))&&(eq(L.y,R.y))&&(eq(L.z,R.z)));
	}

bool operator!= (const vec3 &L, const vec3 &R)
	{
	return((ne(L.x,R.x))||(ne(L.y,R.y))||(ne(L.z,R.z)));
	}

#undef eq
#undef ne

#else

bool operator== (const vec3 &L, const vec3 &R)
	{
	return((L.x==R.x)&&(L.y==R.y)&&(L.z==R.z));
	}

bool operator!= (const vec3 &L, const vec3 &R)
	{
	return((L.x!=R.x)||(L.y!=R.y)||(L.z!=R.z));
	}

#endif

std::ostream& operator<< (std::ostream &os, const vec3 &R)
	{
	os << "(" << R.x << "," << R.y << "," << R.z << ")";
	return(os);
	}

#ifdef VEC_USE_SWIZZLE_SETTING
#define VEC_USE_SWIZZLE
#undef VEC_USE_SWIZZLE_SETTING
#endif
#endif
