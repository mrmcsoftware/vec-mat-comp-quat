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
#include "vec2.h"
#include "vec3.h"

template <class T>
class Vec4
	{
	public:
		union
			{
			struct { T x,y,z,w; };
			struct { T r,g,b,a; };
			struct { T V[4]; };
			};

		Vec4<T>() { x=y=z=w=0; }

		Vec4<T>(T cx, T cy, T cz, T cw) { x=cx; y=cy; z=cz; w=cw; }

		Vec4<T>(T cx) { x=y=z=w=cx; }

		Vec4<T>(Vec3<T> v, T cw) { x=v.x; y=v.y; z=v.z; w=cw; }

		Vec4<T>(const Vec4<T> &v) { x=v.x; y=v.y; z=v.z; w=v.w; }

		Vec4<T>(T v[4]) { x=v[0]; y=v[1]; z=v[2]; w=v[3]; }

		inline Vec2<T> xy() const
			{
			return(Vec2<T>(x,y));
			}

		inline Vec3<T> xyz() const
			{
			return(Vec3<T>(x,y,z));
			}

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

		Vec4<T> operator+ (const Vec4<T> &R) const;
		Vec4<T> operator+ (const T &R) const;
		Vec4<T> operator- () const;
		Vec4<T> operator- (const Vec4<T> &R) const;
		Vec4<T> operator- (const T &R) const;
		Vec4<T> operator* (const Vec4<T> &R) const;
		Vec4<T> operator* (const T &R) const;
		Vec4<T> operator/ (const Vec4<T> &R) const;
		Vec4<T> operator/ (const T &R) const;
		Vec4<T>& operator+= (const Vec4<T> &R);
		Vec4<T>& operator+= (const T &R);
		Vec4<T>& operator-= (const Vec4<T> &R);
		Vec4<T>& operator-= (const T &R);
		Vec4<T>& operator*= (const Vec4<T> &R);
		Vec4<T>& operator*= (const T &R);
		Vec4<T>& operator/= (const Vec4<T> &R);
		Vec4<T>& operator/= (const T &R);
		Vec4<T>& operator++ ();
		Vec4<T> operator++ (int);
		Vec4<T>& operator-- ();
		Vec4<T> operator-- (int);
		bool operator== (const Vec4<T> &R) const;
		bool operator!= (const Vec4<T> &R) const;
	};

template <class T>
Vec4<T> Vec4<T>::operator+ (const Vec4<T> &R) const
	{
	Vec4<T> c; c.x=x+R.x; c.y=y+R.y; c.z=z+R.z; c.w=w+R.w; return(c);
	}

template <class T>
Vec4<T> Vec4<T>::operator+ (const T &R) const
	{
	Vec4<T> c; c.x=x+R; c.y=y+R; c.z=z+R; c.w=w+R; return(c);
	}

template <class T, class U>
Vec4<T> operator+ (const U &L, const Vec4<T> &R)
	{
	Vec4<T> c; c.x=L+R.x; c.y=L+R.y; c.z=L+R.z; c.w=L+R.w; return(c);
	}

template <class T>
Vec4<T> Vec4<T>::operator- () const
	{
	Vec4<T> c; c.x=-x; c.y=-y; c.z=-z; c.w=-w; return(c);
	}

template <class T>
Vec4<T> Vec4<T>::operator- (const Vec4<T> &R) const
	{
	Vec4<T> c; c.x=x-R.x; c.y=y-R.y; c.z=z-R.z; c.w=w-R.w; return(c);
	}

template <class T>
Vec4<T> Vec4<T>::operator- (const T &R) const
	{
	Vec4<T> c; c.x=x-R; c.y=y-R; c.z=z-R; c.w=w-R; return(c);
	}

template <class T, class U>
Vec4<T> operator- (const U &L, const Vec4<T> &R)
	{
	Vec4<T> c; c.x=L-R.x; c.y=L-R.y; c.z=L-R.z; c.w=L-R.w; return(c);
	}

template <class T>
Vec4<T> Vec4<T>::operator* (const Vec4<T> &R) const
	{
	Vec4<T> c;
	c.x=R.x*x; c.y=R.y*y; c.z=R.z*z; c.w=R.w*w;
	return(c);
	}

template <class T, class U>
Vec4<T> operator* (const U &L, const Vec4<T> &R)
	{
	Vec4<T> c;
	c.x=R.x*L; c.y=R.y*L; c.z=R.z*L; c.w=R.w*L;
	return(c);
	}

template <class T>
Vec4<T> Vec4<T>::operator* (const T &R) const
	{
	return(R*(*this));
	}

template <class T>
Vec4<T> Vec4<T>::operator/ (const Vec4<T> &R) const
	{
	Vec4<T> c;
	c.x=x/R.x; c.y=y/R.y; c.z=z/R.z; c.w=w/R.w;
	return(c);
	}

template <class T>
Vec4<T> Vec4<T>::operator/ (const T &R) const
	{
	Vec4<T> c;
	c.x=x/R; c.y=y/R; c.z=z/R; c.w=w/R;
	return(c);
	}

template <class T>
Vec4<T>& Vec4<T>::operator+= (const Vec4<T> &R)
	{
	x+=R.x; y+=R.y; z+=R.z; w+=R.w;
	return(*this);
	}

template <class T>
Vec4<T>& Vec4<T>::operator+= (const T &R)
	{
	x+=R; y+=R; z+=R; w+=R;
	return(*this);
	}

template <class T>
Vec4<T>& Vec4<T>::operator-= (const Vec4<T> &R)
	{
	x-=R.x; y-=R.y; z-=R.z; w-=R.w;
	return(*this);
	}

template <class T>
Vec4<T>& Vec4<T>::operator-= (const T &R)
	{
	x-=R; y-=R; z-=R; w-=R;
	return(*this);
	}

template <class T>
Vec4<T>& Vec4<T>::operator*= (const Vec4<T> &R)
	{
	x*=R.x; y*=R.y; z*=R.z; w*=R.w;
	return(*this);
	}

template <class T>
Vec4<T>& Vec4<T>::operator*= (const T &R)
	{
	x*=R; y*=R; z*=R; w*=R;
	return(*this);
	}

template <class T>
Vec4<T>& Vec4<T>::operator/= (const Vec4<T> &R)
	{
	x/=R.x; y/=R.y; z/=R.z; w/=R.w;
	return(*this);
	}

template <class T>
Vec4<T>& Vec4<T>::operator/= (const T &R)
	{
	x/=R; y/=R; z/=R; w/=R;
	return(*this);
	}

template <class T>
Vec4<T>& Vec4<T>::operator++ ()
	{
	++x; ++y; ++z; ++w;
	return(*this);
	}

template <class T>
Vec4<T> Vec4<T>::operator++ (int)
	{
	Vec4<T> c=*this;
	x++; y++; z++; w++;
	return(c);
	}

template <class T>
Vec4<T>& Vec4<T>::operator-- ()
	{
	--x; --y; --z; --w;
	return(*this);
	}

template <class T>
Vec4<T> Vec4<T>::operator-- (int)
	{
	Vec4<T> c=*this;
	x--; y--; z--; w--;
	return(c);
	}

#ifdef EPSILONCOMP

#define eq(a,b) (fabs(a-b)<EPSILONCOMP)
#define ne(a,b) (fabs(a-b)>=EPSILONCOMP)

template <class T>
bool Vec4<T>::operator== (const Vec4<T> &R) const
	{
	return((eq(x,R.x))&&(eq(y,R.y))&&(eq(z,R.z))&&(eq(w,R.w)));
	}

template <class T>
bool Vec4<T>::operator!= (const Vec4<T> &R) const
	{
	return((ne(x,R.x))||(ne(y,R.y))||(ne(z,R.z))||(ne(w,R.w)));
	}

#undef eq
#undef ne

#else

template <class T>
bool Vec4<T>::operator== (const Vec4<T> &R) const
	{
	return((x==R.x)&&(y==R.y)&&(z==R.z)&&(w==R.w));
	}

template <class T>
bool Vec4<T>::operator!= (const Vec4<T> &R) const
	{
	return((x!=R.x)||(y!=R.y)||(z!=R.z)||(w!=R.w));
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
