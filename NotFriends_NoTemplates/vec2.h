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

#define eq(a,b) (fabs(a-b)<EPSILONCOMP)
#define ne(a,b) (fabs(a-b)>=EPSILONCOMP)

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

#endif
