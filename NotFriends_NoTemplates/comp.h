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

// complex is already a part of STL, so should use something else
//    unless this is put in it's own namespace

class comp;

inline comp MagPhase2Complex(const float &mag, const float &phase);

class comp
	{
	public:
		union
			{
			struct { float r,i; };
			struct { float real,imaginary; };
			struct { float re,im; };
			struct { float V[2]; };
			};

		comp() { r=i=0; }

		/* Yes, I know this can be done with member initializer lists as in:
		comp(float cr, float ci) : r(cr),i(ci) { } */

		comp(float cr, float ci=0) { r=cr; i=ci; }

		comp(const comp &s) { r=s.r; i=s.i; }

		comp(float v[2]) { r=v[0]; i=v[1]; }

		inline comp square() const
			{
			comp c;
			c=comp(r*r-i*i,2.0*r*i);
			return(c);
			}

		inline float dot() const
			{
			float c;
			c=r*r+i*i;
			return(c);
			}

		inline float dot(const comp &q) const
			{
			float c;
			c=r*q.r+i*q.i;
			return(c);
			}

		inline float mag() const // mag aka abs
			{
			float c;
			c=sqrt(r*r+i*i);
			return(c);
			}

		inline float phase() const // phase aka arg
			{
			float theta;
			//theta=float(atan(i/r));
// also could do:
			theta=float(atan2(i,r));
// also could do:
/*
			float mag;
			mag=sqrt(r*r+i*i);
			if ((r==0.0)&&(i==0.0)) { theta=0.0; }
			else { theta=acos(r/mag); }
			if (i<0.0) { theta=-theta; }
*/
			return(theta);
			}

		inline comp const normalized() const
			{
			float mag=sqrt(r*r+i*i);
			if (mag!=0.0)
				{
				comp c;
				c.r=r/mag; c.i=i/mag;
				return(c);
				}
			return(comp(0.0,0.0));
			}

		inline float normalize()
			{
			float mag=sqrt(r*r+i*i);
			if (mag!=0.0) { r/=mag; i/=mag; }
			else { r=i=0.0; }
			return(mag);
			}

		inline comp conjugate() const
			{
			return(comp(r,-i));
			}

		inline float operator[] (int i) const
			{
			assert((i>=0)&&(i<2));
			return(V[i]);
			}

		inline float& operator[] (int i)
			{
			assert((i>=0)&&(i<2));
			return(V[i]);
			}
	};

comp operator+ (const comp &L, const comp &R)
	{
	return(comp(L.r+R.r,L.i+R.i));
	}

comp operator+ (const comp &L, const float &R)
	{
	comp c; c.r=L.r+R; c.i=L.i;
	return(c);
	}

comp operator+ (const float &L, const comp &R)
	{
	comp c; c.r=L+R.r; c.i=R.i;
	return(c);
	}

comp operator- (const comp &R)
	{
	comp c; c.r=-R.r; c.i=-R.i; return(c);
	}

comp operator- (const comp &L, const comp &R)
	{
	comp c; c.r=L.r-R.r; c.i=L.i-R.i;
	return(c);
	}

comp operator- (const comp &L, const float &R)
	{
	comp c; c.r=L.r-R; c.i=L.i;
	return(c);
	}

comp operator- (const float &L, const comp &R)
	{
	comp c; c.r=L-R.r; c.i=-R.i;
	return(c);
	}

comp operator* (const comp &L, const comp &R)
	{
	comp c;
	c=comp(L.r*R.r-L.i*R.i,L.r*R.i+L.i*R.r);
	return(c);
	}

comp operator* (const float &L, const comp &R)
	{
	comp c;
	c.r=R.r*L; c.i=R.i*L;
	return(c);
	}

comp operator* (const comp &L, const float &R)
	{
	return(R*L);
	}

comp operator/ (const comp &L, const comp &R)
	{
	return(comp(MagPhase2Complex(L.mag()/R.mag(),L.phase()-R.phase())));
// or:
/*
	float divtemp=R.r*R.r+R.i*R.i;
	if (divtemp==0.0) { return(comp(0.0,0.0)); }
	return(comp((L.r*R.r+L.i*R.i)/divtemp,(L.i*R.r-L.r*R.i)/divtemp));
*/
	}

comp operator/ (const comp &L, const float &R)
	{
	comp c;
	c.r=L.r/R; c.i=L.i/R;
	return(c);
	}

comp& operator+= (comp &L, const comp &R)
	{
	L.r+=R.r; L.i+=R.i;
	return(L);
	}

comp& operator+= (comp &L, const float &R)
	{
	L.r+=R;
	return(L);
	}

comp& operator-= (comp &L, const comp &R)
	{
	L.r-=R.r; L.i-=R.i;
	return(L);
	}

comp& operator-= (comp &L, const float &R)
	{
	L.r-=R;
	return(L);
	}

comp& operator*= (comp &L, const comp &R)
	{
	L=L*R;
	return(L);
	}

comp& operator*= (comp &L, const float &R)
	{
	L.r*=R; L.i*=R;
	return(L);
	}

comp& operator/= (comp &L, const comp &R)
	{
	L=L/R;
	return(L);
	}

comp& operator/= (comp &L, const float &R)
	{
	L.r/=R; L.i/=R;
	return(L);
	}

#ifdef EPSILONCOMP

#define eq(a,b) (fabs(a-b)<EPSILONCOMP)
#define ne(a,b) (fabs(a-b)>=EPSILONCOMP)

bool operator== (const comp &L, const comp &R)
	{
	return((eq(L.r,R.r))&&(eq(L.i,R.i)));
	}

bool operator!= (const comp &L, const comp &R)
	{
	return((ne(L.r,R.r))||(ne(L.i,R.i)));
	}

#undef eq
#undef ne

#else

bool operator== (const comp &L, const comp &R)
	{
	return((L.r==R.r)&&(L.i==R.i));
	}

bool operator!= (const comp &L, const comp &R)
	{
	return((L.r!=R.r)||(L.i!=R.i));
	}

#endif

std::ostream& operator<< (std::ostream &os, const comp &R)
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

inline comp MagPhase2Complex(const float &mag, const float &phase)
{
return(comp(mag*cos(phase),mag*sin(phase)));
}

inline float abs(const comp &z1)
{
float size;
size=sqrt(z1.r*z1.r+z1.i*z1.i);
return(size);
}

comp cos(const comp &z1)
{
return(comp(cos(z1.r)*cosh(z1.i),-sin(z1.r)*sinh(z1.i)));
}

comp sin(const comp &z1)  
{
return(comp(sin(z1.r)*cosh(z1.i),cos(z1.r)*sinh(z1.i)));
}

comp ztoz(const comp &z1)
{
float r,theta,newr,newtheta;
r=sqrt(z1.r*z1.r+z1.i*z1.i);
theta=z1.phase();
newr=pow(r,z1.r)*exp(-z1.i*theta);
newtheta=z1.r*theta+z1.i*log(r);
return(comp(newr*cos(newtheta),newr*sin(newtheta)));
}

comp cpow(const comp &z1, const float &p)
{
float r,theta,newr,newtheta;
r=sqrt(z1.r*z1.r+z1.i*z1.i);
theta=z1.phase();
newr=pow(r,p);
newtheta=p*theta;
return(comp(newr*cos(newtheta),newr*sin(newtheta)));
}

comp exp(const comp &z1)
{
return(comp(exp(z1.r)*cos(z1.i),exp(z1.r)*sin(z1.i)));
}

comp cosh(const comp &z1)
{
return(comp(cos(z1.i)*cosh(z1.r),sin(z1.i)*sinh(z1.r)));
}

comp sinh(const comp &z1)
{
return(comp(cos(z1.i)*sinh(z1.r),sin(z1.i)*cosh(z1.r)));
}

comp log(const comp &z1)
{
return(comp(log(z1.mag()),z1.phase()));
}

comp log10(const comp &z1)
{
return(log(z1)/log(10.0));
}

comp log2(const comp &z1)
{
return(log(z1)/log(2.0));
}

comp tan(const comp &z1)
{
return(sin(z1)/cos(z1));
}

comp tanh(const comp &z1)
{
return(sinh(z1)/cosh(z1));
}

comp sqrt(const comp &z1)
{
return(cpow(z1,.5));
}

comp acos(const comp &z1)
{
return(comp(0.0,-1.0)*log(z1+sqrt(z1*z1-1.0)));
}

comp asin(const comp &z1)
{
return(comp(0.0,-1.0)*log(comp(-z1.i,z1.r)+sqrt(1.0-z1*z1)));
}

comp atan(const comp &z1)
{
return(comp(1.0,0.0)/comp(0.0,2.0)*log((1.0+comp(-z1.i,z1.r))/(1.0-comp(-z1.i,z1.r))));
}

comp acosh(const comp &z1)
{
return(2.0*log(sqrt((z1+1.0)/2.0)+sqrt((z1-1.0)/2.0)));
}

comp asinh(const comp &z1)
{
return(log(z1+sqrt(z1*z1+1.0)));
}

comp atanh(const comp &z1)
{
return(.5*log((1.0+z1)/(1.0-z1)));
}

#ifdef INFINITY

comp cproj(const comp &z1)
{
// I don't see the point in this function, especially since no one seems to
// agree on how to implement it, but having said that...
// I think this is how it's done
if ((std::isinf(z1.r)||(std::isinf(z1.i))))
	{ return(comp(INFINITY,copysign(0.0,z1.i))); }
return(z1);
}

#endif

comp polar(const float &rho, const float &theta)
{
return(comp(rho*cos(theta),rho*sin(theta)));
}

comp cpow(const comp &z1, const comp &z2)
{
return(exp(z2*log(z1)));
}

comp cpow(const float &x, const comp &z2)
{
return(exp(z2*log(x)));
}

#endif
