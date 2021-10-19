/*********************************************************
   2x2 matrix class
   Copyright © 2021 Mark Craig

   https://www.youtube.com/MrMcSoftware
**********************************************************/

#ifndef _MAT2_H
#define _MAT2_H

#include <cstdio>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "vec2.h"

template <class T>
class Mat2
	{
	public:
		union
			{
			struct { T m[2][2]; };
			struct { T M[4]; };
			struct { T x0,x1,y0,y1; };
			};

		Mat2<T>() { x0=y0=x1=y1=0; }

		Mat2<T>(T X0) { y0=x1=0; x0=y1=X0; }

		Mat2<T>(T X0, T Y0, T X1, T Y1) { x0=X0; y0=Y0; x1=X1; y1=Y1; }

		Mat2<T>(Vec2<T> v1, Vec2<T> v2) { x0=v1.x; y0=v1.y; x1=v2.x; y1=v2.y; }

		Mat2<T>(const Mat2<T> &v) { x0=v.x0; y0=v.y0; x1=v.x1; y1=v.y1; }

		inline Mat2<T> const transpose() const
			{
			Mat2<T> trans;
			trans.m[0][0]=m[0][0]; trans.m[1][0]=m[0][1];
			trans.m[0][1]=m[1][0]; trans.m[1][1]=m[1][1];
			return(trans);
			}

		inline T const determinant() const
			{
			return(m[0][0]*m[1][1]-m[1][0]*m[0][1]);
			}

		inline Mat2<T> const inverse() const
			{
			T invdet=static_cast<T>(1)/(m[0][0]*m[1][1]-m[1][0]*m[0][1]);
			Mat2<T> inv;
			inv.m[0][0]=m[1][1]*invdet;
			inv.m[1][0]=-m[1][0]*invdet;
			inv.m[0][1]=-m[0][1]*invdet;
			inv.m[1][1]=m[0][0]*invdet;
			return(inv);
			}

		inline void const print(int nl=1) const
			{
			printf("| %9.4f %9.4f |\n",m[0][0],m[0][1]);
			printf("| %9.4f %9.4f |\n",m[1][0],m[1][1]);
			if (nl) { printf("\n"); }
			}

		Mat2<T> operator+ (const Mat2<T> &R) const;
		Mat2<T> operator- () const;
		Mat2<T> operator- (const Mat2<T> &R) const;
		Vec2<T> operator* (const Vec2<T> &R) const;
		Mat2<T> operator* (const T &R) const;
		Mat2<T> operator* (const Mat2<T> &R) const;
		Mat2<T> operator/ (const T &R) const;
		Mat2<T> operator/ (const Mat2<T> &R) const;
		Mat2<T>& operator+= (const Mat2<T> &R);
		Mat2<T>& operator-= (const Mat2<T> &R);
		Mat2<T>& operator*= (const Mat2<T> &R);
		Mat2<T>& operator*= (const T &R);
		Mat2<T>& operator/= (const Mat2<T> &R);
		Mat2<T>& operator/= (const T &R);
		bool operator== (const Mat2<T> &R) const;
		bool operator!= (const Mat2<T> &R) const;
	};

template <class T>
Mat2<T> Mat2<T>::operator+ (const Mat2<T> &R) const
	{
	Mat2<T> c;
	c.m[0][0]=m[0][0]+R.m[0][0]; c.m[1][0]=m[1][0]+R.m[1][0];
	c.m[0][1]=m[0][1]+R.m[0][1]; c.m[1][1]=m[1][1]+R.m[1][1];
	return(c);
	}

template <class T>
Mat2<T> Mat2<T>::operator- () const
	{
	Mat2<T> c;
	c.x0=-x0; c.y0=-y0;
	c.x1=-x1; c.y1=-y1;
	return(c);
	}

template <class T>
Mat2<T> Mat2<T>::operator- (const Mat2<T> &R) const
	{
	Mat2<T> c;
	c.m[0][0]=m[0][0]-R.m[0][0]; c.m[1][0]=m[1][0]-R.m[1][0];
	c.m[0][1]=m[0][1]-R.m[0][1]; c.m[1][1]=m[1][1]-R.m[1][1];
	return(c);
	}

template <class T>
Vec2<T> Mat2<T>::operator* (const Vec2<T> &R) const
	{
	Vec2<T> c;
	c.x=R.x*x0+R.y*x1;
	c.y=R.x*y0+R.y*y1;
	return(c);
	}

template <class T>
Vec2<T> operator* (const Vec2<T> &L, const Mat2<T> &R)
	{
	Vec2<T> c;
	c.x=L.x*R.x0+L.y*R.y0;
	c.y=L.x*R.x1+L.y*R.y1;
	return(c);
	}

template <class T>
Mat2<T> Mat2<T>::operator* (const T &R) const
	{
	Mat2<T> c;
	c.m[0][0]=m[0][0]*R; c.m[1][0]=m[1][0]*R;
	c.m[0][1]=m[0][1]*R; c.m[1][1]=m[1][1]*R;
	return(c);
	}

#if _MSC_VER == 1200
template <class T>
Mat2<T> operator* (const T &L, const Mat2<T> &R)
#else
template <class T, class U>
Mat2<T> operator* (const U &L, const Mat2<T> &R)
#endif
	{
	return(R*L);
	}

template <class T>
Mat2<T> Mat2<T>::operator* (const Mat2<T> &R) const
	{
	Mat2<T> c;
	c.m[0][0]=R.m[0][0]*m[0][0]+R.m[1][0]*m[0][1];
	c.m[1][0]=R.m[0][0]*m[1][0]+R.m[1][0]*m[1][1];
	c.m[0][1]=R.m[0][1]*m[0][0]+R.m[1][1]*m[0][1];
	c.m[1][1]=R.m[0][1]*m[1][0]+R.m[1][1]*m[1][1];
	return(c);
	}

template <class T>
Mat2<T> Mat2<T>::operator/ (const T &R) const
	{
	Mat2<T> c;
	c.m[0][0]=m[0][0]/R; c.m[1][0]=m[1][0]/R;
	c.m[0][1]=m[0][1]/R; c.m[1][1]=m[1][1]/R;
	return(c);
	}

template <class T>
Mat2<T> Mat2<T>::operator/ (const Mat2<T> &R) const
	{
	return(*this*R.inverse());
	}

template <class T>
Mat2<T>& Mat2<T>::operator+= (const Mat2<T> &R)
	{
	*this=*this+R;
	return(*this);
	}

template <class T>
Mat2<T>& Mat2<T>::operator-= (const Mat2<T> &R)
	{
	*this=*this-R;
	return(*this);
	}

template <class T>
Mat2<T>& Mat2<T>::operator*= (const Mat2<T> &R)
	{
	*this=*this*R;
	return(*this);
	}

template <class T>
Mat2<T>& Mat2<T>::operator*= (const T &R)
	{
	*this=*this*R;
	return(*this);
	}

template <class T>
Mat2<T>& Mat2<T>::operator/= (const Mat2<T> &R)
	{
	*this=*this/R;
	return(*this);
	}

template <class T>
Mat2<T>& Mat2<T>::operator/= (const T &R)
	{
	*this=*this/R;
	return(*this);
	}

#ifdef EPSILONCOMP

#define eq(a,b) (fabs(a-b)<EPSILONCOMP)
#define ne(a,b) (fabs(a-b)>=EPSILONCOMP)

template <class T>
bool Mat2<T>::operator== (const Mat2<T> &R) const
	{
	return((eq(M[0],R.M[0]))&&(eq(M[1],R.M[1]))
		&&(eq(M[2],R.M[2]))&&(eq(M[3],R.M[3])));
	}

template <class T>
bool Mat2<T>::operator!= (const Mat2<T> &R) const
	{
	return((ne(M[0],R.M[0]))||(ne(M[1],R.M[1]))
		||(ne(M[2],R.M[2]))||(ne(M[3],R.M[3])));
	}

#undef eq
#undef ne

#else

template <class T>
bool Mat2<T>::operator== (const Mat2<T> &R) const
	{
	return((M[0]==R.M[0])&&(M[1]==R.M[1])&&(M[2]==R.M[2])
		&&(M[3]==R.M[3]));
	}

template <class T>
bool Mat2<T>::operator!= (const Mat2<T> &R) const
	{
	return((M[0]!=R.M[0])||(M[1]!=R.M[1])||(M[2]!=R.M[2])
		||(M[3]!=R.M[3]));
	}

#endif

#define FORM std::setprecision(4) << std::setw(9)

template <class T>
std::ostream& operator<< (std::ostream &os, const Mat2<T> &R)
	{
	std::ios_base::fmtflags f = os.flags();
	os << std::fixed;
	os << std::endl;
	os << "| " << FORM << R.x0 << " " << FORM << R.x1 << " |" << std::endl;
	os << "| " << FORM << R.y0 << " " << FORM << R.y1 << " |" << std::endl;
	os.flags(f);
	return(os);
	}

typedef Mat2<float> mat2;

#endif
