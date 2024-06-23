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
#include "swizzle.h"
#endif
#ifdef VEC_USE_MAT
#include "mat2.h"

template <class T>
class Mat2;
#endif

// Warning: anonymous unions and structs are not guaranteed to work in every
//          compiler/C++ version

template <class T>
class Vec2
	{
	public:
		union
			{
			struct { T x,y; };
			struct { T s,t; };
			struct { T u,v; };
			struct { T V[2]; };
#ifdef VEC_USE_SWIZZLE
			swizzle2<Vec2<T>,T,1,0> yx;
#endif
			};

		Vec2<T>() { x=y=0; }

		Vec2<T>(T cx, T cy) { x=cx; y=cy; }

		Vec2<T>(T cx) { x=y=cx; }

		Vec2<T>(const Vec2<T> &v) { x=v.x; y=v.y; }

		Vec2<T>(T v[2]) { x=v[0]; y=v[1]; }

#ifndef VEC_USE_SWIZZLE
		inline Vec2<T> yx() const
			{
			return(Vec2<T>(y,x));
			}
#endif

		inline T dot() const
			{
			T r=x*x+y*y;
			return(r);
			}

		inline T dot(const Vec2<T> &q) const
			{
			T r=x*q.x+y*q.y;
			return(r);
			}

		inline T length() const
			{
			T r=sqrt(x*x+y*y);
			return(r);
			}

		inline Vec2<T> const normalized() const
			{
			T mag=sqrt(x*x+y*y);
			if (mag!=0.0)
				{
				Vec2<T> r;
				r.x=x/mag; r.y=y/mag;
				return(r);
				}
			return(Vec2<T>(0.0,0.0));
			}

		inline T normalize()
			{
			T mag=sqrt(x*x+y*y);
			if (mag!=0.0) { x/=mag; y/=mag; }
			else { x=y=0.0; }
			return(mag);
			}

		inline T operator[] (int i) const
			{
			assert((i>=0)&&(i<2));
			return(V[i]);
			}

		inline T& operator[] (int i)
			{
			assert((i>=0)&&(i<2));
			return(V[i]);
			}

	inline Vec2<T> operator+ (const Vec2<T> &R) const
		{
		Vec2<T> c; c.x=x+R.x; c.y=y+R.y; return(c);
		}

	inline Vec2<T> operator+ (const T &R) const
		{
		Vec2<T> c; c.x=x+R; c.y=y+R; return(c);
		}

	inline Vec2<T> operator- () const
		{
		Vec2<T> c; c.x=-x; c.y=-y; return(c);
		}

	inline Vec2<T> operator- (const Vec2<T> &R) const
		{
		Vec2<T> c; c.x=x-R.x; c.y=y-R.y; return(c);
		}

	inline Vec2<T> operator- (const T &R) const
		{
		Vec2<T> c; c.x=x-R; c.y=y-R; return(c);
		}

	inline Vec2<T> operator* (const Vec2<T> &R) const
		{
		Vec2<T> c;
		c.x=R.x*x; c.y=R.y*y;
		return(c);
		}

	inline Vec2<T> operator* (const T &R) const
		{
		return(R*(*this));
		}

	inline Vec2<T> operator/ (const Vec2<T> &R) const
		{
		Vec2<T> c;
		c.x=x/R.x; c.y=y/R.y;
		return(c);
		}

	inline Vec2<T> operator/ (const T &R) const
		{
		Vec2<T> c;
		c.x=x/R; c.y=y/R;
		return(c);
		}

	inline Vec2<T>& operator+= (const Vec2<T> &R)
		{
		x+=R.x; y+=R.y;
		return(*this);
		}

	inline Vec2<T>& operator+= (const T &R)
		{
		x+=R; y+=R;
		return(*this);
		}

	inline Vec2<T>& operator-= (const Vec2<T> &R)
		{
		x-=R.x; y-=R.y;
		return(*this);
		}

	inline Vec2<T>& operator-= (const T &R)
		{
		x-=R; y-=R;
		return(*this);
		}

	inline Vec2<T>& operator*= (const Vec2<T> &R)
		{
		x*=R.x; y*=R.y;
		return(*this);
		}

	inline Vec2<T>& operator*= (const T &R)
		{
		x*=R; y*=R;
		return(*this);
		}

#ifdef VEC_USE_MAT
	inline Vec2<T>& operator*= (const Mat2<T> &R)
		{
		*this=*this*R;
		return(*this);
		}
#endif

	inline Vec2<T>& operator/= (const Vec2<T> &R)
		{
		x/=R.x; y/=R.y;
		return(*this);
		}

	inline Vec2<T>& operator/= (const T &R)
		{
		x/=R; y/=R;
		return(*this);
		}

	inline Vec2<T>& operator++ ()
		{
		++x; ++y;
		return(*this);
		}

	inline Vec2<T> operator++ (int)
		{
		Vec2<T> c=(*this);
		x++; y++;
		return(c);
		}

	inline Vec2<T>& operator-- ()
		{
		--x; --y;
		return(*this);
		}

	inline Vec2<T> operator-- (int)
		{
		Vec2<T> c=(*this);
		x--; y--;
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

	inline bool operator== (const Vec2<T> &R) const
		{
		return((eq(x,R.x))&&(eq(y,R.y)));
		}

	inline bool operator!= (const Vec2<T> &R) const
		{
		return((ne(x,R.x))||(ne(y,R.y)));
		}

#undef eq
#undef ne

#else

	inline bool operator== (const Vec2<T> &R) const
		{
		return((x==R.x)&&(y==R.y));
		}

	inline bool operator!= (const Vec2<T> &R) const
		{
		return((x!=R.x)||(y!=R.y));
		}

#endif
	};

template <class T, class U>
Vec2<T> operator+ (const U &L, const Vec2<T> &R)
	{
	Vec2<T> c; c.x=L+R.x; c.y=L+R.y; return(c);
	}

template <class T, class U>
Vec2<T> operator- (const U &L, const Vec2<T> &R)
	{
	Vec2<T> c; c.x=L-R.x; c.y=L-R.y; return(c);
	}

template <class T, class U>
Vec2<T> operator* (const U &L, const Vec2<T> &R)
	{
	Vec2<T> c;
	c.x=R.x*L; c.y=R.y*L;
	return(c);
	}

template <class T>
std::ostream& operator<< (std::ostream &os, const Vec2<T> &R)
	{
	os << "(" << R.x << "," << R.y << ")";
	return(os);
	}

typedef Vec2<float> vec2;
typedef Vec2<int> ivec2;
typedef Vec2<bool> bvec2;

#endif
