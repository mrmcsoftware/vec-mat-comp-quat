/*********************************************************
   4x4 matrix class
   Copyright © 2021 Mark Craig

   https://www.youtube.com/MrMcSoftware
**********************************************************/

#ifndef _MAT4_H
#define _MAT4_H

#include <cstdio>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "vec4.h"

template <class T>
class Mat4
	{
	public:
		union
			{
			struct { T m[4][4]; };
			struct { T M[16]; };
			struct { T x0,x1,x2,x3,y0,y1,y2,y3,z0,z1,z2,z3,w0,w1,w2,w3; };
			};

		Mat4<T>() { x0=y0=z0=w0=x1=y1=z1=w1=x2=y2=z2=w2=x3=y3=z3=w3=0; }

		Mat4<T>(T X0) { y0=z0=w0=x1=z1=w1=x2=y2=w2=x3=y3=z3=0; x0=y1=z2=w3=X0; }

		Mat4<T>(T X0, T Y0, T Z0, T W0, T X1, T Y1, T Z1, T W1, T X2, T Y2, T Z2, T W2, T X3, T Y3, T Z3, T W3)
			{ x0=X0; y0=Y0; z0=Z0; w0=W0; x1=X1; y1=Y1; z1=Z1; w1=W1; x2=X2; y2=Y2; z2=Z2; w2=W2; x3=X3; y3=Y3; z3=Z3; w3=W3; }

		Mat4<T>(Vec4<T> v1, Vec4<T> v2, Vec4<T> v3, Vec4<T> v4)
			{ x0=v1.x; y0=v1.y; z0=v1.z; w0=v1.w; x1=v2.x; y1=v2.y; z1=v2.z; w1=v2.w; x2=v3.x; y2=v3.y; z2=v3.z; w2=v3.w; x3=v4.x; y3=v4.y; z3=v4.z; w3=v4.w; }

		Mat4<T>(const Mat4<T> &v)
			{ x0=v.x0; y0=v.y0; z0=v.z0; w0=v.w0; x1=v.x1; y1=v.y1; z1=v.z1; w1=v.w1; x2=v.x2; y2=v.y2; z2=v.z2; w2=v.w2; x3=v.x3; y3=v.y3; z3=v.z3; w3=v.w3; }

		inline Mat4<T> const transpose() const
			{
			Mat4<T> trans;
			trans.m[0][0]=m[0][0]; trans.m[1][0]=m[0][1]; trans.m[2][0]=m[0][2];
			trans.m[3][0]=m[0][3];
			trans.m[0][1]=m[1][0]; trans.m[1][1]=m[1][1]; trans.m[2][1]=m[1][2];
			trans.m[3][1]=m[1][3];
			trans.m[0][2]=m[2][0]; trans.m[1][2]=m[2][1]; trans.m[2][2]=m[2][2];
			trans.m[3][2]=m[2][3];
			trans.m[0][3]=m[3][0]; trans.m[1][3]=m[3][1]; trans.m[2][3]=m[3][2];
			trans.m[3][3]=m[3][3];
			return(trans);
			}

		/* I didn't feel like deriving determinant and inverse of 4x4 matrix -
			these are based on GLM (Copyright (c) 2005 - G-Truc Creation) */

		inline T const determinant() const
			{
			T f0=m[2][2]*m[3][3]-m[2][3]*m[3][2];
			T f1=m[1][2]*m[3][3]-m[1][3]*m[3][2];
			T f2=m[1][2]*m[2][3]-m[1][3]*m[2][2];
			T f3=m[0][2]*m[3][3]-m[0][3]*m[3][2];
			T f4=m[0][2]*m[2][3]-m[0][3]*m[2][2];
			T f5=m[0][2]*m[1][3]-m[0][3]*m[1][2];
			Vec4<T> dc=Vec4<T>((m[1][1]*f0-m[2][1]*f1+m[3][1]*f2),-(m[0][1]*f0-m[2][1]*f3+m[3][1]*f4),(m[0][1]*f1-m[1][1]*f3+m[3][1]*f5),
				-(m[0][1]*f2-m[1][1]*f4+m[2][1]*f5));
			return(m[0][0]*dc.x+m[1][0]*dc.y+m[2][0]*dc.z+m[3][0]*dc.w);
			}

		inline Mat4<T> const inverse() const
			{
			T c00=m[2][2]*m[3][3]-m[2][3]*m[3][2];
			T c02=m[2][1]*m[3][3]-m[2][3]*m[3][1];
			T c03=m[2][1]*m[3][2]-m[2][2]*m[3][1];
			T c04=m[1][2]*m[3][3]-m[1][3]*m[3][2];
			T c06=m[1][1]*m[3][3]-m[1][3]*m[3][1];
			T c07=m[1][1]*m[3][2]-m[1][2]*m[3][1];
			T c08=m[1][2]*m[2][3]-m[1][3]*m[2][2];
			T c10=m[1][1]*m[2][3]-m[1][3]*m[2][1];
			T c11=m[1][1]*m[2][2]-m[1][2]*m[2][1];
			T c12=m[0][2]*m[3][3]-m[0][3]*m[3][2];
			T c14=m[0][1]*m[3][3]-m[0][3]*m[3][1];
			T c15=m[0][1]*m[3][2]-m[0][2]*m[3][1];
			T c16=m[0][2]*m[2][3]-m[0][3]*m[2][2];
			T c18=m[0][1]*m[2][3]-m[0][3]*m[2][1];
			T c19=m[0][1]*m[2][2]-m[0][2]*m[2][1];
			T c20=m[0][2]*m[1][3]-m[0][3]*m[1][2];
			T c22=m[0][1]*m[1][3]-m[0][3]*m[1][1];
			T c23=m[0][1]*m[1][2]-m[0][2]*m[1][1];
			Vec4<T> f0(c00,c00,c02,c03);
			Vec4<T> f1(c04,c04,c06,c07);
			Vec4<T> f2(c08,c08,c10,c11);
			Vec4<T> f3(c12,c12,c14,c15);
			Vec4<T> f4(c16,c16,c18,c19);
			Vec4<T> f5(c20,c20,c22,c23);
			Vec4<T> v0(m[0][1],m[0][0],m[0][0],m[0][0]);
			Vec4<T> v1(m[1][1],m[1][0],m[1][0],m[1][0]);
			Vec4<T> v2(m[2][1],m[2][0],m[2][0],m[2][0]);
			Vec4<T> v3(m[3][1],m[3][0],m[3][0],m[3][0]);
			Vec4<T> i0(v1*f0-v2*f1+v3*f2);
			Vec4<T> i1(v0*f0-v2*f3+v3*f4);
			Vec4<T> i2(v0*f1-v1*f3+v3*f5);
			Vec4<T> i3(v0*f2-v1*f4+v2*f5);
			Vec4<T> sA(1,-1,1,-1);
			Vec4<T> sB(-1,1,-1,1);
			Mat4<T> inv(i0*sA,i1*sB,i2*sA,i3*sB);
			Vec4<T> r0(inv.m[0][0],inv.m[0][1],inv.m[0][2],inv.m[0][3]);
			Vec4<T> d0(m[0][0]*r0.x,m[1][0]*r0.y,m[2][0]*r0.z,m[3][0]*r0.w);
			T d1=(d0.x+d0.y)+(d0.z+d0.w);
			T invdet= static_cast<T>(1)/d1;
			return(inv*invdet);
			}

		inline void const print(int nl=1) const
			{
			printf("| %9.4f %9.4f %9.4f %9.4f |\n",m[0][0],m[0][1],m[0][2],m[0][3]);
			printf("| %9.4f %9.4f %9.4f %9.4f |\n",m[1][0],m[1][1],m[1][2],m[1][3]);
			printf("| %9.4f %9.4f %9.4f %9.4f |\n",m[2][0],m[2][1],m[2][2],m[2][3]);
			printf("| %9.4f %9.4f %9.4f %9.4f |\n",m[3][0],m[3][1],m[3][2],m[3][3]);
			if (nl) { printf("\n"); }
			}

		Mat4<T> operator+ (const Mat4<T> &R) const;
		Mat4<T> operator- () const;
		Mat4<T> operator- (const Mat4<T> &R) const;
		Vec4<T> operator* (const Vec4<T> &R) const;
		Mat4<T> operator* (const T &R) const;
		Mat4<T> operator* (const Mat4<T> &R) const;
		Mat4<T> operator/ (const T &R) const;
		Mat4<T> operator/ (const Mat4<T> &R) const;
		Mat4<T>& operator+= (const Mat4<T> &R);
		Mat4<T>& operator-= (const Mat4<T> &R);
		Mat4<T>& operator*= (const Mat4<T> &R);
		Mat4<T>& operator*= (const T &R);
		Mat4<T>& operator/= (const Mat4<T> &R);
		Mat4<T>& operator/= (const T &R);
		bool operator== (const Mat4<T> &R) const;
		bool operator!= (const Mat4<T> &R) const;
	};

template <class T>
Mat4<T> Mat4<T>::operator+ (const Mat4<T> &R) const
	{
	Mat4<T> c;
	c.m[0][0]=m[0][0]+R.m[0][0]; c.m[1][0]=m[1][0]+R.m[1][0]; c.m[2][0]=m[2][0]+R.m[2][0]; c.m[3][0]=m[3][0]+R.m[3][0];
	c.m[0][1]=m[0][1]+R.m[0][1]; c.m[1][1]=m[1][1]+R.m[1][1]; c.m[2][1]=m[2][1]+R.m[2][1]; c.m[3][1]=m[3][1]+R.m[3][1];
	c.m[0][2]=m[0][2]+R.m[0][2]; c.m[1][2]=m[1][2]+R.m[1][2]; c.m[2][2]=m[2][2]+R.m[2][2]; c.m[3][2]=m[3][2]+R.m[3][2];
	c.m[0][3]=m[0][3]+R.m[0][3]; c.m[1][3]=m[1][3]+R.m[1][3]; c.m[2][3]=m[2][3]+R.m[2][3]; c.m[3][3]=m[3][3]+R.m[3][3];
	return(c);
	}

template <class T>
Mat4<T> Mat4<T>::operator- () const
	{
	Mat4<T> c;
	c.x0=-x0; c.y0=-y0; c.z0=-z0; c.w0=-w0;
	c.x1=-x1; c.y1=-y1; c.z1=-z1; c.w1=-w1;
	c.x2=-x2; c.y2=-y2; c.z2=-z2; c.w2=-w2;
	c.x3=-x3; c.y3=-y3; c.z3=-z3; c.w3=-w3;
	return(c);
	}

template <class T>
Mat4<T> Mat4<T>::operator- (const Mat4<T> &R) const
	{
	Mat4<T> c;
	c.m[0][0]=m[0][0]-R.m[0][0]; c.m[1][0]=m[1][0]-R.m[1][0]; c.m[2][0]=m[2][0]-R.m[2][0]; c.m[3][0]=m[3][0]-R.m[3][0];
	c.m[0][1]=m[0][1]-R.m[0][1]; c.m[1][1]=m[1][1]-R.m[1][1]; c.m[2][1]=m[2][1]-R.m[2][1]; c.m[3][1]=m[3][1]-R.m[3][1];
	c.m[0][2]=m[0][2]-R.m[0][2]; c.m[1][2]=m[1][2]-R.m[1][2]; c.m[2][2]=m[2][2]-R.m[2][2]; c.m[3][2]=m[3][2]-R.m[3][2];
	c.m[0][3]=m[0][3]-R.m[0][3]; c.m[1][3]=m[1][3]-R.m[1][3]; c.m[2][3]=m[2][3]-R.m[2][3]; c.m[3][3]=m[3][3]-R.m[3][3];
	return(c);
	}

template <class T>
Vec4<T> Mat4<T>::operator* (const Vec4<T> &R) const
	{
	Vec4<T> c;
	c.x=R.x*x0+R.y*x1+R.z*x2+R.w*x3;
	c.y=R.x*y0+R.y*y1+R.z*y2+R.w*y3;
	c.z=R.x*z0+R.y*z1+R.z*z2+R.w*z3;
	c.w=R.x*w0+R.y*w1+R.z*w2+R.w*w3;
	return(c);
	}

template <class T>
Vec4<T> operator* (const Vec4<T> &L, const Mat4<T> &R)
	{
	Vec4<T> c;
	c.x=L.x*R.x0+L.y*R.y0+L.z*R.z0+L.w*R.w0;
	c.y=L.x*R.x1+L.y*R.y1+L.z*R.z1+L.w*R.w1;
	c.z=L.x*R.x2+L.y*R.y2+L.z*R.z2+L.w*R.w2;
	c.w=L.x*R.x3+L.y*R.y3+L.z*R.z3+L.w*R.w3;
	return(c);
	}

template <class T>
Mat4<T> Mat4<T>::operator* (const T &R) const
	{
	Mat4<T> c;
	c.m[0][0]=m[0][0]*R; c.m[1][0]=m[1][0]*R; c.m[2][0]=m[2][0]*R; c.m[3][0]=m[3][0]*R;
	c.m[0][1]=m[0][1]*R; c.m[1][1]=m[1][1]*R; c.m[2][1]=m[2][1]*R; c.m[3][1]=m[3][1]*R;
	c.m[0][2]=m[0][2]*R; c.m[1][2]=m[1][2]*R; c.m[2][2]=m[2][2]*R; c.m[3][2]=m[3][2]*R;
	c.m[0][3]=m[0][3]*R; c.m[1][3]=m[1][3]*R; c.m[2][3]=m[2][3]*R; c.m[3][3]=m[3][3]*R;
	return(c);
	}

#if _MSC_VER == 1200
template <class T>
Mat4<T> operator* (const T &L, const Mat4<T> &R)
#else
template <class T, class U>
Mat4<T> operator* (const U &L, const Mat4<T> &R)
#endif
	{
	return(R*L);
	}

template <class T>
Mat4<T> Mat4<T>::operator* (const Mat4<T> &R) const
	{
	Mat4<T> c;
	int i,j;
	for (j=0;j<4;j++)
		{
		for (i=0;i<4;i++)
			{
			c.m[i][j]=R.m[0][j]*m[i][0]+R.m[1][j]*m[i][1]+R.m[2][j]*m[i][2]+R.m[3][j]*m[i][3];
			}
		}
	return(c);
	}

template <class T>
Mat4<T> Mat4<T>::operator/ (const T &R) const
	{
	Mat4<T> c;
	c.m[0][0]=m[0][0]/R; c.m[1][0]=m[1][0]/R; c.m[2][0]=m[2][0]/R; c.m[3][0]=m[3][0]/R;
	c.m[0][1]=m[0][1]/R; c.m[1][1]=m[1][1]/R; c.m[2][1]=m[2][1]/R; c.m[3][1]=m[3][1]/R;
	c.m[0][2]=m[0][2]/R; c.m[1][2]=m[1][2]/R; c.m[2][2]=m[2][2]/R; c.m[3][2]=m[3][2]/R;
	c.m[0][3]=m[0][3]/R; c.m[1][3]=m[1][3]/R; c.m[2][3]=m[2][3]/R; c.m[3][3]=m[3][3]/R;
	return(c);
	}

template <class T>
Mat4<T> Mat4<T>::operator/ (const Mat4<T> &R) const
	{
	return(*this*R.inverse());
	}

template <class T>
Mat4<T>& Mat4<T>::operator+= (const Mat4<T> &R)
	{
	*this=*this+R;
	return(*this);
	}

template <class T>
Mat4<T>& Mat4<T>::operator-= (const Mat4<T> &R)
	{
	*this=*this-R;
	return(*this);
	}

template <class T>
Mat4<T>& Mat4<T>::operator*= (const Mat4<T> &R)
	{
	*this=*this*R;
	return(*this);
	}

template <class T>
Mat4<T>& Mat4<T>::operator*= (const T &R)
	{
	*this=*this*R;
	return(*this);
	}

template <class T>
Mat4<T>& Mat4<T>::operator/= (const Mat4<T> &R)
	{
	*this=*this/R;
	return(*this);
	}

template <class T>
Mat4<T>& Mat4<T>::operator/= (const T &R)
	{
	*this=*this/R;
	return(*this);
	}

#ifdef EPSILONCOMP

#define eq(a,b) (fabs(a-b)<EPSILONCOMP)
#define ne(a,b) (fabs(a-b)>=EPSILONCOMP)

template <class T>
bool Mat4<T>::operator== (const Mat4<T> &R) const
	{
	return((eq(M[0],R.M[0]))&&(eq(M[1],R.M[1]))
		&&(eq(M[2],R.M[2]))&&(eq(M[3],R.M[3]))
		&&(eq(M[4],R.M[4]))&&(eq(M[5],R.M[5]))
		&&(eq(M[6],R.M[6]))&&(eq(M[7],R.M[7]))
		&&(eq(M[8],R.M[8]))&&(eq(M[9],R.M[9]))
		&&(eq(M[10],R.M[10]))&&(eq(M[11],R.M[11]))
		&&(eq(M[12],R.M[12]))&&(eq(M[13],R.M[13]))
		&&(eq(M[14],R.M[14]))&&(eq(M[15],R.M[15])));
	}

template <class T>
bool Mat4<T>::operator!= (const Mat4<T> &R) const
	{
	return((ne(M[0],R.M[0]))||(ne(M[1],R.M[1]))
		||(ne(M[2],R.M[2]))||(ne(M[3],R.M[3]))
		||(ne(M[4],R.M[4]))||(ne(M[5],R.M[5]))
		||(ne(M[6],R.M[6]))||(ne(M[7],R.M[7]))
		||(ne(M[8],R.M[8]))||(ne(M[9],R.M[9]))
		||(ne(M[10],R.M[10]))||(ne(M[11],R.M[11]))
		||(ne(M[12],R.M[12]))||(ne(M[13],R.M[13]))
		||(ne(M[14],R.M[14]))||(ne(M[15],R.M[15])));
	}

#undef eq
#undef ne

#else

template <class T>
bool Mat4<T>::operator== (const Mat4<T> &R) const
	{
	return((M[0]==R.M[0])&&(M[1]==R.M[1])&&(M[2]==R.M[2])
		&&(M[3]==R.M[3])&&(M[4]==R.M[4])&&(M[5]==R.M[5])
		&&(M[6]==R.M[6])&&(M[7]==R.M[7])&&(M[8]==R.M[8])
		&&(M[9]==R.M[9])&&(M[10]==R.M[10])&&(M[11]==R.M[11])
		&&(M[12]==R.M[12])&&(M[13]==R.M[13])&&(M[14]==R.M[14])
		&&(M[15]==R.M[15]));
	}

template <class T>
bool Mat4<T>::operator!= (const Mat4<T> &R) const
	{
	return((M[0]!=R.M[0])||(M[1]!=R.M[1])||(M[2]!=R.M[2])
		||(M[3]!=R.M[3])||(M[4]!=R.M[4])||(M[5]!=R.M[5])
		||(M[6]!=R.M[6])||(M[7]!=R.M[7])||(M[8]!=R.M[8])
		||(M[9]!=R.M[9])||(M[10]!=R.M[10])||(M[11]!=R.M[11])
		||(M[12]!=R.M[12])||(M[13]!=R.M[13])||(M[14]!=R.M[14])
		||(M[15]!=R.M[15]));
	}

#endif

#define FORM std::setprecision(4) << std::setw(9)

template <class T>
std::ostream& operator<< (std::ostream &os, const Mat4<T> &R)
	{
	std::ios_base::fmtflags f = os.flags();
	os << std::fixed;
	os << std::endl;
	os << "| " << FORM << R.x0 << " " << FORM << R.x1 << " " << FORM << R.x2 << " " << FORM << R.x3 << " |" << std::endl;
	os << "| " << FORM << R.y0 << " " << FORM << R.y1 << " " << FORM << R.y2 << " " << FORM << R.y3 << " |" << std::endl;
	os << "| " << FORM << R.z0 << " " << FORM << R.z1 << " " << FORM << R.z2 << " " << FORM << R.z3 << " |" << std::endl;
	os << "| " << FORM << R.w0 << " " << FORM << R.w1 << " " << FORM << R.w2 << " " << FORM << R.w3 << " |" << std::endl;
	os.flags(f);
	return(os);
	}

typedef Mat4<float> mat4;

#endif
