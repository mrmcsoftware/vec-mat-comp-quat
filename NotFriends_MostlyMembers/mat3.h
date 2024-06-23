/*********************************************************
   3x3 matrix class
   Copyright © 2021 Mark Craig

   https://www.youtube.com/MrMcSoftware
**********************************************************/

#ifndef _MAT3_H
#define _MAT3_H

#include <cstdio>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "vec3.h"

#ifdef VEC_USE_MAT
template <class T>
class Vec3;
#endif

template <class T>
class Mat3
	{
	public:
		union
			{
			struct { T m[3][3]; };
			struct { T M[9]; };
			struct { T x0,x1,x2,y0,y1,y2,z0,z1,z2; };
			};

		Mat3<T>() { x0=y0=z0=x1=y1=z1=x2=y2=z2=0; }

		Mat3<T>(T X0) { y0=z0=x1=z1=x2=y2=0; x0=y1=z2=X0; }

		Mat3<T>(T X0, T Y0, T Z0, T X1, T Y1, T Z1, T X2, T Y2, T Z2) { x0=X0; y0=Y0; z0=Z0; x1=X1; y1=Y1; z1=Z1; x2=X2; y2=Y2; z2=Z2; }

		Mat3<T>(Vec3<T> v1, Vec3<T> v2, Vec3<T> v3) { x0=v1.x; y0=v1.y; z0=v1.z; x1=v2.x; y1=v2.y; z1=v2.z; x2=v3.x; y2=v3.y; z2=v3.z; }

		Mat3<T>(const Mat3<T> &v) { x0=v.x0; y0=v.y0; z0=v.z0; x1=v.x1; y1=v.y1; z1=v.z1; x2=v.x2; y2=v.y2; z2=v.z2; }

		inline Mat3<T> const transpose() const
			{
			Mat3<T> trans;
			trans.m[0][0]=m[0][0]; trans.m[1][0]=m[0][1]; trans.m[2][0]=m[0][2];
			trans.m[0][1]=m[1][0]; trans.m[1][1]=m[1][1]; trans.m[2][1]=m[1][2];
			trans.m[0][2]=m[2][0]; trans.m[1][2]=m[2][1]; trans.m[2][2]=m[2][2];
			return(trans);
			}

		/* I didn't feel like deriving determinant and inverse of 3x3 matrix -
			these are based on GLM (Copyright (c) 2005 - G-Truc Creation) */

		inline T const determinant() const
			{
			return(
				+ m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
				- m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
				+ m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]));
			}

		inline Mat3<T> const inverse() const
			{
			T invdet=static_cast<T>(1)/(
				+ m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
				- m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
				+ m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]));
			Mat3<T> inv;
			inv.m[0][0] = + (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * invdet;
			inv.m[1][0] = - (m[1][0] * m[2][2] - m[2][0] * m[1][2]) * invdet;
			inv.m[2][0] = + (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * invdet;
			inv.m[0][1] = - (m[0][1] * m[2][2] - m[2][1] * m[0][2]) * invdet;
			inv.m[1][1] = + (m[0][0] * m[2][2] - m[2][0] * m[0][2]) * invdet;
			inv.m[2][1] = - (m[0][0] * m[2][1] - m[2][0] * m[0][1]) * invdet;
			inv.m[0][2] = + (m[0][1] * m[1][2] - m[1][1] * m[0][2]) * invdet;
			inv.m[1][2] = - (m[0][0] * m[1][2] - m[1][0] * m[0][2]) * invdet;
			inv.m[2][2] = + (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * invdet;
			return(inv);
			}

		inline void const print(int nl=1) const
			{
			printf("| %9.4f %9.4f %9.4f |\n",m[0][0],m[0][1],m[0][2]);
			printf("| %9.4f %9.4f %9.4f |\n",m[1][0],m[1][1],m[1][2]);
			printf("| %9.4f %9.4f %9.4f |\n",m[2][0],m[2][1],m[2][2]);
			if (nl) { printf("\n"); }
			}

		inline void const latex(int nl=1, bool fixedl=true, std::ostream &os=std::cout) const
			{
#if 0
			printf("$$ \\left[ \\begin{array}{ccc}\n");
			printf("%9.4f & %9.4f & %9.4f\\\\\n",m[0][0],m[0][1],m[0][2]);
			printf("%9.4f & %9.4f & %9.4f\\\\\n",m[1][0],m[1][1],m[1][2]);
			printf("%9.4f & %9.4f & %9.4f\n",m[2][0],m[2][1],m[2][2]);
			printf("\\end{array} \\right] $$\n");
			if (nl) { printf("\n"); }
#else
			std::ios_base::fmtflags f;
			if (fixedl) { f = os.flags(); os << std::fixed; }
			std::streamsize cwidth = os.width();
			std::streamsize cprecision = os.precision();
			os.width(9); os.precision(4);
			os << "$$ \\left[ \\begin{array}{ccc}\n";
			os << m[0][0] << " & " << m[0][1] << " & " << m[0][2] << "\\\\\n";
			os << m[1][0] << " & " << m[1][1] << " & " << m[1][2] << "\\\\\n";
			os << m[2][0] << " & " << m[2][1] << " & " << m[2][2] << "\n";
			os << "\\end{array} \\right] $$\n";
			if (nl) { os << "\n"; }
			os.width(cwidth); os.precision(cprecision);
			if (fixedl) { os.flags(f); }
#endif
			}

		Mat3<T> operator+ (const Mat3<T> &R) const;
		Mat3<T> operator- () const;
		Mat3<T> operator- (const Mat3<T> &R) const;
		Vec3<T> operator* (const Vec3<T> &R) const;
		Mat3<T> operator* (const T &R) const;
		Mat3<T> operator* (const Mat3<T> &R) const;
		Mat3<T> operator/ (const T &R) const;
		Mat3<T> operator/ (const Mat3<T> &R) const;
		Mat3<T>& operator+= (const Mat3<T> &R);
		Mat3<T>& operator-= (const Mat3<T> &R);
		Mat3<T>& operator*= (const Mat3<T> &R);
		Mat3<T>& operator*= (const T &R);
		Mat3<T>& operator/= (const Mat3<T> &R);
		Mat3<T>& operator/= (const T &R);
		bool operator== (const Mat3<T> &R) const;
		bool operator!= (const Mat3<T> &R) const;
	};

template <class T>
Mat3<T> Mat3<T>::operator+ (const Mat3<T> &R) const
	{
	Mat3<T> c;
	c.m[0][0]=m[0][0]+R.m[0][0]; c.m[1][0]=m[1][0]+R.m[1][0]; c.m[2][0]=m[2][0]+R.m[2][0];
	c.m[0][1]=m[0][1]+R.m[0][1]; c.m[1][1]=m[1][1]+R.m[1][1]; c.m[2][1]=m[2][1]+R.m[2][1];
	c.m[0][2]=m[0][2]+R.m[0][2]; c.m[1][2]=m[1][2]+R.m[1][2]; c.m[2][2]=m[2][2]+R.m[2][2];
	return(c);
	}

template <class T>
Mat3<T> Mat3<T>::operator- () const
	{
	Mat3<T> c;
	c.x0=-x0; c.y0=-y0; c.z0=-z0;
	c.x1=-x1; c.y1=-y1; c.z1=-z1;
	c.x2=-x2; c.y2=-y2; c.z2=-z2;
	return(c);
	}

template <class T>
Mat3<T> Mat3<T>::operator- (const Mat3<T> &R) const
	{
	Mat3<T> c;
	c.m[0][0]=m[0][0]-R.m[0][0]; c.m[1][0]=m[1][0]-R.m[1][0]; c.m[2][0]=m[2][0]-R.m[2][0];
	c.m[0][1]=m[0][1]-R.m[0][1]; c.m[1][1]=m[1][1]-R.m[1][1]; c.m[2][1]=m[2][1]-R.m[2][1];
	c.m[0][2]=m[0][2]-R.m[0][2]; c.m[1][2]=m[1][2]-R.m[1][2]; c.m[2][2]=m[2][2]-R.m[2][2];
	return(c);
	}

template <class T>
Vec3<T> Mat3<T>::operator* (const Vec3<T> &R) const
	{
	Vec3<T> c;
	c.x=R.x*x0+R.y*x1+R.z*x2;
	c.y=R.x*y0+R.y*y1+R.z*y2;
	c.z=R.x*z0+R.y*z1+R.z*z2;
	return(c);
	}

template <class T>
Vec3<T> operator* (const Vec3<T> &L, const Mat3<T> &R)
	{
	Vec3<T> c;
	c.x=L.x*R.x0+L.y*R.y0+L.z*R.z0;
	c.y=L.x*R.x1+L.y*R.y1+L.z*R.z1;
	c.z=L.x*R.x2+L.y*R.y2+L.z*R.z2;
	return(c);
	}

template <class T>
Mat3<T> Mat3<T>::operator* (const T &R) const
	{
	Mat3<T> c;
	c.m[0][0]=m[0][0]*R; c.m[1][0]=m[1][0]*R; c.m[2][0]=m[2][0]*R;
	c.m[0][1]=m[0][1]*R; c.m[1][1]=m[1][1]*R; c.m[2][1]=m[2][1]*R;
	c.m[0][2]=m[0][2]*R; c.m[1][2]=m[1][2]*R; c.m[2][2]=m[2][2]*R;
	return(c);
	}

#if _MSC_VER == 1200
template <class T>
Mat3<T> operator* (const T &L, const Mat3<T> &R)
#else
template <class T, class U>
Mat3<T> operator* (const U &L, const Mat3<T> &R)
#endif
	{
	return(R*L);
	}

template <class T>
Mat3<T> Mat3<T>::operator* (const Mat3<T> &R) const
	{
	Mat3<T> c;
	c.m[0][0]=R.m[0][0]*m[0][0]+R.m[1][0]*m[0][1]+R.m[2][0]*m[0][2];
	c.m[1][0]=R.m[0][0]*m[1][0]+R.m[1][0]*m[1][1]+R.m[2][0]*m[1][2];
	c.m[2][0]=R.m[0][0]*m[2][0]+R.m[1][0]*m[2][1]+R.m[2][0]*m[2][2];
	c.m[0][1]=R.m[0][1]*m[0][0]+R.m[1][1]*m[0][1]+R.m[2][1]*m[0][2];
	c.m[1][1]=R.m[0][1]*m[1][0]+R.m[1][1]*m[1][1]+R.m[2][1]*m[1][2];
	c.m[2][1]=R.m[0][1]*m[2][0]+R.m[1][1]*m[2][1]+R.m[2][1]*m[2][2];
	c.m[0][2]=R.m[0][2]*m[0][0]+R.m[1][2]*m[0][1]+R.m[2][2]*m[0][2];
	c.m[1][2]=R.m[0][2]*m[1][0]+R.m[1][2]*m[1][1]+R.m[2][2]*m[1][2];
	c.m[2][2]=R.m[0][2]*m[2][0]+R.m[1][2]*m[2][1]+R.m[2][2]*m[2][2];
	return(c);
	}

template <class T>
Mat3<T> Mat3<T>::operator/ (const T &R) const
	{
	Mat3<T> c;
	c.m[0][0]=m[0][0]/R; c.m[1][0]=m[1][0]/R; c.m[2][0]=m[2][0]/R;
	c.m[0][1]=m[0][1]/R; c.m[1][1]=m[1][1]/R; c.m[2][1]=m[2][1]/R;
	c.m[0][2]=m[0][2]/R; c.m[1][2]=m[1][2]/R; c.m[2][2]=m[2][2]/R;
	return(c);
	}

template <class T>
Mat3<T> Mat3<T>::operator/ (const Mat3<T> &R) const
	{
	return(*this*R.inverse());
	}

template <class T>
Mat3<T>& Mat3<T>::operator+= (const Mat3<T> &R)
	{
	*this=*this+R;
	return(*this);
	}

template <class T>
Mat3<T>& Mat3<T>::operator-= (const Mat3<T> &R)
	{
	*this=*this-R;
	return(*this);
	}

template <class T>
Mat3<T>& Mat3<T>::operator*= (const Mat3<T> &R)
	{
	*this=*this*R;
	return(*this);
	}

template <class T>
Mat3<T>& Mat3<T>::operator*= (const T &R)
	{
	*this=*this*R;
	return(*this);
	}

template <class T>
Mat3<T>& Mat3<T>::operator/= (const Mat3<T> &R)
	{
	*this=*this/R;
	return(*this);
	}

template <class T>
Mat3<T>& Mat3<T>::operator/= (const T &R)
	{
	*this=*this/R;
	return(*this);
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
bool Mat3<T>::operator== (const Mat3<T> &R) const
	{
	return((eq(M[0],R.M[0]))&&(eq(M[1],R.M[1]))
		&&(eq(M[2],R.M[2]))&&(eq(M[3],R.M[3]))
		&&(eq(M[4],R.M[4]))&&(eq(M[5],R.M[5]))
		&&(eq(M[6],R.M[6]))&&(eq(M[7],R.M[7]))
		&&(eq(M[8],R.M[8])));
	}

template <class T>
bool Mat3<T>::operator!= (const Mat3<T> &R) const
	{
	return((ne(M[0],R.M[0]))||(ne(M[1],R.M[1]))
		||(ne(M[2],R.M[2]))||(ne(M[3],R.M[3]))
		||(ne(M[4],R.M[4]))||(ne(M[5],R.M[5]))
		||(ne(M[6],R.M[6]))||(ne(M[7],R.M[7]))
		||(ne(M[8],R.M[8])));
	}

#undef eq
#undef ne

#else

template <class T>
bool Mat3<T>::operator== (const Mat3<T> &R) const
	{
	return((M[0]==R.M[0])&&(M[1]==R.M[1])&&(M[2]==R.M[2])
		&&(M[3]==R.M[3])&&(M[4]==R.M[4])&&(M[5]==R.M[5])
		&&(M[6]==R.M[6])&&(M[7]==R.M[7])&&(M[8]==R.M[8]));
	}

template <class T>
bool Mat3<T>::operator!= (const Mat3<T> &R) const
	{
	return((M[0]!=R.M[0])||(M[1]!=R.M[1])||(M[2]!=R.M[2])
		||(M[3]!=R.M[3])||(M[4]!=R.M[4])||(M[5]!=R.M[5])
		||(M[6]!=R.M[6])||(M[7]!=R.M[7])||(M[8]!=R.M[8]));
	}

#endif

#define FORM std::setprecision(4) << std::setw(9)

template <class T>
std::ostream& operator<< (std::ostream &os, const Mat3<T> &R)
	{
	std::ios_base::fmtflags f = os.flags();
	os << std::fixed;
	os << std::endl;
	os << "| " << FORM << R.x0 << " " << FORM << R.x1 << " " << FORM << R.x2 << " |" << std::endl;
	os << "| " << FORM << R.y0 << " " << FORM << R.y1 << " " << FORM << R.y2 << " |" << std::endl;
	os << "| " << FORM << R.z0 << " " << FORM << R.z1 << " " << FORM << R.z2 << " |" << std::endl;
	os.flags(f);
	return(os);
	}

typedef Mat3<float> mat3;

#endif
