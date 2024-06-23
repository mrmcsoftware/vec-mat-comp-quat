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

#ifdef VEC_USE_MAT
template <class T>
class Vec2;
#endif

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

		inline void const latex(int nl=1, bool fixedl=true, std::ostream &os=std::cout) const
			{
#if 0
			printf("$$ \\left[ \\begin{array}{cc}\n");
			printf("%9.4f & %9.4f\\\\\n",m[0][0],m[0][1]);
			printf("%9.4f & %9.4f\n",m[1][0],m[1][1]);
			printf("\\end{array} \\right] $$\n");
			if (nl) { printf("\n"); }
#else
			std::ios_base::fmtflags f;
			if (fixedl) { f = os.flags(); os << std::fixed; }
			std::streamsize cwidth = os.width();
			std::streamsize cprecision = os.precision();
			os.width(9); os.precision(4);
			os << "$$ \\left[ \\begin{array}{cc}\n";
			os << m[0][0] << " & " << m[0][1] << "\\\\\n";
			os << m[1][0] << " & " << m[1][1] << "\n";
			os << "\\end{array} \\right] $$\n";
			if (nl) { os << "\n"; }
			os.width(cwidth); os.precision(cprecision);
			if (fixedl) { os.flags(f); }
#endif
			}

	friend Mat2<T> operator+ (const Mat2<T> &L, const Mat2<T> &R)
		{
		Mat2<T> c;
		c.m[0][0]=L.m[0][0]+R.m[0][0]; c.m[1][0]=L.m[1][0]+R.m[1][0];
		c.m[0][1]=L.m[0][1]+R.m[0][1]; c.m[1][1]=L.m[1][1]+R.m[1][1];
		return(c);
		}

	friend Mat2<T> operator- (const Mat2<T> &R)
		{
		Mat2<T> c;
		c.x0=-R.x0; c.y0=-R.y0;
		c.x1=-R.x1; c.y1=-R.y1;
		return(c);
		}

	friend Mat2<T> operator- (const Mat2<T> &L, const Mat2<T> &R)
		{
		Mat2<T> c;
		c.m[0][0]=L.m[0][0]-R.m[0][0]; c.m[1][0]=L.m[1][0]-R.m[1][0];
		c.m[0][1]=L.m[0][1]-R.m[0][1]; c.m[1][1]=L.m[1][1]-R.m[1][1];
		return(c);
		}

	friend Vec2<T> operator* (const Mat2<T> &L, const Vec2<T> &R)
		{
		Vec2<T> c;
		c.x=R.x*L.x0+R.y*L.x1;
		c.y=R.x*L.y0+R.y*L.y1;
		return(c);
		}

	friend Vec2<T> operator* (const Vec2<T> &L, const Mat2<T> &R)
		{
		Vec2<T> c;
		c.x=L.x*R.x0+L.y*R.y0;
		c.y=L.x*R.x1+L.y*R.y1;
		return(c);
		}

	friend Mat2<T> operator* (const Mat2<T> &L, const T &R)
		{
		Mat2<T> c;
		c.m[0][0]=L.m[0][0]*R; c.m[1][0]=L.m[1][0]*R;
		c.m[0][1]=L.m[0][1]*R; c.m[1][1]=L.m[1][1]*R;
		return(c);
		}

	friend Mat2<T> operator* (const T &L, const Mat2<T> &R)
		{
		return(R*L);
		}

	friend Mat2<T> operator* (const Mat2<T> &L, const Mat2<T> &R)
		{
		Mat2<T> c;
		c.m[0][0]=R.m[0][0]*L.m[0][0]+R.m[1][0]*L.m[0][1];
		c.m[1][0]=R.m[0][0]*L.m[1][0]+R.m[1][0]*L.m[1][1];
		c.m[0][1]=R.m[0][1]*L.m[0][0]+R.m[1][1]*L.m[0][1];
		c.m[1][1]=R.m[0][1]*L.m[1][0]+R.m[1][1]*L.m[1][1];
		return(c);
		}

	friend Mat2<T> operator/ (const Mat2<T> &L, const T &R)
		{
		Mat2<T> c;
		c.m[0][0]=L.m[0][0]/R; c.m[1][0]=L.m[1][0]/R;
		c.m[0][1]=L.m[0][1]/R; c.m[1][1]=L.m[1][1]/R;
		return(c);
		}

	friend Mat2<T> operator/ (const Mat2<T> &L, const Mat2<T> &R)
		{
		return(L*R.inverse());
		}

	friend Mat2<T>& operator+= (Mat2<T> &L, const Mat2<T> &R)
		{
		L=L+R;
		return(L);
		}

	friend Mat2<T>& operator-= (Mat2<T> &L, const Mat2<T> &R)
		{
		L=L-R;
		return(L);
		}

	friend Mat2<T>& operator*= (Mat2<T> &L, const Mat2<T> &R)
		{
		L=L*R;
		return(L);
		}

	friend Mat2<T>& operator*= (Mat2<T> &L, const T &R)
		{
		L=L*R;
		return(L);
		}

	friend Mat2<T>& operator/= (Mat2<T> &L, const Mat2<T> &R)
		{
		L=L/R;
		return(L);
		}

	friend Mat2<T>& operator/= (Mat2<T> &L, const T &R)
		{
		L=L/R;
		return(L);
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

	friend bool operator== (const Mat2<T> &L, const Mat2<T> &R)
		{
		return((eq(L.M[0],R.M[0]))&&(eq(L.M[1],R.M[1]))
			&&(eq(L.M[2],R.M[2]))&&(eq(L.M[3],R.M[3])));
		}

	friend bool operator!= (const Mat2<T> &L, const Mat2<T> &R)
		{
		return((ne(L.M[0],R.M[0]))||(ne(L.M[1],R.M[1]))
			||(ne(L.M[2],R.M[2]))||(ne(L.M[3],R.M[3])));
		}

#undef eq
#undef ne

#else

	friend bool operator== (const Mat2<T> &L, const Mat2<T> &R)
		{
		return((L.M[0]==R.M[0])&&(L.M[1]==R.M[1])&&(L.M[2]==R.M[2])
			&&(L.M[3]==R.M[3]));
		}

	friend bool operator!= (const Mat2<T> &L, const Mat2<T> &R)
		{
		return((L.M[0]!=R.M[0])||(L.M[1]!=R.M[1])||(L.M[2]!=R.M[2])
			||(L.M[3]!=R.M[3]));
		}

#endif

#define FORM std::setprecision(4) << std::setw(9)

	friend std::ostream& operator<< (std::ostream &os, const Mat2<T> &R)
		{
		std::ios_base::fmtflags f = os.flags();
		os << std::fixed;
		os << std::endl;
		os << "| " << FORM << R.x0 << " " << FORM << R.x1 << " |" << std::endl;
		os << "| " << FORM << R.y0 << " " << FORM << R.y1 << " |" << std::endl;
		os.flags(f);
		return(os);
		}
	};

typedef Mat2<float> mat2;

#endif
