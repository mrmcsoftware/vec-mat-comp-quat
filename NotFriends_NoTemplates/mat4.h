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

#ifdef VEC_USE_MAT
class vec4;
#endif
class mat4;
mat4 operator* (const mat4 &L, const float &R);

class mat4
	{
	public:
		union
			{
			struct { float m[4][4]; };
			struct { float M[16]; };
			struct { float x0,x1,x2,x3,y0,y1,y2,y3,z0,z1,z2,z3,w0,w1,w2,w3; };
			};

		mat4() { x0=y0=z0=w0=x1=y1=z1=w1=x2=y2=z2=w2=x3=y3=z3=w3=0; }

		mat4(float X0) { y0=z0=w0=x1=z1=w1=x2=y2=w2=x3=y3=z3=0; x0=y1=z2=w3=X0; }

		mat4(float X0, float Y0, float Z0, float W0, float X1, float Y1, float Z1, float W1, float X2, float Y2, float Z2, float W2, float X3, float Y3, float Z3, float W3)
			{ x0=X0; y0=Y0; z0=Z0; w0=W0; x1=X1; y1=Y1; z1=Z1; w1=W1; x2=X2; y2=Y2; z2=Z2; w2=W2; x3=X3; y3=Y3; z3=Z3; w3=W3; }

		mat4(vec4 v1, vec4 v2, vec4 v3, vec4 v4)
			{ x0=v1.x; y0=v1.y; z0=v1.z; w0=v1.w; x1=v2.x; y1=v2.y; z1=v2.z; w1=v2.w; x2=v3.x; y2=v3.y; z2=v3.z; w2=v3.w; x3=v4.x; y3=v4.y; z3=v4.z; w3=v4.w; }

		mat4(const mat4 &v)
			{ x0=v.x0; y0=v.y0; z0=v.z0; w0=v.w0; x1=v.x1; y1=v.y1; z1=v.z1; w1=v.w1; x2=v.x2; y2=v.y2; z2=v.z2; w2=v.w2; x3=v.x3; y3=v.y3; z3=v.z3; w3=v.w3; }

		inline mat4 const transpose() const
			{
			mat4 trans;
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

		inline float const determinant() const
			{
			float f0=m[2][2]*m[3][3]-m[2][3]*m[3][2];
			float f1=m[1][2]*m[3][3]-m[1][3]*m[3][2];
			float f2=m[1][2]*m[2][3]-m[1][3]*m[2][2];
			float f3=m[0][2]*m[3][3]-m[0][3]*m[3][2];
			float f4=m[0][2]*m[2][3]-m[0][3]*m[2][2];
			float f5=m[0][2]*m[1][3]-m[0][3]*m[1][2];
			vec4 dc=vec4((m[1][1]*f0-m[2][1]*f1+m[3][1]*f2),-(m[0][1]*f0-m[2][1]*f3+m[3][1]*f4),(m[0][1]*f1-m[1][1]*f3+m[3][1]*f5),
				-(m[0][1]*f2-m[1][1]*f4+m[2][1]*f5));
			return(m[0][0]*dc.x+m[1][0]*dc.y+m[2][0]*dc.z+m[3][0]*dc.w);
			}

		inline mat4 const inverse() const
			{
			float c00=m[2][2]*m[3][3]-m[2][3]*m[3][2];
			float c02=m[2][1]*m[3][3]-m[2][3]*m[3][1];
			float c03=m[2][1]*m[3][2]-m[2][2]*m[3][1];
			float c04=m[1][2]*m[3][3]-m[1][3]*m[3][2];
			float c06=m[1][1]*m[3][3]-m[1][3]*m[3][1];
			float c07=m[1][1]*m[3][2]-m[1][2]*m[3][1];
			float c08=m[1][2]*m[2][3]-m[1][3]*m[2][2];
			float c10=m[1][1]*m[2][3]-m[1][3]*m[2][1];
			float c11=m[1][1]*m[2][2]-m[1][2]*m[2][1];
			float c12=m[0][2]*m[3][3]-m[0][3]*m[3][2];
			float c14=m[0][1]*m[3][3]-m[0][3]*m[3][1];
			float c15=m[0][1]*m[3][2]-m[0][2]*m[3][1];
			float c16=m[0][2]*m[2][3]-m[0][3]*m[2][2];
			float c18=m[0][1]*m[2][3]-m[0][3]*m[2][1];
			float c19=m[0][1]*m[2][2]-m[0][2]*m[2][1];
			float c20=m[0][2]*m[1][3]-m[0][3]*m[1][2];
			float c22=m[0][1]*m[1][3]-m[0][3]*m[1][1];
			float c23=m[0][1]*m[1][2]-m[0][2]*m[1][1];
			vec4 f0(c00,c00,c02,c03);
			vec4 f1(c04,c04,c06,c07);
			vec4 f2(c08,c08,c10,c11);
			vec4 f3(c12,c12,c14,c15);
			vec4 f4(c16,c16,c18,c19);
			vec4 f5(c20,c20,c22,c23);
			vec4 v0(m[0][1],m[0][0],m[0][0],m[0][0]);
			vec4 v1(m[1][1],m[1][0],m[1][0],m[1][0]);
			vec4 v2(m[2][1],m[2][0],m[2][0],m[2][0]);
			vec4 v3(m[3][1],m[3][0],m[3][0],m[3][0]);
			vec4 i0(v1*f0-v2*f1+v3*f2);
			vec4 i1(v0*f0-v2*f3+v3*f4);
			vec4 i2(v0*f1-v1*f3+v3*f5);
			vec4 i3(v0*f2-v1*f4+v2*f5);
			vec4 sA(1,-1,1,-1);
			vec4 sB(-1,1,-1,1);
			mat4 inv(i0*sA,i1*sB,i2*sA,i3*sB);
			vec4 r0(inv.m[0][0],inv.m[0][1],inv.m[0][2],inv.m[0][3]);
			vec4 d0(m[0][0]*r0.x,m[1][0]*r0.y,m[2][0]*r0.z,m[3][0]*r0.w);
			float d1=(d0.x+d0.y)+(d0.z+d0.w);
			float invdet=1.0/d1;
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

		inline void const latex(int nl=1, bool fixedl=true, std::ostream &os=std::cout) const
			{
#if 0
			printf("$$ \\left[ \\begin{array}{cccc}\n");
			printf("%9.4f & %9.4f & %9.4f & %9.4f\\\\\n",m[0][0],m[0][1],m[0][2],m[0][3]);
			printf("%9.4f & %9.4f & %9.4f & %9.4f\\\\\n",m[1][0],m[1][1],m[1][2],m[1][3]);
			printf("%9.4f & %9.4f & %9.4f & %9.4f\\\\\n",m[2][0],m[2][1],m[2][2],m[2][3]);
			printf("%9.4f & %9.4f & %9.4f & %9.4f\n",m[3][0],m[3][1],m[3][2],m[3][3]);
			printf("\\end{array} \\right] $$\n");
			if (nl) { printf("\n"); }
#else
			std::ios_base::fmtflags f;
			if (fixedl) { f = os.flags(); os << std::fixed; }
			std::streamsize cwidth = os.width();
			std::streamsize cprecision = os.precision();
			os.width(9); os.precision(4);
			os << "$$ \\left[ \\begin{array}{cccc}\n";
			os << m[0][0] << " & " << m[0][1] << " & " << m[0][2] << " & " << m[0][3] << "\\\\\n";
			os << m[1][0] << " & " << m[1][1] << " & " << m[1][2] << " & " << m[1][3] << "\\\\\n";
			os << m[2][0] << " & " << m[2][1] << " & " << m[2][2] << " & " << m[2][3] << "\\\\\n";
			os << m[3][0] << " & " << m[3][1] << " & " << m[3][2] << " & " << m[3][3] << "\n";
			os << "\\end{array} \\right] $$\n";
			if (nl) { os << "\n"; }
			os.width(cwidth); os.precision(cprecision);
			if (fixedl) { os.flags(f); }
#endif
			}
	};

mat4 operator+ (const mat4 &L, const mat4 &R)
	{
	mat4 c;
	c.m[0][0]=L.m[0][0]+R.m[0][0]; c.m[1][0]=L.m[1][0]+R.m[1][0]; c.m[2][0]=L.m[2][0]+R.m[2][0]; c.m[3][0]=L.m[3][0]+R.m[3][0];
	c.m[0][1]=L.m[0][1]+R.m[0][1]; c.m[1][1]=L.m[1][1]+R.m[1][1]; c.m[2][1]=L.m[2][1]+R.m[2][1]; c.m[3][1]=L.m[3][1]+R.m[3][1];
	c.m[0][2]=L.m[0][2]+R.m[0][2]; c.m[1][2]=L.m[1][2]+R.m[1][2]; c.m[2][2]=L.m[2][2]+R.m[2][2]; c.m[3][2]=L.m[3][2]+R.m[3][2];
	c.m[0][3]=L.m[0][3]+R.m[0][3]; c.m[1][3]=L.m[1][3]+R.m[1][3]; c.m[2][3]=L.m[2][3]+R.m[2][3]; c.m[3][3]=L.m[3][3]+R.m[3][3];
	return(c);
	}

mat4 operator- (const mat4 &R)
	{
	mat4 c;
	c.x0=-R.x0; c.y0=-R.y0; c.z0=-R.z0; c.w0=-R.w0;
	c.x1=-R.x1; c.y1=-R.y1; c.z1=-R.z1; c.w1=-R.w1;
	c.x2=-R.x2; c.y2=-R.y2; c.z2=-R.z2; c.w2=-R.w2;
	c.x3=-R.x3; c.y3=-R.y3; c.z3=-R.z3; c.w3=-R.w3;
	return(c);
	}

mat4 operator- (const mat4 &L, const mat4 &R)
	{
	mat4 c;
	c.m[0][0]=L.m[0][0]-R.m[0][0]; c.m[1][0]=L.m[1][0]-R.m[1][0]; c.m[2][0]=L.m[2][0]-R.m[2][0]; c.m[3][0]=L.m[3][0]-R.m[3][0];
	c.m[0][1]=L.m[0][1]-R.m[0][1]; c.m[1][1]=L.m[1][1]-R.m[1][1]; c.m[2][1]=L.m[2][1]-R.m[2][1]; c.m[3][1]=L.m[3][1]-R.m[3][1];
	c.m[0][2]=L.m[0][2]-R.m[0][2]; c.m[1][2]=L.m[1][2]-R.m[1][2]; c.m[2][2]=L.m[2][2]-R.m[2][2]; c.m[3][2]=L.m[3][2]-R.m[3][2];
	c.m[0][3]=L.m[0][3]-R.m[0][3]; c.m[1][3]=L.m[1][3]-R.m[1][3]; c.m[2][3]=L.m[2][3]-R.m[2][3]; c.m[3][3]=L.m[3][3]-R.m[3][3];
	return(c);
	}

vec4 operator* (const mat4 &L, const vec4 &R)
	{
	vec4 c;
	c.x=R.x*L.x0+R.y*L.x1+R.z*L.x2+R.w*L.x3;
	c.y=R.x*L.y0+R.y*L.y1+R.z*L.y2+R.w*L.y3;
	c.z=R.x*L.z0+R.y*L.z1+R.z*L.z2+R.w*L.z3;
	c.w=R.x*L.w0+R.y*L.w1+R.z*L.w2+R.w*L.w3;
	return(c);
	}

vec4 operator* (const vec4 &L, const mat4 &R)
	{
	vec4 c;
	c.x=L.x*R.x0+L.y*R.y0+L.z*R.z0+L.w*R.w0;
	c.y=L.x*R.x1+L.y*R.y1+L.z*R.z1+L.w*R.w1;
	c.z=L.x*R.x2+L.y*R.y2+L.z*R.z2+L.w*R.w2;
	c.w=L.x*R.x3+L.y*R.y3+L.z*R.z3+L.w*R.w3;
	return(c);
	}

mat4 operator* (const mat4 &L, const float &R)
	{
	mat4 c;
	c.m[0][0]=L.m[0][0]*R; c.m[1][0]=L.m[1][0]*R; c.m[2][0]=L.m[2][0]*R; c.m[3][0]=L.m[3][0]*R;
	c.m[0][1]=L.m[0][1]*R; c.m[1][1]=L.m[1][1]*R; c.m[2][1]=L.m[2][1]*R; c.m[3][1]=L.m[3][1]*R;
	c.m[0][2]=L.m[0][2]*R; c.m[1][2]=L.m[1][2]*R; c.m[2][2]=L.m[2][2]*R; c.m[3][2]=L.m[3][2]*R;
	c.m[0][3]=L.m[0][3]*R; c.m[1][3]=L.m[1][3]*R; c.m[2][3]=L.m[2][3]*R; c.m[3][3]=L.m[3][3]*R;
	return(c);
	}

mat4 operator* (const float &L, const mat4 &R)
	{
	return(R*L);
	}

mat4 operator* (const mat4 &L, const mat4 &R)
	{
	mat4 c;
	int i,j;
	for (j=0;j<4;j++)
		{
		for (i=0;i<4;i++)
			{
			c.m[i][j]=R.m[0][j]*L.m[i][0]+R.m[1][j]*L.m[i][1]+R.m[2][j]*L.m[i][2]+R.m[3][j]*L.m[i][3];
			}
		}
	return(c);
	}

mat4 operator/ (const mat4 &L, const float &R)
	{
	mat4 c;
	c.m[0][0]=L.m[0][0]/R; c.m[1][0]=L.m[1][0]/R; c.m[2][0]=L.m[2][0]/R; c.m[3][0]=L.m[3][0]/R;
	c.m[0][1]=L.m[0][1]/R; c.m[1][1]=L.m[1][1]/R; c.m[2][1]=L.m[2][1]/R; c.m[3][1]=L.m[3][1]/R;
	c.m[0][2]=L.m[0][2]/R; c.m[1][2]=L.m[1][2]/R; c.m[2][2]=L.m[2][2]/R; c.m[3][2]=L.m[3][2]/R;
	c.m[0][3]=L.m[0][3]/R; c.m[1][3]=L.m[1][3]/R; c.m[2][3]=L.m[2][3]/R; c.m[3][3]=L.m[3][3]/R;
	return(c);
	}

mat4 operator/ (const mat4 &L, const mat4 &R)
	{
	return(L*R.inverse());
	}

mat4& operator+= (mat4 &L, const mat4 &R)
	{
	L=L+R;
	return(L);
	}

mat4& operator-= (mat4 &L, const mat4 &R)
	{
	L=L-R;
	return(L);
	}

mat4& operator*= (mat4 &L, const mat4 &R)
	{
	L=L*R;
	return(L);
	}

mat4& operator*= (mat4 &L, const float &R)
	{
	L=L*R;
	return(L);
	}

mat4& operator/= (mat4 &L, const mat4 &R)
	{
	L=L/R;
	return(L);
	}

mat4& operator/= (mat4 &L, const float &R)
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

bool operator== (const mat4 &L, const mat4 &R)
	{
	return((eq(L.M[0],R.M[0]))&&(eq(L.M[1],R.M[1]))
		&&(eq(L.M[2],R.M[2]))&&(eq(L.M[3],R.M[3]))
		&&(eq(L.M[4],R.M[4]))&&(eq(L.M[5],R.M[5]))
		&&(eq(L.M[6],R.M[6]))&&(eq(L.M[7],R.M[7]))
		&&(eq(L.M[8],R.M[8]))&&(eq(L.M[9],R.M[9]))
		&&(eq(L.M[10],R.M[10]))&&(eq(L.M[11],R.M[11]))
		&&(eq(L.M[12],R.M[12]))&&(eq(L.M[13],R.M[13]))
		&&(eq(L.M[14],R.M[14]))&&(eq(L.M[15],R.M[15])));
	}

bool operator!= (const mat4 &L, const mat4 &R)
	{
	return((ne(L.M[0],R.M[0]))||(ne(L.M[1],R.M[1]))
		||(ne(L.M[2],R.M[2]))||(ne(L.M[3],R.M[3]))
		||(ne(L.M[4],R.M[4]))||(ne(L.M[5],R.M[5]))
		||(ne(L.M[6],R.M[6]))||(ne(L.M[7],R.M[7]))
		||(ne(L.M[8],R.M[8]))||(ne(L.M[9],R.M[9]))
		||(ne(L.M[10],R.M[10]))||(ne(L.M[11],R.M[11]))
		||(ne(L.M[12],R.M[12]))||(ne(L.M[13],R.M[13]))
		||(ne(L.M[14],R.M[14]))||(ne(L.M[15],R.M[15])));
	}

#undef eq
#undef ne

#else

bool operator== (const mat4 &L, const mat4 &R)
	{
	return((L.M[0]==R.M[0])&&(L.M[1]==R.M[1])&&(L.M[2]==R.M[2])
		&&(L.M[3]==R.M[3])&&(L.M[4]==R.M[4])&&(L.M[5]==R.M[5])
		&&(L.M[6]==R.M[6])&&(L.M[7]==R.M[7])&&(L.M[8]==R.M[8])
		&&(L.M[9]==R.M[9])&&(L.M[10]==R.M[10])&&(L.M[11]==R.M[11])
		&&(L.M[12]==R.M[12])&&(L.M[13]==R.M[13])&&(L.M[14]==R.M[14])
		&&(L.M[15]==R.M[15]));
	}

bool operator!= (const mat4 &L, const mat4 &R)
	{
	return((L.M[0]!=R.M[0])||(L.M[1]!=R.M[1])||(L.M[2]!=R.M[2])
		||(L.M[3]!=R.M[3])||(L.M[4]!=R.M[4])||(L.M[5]!=R.M[5])
		||(L.M[6]!=R.M[6])||(L.M[7]!=R.M[7])||(L.M[8]!=R.M[8])
		||(L.M[9]!=R.M[9])||(L.M[10]!=R.M[10])||(L.M[11]!=R.M[11])
		||(L.M[12]!=R.M[12])||(L.M[13]!=R.M[13])||(L.M[14]!=R.M[14])
		||(L.M[15]!=R.M[15]));
	}

#endif

#define FORM std::setprecision(4) << std::setw(9)

std::ostream& operator<< (std::ostream &os, const mat4 &R)
	{
	std::ios_base::fmtflags f = os.flags();
	os << std::fixed;
	os << "" << std::endl;
	os << "| " << FORM << R.x0 << " " << FORM << R.x1 << " " << FORM << R.x2 << " " << FORM << R.x3 << " |" << std::endl;
	os << "| " << FORM << R.y0 << " " << FORM << R.y1 << " " << FORM << R.y2 << " " << FORM << R.y3 << " |" << std::endl;
	os << "| " << FORM << R.z0 << " " << FORM << R.z1 << " " << FORM << R.z2 << " " << FORM << R.z3 << " |" << std::endl;
	os << "| " << FORM << R.w0 << " " << FORM << R.w1 << " " << FORM << R.w2 << " " << FORM << R.w3 << " |" << std::endl;
	os.flags(f);
	return(os);
	}

#endif
