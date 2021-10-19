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
#include "vec2.h"

template <class T>
class Vec3
	{
	public:
		union
			{
			struct { T x,y,z; };
			struct { T r,g,b; };
			struct { T V[3]; };
			};

		Vec3<T>() { x=y=z=0; }

		Vec3<T>(T cx, T cy, T cz) { x=cx; y=cy; z=cz; }

		Vec3<T>(T cx) { x=y=z=cx; }

		Vec3<T>(Vec2<T> v, T cz) { x=v.x; y=v.y; z=cz; }

		Vec3<T>(const Vec3<T> &v) { x=v.x; y=v.y; z=v.z; }

		Vec3<T>(T v[3]) { x=v[0]; y=v[1]; z=v[2]; }

		inline Vec2<T> xy() const
			{
			return(Vec2<T>(x,y));
			}

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

	friend Vec3<T> operator+ (const Vec3<T> &L, const Vec3<T> &R)
		{
		Vec3<T> c; c.x=L.x+R.x; c.y=L.y+R.y; c.z=L.z+R.z; return(c);
		}

	friend Vec3<T> operator+ (const Vec3<T> &L, const T &R)
		{
		Vec3<T> c; c.x=L.x+R; c.y=L.y+R; c.z=L.z+R; return(c);
		}

	friend Vec3<T> operator+ (const T &L, const Vec3<T> &R)
		{
		Vec3<T> c; c.x=L+R.x; c.y=L+R.y; c.z=L+R.z; return(c);
		}

	friend Vec3<T> operator- (const Vec3<T> &R)
		{
		Vec3<T> c; c.x=-R.x; c.y=-R.y; c.z=-R.z; return(c);
		}

	friend Vec3<T> operator- (const Vec3<T> &L, const Vec3<T> &R)
		{
		Vec3<T> c; c.x=L.x-R.x; c.y=L.y-R.y; c.z=L.z-R.z; return(c);
		}

	friend Vec3<T> operator- (const Vec3<T> &L, const T &R)
		{
		Vec3<T> c; c.x=L.x-R; c.y=L.y-R; c.z=L.z-R; return(c);
		}

	friend Vec3<T> operator- (const T &L, const Vec3<T> &R)
		{
		Vec3<T> c; c.x=L-R.x; c.y=L-R.y; c.z=L-R.z; return(c);
		}

	friend Vec3<T> operator* (const Vec3<T> &L, const Vec3<T> &R)
		{
		Vec3<T> c;
		c.x=R.x*L.x; c.y=R.y*L.y; c.z=R.z*L.z;
		return(c);
		}

	friend Vec3<T> operator* (const T &L, const Vec3<T> &R)
		{
		Vec3<T> c;
		c.x=R.x*L; c.y=R.y*L; c.z=R.z*L;
		return(c);
		}

	friend Vec3<T> operator* (const Vec3<T> &L, const T &R)
		{
		return(R*L);
		}

	friend Vec3<T> operator/ (const Vec3<T> &L, const Vec3<T> &R)
		{
		Vec3<T> c;
		c.x=L.x/R.x; c.y=L.y/R.y; c.z=L.z/R.z;
		return(c);
		}

	friend Vec3<T> operator/ (const Vec3<T> &L, const T &R)
		{
		Vec3<T> c;
		c.x=L.x/R; c.y=L.y/R; c.z=L.z/R;
		return(c);
		}

	friend Vec3<T>& operator+= (Vec3<T> &L, const Vec3<T> &R)
		{
		L.x+=R.x; L.y+=R.y; L.z+=R.z;
		return(L);
		}

	friend Vec3<T>& operator+= (Vec3<T> &L, const T &R)
		{
		L.x+=R; L.y+=R; L.z+=R;
		return(L);
		}

	friend Vec3<T>& operator-= (Vec3<T> &L, const Vec3<T> &R)
		{
		L.x-=R.x; L.y-=R.y; L.z-=R.z;
		return(L);
		}

	friend Vec3<T>& operator-= (Vec3<T> &L, const T &R)
		{
		L.x-=R; L.y-=R; L.z-=R;
		return(L);
		}

	friend Vec3<T>& operator*= (Vec3<T> &L, const Vec3<T> &R)
		{
		L.x*=R.x; L.y*=R.y; L.z*=R.z;
		return(L);
		}

	friend Vec3<T>& operator*= (Vec3<T> &L, const T &R)
		{
		L.x*=R; L.y*=R; L.z*=R;
		return(L);
		}

	friend Vec3<T>& operator/= (Vec3<T> &L, const Vec3<T> &R)
		{
		L.x/=R.x; L.y/=R.y; L.z/=R.z;
		return(L);
		}

	friend Vec3<T>& operator/= (Vec3<T> &L, const T &R)
		{
		L.x/=R; L.y/=R; L.z/=R;
		return(L);
		}

	friend Vec3<T>& operator++ (Vec3<T> &R)
		{
		++R.x; ++R.y; ++R.z;
		return(R);
		}

	friend Vec3<T> operator++ (Vec3<T> &L, int)
		{
		Vec3<T> c=L;
		L.x++; L.y++; L.z++;
		return(c);
		}

	friend Vec3<T>& operator-- (Vec3<T> &R)
		{
		--R.x; --R.y; --R.z;
		return(R);
		}

	friend Vec3<T> operator-- (Vec3<T> &L, int)
		{
		Vec3<T> c=L;
		L.x--; L.y--; L.z--;
		return(c);
		}

#ifdef EPSILONCOMP

#define eq(a,b) (fabs(a-b)<EPSILONCOMP)
#define ne(a,b) (fabs(a-b)>=EPSILONCOMP)

	friend bool operator== (const Vec3<T> &L, const Vec3<T> &R)
		{
		return((eq(L.x,R.x))&&(eq(L.y,R.y))&&(eq(L.z,R.z)));
		}

	friend bool operator!= (const Vec3<T> &L, const Vec3<T> &R)
		{
		return((ne(L.x,R.x))||(ne(L.y,R.y))||(ne(L.z,R.z)));
		}

#undef eq
#undef ne

#else

	friend bool operator== (const Vec3<T> &L, const Vec3<T> &R)
		{
		return((L.x==R.x)&&(L.y==R.y)&&(L.z==R.z));
		}

	friend bool operator!= (const Vec3<T> &L, const Vec3<T> &R)
		{
		return((L.x!=R.x)||(L.y!=R.y)||(L.z!=R.z));
		}

#endif

	friend std::ostream& operator<< (std::ostream &os, const Vec3<T> &R)
		{
		os << "(" << R.x << "," << R.y << "," << R.z << ")";
		return(os);
		}
	};

typedef Vec3<float> vec3;
typedef Vec3<int> ivec3;

#endif
