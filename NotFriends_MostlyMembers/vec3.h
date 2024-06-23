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
#include "swizzle.h"
#endif
#include "vec2.h"
#ifdef VEC_USE_MAT
#include "mat3.h"

template <class T>
class Mat3;
#endif

template <class T>
class Vec3
	{
	public:
		union
			{
			struct { T x,y,z; };
			struct { T r,g,b; };
			struct { T V[3]; };
#ifdef VEC_USE_SWIZZLE
			swizzle2<Vec2<T>,T,1,0> yx;
			swizzle2<Vec2<T>,T,0,1> xy;
			swizzle2<Vec2<T>,T,1,2> yz;
			swizzle2<Vec2<T>,T,0,2> xz;
			swizzle3<Vec3<T>,T,2,1,0> zyx;
			swizzle3<Vec3<T>,T,2,1,0> bgr;
#endif
			};

		Vec3<T>() { x=y=z=0; }

		Vec3<T>(T cx, T cy, T cz) { x=cx; y=cy; z=cz; }

		Vec3<T>(T cx) { x=y=z=cx; }

		Vec3<T>(Vec2<T> v, T cz) { x=v.x; y=v.y; z=cz; }

		Vec3<T>(const Vec3<T> &v) { x=v.x; y=v.y; z=v.z; }

		Vec3<T>(T v[3]) { x=v[0]; y=v[1]; z=v[2]; }

#ifndef VEC_USE_SWIZZLE
		inline Vec2<T> xy() const
			{
			return(Vec2<T>(x,y));
			}
#endif

		inline T dot() const
			{
			T r=x*x+y*y+z*z;
			return(r);
			}

		inline T dot(const Vec3<T> &q) const
			{
			T r=x*q.x+y*q.y+z*q.z;
			return(r);
			}

		inline Vec3<T> cross(const Vec3<T> &q) const
			{
			Vec3<T> v1;
			v1.x=y*q.z-z*q.y;
			v1.y=z*q.x-x*q.z;
			v1.z=x*q.y-y*q.x;
			return(v1);
			}

		inline T length() const
			{
			T r=sqrt(x*x+y*y+z*z);
			return(r);
			}

		inline Vec3<T> const normalized() const
			{
			T mag=sqrt(x*x+y*y+z*z);
			if (mag!=0.0)
				{
				Vec3<T> r;
				r.x=x/mag; r.y=y/mag; r.z=z/mag;
				return(r);
				}
			return(Vec3<T>(0.0,0.0,0.0));
			}

		inline T normalize()
			{
			T mag=sqrt(x*x+y*y+z*z);
			if (mag!=0.0) { x/=mag; y/=mag; z/=mag; }
			else { x=y=z=0.0; }
			return(mag);
			}

		// this one used if "const vec3 variable" or sometimes if "var1=var2[2]"
		//    Note: apparently, T& will also work
		inline T operator[] (int i) const
			{
			assert((i>=0)&&(i<3));
			return(V[i]);
			}

		// this one used if "var1=var2[2]" or if "var2[2]=var1"
		inline T& operator[] (int i)
			{
			assert((i>=0)&&(i<3));
			return(V[i]);
			}

		Vec3<T> operator+ (const Vec3<T> &R) const;
		Vec3<T> operator+ (const T &R) const;
		Vec3<T> operator- () const;
		Vec3<T> operator- (const Vec3<T> &R) const;
		Vec3<T> operator- (const T &R) const;
		Vec3<T> operator* (const Vec3<T> &R) const;
		Vec3<T> operator* (const T &R) const;
		Vec3<T> operator/ (const Vec3<T> &R) const;
		Vec3<T> operator/ (const T &R) const;
		Vec3<T>& operator+= (const Vec3<T> &R);
		Vec3<T>& operator+= (const T &R);
		Vec3<T>& operator-= (const Vec3<T> &R);
		Vec3<T>& operator-= (const T &R);
		Vec3<T>& operator*= (const Vec3<T> &R);
		Vec3<T>& operator*= (const T &R);
#ifdef VEC_USE_MAT
		Vec3<T>& operator*= (const Mat3<T> &R);
#endif
		Vec3<T>& operator/= (const Vec3<T> &R);
		Vec3<T>& operator/= (const T &R);
		Vec3<T>& operator++ ();
		Vec3<T> operator++ (int);
		Vec3<T>& operator-- ();
		Vec3<T> operator-- (int);
		bool operator== (const Vec3<T> &R) const;
		bool operator!= (const Vec3<T> &R) const;
	};

template <class T>
Vec3<T> Vec3<T>::operator+ (const Vec3<T> &R) const
	{
	Vec3<T> c; c.x=x+R.x; c.y=y+R.y; c.z=z+R.z; return(c);
	}

template <class T>
Vec3<T> Vec3<T>::operator+ (const T &R) const
	{
	Vec3<T> c; c.x=x+R; c.y=y+R; c.z=z+R; return(c);
	}

template <class T, class U>
Vec3<T> operator+ (const U &L, const Vec3<T> &R)
	{
	Vec3<T> c; c.x=L+R.x; c.y=L+R.y; c.z=L+R.z; return(c);
	}

template <class T>
Vec3<T> Vec3<T>::operator- () const
	{
	Vec3<T> c; c.x=-x; c.y=-y; c.z=-z; return(c);
	}

template <class T>
Vec3<T> Vec3<T>::operator- (const Vec3<T> &R) const
	{
	Vec3<T> c; c.x=x-R.x; c.y=y-R.y; c.z=z-R.z; return(c);
	}

template <class T>
Vec3<T> Vec3<T>::operator- (const T &R) const
	{
	Vec3<T> c; c.x=x-R; c.y=y-R; c.z=z-R; return(c);
	}

template <class T, class U>
Vec3<T> operator- (const U &L, const Vec3<T> &R)
	{
	Vec3<T> c; c.x=L-R.x; c.y=L-R.y; c.z=L-R.z; return(c);
	}

template <class T>
Vec3<T> Vec3<T>::operator* (const Vec3<T> &R) const
	{
	Vec3<T> c;
	c.x=R.x*x; c.y=R.y*y; c.z=R.z*z;
	return(c);
	}

template <class T, class U>
Vec3<T> operator* (const U &L, const Vec3<T> &R)
	{
	Vec3<T> c;
	c.x=R.x*L; c.y=R.y*L; c.z=R.z*L;
	return(c);
	}

template <class T>
Vec3<T> Vec3<T>::operator* (const T &R) const
	{
	return(R*(*this));
	}

template <class T>
Vec3<T> Vec3<T>::operator/ (const Vec3<T> &R) const
	{
	Vec3<T> c;
	c.x=x/R.x; c.y=y/R.y; c.z=z/R.z;
	return(c);
	}

template <class T>
Vec3<T> Vec3<T>::operator/ (const T &R) const
	{
	Vec3<T> c;
	c.x=x/R; c.y=y/R; c.z=z/R;
	return(c);
	}

template <class T>
Vec3<T>& Vec3<T>::operator+= (const Vec3<T> &R)
	{
	x+=R.x; y+=R.y; z+=R.z;
	return(*this);
	}

template <class T>
Vec3<T>& Vec3<T>::operator+= (const T &R)
	{
	x+=R; y+=R; z+=R;
	return(*this);
	}

template <class T>
Vec3<T>& Vec3<T>::operator-= (const Vec3<T> &R)
	{
	x-=R.x; y-=R.y; z-=R.z;
	return(*this);
	}

template <class T>
Vec3<T>& Vec3<T>::operator-= (const T &R)
	{
	x-=R; y-=R; z-=R;
	return(*this);
	}

template <class T>
Vec3<T>& Vec3<T>::operator*= (const Vec3<T> &R)
	{
	x*=R.x; y*=R.y; z*=R.z;
	return(*this);
	}

template <class T>
Vec3<T>& Vec3<T>::operator*= (const T &R)
	{
	x*=R; y*=R; z*=R;
	return(*this);
	}

#ifdef VEC_USE_MAT
template <class T>
Vec3<T>& Vec3<T>::operator*= (const Mat3<T> &R)
	{
	*this=*this*R;
	return(*this);
	}
#endif

template <class T>
Vec3<T>& Vec3<T>::operator/= (const Vec3<T> &R)
	{
	x/=R.x; y/=R.y; z/=R.z;
	return(*this);
	}

template <class T>
Vec3<T>& Vec3<T>::operator/= (const T &R)
	{
	x/=R; y/=R; z/=R;
	return(*this);
	}

template <class T>
Vec3<T>& Vec3<T>::operator++ ()
	{
	++x; ++y; ++z;
	return(*this);
	}

template <class T>
Vec3<T> Vec3<T>::operator++ (int)
	{
	Vec3<T> c=*this;
	x++; y++; z++;
	return(c);
	}

template <class T>
Vec3<T>& Vec3<T>::operator-- ()
	{
	--x; --y; --z;
	return(*this);
	}

template <class T>
Vec3<T> Vec3<T>::operator-- (int)
	{
	Vec3<T> c=*this;
	x--; y--; z--;
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
bool Vec3<T>::operator== (const Vec3<T> &R) const
	{
	return((eq(x,R.x))&&(eq(y,R.y))&&(eq(z,R.z)));
	}

template <class T>
bool Vec3<T>::operator!= (const Vec3<T> &R) const
	{
	return((ne(x,R.x))||(ne(y,R.y))||(ne(z,R.z)));
	}

#undef eq
#undef ne

#else

template <class T>
bool Vec3<T>::operator== (const Vec3<T> &R) const
	{
	return((x==R.x)&&(y==R.y)&&(z==R.z));
	}

template <class T>
bool Vec3<T>::operator!= (const Vec3<T> &R) const
	{
	return((x!=R.x)||(y!=R.y)||(z!=R.z));
	}

#endif

template <class T>
std::ostream& operator<< (std::ostream &os, const Vec3<T> &R)
	{
	os << "(" << R.x << "," << R.y << "," << R.z << ")";
	return(os);
	}

typedef Vec3<float> vec3;
typedef Vec3<int> ivec3;

#endif
