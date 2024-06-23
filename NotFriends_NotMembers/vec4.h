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
#include "swizzle.h"
#endif
#include "vec2.h"
#include "vec3.h"
#ifdef VEC_USE_MAT
#include "mat4.h"

template <class T>
class Mat4;
#endif

template <class T>
class Vec4
	{
	public:
		union
			{
			struct { T x,y,z,w; };
			struct { T r,g,b,a; };
			struct { T V[4]; };
#ifdef VEC_USE_SWIZZLE
			swizzle2<Vec2<T>,T,1,0> yx;
			swizzle2<Vec2<T>,T,0,1> xy;
			swizzle2<Vec2<T>,T,1,2> yz;
			swizzle2<Vec2<T>,T,0,2> xz;
			swizzle3<Vec3<T>,T,2,1,0> zyx;
			swizzle3<Vec3<T>,T,2,1,0> bgr;
			swizzle3<Vec3<T>,T,0,1,2> xyz;
			swizzle3<Vec3<T>,T,0,1,2> rgb;
			swizzle4<Vec4<T>,T,3,2,1,0> wzyx;
			swizzle4<Vec4<T>,T,3,2,1,0> abgr;
#endif
			};

		Vec4<T>() { x=y=z=w=0; }

		Vec4<T>(T cx, T cy, T cz, T cw) { x=cx; y=cy; z=cz; w=cw; }

		Vec4<T>(T cx) { x=y=z=w=cx; }

		Vec4<T>(Vec3<T> v, T cw) { x=v.x; y=v.y; z=v.z; w=cw; }

		Vec4<T>(const Vec4<T> &v) { x=v.x; y=v.y; z=v.z; w=v.w; }

		Vec4<T>(T v[4]) { x=v[0]; y=v[1]; z=v[2]; w=v[3]; }

#ifndef VEC_USE_SWIZZLE
		inline Vec2<T> xy() const
			{
			return(Vec2<T>(x,y));
			}

		inline Vec3<T> xyz() const
			{
			return(Vec3<T>(x,y,z));
			}
#endif

		inline T dot() const
			{
			T r=x*x+y*y+z*z+w*w;
			return(r);
			}

		inline T dot(const Vec4<T> &q) const
			{
			T r=x*q.x+y*q.y+z*q.z+w*q.w;
			return(r);
			}

		inline T length() const
			{
			T r=sqrt(x*x+y*y+z*z+w*w);
			return(r);
			}

		inline Vec4<T> const normalized() const
			{
			T mag=sqrt(x*x+y*y+z*z+w*w);
			if (mag!=0.0)
				{
				Vec4<T> r;
				r.x=x/mag; r.y=y/mag; r.z=z/mag; r.w=w/mag;
				return(r);
				}
			return(Vec4<T>(0.0,0.0,0.0,0.0));
			}

		inline T normalize()
			{
			T mag=sqrt(x*x+y*y+z*z+w*w);
			if (mag!=0.0) { x/=mag; y/=mag; z/=mag; w/=mag; }
			else { x=y=z=w=0.0; }
			return(mag);
			}

		inline T operator[] (int i) const
			{
			assert((i>=0)&&(i<4));
			return(V[i]);
			}

		inline T& operator[] (int i)
			{
			assert((i>=0)&&(i<4));
			return(V[i]);
			}
	};

template <class T>
Vec4<T> operator+ (const Vec4<T> &L, const Vec4<T> &R)
	{
	Vec4<T> c; c.x=L.x+R.x; c.y=L.y+R.y; c.z=L.z+R.z; c.w=L.w+R.w; return(c);
	}

template <class T, class U>
Vec4<T> operator+ (const Vec4<T> &L, const U &R)
	{
	Vec4<T> c; c.x=L.x+R; c.y=L.y+R; c.z=L.z+R; c.w=L.w+R; return(c);
	}

template <class T, class U>
Vec4<T> operator+ (const U &L, const Vec4<T> &R)
	{
	Vec4<T> c; c.x=L+R.x; c.y=L+R.y; c.z=L+R.z; c.w=L+R.w; return(c);
	}

template <class T>
Vec4<T> operator- (const Vec4<T> &R)
	{
	Vec4<T> c; c.x=-R.x; c.y=-R.y; c.z=-R.z; c.w=-R.w; return(c);
	}

template <class T>
Vec4<T> operator- (const Vec4<T> &L, const Vec4<T> &R)
	{
	Vec4<T> c; c.x=L.x-R.x; c.y=L.y-R.y; c.z=L.z-R.z; c.w=L.w-R.w; return(c);
	}

template <class T, class U>
Vec4<T> operator- (const Vec4<T> &L, const U &R)
	{
	Vec4<T> c; c.x=L.x-R; c.y=L.y-R; c.z=L.z-R; c.w=L.w-R; return(c);
	}

template <class T, class U>
Vec4<T> operator- (const U &L, const Vec4<T> &R)
	{
	Vec4<T> c; c.x=L-R.x; c.y=L-R.y; c.z=L-R.z; c.w=L-R.w; return(c);
	}

template <class T>
Vec4<T> operator* (const Vec4<T> &L, const Vec4<T> &R)
	{
	Vec4<T> c;
	c.x=R.x*L.x; c.y=R.y*L.y; c.z=R.z*L.z; c.w=R.w*L.w;
	return(c);
	}

template <class T, class U>
Vec4<T> operator* (const U &L, const Vec4<T> &R)
	{
	Vec4<T> c;
	c.x=R.x*L; c.y=R.y*L; c.z=R.z*L; c.w=R.w*L;
	return(c);
	}

template <class T, class U>
Vec4<T> operator* (const Vec4<T> &L, const U &R)
	{
	return(R*L);
	}

template <class T>
Vec4<T> operator/ (const Vec4<T> &L, const Vec4<T> &R)
	{
	Vec4<T> c;
	c.x=L.x/R.x; c.y=L.y/R.y; c.z=L.z/R.z; c.w=L.w/R.w;
	return(c);
	}

template <class T, class U>
Vec4<T> operator/ (const Vec4<T> &L, const U &R)
	{
	Vec4<T> c;
	c.x=L.x/R; c.y=L.y/R; c.z=L.z/R; c.w=L.w/R;
	return(c);
	}

template <class T>
Vec4<T>& operator+= (Vec4<T> &L, const Vec4<T> &R)
	{
	L.x+=R.x; L.y+=R.y; L.z+=R.z; L.w+=R.w;
	return(L);
	}

template <class T, class U>
Vec4<T>& operator+= (Vec4<T> &L, const U &R)
	{
	L.x+=R; L.y+=R; L.z+=R; L.w+=R;
	return(L);
	}

template <class T>
Vec4<T>& operator-= (Vec4<T> &L, const Vec4<T> &R)
	{
	L.x-=R.x; L.y-=R.y; L.z-=R.z; L.w-=R.w;
	return(L);
	}

template <class T, class U>
Vec4<T>& operator-= (Vec4<T> &L, const U &R)
	{
	L.x-=R; L.y-=R; L.z-=R; L.w-=R;
	return(L);
	}

template <class T>
Vec4<T>& operator*= (Vec4<T> &L, const Vec4<T> &R)
	{
	L.x*=R.x; L.y*=R.y; L.z*=R.z; L.w*=R.w;
	return(L);
	}

template <class T, class U>
Vec4<T>& operator*= (Vec4<T> &L, const U &R)
	{
	L.x*=R; L.y*=R; L.z*=R; L.w*=R;
	return(L);
	}

#ifdef VEC_USE_MAT
template <class T, class U>
Vec4<T>& operator*= (Vec4<T> &L, const Mat4<U> &R)
	{
	L=L*R;
	return(L);
	}
#endif

template <class T>
Vec4<T>& operator/= (Vec4<T> &L, const Vec4<T> &R)
	{
	L.x/=R.x; L.y/=R.y; L.z/=R.z; L.w/=R.w;
	return(L);
	}

template <class T, class U>
Vec4<T>& operator/= (Vec4<T> &L, const U &R)
	{
	L.x/=R; L.y/=R; L.z/=R; L.w/=R;
	return(L);
	}

template <class T>
Vec4<T>& operator++ (Vec4<T> &R)
	{
	++R.x; ++R.y; ++R.z; ++R.w;
	return(R);
	}

template <class T>
Vec4<T> operator++ (Vec4<T> &L, int)
	{
	Vec4<T> c=L;
	L.x++; L.y++; L.z++; L.w++;
	return(c);
	}

template <class T>
Vec4<T>& operator-- (Vec4<T> &R)
	{
	--R.x; --R.y; --R.z; --R.w;
	return(R);
	}

template <class T>
Vec4<T> operator-- (Vec4<T> &L, int)
	{
	Vec4<T> c=L;
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

template <class T>
bool operator== (const Vec4<T> &L, const Vec4<T> &R)
	{
	return((eq(L.x,R.x))&&(eq(L.y,R.y))&&(eq(L.z,R.z))&&(eq(L.w,R.w)));
	}

template <class T>
bool operator!= (const Vec4<T> &L, const Vec4<T> &R)
	{
	return((ne(L.x,R.x))||(ne(L.y,R.y))||(ne(L.z,R.z))||(ne(L.w,R.w)));
	}

#undef eq
#undef ne

#else

template <class T>
bool operator== (const Vec4<T> &L, const Vec4<T> &R)
	{
	return((L.x==R.x)&&(L.y==R.y)&&(L.z==R.z)&&(L.w==R.w));
	}

template <class T>
bool operator!= (const Vec4<T> &L, const Vec4<T> &R)
	{
	return((L.x!=R.x)||(L.y!=R.y)||(L.z!=R.z)||(L.w!=R.w));
	}

#endif

template <class T>
std::ostream& operator<< (std::ostream &os, const Vec4<T> &R)
	{
	os << "(" << R.x << "," << R.y << "," << R.z << "," << R.w << ")";
	return(os);
	}

typedef Vec4<float> vec4;

#endif
