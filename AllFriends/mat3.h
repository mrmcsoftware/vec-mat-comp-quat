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

	friend Mat3<T> operator+ (const Mat3<T> &L, const Mat3<T> &R)
		{
		Mat3<T> c;
		c.m[0][0]=L.m[0][0]+R.m[0][0]; c.m[1][0]=L.m[1][0]+R.m[1][0]; c.m[2][0]=L.m[2][0]+R.m[2][0];
		c.m[0][1]=L.m[0][1]+R.m[0][1]; c.m[1][1]=L.m[1][1]+R.m[1][1]; c.m[2][1]=L.m[2][1]+R.m[2][1];
		c.m[0][2]=L.m[0][2]+R.m[0][2]; c.m[1][2]=L.m[1][2]+R.m[1][2]; c.m[2][2]=L.m[2][2]+R.m[2][2];
		return(c);
		}

	friend Mat3<T> operator- (const Mat3<T> &R)
		{
		Mat3<T> c;
		c.x0=-R.x0; c.y0=-R.y0; c.z0=-R.z0;
		c.x1=-R.x1; c.y1=-R.y1; c.z1=-R.z1;
		c.x2=-R.x2; c.y2=-R.y2; c.z2=-R.z2;
		return(c);
		}

	friend Mat3<T> operator- (const Mat3<T> &L, const Mat3<T> &R)
		{
		Mat3<T> c;
		c.m[0][0]=L.m[0][0]-R.m[0][0]; c.m[1][0]=L.m[1][0]-R.m[1][0]; c.m[2][0]=L.m[2][0]-R.m[2][0];
		c.m[0][1]=L.m[0][1]-R.m[0][1]; c.m[1][1]=L.m[1][1]-R.m[1][1]; c.m[2][1]=L.m[2][1]-R.m[2][1];
		c.m[0][2]=L.m[0][2]-R.m[0][2]; c.m[1][2]=L.m[1][2]-R.m[1][2]; c.m[2][2]=L.m[2][2]-R.m[2][2];
		return(c);
		}

	friend Vec3<T> operator* (const Mat3<T> &L, const Vec3<T> &R)
		{
		Vec3<T> c;
		c.x=R.x*L.x0+R.y*L.x1+R.z*L.x2;
		c.y=R.x*L.y0+R.y*L.y1+R.z*L.y2;
		c.z=R.x*L.z0+R.y*L.z1+R.z*L.z2;
		return(c);
		}

	friend Vec3<T> operator* (const Vec3<T> &L, const Mat3<T> &R)
		{
		Vec3<T> c;
		c.x=L.x*R.x0+L.y*R.y0+L.z*R.z0;
		c.y=L.x*R.x1+L.y*R.y1+L.z*R.z1;
		c.z=L.x*R.x2+L.y*R.y2+L.z*R.z2;
		return(c);
		}

	friend Mat3<T> operator* (const Mat3<T> &L, const T &R)
		{
		Mat3<T> c;
		c.m[0][0]=L.m[0][0]*R; c.m[1][0]=L.m[1][0]*R; c.m[2][0]=L.m[2][0]*R;
		c.m[0][1]=L.m[0][1]*R; c.m[1][1]=L.m[1][1]*R; c.m[2][1]=L.m[2][1]*R;
		c.m[0][2]=L.m[0][2]*R; c.m[1][2]=L.m[1][2]*R; c.m[2][2]=L.m[2][2]*R;
		return(c);
		}

	friend Mat3<T> operator* (const T &L, const Mat3<T> &R)
		{
		return(R*L);
		}

	friend Mat3<T> operator* (const Mat3<T> &L, const Mat3<T> &R)
		{
		Mat3<T> c;
		c.m[0][0]=R.m[0][0]*L.m[0][0]+R.m[1][0]*L.m[0][1]+R.m[2][0]*L.m[0][2];
		c.m[1][0]=R.m[0][0]*L.m[1][0]+R.m[1][0]*L.m[1][1]+R.m[2][0]*L.m[1][2];
		c.m[2][0]=R.m[0][0]*L.m[2][0]+R.m[1][0]*L.m[2][1]+R.m[2][0]*L.m[2][2];
		c.m[0][1]=R.m[0][1]*L.m[0][0]+R.m[1][1]*L.m[0][1]+R.m[2][1]*L.m[0][2];
		c.m[1][1]=R.m[0][1]*L.m[1][0]+R.m[1][1]*L.m[1][1]+R.m[2][1]*L.m[1][2];
		c.m[2][1]=R.m[0][1]*L.m[2][0]+R.m[1][1]*L.m[2][1]+R.m[2][1]*L.m[2][2];
		c.m[0][2]=R.m[0][2]*L.m[0][0]+R.m[1][2]*L.m[0][1]+R.m[2][2]*L.m[0][2];
		c.m[1][2]=R.m[0][2]*L.m[1][0]+R.m[1][2]*L.m[1][1]+R.m[2][2]*L.m[1][2];
		c.m[2][2]=R.m[0][2]*L.m[2][0]+R.m[1][2]*L.m[2][1]+R.m[2][2]*L.m[2][2];
		return(c);
		}

	friend Mat3<T> operator/ (const Mat3<T> &L, const T &R)
		{
		Mat3<T> c;
		c.m[0][0]=L.m[0][0]/R; c.m[1][0]=L.m[1][0]/R; c.m[2][0]=L.m[2][0]/R;
		c.m[0][1]=L.m[0][1]/R; c.m[1][1]=L.m[1][1]/R; c.m[2][1]=L.m[2][1]/R;
		c.m[0][2]=L.m[0][2]/R; c.m[1][2]=L.m[1][2]/R; c.m[2][2]=L.m[2][2]/R;
		return(c);
		}

	friend Mat3<T> operator/ (const Mat3<T> &L, const Mat3<T> &R)
		{
		return(L*R.inverse());
		}

	friend Mat3<T>& operator+= (Mat3<T> &L, const Mat3<T> &R)
		{
		L=L+R;
		return(L);
		}

	friend Mat3<T>& operator-= (Mat3<T> &L, const Mat3<T> &R)
		{
		L=L-R;
		return(L);
		}

	friend Mat3<T>& operator*= (Mat3<T> &L, const Mat3<T> &R)
		{
		L=L*R;
		return(L);
		}

	friend Mat3<T>& operator*= (Mat3<T> &L, const T &R)
		{
		L=L*R;
		return(L);
		}

	friend Mat3<T>& operator/= (Mat3<T> &L, const Mat3<T> &R)
		{
		L=L/R;
		return(L);
		}

	friend Mat3<T>& operator/= (Mat3<T> &L, const T &R)
		{
		L=L/R;
		return(L);
		}

#ifdef EPSILONCOMP

#define eq(a,b) (fabs(a-b)<EPSILONCOMP)
#define ne(a,b) (fabs(a-b)>=EPSILONCOMP)

	friend bool operator== (const Mat3<T> &L, const Mat3<T> &R)
		{
		return((eq(L.M[0],R.M[0]))&&(eq(L.M[1],R.M[1]))
			&&(eq(L.M[2],R.M[2]))&&(eq(L.M[3],R.M[3]))
			&&(eq(L.M[4],R.M[4]))&&(eq(L.M[5],R.M[5]))
			&&(eq(L.M[6],R.M[6]))&&(eq(L.M[7],R.M[7]))
			&&(eq(L.M[8],R.M[8])));
		}

	friend bool operator!= (const Mat3<T> &L, const Mat3<T> &R)
		{
		return((ne(L.M[0],R.M[0]))||(ne(L.M[1],R.M[1]))
			||(ne(L.M[2],R.M[2]))||(ne(L.M[3],R.M[3]))
			||(ne(L.M[4],R.M[4]))||(ne(L.M[5],R.M[5]))
			||(ne(L.M[6],R.M[6]))||(ne(L.M[7],R.M[7]))
			||(ne(L.M[8],R.M[8])));
		}

#undef eq
#undef ne

#else

	friend bool operator== (const Mat3<T> &L, const Mat3<T> &R)
		{
		return((L.M[0]==R.M[0])&&(L.M[1]==R.M[1])&&(L.M[2]==R.M[2])
			&&(L.M[3]==R.M[3])&&(L.M[4]==R.M[4])&&(L.M[5]==R.M[5])
			&&(L.M[6]==R.M[6])&&(L.M[7]==R.M[7])&&(L.M[8]==R.M[8]));
		}

	friend bool operator!= (const Mat3<T> &L, const Mat3<T> &R)
		{
		return((L.M[0]!=R.M[0])||(L.M[1]!=R.M[1])||(L.M[2]!=R.M[2])
			||(L.M[3]!=R.M[3])||(L.M[4]!=R.M[4])||(L.M[5]!=R.M[5])
			||(L.M[6]!=R.M[6])||(L.M[7]!=R.M[7])||(L.M[8]!=R.M[8]));
		}

#endif

#define FORM std::setprecision(4) << std::setw(9)

	friend std::ostream& operator<< (std::ostream &os, const Mat3<T> &R)
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
	};

typedef Mat3<float> mat3;

#endif
