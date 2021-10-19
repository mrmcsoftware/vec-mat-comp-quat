/*********************************************************
   Complex number class
   Copyright © 2021 Mark Craig

   https://www.youtube.com/MrMcSoftware
**********************************************************/

#ifndef _COMP_H
#define _COMP_H

#ifndef C_DISPLAY_FORMAT
#define C_DISPLAY_FORMAT 0 // 0: 1+j2  1: 1,2i  2: 1+2i  3: 1,2
#endif

#include <cmath>
#include <iostream>
#include <cassert>

template <class T>
class Comp;

template <class T>
inline Comp<T> MagPhase2Complex(const T &mag, const T &phase);

template <class T>
class Comp
	{
	public:
		union
			{
			struct { T r,i; };
			struct { T real,imaginary; };
			struct { T re,im; };
			struct { T V[2]; };
			};

		Comp<T>() { r=i=0; }

		/* Yes, I know this can be done with member initializer lists as in:
		Comp<T>(T cr, T ci) : r(cr),i(ci) { } */

		Comp<T>(T cr, T ci=0) { r=cr; i=ci; }

		Comp<T>(const Comp<T> &s) { r=s.r; i=s.i; }

		Comp<T>(T v[2]) { r=v[0]; i=v[1]; }

		inline Comp<T> square() const
			{
			Comp<T> c;
			c=Comp<T>(r*r-i*i,static_cast<T>(2)*r*i);
			return(c);
			}

		inline T dot() const
			{
			T c;
			c=r*r+i*i;
			return(c);
			}

		inline T dot(const Comp<T> &q) const
			{
			T c;
			c=r*q.r+i*q.i;
			return(c);
			}

		inline T mag() const // mag aka abs
			{
			T c;
			c=sqrt(r*r+i*i);
			return(c);
			}

		inline T phase() const // phase aka arg
			{
			T theta;
			//theta=static_cast<T>(atan(i/r));
// also could do:
			theta=static_cast<T>(atan2(i,r));
// also could do:
/*
			T mag;
			mag=sqrt(r*r+i*i);
			if ((r==0.0)&&(i==0.0)) { theta=0.0; }
			else { theta=acos(r/mag); }
			if (i<0.0) { theta=-theta; }
*/
			return(theta);
			}

		inline Comp<T> const normalized() const
			{
			T mag=sqrt(r*r+i*i);
			if (mag!=0.0)
				{
				Comp<T> c;
				c.r=r/mag; c.i=i/mag;
				return(c);
				}
			return(Comp(0.0,0.0));
			}

		inline T normalize()
			{
			T mag=sqrt(r*r+i*i);
			if (mag!=0.0) { r/=mag; i/=mag; }
			else { r=i=0.0; }
			return(mag);
			}

		inline Comp<T> conjugate() const
			{
			return(Comp<T>(r,-i));
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

	friend Comp<T> operator+ (const Comp<T> &L, const Comp<T> &R)
		{
		return(Comp<T>(L.r+R.r,L.i+R.i));
		}

	friend Comp<T> operator+ (const Comp<T> &L, const T &R)
		{
		Comp<T> c; c.r=L.r+R; c.i=L.i;
		return(c);
		}

	friend Comp<T> operator+ (const T &L, const Comp<T> &R)
		{
		Comp<T> c; c.r=L+R.r; c.i=R.i;
		return(c);
		}

	friend Comp<T> operator- (const Comp<T> &R)
		{
		Comp<T> c; c.r=-R.r; c.i=-R.i; return(c);
		}

	friend Comp<T> operator- (const Comp<T> &L, const Comp<T> &R)
		{
		Comp<T> c; c.r=L.r-R.r; c.i=L.i-R.i;
		return(c);
		}

	friend Comp<T> operator- (const Comp<T> &L, const T &R)
		{
		Comp<T> c; c.r=L.r-R; c.i=L.i;
		return(c);
		}

	friend Comp<T> operator- (const T &L, const Comp<T> &R)
		{
		Comp<T> c; c.r=L-R.r; c.i=-R.i;
		return(c);
		}

	friend Comp<T> operator* (const Comp<T> &L, const Comp<T> &R)
		{
		Comp<T> c;
		c=Comp<T>(L.r*R.r-L.i*R.i,L.r*R.i+L.i*R.r);
		return(c);
		}

	friend Comp<T> operator* (const T &L, const Comp<T> &R)
		{
		Comp<T> c;
		c.r=R.r*L; c.i=R.i*L;
		return(c);
		}

	friend Comp<T> operator* (const Comp<T> &L, const T &R)
		{
		return(R*L);
		}

	friend Comp<T> operator/ (const Comp<T> &L, const Comp<T> &R)
		{
		return(Comp<T>(MagPhase2Complex(L.mag()/R.mag(),L.phase()-R.phase())));
// or:
/*
		T divtemp=R.r*R.r+R.i*R.i;
		if (divtemp==0.0) { return(Comp<T>(0.0,0.0)); }
		return(Comp<T>((L.r*R.r+L.i*R.i)/divtemp,(L.i*R.r-L.r*R.i)/divtemp));
*/
		}

	friend Comp<T> operator/ (const Comp<T> &L, const T &R)
		{
		Comp<T> c;
		c.r=L.r/R; c.i=L.i/R;
		return(c);
		}

	friend Comp<T>& operator+= (Comp<T> &L, const Comp<T> &R)
		{
		L.r+=R.r; L.i+=R.i;
		return(L);
		}

	friend Comp<T>& operator+= (Comp<T> &L, const T &R)
		{
		L.r+=R;
		return(L);
		}

	friend Comp<T>& operator-= (Comp<T> &L, const Comp<T> &R)
		{
		L.r-=R.r; L.i-=R.i;
		return(L);
		}

	friend Comp<T>& operator-= (Comp<T> &L, const T &R)
		{
		L.r-=R;
		return(L);
		}

	friend Comp<T>& operator*= (Comp<T> &L, const Comp<T> &R)
		{
		L=L*R;
		return(L);
		}

	friend Comp<T>& operator*= (Comp<T> &L, const T &R)
		{
		L.r*=R; L.i*=R;
		return(L);
		}

	friend Comp<T>& operator/= (Comp<T> &L, const Comp<T> &R)
		{
		L=L/R;
		return(L);
		}

	friend Comp<T>& operator/= (Comp<T> &L, const T &R)
		{
		L.r/=R; L.i/=R;
		return(L);
		}

#ifdef EPSILONCOMP

#define eq(a,b) (fabs(a-b)<EPSILONCOMP)
#define ne(a,b) (fabs(a-b)>=EPSILONCOMP)

	friend bool operator== (const Comp<T> &L, const Comp<T> &R)
		{
		return((eq(L.r,R.r))&&(eq(L.i,R.i)));
		}

	friend bool operator!= (const Comp<T> &L, const Comp<T> &R)
		{
		return((ne(L.r,R.r))||(ne(L.i,R.i)));
		}

#undef eq
#undef ne

#else

	friend bool operator== (const Comp<T> &L, const Comp<T> &R)
		{
		return((L.r==R.r)&&(L.i==R.i));
		}

	friend bool operator!= (const Comp<T> &L, const Comp<T> &R)
		{
		return((L.r!=R.r)||(L.i!=R.i));
		}

#endif

	friend std::ostream& operator<< (std::ostream &os, const Comp<T> &R)
		{
#if C_DISPLAY_FORMAT==1
		os << "(" << R.r << "," << R.i << "i)";
#elif C_DISPLAY_FORMAT==2
		os << "(" << R.r << "+" << R.i << "i)";
#elif C_DISPLAY_FORMAT==3
		os << "(" << R.r << "," << R.i << ")";
#else
		os << "(" << R.r << "+j" << R.i << ")";
#endif
		return(os);
		}
	};

template <class T>
inline Comp<T> MagPhase2Complex(const T &mag, const T &phase)
{
return(Comp<T>(mag*cos(phase),mag*sin(phase)));
}

template <class T>
inline T abs(const Comp<T> &z1)
{
T size;
size=sqrt(z1.r*z1.r+z1.i*z1.i);
return(size);
}

template <class T>
Comp<T> cos(const Comp<T> &z1)
{
return(Comp<T>(cos(z1.r)*cosh(z1.i),-sin(z1.r)*sinh(z1.i)));
}

template <class T>
Comp<T> sin(const Comp<T> &z1)  
{
return(Comp<T>(sin(z1.r)*cosh(z1.i),cos(z1.r)*sinh(z1.i)));
}

template <class T>
Comp<T> ztoz(const Comp<T> &z1)
{
T r,theta,newr,newtheta;
r=sqrt(z1.r*z1.r+z1.i*z1.i);
theta=z1.phase();
newr=pow(r,z1.r)*exp(-z1.i*theta);
newtheta=z1.r*theta+z1.i*log(r);
return(Comp<T>(newr*cos(newtheta),newr*sin(newtheta)));
}

#if _MSC_VER == 1200
template <class T>
Comp<T> cpow(const Comp<T> &z1, const T &p)
#else
template <class T, class U>
Comp<T> cpow(const Comp<T> &z1, const U &p)
#endif
{
T r,theta,newr,newtheta;
r=sqrt(z1.r*z1.r+z1.i*z1.i);
theta=z1.phase();
newr=pow(r,p);
newtheta=p*theta;
return(Comp<T>(newr*cos(newtheta),newr*sin(newtheta)));
}

template <class T>
Comp<T> exp(const Comp<T> &z1)
{
return(Comp<T>(exp(z1.r)*cos(z1.i),exp(z1.r)*sin(z1.i)));
}

template <class T>
Comp<T> cosh(const Comp<T> &z1)
{
return(Comp<T>(cos(z1.i)*cosh(z1.r),sin(z1.i)*sinh(z1.r)));
}

template <class T>
Comp<T> sinh(const Comp<T> &z1)
{
return(Comp<T>(cos(z1.i)*sinh(z1.r),sin(z1.i)*cosh(z1.r)));
}

template <class T>
Comp<T> log(const Comp<T> &z1)
{
return(Comp<T>(log(z1.mag()),z1.phase()));
}

template <class T>
Comp<T> log10(const Comp<T> &z1)
{
return(log(z1)/log(10.0));
}

template <class T>
Comp<T> log2(const Comp<T> &z1)
{
return(log(z1)/log(2.0));
}

template <class T>
Comp<T> tan(const Comp<T> &z1)
{
return(sin(z1)/cos(z1));
}

template <class T>
Comp<T> tanh(const Comp<T> &z1)
{
return(sinh(z1)/cosh(z1));
}

template <class T>
Comp<T> sqrt(const Comp<T> &z1)
{
return(cpow(z1,static_cast<T>(.5)));
}

template <class T>
Comp<T> acos(const Comp<T> &z1)
{
return(Comp<T>(0.0,-1.0)*log(z1+sqrt(z1*z1-static_cast<T>(1))));
}

template <class T>
Comp<T> asin(const Comp<T> &z1)
{
return(Comp<T>(0.0,-1.0)*log(Comp<T>(-z1.i,z1.r)+sqrt(static_cast<T>(1)-z1*z1)));
}

template <class T>
Comp<T> atan(const Comp<T> &z1)
{
return(Comp<T>(1.0,0.0)/Comp<T>(0.0,2.0)*log((static_cast<T>(1)+Comp<T>(-z1.i,z1.r))/(static_cast<T>(1)-Comp<T>(-z1.i,z1.r))));
}

template <class T>
Comp<T> acosh(const Comp<T> &z1)
{
return(static_cast<T>(2)*log(sqrt((z1+static_cast<T>(1))/static_cast<T>(2))+sqrt((z1-static_cast<T>(1))/static_cast<T>(2))));
}

template <class T>
Comp<T> asinh(const Comp<T> &z1)
{
return(log(z1+sqrt(z1*z1+static_cast<T>(1))));
}

template <class T>
Comp<T> atanh(const Comp<T> &z1)
{
return(static_cast<T>(.5)*log((static_cast<T>(1)+z1)/(static_cast<T>(1)-z1)));
}

#ifdef INFINITY

template <class T>
Comp<T> cproj(const Comp<T> &z1)
{
// I don't see the point in this function, especially since no one seems to
// agree on how to implement it, but having said that...
// I think this is how it's done
if ((std::isinf(z1.r)||(std::isinf(z1.i))))
	{ return(Comp<T>(INFINITY,copysign(0.0,z1.i))); }
return(z1);
}

#endif

template <class T>
Comp<T> polar(const T &rho, const T &theta)
{
return(Comp<T>(rho*cos(theta),rho*sin(theta)));
}

template <class T>
Comp<T> cpow(const Comp<T> &z1, const Comp<T> &z2)
{
return(exp(z2*log(z1)));
}

#if _MSC_VER == 1200
template <class T>
Comp<T> cpow(const T &x, const Comp<T> &z2)
#else
template <class T, class U>
Comp<T> cpow(const U &x, const Comp<T> &z2)
#endif
{
return(exp(z2*log(x)));
}

typedef Comp<float> comp;

#endif
