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
			};

		Vec2<T>() { x=y=0; }

		Vec2<T>(T cx, T cy) { x=cx; y=cy; }

		Vec2<T>(T cx) { x=y=cx; }

		Vec2<T>(const Vec2<T> &v) { x=v.x; y=v.y; }

		Vec2<T>(T v[2]) { x=v[0]; y=v[1]; }

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

	friend Vec2<T> operator+ (const Vec2<T> &L, const Vec2<T> &R)
		{
		Vec2<T> c; c.x=L.x+R.x; c.y=L.y+R.y; return(c);
		}

	friend Vec2<T> operator+ (const Vec2<T> &L, const T &R)
		{
		Vec2<T> c; c.x=L.x+R; c.y=L.y+R; return(c);
		}

	friend Vec2<T> operator+ (const T &L, const Vec2<T> &R)
		{
		Vec2<T> c; c.x=L+R.x; c.y=L+R.y; return(c);
		}

	friend Vec2<T> operator- (const Vec2<T> &R)
		{
		Vec2<T> c; c.x=-R.x; c.y=-R.y; return(c);
		}

	friend Vec2<T> operator- (const Vec2<T> &L, const Vec2<T> &R)
		{
		Vec2<T> c; c.x=L.x-R.x; c.y=L.y-R.y; return(c);
		}

	friend Vec2<T> operator- (const Vec2<T> &L, const T &R)
		{
		Vec2<T> c; c.x=L.x-R; c.y=L.y-R; return(c);
		}

	friend Vec2<T> operator- (const T &L, const Vec2<T> &R)
		{
		Vec2<T> c; c.x=L-R.x; c.y=L-R.y; return(c);
		}

	friend Vec2<T> operator* (const Vec2<T> &L, const Vec2<T> &R)
		{
		Vec2<T> c;
		c.x=R.x*L.x; c.y=R.y*L.y;
		return(c);
		}

	friend Vec2<T> operator* (const T &L, const Vec2<T> &R)
		{
		Vec2<T> c;
		c.x=R.x*L; c.y=R.y*L;
		return(c);
		}

	friend Vec2<T> operator* (const Vec2<T> &L, const T &R)
		{
		return(R*L);
		}

	friend Vec2<T> operator/ (const Vec2<T> &L, const Vec2<T> &R)
		{
		Vec2<T> c;
		c.x=L.x/R.x; c.y=L.y/R.y;
		return(c);
		}

	friend Vec2<T> operator/ (const Vec2<T> &L, const T &R)
		{
		Vec2<T> c;
		c.x=L.x/R; c.y=L.y/R;
		return(c);
		}

	friend Vec2<T>& operator+= (Vec2<T> &L, const Vec2<T> &R)
		{
		L.x+=R.x; L.y+=R.y;
		return(L);
		}

	friend Vec2<T>& operator+= (Vec2<T> &L, const T &R)
		{
		L.x+=R; L.y+=R;
		return(L);
		}

	friend Vec2<T>& operator-= (Vec2<T> &L, const Vec2<T> &R)
		{
		L.x-=R.x; L.y-=R.y;
		return(L);
		}

	friend Vec2<T>& operator-= (Vec2<T> &L, const T &R)
		{
		L.x-=R; L.y-=R;
		return(L);
		}

	friend Vec2<T>& operator*= (Vec2<T> &L, const Vec2<T> &R)
		{
		L.x*=R.x; L.y*=R.y;
		return(L);
		}

	friend Vec2<T>& operator*= (Vec2<T> &L, const T &R)
		{
		L.x*=R; L.y*=R;
		return(L);
		}

	friend Vec2<T>& operator/= (Vec2<T> &L, const Vec2<T> &R)
		{
		L.x/=R.x; L.y/=R.y;
		return(L);
		}

	friend Vec2<T>& operator/= (Vec2<T> &L, const T &R)
		{
		L.x/=R; L.y/=R;
		return(L);
		}

	friend Vec2<T>& operator++ (Vec2<T> &R)
		{
		++R.x; ++R.y;
		return(R);
		}

	friend Vec2<T> operator++ (Vec2<T> &L, int)
		{
		Vec2<T> c=L;
		L.x++; L.y++;
		return(c);
		}

	friend Vec2<T>& operator-- (Vec2<T> &R)
		{
		--R.x; --R.y;
		return(R);
		}

	friend Vec2<T> operator-- (Vec2<T> &L, int)
		{
		Vec2<T> c=L;
		L.x--; L.y--;
		return(c);
		}

#ifdef EPSILONCOMP

#define eq(a,b) (fabs(a-b)<EPSILONCOMP)
#define ne(a,b) (fabs(a-b)>=EPSILONCOMP)

	friend bool operator== (const Vec2<T> &L, const Vec2<T> &R)
		{
		return((eq(L.x,R.x))&&(eq(L.y,R.y)));
		}

	friend bool operator!= (const Vec2<T> &L, const Vec2<T> &R)
		{
		return((ne(L.x,R.x))||(ne(L.y,R.y)));
		}

#undef eq
#undef ne

#else

	friend bool operator== (const Vec2<T> &L, const Vec2<T> &R)
		{
		return((L.x==R.x)&&(L.y==R.y));
		}

	friend bool operator!= (const Vec2<T> &L, const Vec2<T> &R)
		{
		return((L.x!=R.x)||(L.y!=R.y));
		}

#endif

	friend std::ostream& operator<< (std::ostream &os, const Vec2<T> &R)
		{
		os << "(" << R.x << "," << R.y << ")";
		return(os);
		}
	};

typedef Vec2<float> vec2;
typedef Vec2<int> ivec2;
typedef Vec2<bool> bvec2;

#endif
