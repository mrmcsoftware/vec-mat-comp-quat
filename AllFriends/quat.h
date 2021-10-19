/*********************************************************
   Quaternion number class
   Copyright © 2021 Mark Craig

   https://www.youtube.com/MrMcSoftware
**********************************************************/

#ifndef _QUAT_H
#define _QUAT_H

#ifndef Q_DISPLAY_FORMAT
#define Q_DISPLAY_FORMAT 0 // 0: 1,2i,3j,4k  1: 1+2i+3j+4k  2: 1,2,3,4
#endif
#ifndef EULER2QUAT_METHOD
#define EULER2QUAT_METHOD 0
#endif

#include <cmath>
#include <iostream>
#include <cassert>
#include "vec3.h"
#include "mat4.h"
#include "comp.h"

template <class T>
class Quat
	{
	public:
		union
			{
			struct { T w,x,y,z; };
			struct { T X,Y,Z,W; };
			struct { T V[4]; };
			};

		Quat<T>() { x=y=z=w=0; }

		/* Yes, I know this can be done with member initializer lists as in:
		Quat<T>(T cw, T cx, T cy, T cz) : x(cx),y(cy),z(cz),w(cw) { } */

		Quat<T>(T cw, T cx, T cy, T cz) { x=cx; y=cy; z=cz; w=cw; }

#if EULER2QUAT_METHOD==0
		Quat<T>(const Vec3<T> &ea) // Euler angles
			{
			Vec3<T> c,s;
			// vec3 order: yaw/heading, pitch/attitude, roll/bank
			// yaw=heading=Y pitch=attitude=Z roll=bank=X
			// YZX
			// euler rotation order: roll, pitch, yaw
			c.x=cos(ea.x*T(0.5)); // c.x=yaw
			c.y=cos(ea.y*T(0.5)); // c.y=pitch
			c.z=cos(ea.z*T(0.5)); // c.z=roll
			s.x=sin(ea.x*T(0.5)); // s.x=yaw
			s.y=sin(ea.y*T(0.5)); // s.y=pitch
			s.z=sin(ea.z*T(0.5)); // s.z=roll
			w=c.x*c.y*c.z-s.x*s.y*s.z;
			x=c.x*c.y*s.z+s.x*s.y*c.z;
			y=s.x*c.y*c.z+c.x*s.y*s.z;
			z=c.x*s.y*c.z-s.x*c.y*s.z;
			}
#elif EULER2QUAT_METHOD==2
		// Based on GLM, mostly matches Wikipedia
		Quat<T>(const Vec3<T> &ea) // Euler angles
			{
			Vec3<T> c,s;
			// vec3 order: yaw/heading, roll/bank, pitch/attitude
			// yaw=heading=Y pitch=attitude=Z roll=bank=X?
			// ZYX
			// euler rotation order: roll, yaw, pitch
			c.x=cos(ea.y*T(0.5));
			c.y=cos(ea.x*T(0.5));
			c.z=cos(ea.z*T(0.5));
			s.x=sin(ea.y*T(0.5));
			s.y=sin(ea.x*T(0.5));
			s.z=sin(ea.z*T(0.5));
			w=c.x*c.y*c.z+s.x*s.y*s.z;
			x=s.x*c.y*c.z-c.x*s.y*s.z;
			y=c.x*s.y*c.z+s.x*c.y*s.z;
			z=c.x*c.y*s.z-s.x*s.y*c.z;
			}
#else
		// Based on Wikipedia
		Quat<T>(const Vec3<T> &ea) // Euler angles
			{
			Vec3<T> c,s;
			// Note: Wikipedia uses Tait-Bryan angles which swap Y and Z
			//       (Z is up/down rather than Y)
			// vec3 order: roll/bank, yaw/heading, pitch/attitude
			//       or roll/bank, pitch/attitude, yaw/heading if T-B
			// yaw=heading=Z pitch=attitude=Y roll=bank=X
			// ZYX
			// euler rotation order: roll, yaw, pitch
			//       or roll, pitch, yaw if T-B
			c.x=cos(ea.x*T(0.5)); // c.x=roll
			c.y=cos(ea.y*T(0.5)); // c.y=pitch (T-B angles)
			c.z=cos(ea.z*T(0.5)); // c.z=yaw (T-B angles)
			s.x=sin(ea.x*T(0.5)); // s.x=roll
			s.y=sin(ea.y*T(0.5)); // s.y=pitch (T-B angles)
			s.z=sin(ea.z*T(0.5)); // s.z=yaw (T-B angles)
			w=c.x*c.y*c.z+s.x*s.y*s.z;
			x=s.x*c.y*c.z-c.x*s.y*s.z;
			y=c.x*s.y*c.z+s.x*c.y*s.z;
			z=c.x*c.y*s.z-s.x*s.y*c.z;
			}
#endif
	
		Quat<T>(const Quat<T> &s) { x=s.x; y=s.y; z=s.z; w=s.w; }

		Quat<T>(T v[4]) { w=v[0]; x=v[1]; y=v[2]; z=v[3]; }

		Quat<T>(Comp<T> &c) { w=c.r; x=c.i; y=z=0; }

		Quat<T>(const T &s, const Vec3<T> &v) { w=s; x=v.x; y=v.y; z=v.z; }

		Quat<T>(const T &s) { w=s; x=y=z=0.0; }

		inline Quat<T> square() const
			{
			Quat<T> r;
			r.w=w*w-(x*x+y*y+z*z);
			r.x=2.0*w*x; r.y=2.0*w*y; r.z=2.0*w*z;
			return(r);
			}

		inline T dot() const
			{
			T r;
			r=x*x+y*y+z*z+w*w;
			return(r);
			}

		inline T dot(const Quat<T> &q) const
			{
			T r;
			r=x*q.x+y*q.y+z*q.z+w*q.w;
			return(r);
			}

		inline T length() const
			{
			T r;
			r=sqrt(x*x+y*y+z*z+w*w);
			return(r);
			}

		inline Quat<T> const normalized() const
			{
			T mag=sqrt(x*x+y*y+z*z+w*w);
			if (mag!=0.0)
				{
				Quat<T> r;
				r.x=x/mag; r.y=y/mag; r.z=z/mag; r.w=w/mag;
				return(r);
				}
			return(Quat(0.0,0.0,0.0,0.0));
			}

		inline T normalize()
			{
			T mag=sqrt(x*x+y*y+z*z+w*w);
			if (mag!=0.0) { x/=mag; y/=mag; z/=mag; w/=mag; }
			else { x=y=z=w=0.0; }
			return(mag);
			}

		inline Quat<T> conjugate() const
			{
			return(Quat<T>(w,-x,-y,-z));
			}

		inline Quat<T> inverse() const
			{
			return(this->conjugate()/this->dot());
			}

		// Note: roll(),pitch(),yaw() rely on quaternion being normalized!!!!
#if EULER2QUAT_METHOD==0
		// yaw=heading=Z pitch=attitude=Y roll=bank=X
		// YZX
		inline T roll()
			{
			T X=static_cast<T>(1)-static_cast<T>(2)*(x*x+z*z);
			T Y=static_cast<T>(2)*(w*x-y*z);
			if ((X==0.0)&&(Y==0.0)) { return(static_cast<T>(0)); }
			return(static_cast<T>(atan2(Y,X)));
			}

		inline T pitch()
			{
			T v=static_cast<T>(2)*(x*y+z*w);
			return(asin((v<-1.0)?static_cast<T>(-1):(v>1.0)?static_cast<T>(1):v));
			}

		inline T yaw()
			{
			T X=static_cast<T>(1)-static_cast<T>(2)*(y*y+z*z);
			T Y=static_cast<T>(2)*(w*y-x*z);
			if ((X==0.0)&&(Y==0.0)) { return(static_cast<T>(static_cast<T>(2)*atan2(x,w))); }
			return(static_cast<T>(atan2(Y,X)));
			}
#elif EULER2QUAT_METHOD==2
		// Based on GLM, but had to swap pitch and roll
#ifndef DONT_SWAP_PITCH_ROLL
		inline T roll()
#else
		inline T pitch()
#endif
			{
			T X=w*w-x*x-y*y+z*z;
			T Y=static_cast<T>(2)*(y*z+w*x);
			if ((X==0.0)&&(Y==0.0)) { return(static_cast<T>(static_cast<T>(2)*atan2(x,w))); }
			return(static_cast<T>(atan2(Y,X)));
			}

#ifndef DONT_SWAP_PITCH_ROLL
		inline T pitch()
#else
		inline T roll()
#endif
			{
			T X=w*w+x*x-y*y-z*z;
			T Y=static_cast<T>(2)*(x*y+w*z);
			if ((X==0.0)&&(Y==0.0)) { return(static_cast<T>(0)); }
			return(static_cast<T>(atan2(Y,X)));
			}

		inline T yaw()
			{
			T v=static_cast<T>(-2)*(x*z-w*y);
			return(asin((v<-1.0)?static_cast<T>(-1):(v>1.0)?static_cast<T>(1):v));
			}
#else
		// Note: Wikipedia uses Tait-Bryan angles which swap Y and Z
		//       (Z is up/down rather than Y) so yaw and pitch are swapped
		//       - I swapped them back

		inline T roll()
			{
			T X=static_cast<T>(1)-static_cast<T>(2)*(x*x+y*y);
			T Y=static_cast<T>(2)*(w*x+y*z);
			if ((X==0.0)&&(Y==0.0)) { return(static_cast<T>(0)); }
			return(static_cast<T>(atan2(Y,X)));
			}

#ifndef DONT_SWAP_YAW_PITCH
		inline T pitch()
#else
		inline T yaw()
#endif
			{
			T X=static_cast<T>(1)-static_cast<T>(2)*(y*y+z*z);
			T Y=static_cast<T>(2)*(w*z+x*y);
			//if ((X==0.0)&&(Y==0.0)) { return(static_cast<T>(static_cast<T>(2)*atan2(y,x))); }
			return(static_cast<T>(atan2(Y,X)));
			}

#ifndef DONT_SWAP_YAW_PITCH
		inline T yaw()
#else
		inline T pitch()
#endif
			{
			T v=static_cast<T>(2)*(w*y-z*x);
			return(asin((v<-1.0)?static_cast<T>(-1):(v>1.0)?static_cast<T>(1):v));
			}
#endif

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

	friend Quat<T> operator+ (const Quat<T> &L, const Quat<T> &R)
		{
		return(Quat<T>(L.w+R.w,L.x+R.x,L.y+R.y,L.z+R.z));
		}

	friend Quat<T> operator- (const Quat<T> &R)
		{
		Quat<T> c; c.x=-R.x; c.y=-R.y; c.z=-R.z; c.w=-R.w; return(c);
		}

	friend Quat<T> operator- (const Quat<T> &L, const Quat<T> &R)
		{
		Quat<T> c; c.x=L.x-R.x; c.y=L.y-R.y; c.z=L.z-R.z; c.w=L.w-R.w;
		return(c);
		}

	friend Quat<T> operator* (const Quat<T> &L, const Quat<T> &R)
		{
		Quat<T> c;
		c.w=L.w*R.w-(L.x*R.x+L.y*R.y+L.z*R.z);
		c.x=L.w*R.x+R.w*L.x+L.y*R.z-L.z*R.y;
		c.y=L.w*R.y+R.w*L.y+L.z*R.x-L.x*R.z;
		c.z=L.w*R.z+R.w*L.z+L.x*R.y-L.y*R.x;
		return(c);
		}

	friend Quat<T> operator* (const T &L, const Quat<T> &R)
		{
		Quat<T> c;
		c.x=R.x*L; c.y=R.y*L; c.z=R.z*L; c.w=R.w*L;
		return(c);
		}

	friend Quat<T> operator* (const Quat<T> &L, const T &R)
		{
		return(R*L);
		}

	friend Vec3<T> operator* (const Quat<T> &L, const Vec3<T> &R)
		{
		// Based on GLM
		Vec3<T> qv(L.x,L.y,L.z);
		Vec3<T> uv(qv.cross(R));
		Vec3<T> uuv(qv.cross(uv));
		return(R+((uv*L.w)+uuv)*static_cast<T>(2));
		}

	friend Quat<T> operator/ (const Quat<T> &L, const Quat<T> &R)
		{
		return(L*R.inverse());
		}

	friend Quat<T> operator/ (const Quat<T> &L, const T &R)
		{
		Quat<T> c;
		c.x=L.x/R; c.y=L.y/R; c.z=L.z/R; c.w=L.w/R;
		return(c);
		}

	friend Quat<T>& operator+= (Quat<T> &L, const Quat<T> &R)
		{
		L.x+=R.x; L.y+=R.y; L.z+=R.z; L.w+=R.w;
		return(L);
		}

	friend Quat<T>& operator-= (Quat<T> &L, const Quat<T> &R)
		{
		L.x-=R.x; L.y-=R.y; L.z-=R.z; L.w-=R.w;
		return(L);
		}

	friend Quat<T>& operator*= (Quat<T> &L, const Quat<T> &R)
		{
		L=L*R;
		return(L);
		}

	friend Quat<T>& operator*= (Quat<T> &L, const T &R)
		{
		L.x*=R; L.y*=R; L.z*=R; L.w*=R;
		return(L);
		}

	friend Quat<T>& operator/= (Quat<T> &L, const Quat<T> &R)
		{
		L=L*R.inverse();
		return(L);
		}

	friend Quat<T>& operator/= (Quat<T> &L, const T &R)
		{
		L.x/=R; L.y/=R; L.z/=R; L.w/=R;
		return(L);
		}

#ifdef EPSILONCOMP

#define eq(a,b) (fabs(a-b)<EPSILONCOMP)
#define ne(a,b) (fabs(a-b)>=EPSILONCOMP)

	friend bool operator== (const Quat<T> &L, const Quat<T> &R)
		{
		return((eq(L.x,R.x))&&(eq(L.y,R.y))&&(eq(L.z,R.z))&&(eq(L.w,R.w)));
		}

	friend bool operator!= (const Quat<T> &L, const Quat<T> &R)
		{
		return((ne(L.x,R.x))||(ne(L.y,R.y))||(ne(L.z,R.z))||(ne(L.w,R.w)));
		}

#undef eq
#undef ne

#else

	friend bool operator== (const Quat<T> &L, const Quat<T> &R)
		{
		return((L.x==R.x)&&(L.y==R.y)&&(L.z==R.z)&&(L.w==R.w));
		}

	friend bool operator!= (const Quat<T> &L, const Quat<T> &R)
		{
		return((L.x!=R.x)||(L.y!=R.y)||(L.z!=R.z)||(L.w!=R.w));
		}

#endif

/*
	// Doesn't seem necessary
	Quat<T>& operator= (const Quat<T> &R)
		{
		this->x=static_cast<T>(R.x); // this-> also not necessary
		this->y=static_cast<T>(R.y);
		this->z=static_cast<T>(R.z);
		this->w=static_cast<T>(R.w);
		return(*this);
		}
*/

	friend std::ostream& operator<< (std::ostream &os, const Quat<T> &R)
		{
#if Q_DISPLAY_FORMAT==1
		os << "(" << R.w << "+" << R.x << "i+" << R.y << "j+" << R.z << "k)";
#elif Q_DISPLAY_FORMAT==2
		os << "(" << R.w << "," << R.x << "," << R.y << "," << R.z << ")";
#else
		os << "(" << R.w << "," << R.x << "i," << R.y << "j," << R.z << "k)";
#endif
		return(os);
		}
	};

template <class T>
Vec3<T> cross(const Vec3<T> &v, const Quat<T> &q)
{
return(q.inverse()*v);
}

template <class T>
Vec3<T> cross(const Quat<T> &q, const Vec3<T> &v)
{
return(q*v);
}

template <class T>
Quat<T> cross(const Quat<T> &q1, const Quat<T> &q2)
{
Quat<T> r;
r.w=q1.w*q2.w-q1.x*q2.x-q1.y*q2.y-q1.z*q2.z;
r.x=q1.w*q2.x+q1.x*q2.w+q1.y*q2.z-q1.z*q2.y;
r.y=q1.w*q2.y+q1.y*q2.w+q1.z*q2.x-q1.x*q2.z;
r.z=q1.w*q2.z+q1.z*q2.w+q1.x*q2.y-q1.y*q2.x;
return(r);
}

// rotate a quaternion (not rotate an arbitrary point)
// if building up a rotation quat, q should start out being (1,0,0,0)
template <class T, class U>
Quat<T> rotate(const Quat<T> &q, const U &a, const Vec3<T> &v)
{
// Note: v must be normalized
T s=sin(a*static_cast<T>(0.5));
Quat<T> r;
r=q*Quat<T>(cos(a*static_cast<T>(0.5)),v.x*s,v.y*s,v.z*s);
return(r);
}

// rotate a point (not rotate a quaternion)
template <class T, class U>
Vec3<T> rotatept(const Vec3<T> &p, const U &a, const Vec3<T> &v)
{
// Note: v must be normalized
T s=sin(a*static_cast<T>(0.5));
Quat<T> q,qn;
q=Quat<T>(cos(a*static_cast<T>(0.5)),v.x*s,v.y*s,v.z*s);
Quat<T> P(0.0,p.x,p.y,p.z);
qn=q*P*q.conjugate();
Vec3<T> r(qn.x,qn.y,qn.z);
return(r);
}

template <class T, class U>
void Quat2AxisAngle(const Quat<T> &q, Vec3<T> &axis, U &theta)
{
T mag=sqrt(q.x*q.x+q.y*q.y+q.z*q.z);
theta=static_cast<U>(2)*atan2(mag,q.w);
axis=Vec3<T>(q.x,q.y,q.z)/mag;
}

template <class T, class U>
Quat<T> lerp(const Quat<T> &q1, const Quat<T> &q2, const U &t)
{
return((static_cast<T>(1)-t)*q1+t*q2);
}

template <class T, class U>
Quat<T> mix(const Quat<T> &q1, const Quat<T> &q2, const U &t)
{
// mix is a slerp without the long to short path flip
T dotp=q1.dot(q2);
if (dotp>.99999) { return(lerp(q1,q2,t)); }
T a=acos(dotp);
return((sin((static_cast<T>(1)-t)*a)*q1+sin(t*a)*q2)/sin(a));
}

template <class T, class U>
Quat<T> slerp(const Quat<T> &q1, const Quat<T> &q2, const U &t)
{
// q1 and q2 should be normalized!
Quat<T> temp=q2;
T dotp=q1.dot(q2);
if (dotp<0.0) { temp=-temp; dotp=-dotp; }
if (dotp>.99999) { return(lerp(q1,q2,t)); }
T a=acos(dotp);
return((sin((static_cast<T>(1)-t)*a)*q1+sin(t*a)*temp)/sin(a));
}

template <class T>
Mat4<T> Quat2Mat4(const Quat<T> &q, int normalize=0)
{
Quat<T> q2;
if (normalize) { q2=q.normalized(); } else { q2=q; }
Mat4<T> r;
T xx=q2.x*q2.x;
T yy=q2.y*q2.y;
T zz=q2.z*q2.z;
T xy=q2.x*q2.y;
T xw=q2.x*q2.w;
T xz=q2.x*q2.z;
T yz=q2.y*q2.z;
T yw=q2.y*q2.w;
T zw=q2.z*q2.w;
r.m[3][3]=static_cast<T>(1);
r.m[0][0]=static_cast<T>(1)-static_cast<T>(2)*(yy+zz);
r.m[1][1]=static_cast<T>(1)-static_cast<T>(2)*(xx+zz);
r.m[2][2]=static_cast<T>(1)-static_cast<T>(2)*(xx+yy);
r.m[1][0]=static_cast<T>(2)*(xy-zw);
r.m[0][1]=static_cast<T>(2)*(xy+zw);
r.m[2][0]=static_cast<T>(2)*(xz+yw);
r.m[0][2]=static_cast<T>(2)*(xz-yw);
r.m[2][1]=static_cast<T>(2)*(yz-xw);
r.m[1][2]=static_cast<T>(2)*(yz+xw);
return(r);
}

typedef Quat<float> quat;

#endif
