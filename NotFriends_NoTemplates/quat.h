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
#include "comp.h"

class quat;
vec3 cross(const vec3 &v, const quat &q);
quat operator/ (const quat &L, const float &R);
quat& operator*= (quat &L, const quat &R);
vec3 operator* (const quat &L, const vec3 &R);

class quat
	{
	public:
		union
			{
			struct { float w,x,y,z; };
			struct { float X,Y,Z,W; };
			struct { float V[4]; };
			};

		quat() { x=y=z=w=0; }

		/* Yes, I know this can be done with member initializer lists as in:
		quat(float cw, float cx, float cy, float cz) : x(cx),y(cy),z(cz),w(cw) { } */

		quat(float cw, float cx, float cy, float cz) { x=cx; y=cy; z=cz; w=cw; }

#if EULER2QUAT_METHOD==0
		quat(const vec3 &ea) // Euler angles
			{
			vec3 c,s;
			// vec3 order: yaw/heading, pitch/attitude, roll/bank
			// yaw=heading=Y pitch=attitude=Z roll=bank=X
			// YZX
			// euler rotation order: roll, pitch, yaw
			c.x=cos(ea.x*float(0.5)); // c.x=yaw
			c.y=cos(ea.y*float(0.5)); // c.y=pitch
			c.z=cos(ea.z*float(0.5)); // c.z=roll
			s.x=sin(ea.x*float(0.5)); // s.x=yaw
			s.y=sin(ea.y*float(0.5)); // s.y=pitch
			s.z=sin(ea.z*float(0.5)); // s.z=roll
			w=c.x*c.y*c.z-s.x*s.y*s.z;
			x=c.x*c.y*s.z+s.x*s.y*c.z;
			y=s.x*c.y*c.z+c.x*s.y*s.z;
			z=c.x*s.y*c.z-s.x*c.y*s.z;
			}
#elif EULER2QUAT_METHOD==2
		// Based on GLM, mostly matches Wikipedia
		quat(const vec3 &ea) // Euler angles
			{
			vec3 c,s;
			// vec3 order: yaw/heading, roll/bank, pitch/attitude
			// yaw=heading=Y pitch=attitude=Z roll=bank=X?
			// ZYX
			// euler rotation order: roll, yaw, pitch
			c.x=cos(ea.y*float(0.5));
			c.y=cos(ea.x*float(0.5));
			c.z=cos(ea.z*float(0.5));
			s.x=sin(ea.y*float(0.5));
			s.y=sin(ea.x*float(0.5));
			s.z=sin(ea.z*float(0.5));
			w=c.x*c.y*c.z+s.x*s.y*s.z;
			x=s.x*c.y*c.z-c.x*s.y*s.z;
			y=c.x*s.y*c.z+s.x*c.y*s.z;
			z=c.x*c.y*s.z-s.x*s.y*c.z;
			}
#else
		// Based on Wikipedia
		quat(const vec3 &ea) // Euler angles
			{
			vec3 c,s;
			// Note: Wikipedia uses Tait-Bryan angles which swap Y and Z
			//       (Z is up/down rather than Y)
			// vec3 order: roll/bank, yaw/heading, pitch/attitude
			//       or roll/bank, pitch/attitude, yaw/heading if T-B
			// yaw=heading=Z pitch=attitude=Y roll=bank=X
			// ZYX
			// euler rotation order: roll, yaw, pitch
			//       or roll, pitch, yaw if T-B
			c.x=cos(ea.x*float(0.5)); // c.x=roll
			c.y=cos(ea.y*float(0.5)); // c.y=pitch (T-B angles)
			c.z=cos(ea.z*float(0.5)); // c.z=yaw (T-B angles)
			s.x=sin(ea.x*float(0.5)); // s.x=roll
			s.y=sin(ea.y*float(0.5)); // s.y=pitch (T-B angles)
			s.z=sin(ea.z*float(0.5)); // s.z=yaw (T-B angles)
			w=c.x*c.y*c.z+s.x*s.y*s.z;
			x=s.x*c.y*c.z-c.x*s.y*s.z;
			y=c.x*s.y*c.z+s.x*c.y*s.z;
			z=c.x*c.y*s.z-s.x*s.y*c.z;
			}
#endif
	
		quat(const quat &s) { x=s.x; y=s.y; z=s.z; w=s.w; }

		quat(float v[4]) { w=v[0]; x=v[1]; y=v[2]; z=v[3]; }

		quat(comp &c) { w=c.r; x=c.i; y=z=0; }

		quat(const float &s, const vec3 &v) { w=s; x=v.x; y=v.y; z=v.z; }

		quat(const float &s) { w=s; x=y=z=0.0; }

		inline quat square() const
			{
			quat r;
			r.w=w*w-(x*x+y*y+z*z);
			r.x=2.0*w*x; r.y=2.0*w*y; r.z=2.0*w*z;
			return(r);
			}

		inline float dot() const
			{
			float r;
			r=x*x+y*y+z*z+w*w;
			return(r);
			}

		inline float dot(const quat &q) const
			{
			float r;
			r=x*q.x+y*q.y+z*q.z+w*q.w;
			return(r);
			}

		inline float length() const
			{
			float r;
			r=sqrt(x*x+y*y+z*z+w*w);
			return(r);
			}

		inline quat const normalized() const
			{
			float mag=sqrt(x*x+y*y+z*z+w*w);
			if (mag!=0.0)
				{
				quat r;
				r.x=x/mag; r.y=y/mag; r.z=z/mag; r.w=w/mag;
				return(r);
				}
			return(quat(0.0,0.0,0.0,0.0));
			}

		inline float normalize()
			{
			float mag=sqrt(x*x+y*y+z*z+w*w);
			if (mag!=0.0) { x/=mag; y/=mag; z/=mag; w/=mag; }
			else { x=y=z=w=0.0; }
			return(mag);
			}

		inline quat conjugate() const
			{
			return(quat(w,-x,-y,-z));
			}

		inline quat inverse() const
			{
			return(this->conjugate()/this->dot());
			}

		// Note: roll(),pitch(),yaw() rely on quaternion being normalized!!!!
#if EULER2QUAT_METHOD==0
		// yaw=heading=Z pitch=attitude=Y roll=bank=X
		// YZX
		inline float roll()
			{
			float X=1.0-2.0*(x*x+z*z);
			float Y=2.0*(w*x-y*z);
			if ((X==0.0)&&(Y==0.0)) { return(0.0); }
			return(float(atan2(Y,X)));
			}

		inline float pitch()
			{
			float v=2.0*(x*y+z*w);
			return(asin((v<-1.0)?-1.0:(v>1.0)?1.0:v));
			}

		inline float yaw()
			{
			float X=1.0-2.0*(y*y+z*z);
			float Y=2.0*(w*y-x*z);
			if ((X==0.0)&&(Y==0.0)) { return(float(2.0*atan2(x,w))); }
			return(float(atan2(Y,X)));
			}
#elif EULER2QUAT_METHOD==2
		// Based on GLM, but had to swap pitch and roll
#ifndef DONT_SWAP_PITCH_ROLL
		inline float roll()
#else
		inline float pitch()
#endif
			{
			float X=w*w-x*x-y*y+z*z;
			float Y=2.0*(y*z+w*x);
			if ((X==0.0)&&(Y==0.0)) { return(float(2.0*atan2(x,w))); }
			return(float(atan2(Y,X)));
			}

#ifndef DONT_SWAP_PITCH_ROLL
		inline float pitch()
#else
		inline float roll()
#endif
			{
			float X=w*w+x*x-y*y-z*z;
			float Y=2.0*(x*y+w*z);
			if ((X==0.0)&&(Y==0.0)) { return(0.0); }
			return(float(atan2(Y,X)));
			}

		inline float yaw()
			{
			float v=-2.0*(x*z-w*y);
			return(asin((v<-1.0)?-1.0:(v>1.0)?1.0:v));
			}
#else
		// Note: Wikipedia uses Tait-Bryan angles which swap Y and Z
		//       (Z is up/down rather than Y) so yaw and pitch are swapped
		//       - I swapped them back

		inline float roll()
			{
			float X=1.0-2.0*(x*x+y*y);
			float Y=2.0*(w*x+y*z);
			if ((X==0.0)&&(Y==0.0)) { return(0.0); }
			return(float(atan2(Y,X)));
			}

#ifndef DONT_SWAP_YAW_PITCH
		inline float pitch()
#else
		inline float yaw()
#endif
			{
			float X=1.0-2.0*(y*y+z*z);
			float Y=2.0*(w*z+x*y);
			//if ((X==0.0)&&(Y==0.0)) { return(float(2.0*atan2(y,x))); }
			return(float(atan2(Y,X)));
			}

#ifndef DONT_SWAP_YAW_PITCH
		inline float yaw()
#else
		inline float pitch()
#endif
			{
			float v=2.0*(w*y-z*x);
			return(asin((v<-1.0)?-1.0:(v>1.0)?1.0:v));
			}
#endif

		inline float operator[] (int i) const
			{
			assert((i>=0)&&(i<4));
			return(V[i]);
			}

		inline float& operator[] (int i)
			{
			assert((i>=0)&&(i<4));
			return(V[i]);
			}

	};

quat operator+ (const quat &L, const quat &R)
	{
	return(quat(L.w+R.w,L.x+R.x,L.y+R.y,L.z+R.z));
	}

quat operator- (const quat &R)
	{
	quat c; c.x=-R.x; c.y=-R.y; c.z=-R.z; c.w=-R.w; return(c);
	}

quat operator- (const quat &L, const quat &R)
	{
	quat c; c.x=L.x-R.x; c.y=L.y-R.y; c.z=L.z-R.z; c.w=L.w-R.w;
	return(c);
	}

quat operator* (const quat &L, const quat &R)
	{
	quat c;
	c.w=L.w*R.w-(L.x*R.x+L.y*R.y+L.z*R.z);
	c.x=L.w*R.x+R.w*L.x+L.y*R.z-L.z*R.y;
	c.y=L.w*R.y+R.w*L.y+L.z*R.x-L.x*R.z;
	c.z=L.w*R.z+R.w*L.z+L.x*R.y-L.y*R.x;
	return(c);
	}

quat operator* (const float &L, const quat &R)
	{
	quat c;
	c.x=R.x*L; c.y=R.y*L; c.z=R.z*L; c.w=R.w*L;
	return(c);
	}

quat operator* (const quat &L, const float &R)
	{
	return(R*L);
	}

vec3 operator* (const quat &L, const vec3 &R)
	{
	// Based on GLM
	vec3 qv(L.x,L.y,L.z);
	vec3 uv(qv.cross(R));
	vec3 uuv(qv.cross(uv));
	return(R+((uv*L.w)+uuv)*2.0);
	}

quat operator/ (const quat &L, const quat &R)
	{
	return(L*R.inverse());
	}

quat operator/ (const quat &L, const float &R)
	{
	quat c;
	c.x=L.x/R; c.y=L.y/R; c.z=L.z/R; c.w=L.w/R;
	return(c);
	}

quat& operator+= (quat &L, const quat &R)
	{
	L.x+=R.x; L.y+=R.y; L.z+=R.z; L.w+=R.w;
	return(L);
	}

quat& operator-= (quat &L, const quat &R)
	{
	L.x-=R.x; L.y-=R.y; L.z-=R.z; L.w-=R.w;
	return(L);
	}

quat& operator*= (quat &L, const quat &R)
	{
	L=L*R;
	return(L);
	}

quat& operator*= (quat &L, const float &R)
	{
	L.x*=R; L.y*=R; L.z*=R; L.w*=R;
	return(L);
	}

quat& operator/= (quat &L, const quat &R)
	{
	L=L*R.inverse();
	return(L);
	}

quat& operator/= (quat &L, const float &R)
	{
	L.x/=R; L.y/=R; L.z/=R; L.w/=R;
	return(L);
	}

#ifdef EPSILONCOMP

#define eq(a,b) (fabs(a-b)<EPSILONCOMP)
#define ne(a,b) (fabs(a-b)>=EPSILONCOMP)

bool operator== (const quat &L, const quat &R)
	{
	return((eq(L.x,R.x))&&(eq(L.y,R.y))&&(eq(L.z,R.z))&&(eq(L.w,R.w)));
	}

bool operator!= (const quat &L, const quat &R)
	{
	return((ne(L.x,R.x))||(ne(L.y,R.y))||(ne(L.z,R.z))||(ne(L.w,R.w)));
	}

#undef eq
#undef ne

#else

bool operator== (const quat &L, const quat &R)
	{
	return((L.x==R.x)&&(L.y==R.y)&&(L.z==R.z)&&(L.w==R.w));
	}

bool operator!= (const quat &L, const quat &R)
	{
	return((L.x!=R.x)||(L.y!=R.y)||(L.z!=R.z)||(L.w!=R.w));
	}

#endif

/*
	// Doesn't seem necessary
	quat& operator= (const quat &R)
		{
		this->x=R.x; // this-> also not necessary
		this->y=R.y;
		this->z=R.z;
		this->w=R.w;
		return(*this);
		}
*/

std::ostream& operator<< (std::ostream &os, const quat &R)
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

vec3 cross(const vec3 &v, const quat &q)
{
return(q.inverse()*v);
}

vec3 cross(const quat &q, const vec3 &v)
{
return(q*v);
}

quat cross(const quat &q1, const quat &q2)
{
quat r;
r.w=q1.w*q2.w-q1.x*q2.x-q1.y*q2.y-q1.z*q2.z;
r.x=q1.w*q2.x+q1.x*q2.w+q1.y*q2.z-q1.z*q2.y;
r.y=q1.w*q2.y+q1.y*q2.w+q1.z*q2.x-q1.x*q2.z;
r.z=q1.w*q2.z+q1.z*q2.w+q1.x*q2.y-q1.y*q2.x;
return(r);
}

// rotate a quaternion (not rotate an arbitrary point)
// if building up a rotation quat, q should start out being (1,0,0,0)
quat rotate(const quat &q, const float &a, const vec3 &v)
{
// Note: v must be normalized
float s=sin(a*0.5);
quat r;
r=q*quat(cos(a*0.5),v.x*s,v.y*s,v.z*s);
return(r);
}

// rotate a point (not rotate a quaternion)
vec3 rotatept(const vec3 &p, const float &a, const vec3 &v)
{
// Note: v must be normalized
float s=sin(a*0.5);
quat q,qn;
q=quat(cos(a*0.5),v.x*s,v.y*s,v.z*s);
quat P(0.0,p.x,p.y,p.z);
qn=q*P*q.conjugate();
vec3 r(qn.x,qn.y,qn.z);
return(r);
}

void Quat2AxisAngle(const quat &q, vec3 &axis, float &theta)
{
float mag=sqrt(q.x*q.x+q.y*q.y+q.z*q.z);
theta=2.0*atan2(mag,q.w);
axis=vec3(q.x,q.y,q.z)/mag;
}

quat lerp(const quat &q1, const quat &q2, const float &t)
{
return((1.0-t)*q1+t*q2);
}

quat mix(const quat &q1, const quat &q2, const float &t)
{
// mix is a slerp without the long to short path flip
float dotp=q1.dot(q2);
if (dotp>.99999) { return(lerp(q1,q2,t)); }
float a=acos(dotp);
return((sin((1.0-t)*a)*q1+sin(t*a)*q2)/sin(a));
}

quat slerp(const quat &q1, const quat &q2, const float &t)
{
// q1 and q2 should be normalized!
quat temp=q2;
float dotp=q1.dot(q2);
if (dotp<0.0) { temp=-temp; dotp=-dotp; }
if (dotp>.99999) { return(lerp(q1,q2,t)); }
float a=acos(dotp);
return((sin((1.0-t)*a)*q1+sin(t*a)*temp)/sin(a));
}

mat4 Quat2Mat4(const quat &q, int normalize=0)
{
quat q2;
if (normalize) { q2=q.normalized(); } else { q2=q; }
mat4 r;
float xx=q2.x*q2.x;
float yy=q2.y*q2.y;
float zz=q2.z*q2.z;
float xy=q2.x*q2.y;
float xw=q2.x*q2.w;
float xz=q2.x*q2.z;
float yz=q2.y*q2.z;
float yw=q2.y*q2.w;
float zw=q2.z*q2.w;
r.m[3][3]=1.0;
r.m[0][0]=1.0-2.0*(yy+zz);
r.m[1][1]=1.0-2.0*(xx+zz);
r.m[2][2]=1.0-2.0*(xx+yy);
r.m[1][0]=2.0*(xy-zw);
r.m[0][1]=2.0*(xy+zw);
r.m[2][0]=2.0*(xz+yw);
r.m[0][2]=2.0*(xz-yw);
r.m[2][1]=2.0*(yz-xw);
r.m[1][2]=2.0*(yz+xw);
return(r);
}

#endif
