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
class Vec2;

template <class T>
Vec2<T> operator+ (const Vec2<T> &L, const Vec2<T> &R);

template <class T, class U>
Vec2<T> operator+ (const Vec2<T> &L, const U &R);

template <class T, class U>
Vec2<T> operator+ (const U &L, const Vec2<T> &R);

template <class T>
Vec2<T> operator- (const Vec2<T> &R);

template <class T>
Vec2<T> operator- (const Vec2<T> &L, const Vec2<T> &R);

template <class T, class U>
Vec2<T> operator- (const Vec2<T> &L, const U &R);

template <class T, class U>
Vec2<T> operator- (const U &L, const Vec2<T> &R);

template <class T>
Vec2<T> operator* (const Vec2<T> &L, const Vec2<T> &R);

template <class T, class U>
Vec2<T> operator* (const U &L, const Vec2<T> &R);

template <class T, class U>
Vec2<T> operator* (const Vec2<T> &L, const U &R);

template <class T>
Vec2<T> operator/ (const Vec2<T> &L, const Vec2<T> &R);

template <class T, class U>
Vec2<T> operator/ (const Vec2<T> &L, const U &R);

template <class T>
Vec2<T>& operator+= (Vec2<T> &L, const Vec2<T> &R);

template <class T, class U>
Vec2<T>& operator+= (Vec2<T> &L, const U &R);

template <class T>
Vec2<T>& operator-= (Vec2<T> &L, const Vec2<T> &R);

template <class T, class U>
Vec2<T>& operator-= (Vec2<T> &L, const U &R);

template <class T>
Vec2<T>& operator*= (Vec2<T> &L, const Vec2<T> &R);

template <class T, class U>
Vec2<T>& operator*= (Vec2<T> &L, const U &R);

#ifdef VEC_USE_MAT
template <class T>
Vec2<T>& operator*= (Vec2<T> &L, const Mat2<T> &R);
#endif

template <class T>
Vec2<T>& operator/= (Vec2<T> &L, const Vec2<T> &R);

template <class T, class U>
Vec2<T>& operator/= (Vec2<T> &L, const U &R);

template <class T>
Vec2<T>& operator++ (Vec2<T> &R);

template <class T>
Vec2<T> operator++ (Vec2<T> &L, int);

template <class T>
Vec2<T>& operator-- (Vec2<T> &R);

template <class T>
Vec2<T> operator-- (Vec2<T> &L, int);

template <class T>
bool operator== (const Vec2<T> &L, const Vec2<T> &R);

template <class T>
bool operator!= (const Vec2<T> &L, const Vec2<T> &R);

template <class T>
std::ostream& operator<< (std::ostream &os, const Vec2<T> &R);

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

	friend Vec2 operator+<T> (const Vec2 &L, const Vec2 &R);
	friend Vec2 operator+<T> (const Vec2 &L, const T &R);
	friend Vec2 operator+<T> (const T &L, const Vec2 &R);
	friend Vec2 operator-<T> (const Vec2 &R);
	friend Vec2 operator-<T> (const Vec2 &L, const Vec2 &R);
	friend Vec2 operator-<T> (const Vec2 &L, const T &R);
	friend Vec2 operator-<T> (const T &L, const Vec2 &R);
	friend Vec2 operator*<T> (const Vec2 &L, const Vec2 &R);
	friend Vec2 operator*<T> (const T &L, const Vec2 &R);
	friend Vec2 operator*<T> (const Vec2 &L, const T &R);
	friend Vec2 operator/<T> (const Vec2 &L, const Vec2 &R);
	friend Vec2 operator/<T> (const Vec2 &L, const T &R);
	friend Vec2& operator+=<T> (Vec2 &L, const Vec2 &R);
	friend Vec2& operator+=<T> (Vec2 &L, const T &R);
	friend Vec2& operator-=<T> (Vec2 &L, const Vec2 &R);
	friend Vec2& operator-=<T> (Vec2 &L, const T &R);
	friend Vec2& operator*=<T> (Vec2 &L, const Vec2 &R);
	friend Vec2& operator*=<T> (Vec2 &L, const T &R);
#ifdef VEC_USE_MAT
	friend Vec2& operator*=<T> (Vec2 &L, const Mat2<T> &R);
#endif
	friend Vec2& operator/=<T> (Vec2 &L, const Vec2 &R);
	friend Vec2& operator/=<T> (Vec2 &L, const T &R);
	friend Vec2& operator++<T> (Vec2 &R);
	friend Vec2 operator++<T> (Vec2 &L, int);
	friend Vec2& operator--<T> (Vec2 &R);
	friend Vec2 operator--<T> (Vec2 &L, int);
	friend bool operator==<T> (const Vec2 &L, const Vec2 &R);
	friend bool operator!=<T> (const Vec2 &L, const Vec2 &R);
	friend std::ostream& operator<<<T> (std::ostream &os, const Vec2 &R);
	};

template <class T>
Vec2<T> operator+ (const Vec2<T> &L, const Vec2<T> &R)
	{
	Vec2<T> c; c.x=L.x+R.x; c.y=L.y+R.y; return(c);
	}

template <class T, class U>
Vec2<T> operator+ (const Vec2<T> &L, const U &R)
	{
	Vec2<T> c; c.x=L.x+R; c.y=L.y+R; return(c);
	}

template <class T, class U>
Vec2<T> operator+ (const U &L, const Vec2<T> &R)
	{
	Vec2<T> c; c.x=L+R.x; c.y=L+R.y; return(c);
	}

template <class T>
Vec2<T> operator- (const Vec2<T> &R)
	{
	Vec2<T> c; c.x=-R.x; c.y=-R.y; return(c);
	}

template <class T>
Vec2<T> operator- (const Vec2<T> &L, const Vec2<T> &R)
	{
	Vec2<T> c; c.x=L.x-R.x; c.y=L.y-R.y; return(c);
	}

template <class T, class U>
Vec2<T> operator- (const Vec2<T> &L, const U &R)
	{
	Vec2<T> c; c.x=L.x-R; c.y=L.y-R; return(c);
	}

template <class T, class U>
Vec2<T> operator- (const U &L, const Vec2<T> &R)
	{
	Vec2<T> c; c.x=L-R.x; c.y=L-R.y; return(c);
	}

template <class T>
Vec2<T> operator* (const Vec2<T> &L, const Vec2<T> &R)
	{
	Vec2<T> c;
	c.x=R.x*L.x; c.y=R.y*L.y;
	return(c);
	}

template <class T, class U>
Vec2<T> operator* (const U &L, const Vec2<T> &R)
	{
	Vec2<T> c;
	c.x=R.x*L; c.y=R.y*L;
	return(c);
	}

template <class T, class U>
Vec2<T> operator* (const Vec2<T> &L, const U &R)
	{
	return(R*L);
	}

template <class T>
Vec2<T> operator/ (const Vec2<T> &L, const Vec2<T> &R)
	{
	Vec2<T> c;
	c.x=L.x/R.x; c.y=L.y/R.y;
	return(c);
	}

template <class T, class U>
Vec2<T> operator/ (const Vec2<T> &L, const U &R)
	{
	Vec2<T> c;
	c.x=L.x/R; c.y=L.y/R;
	return(c);
	}

template <class T>
Vec2<T>& operator+= (Vec2<T> &L, const Vec2<T> &R)
	{
	L.x+=R.x; L.y+=R.y;
	return(L);
	}

template <class T, class U>
Vec2<T>& operator+= (Vec2<T> &L, const U &R)
	{
	L.x+=R; L.y+=R;
	return(L);
	}

template <class T>
Vec2<T>& operator-= (Vec2<T> &L, const Vec2<T> &R)
	{
	L.x-=R.x; L.y-=R.y;
	return(L);
	}

template <class T, class U>
Vec2<T>& operator-= (Vec2<T> &L, const U &R)
	{
	L.x-=R; L.y-=R;
	return(L);
	}

template <class T>
Vec2<T>& operator*= (Vec2<T> &L, const Vec2<T> &R)
	{
	L.x*=R.x; L.y*=R.y;
	return(L);
	}

template <class T, class U>
Vec2<T>& operator*= (Vec2<T> &L, const U &R)
	{
	L.x*=R; L.y*=R;
	return(L);
	}

#ifdef VEC_USE_MAT
template <class T>
Vec2<T>& operator*= (Vec2<T> &L, const Mat2<T> &R)
	{
	L=L*R;
	return(L);
	}
#endif

template <class T>
Vec2<T>& operator/= (Vec2<T> &L, const Vec2<T> &R)
	{
	L.x/=R.x; L.y/=R.y;
	return(L);
	}

template <class T, class U>
Vec2<T>& operator/= (Vec2<T> &L, const U &R)
	{
	L.x/=R; L.y/=R;
	return(L);
	}

template <class T>
Vec2<T>& operator++ (Vec2<T> &R)
	{
	++R.x; ++R.y;
	return(R);
	}

template <class T>
Vec2<T> operator++ (Vec2<T> &L, int)
	{
	Vec2<T> c=L;
	L.x++; L.y++;
	return(c);
	}

template <class T>
Vec2<T>& operator-- (Vec2<T> &R)
	{
	--R.x; --R.y;
	return(R);
	}

template <class T>
Vec2<T> operator-- (Vec2<T> &L, int)
	{
	Vec2<T> c=L;
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

template <class T>
bool operator== (const Vec2<T> &L, const Vec2<T> &R)
	{
	return((eq(L.x,R.x))&&(eq(L.y,R.y)));
	}

template <class T>
bool operator!= (const Vec2<T> &L, const Vec2<T> &R)
	{
	return((ne(L.x,R.x))||(ne(L.y,R.y)));
	}

#undef eq
#undef ne

#else

template <class T>
bool operator== (const Vec2<T> &L, const Vec2<T> &R)
	{
	return((L.x==R.x)&&(L.y==R.y));
	}

template <class T>
bool operator!= (const Vec2<T> &L, const Vec2<T> &R)
	{
	return((L.x!=R.x)||(L.y!=R.y));
	}

#endif

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
