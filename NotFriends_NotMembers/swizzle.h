/*********************************************************
   Swizzle class for vector swizzling
   Copyright © 2024 Mark Craig

   https://www.youtube.com/MrMcSoftware
**********************************************************/

#ifndef _SWIZZLE_H
#define _SWIZZLE_H

/*
   Some would say this is an unsafe way to implement swizzles (specifically,
   the type punning (although, is it really type punning when the underlying
   type is the same (i.e. set of floats to set of floats for example)?)),
   but it's simple and it works.  From what I read, GLM's implementation of
   swizzles won't allow a swizzle to be used as a parameter in a function call.
   This implementation will.  However, use at your own risk.

   In some cases, a cast to a vector class may be required to access member
   functions.  For example, vec4 val(1,3,5,7); float f=val.xy.dot(); won't
   necessarily work - you will likely need to do float f=vec2(val.xy).dot()
   However,
     void process(vec2 x) { cout << x.dot() << endl; }
     ...
     process(val.xy);
   will work.
*/

template <class CT,typename T,int A,int B>
class swizzle2
	{
	T v[2];
	public:
		CT& operator=(const CT &R)
		{
		v[A]=R.x;
		v[B]=R.y;
		return(*(CT*)this);
		//return(*reinterpret_cast<CT*>(this)); // will also work
		}

		operator CT() const
		{
		return(CT(v[A],v[B]));
		}
	};

template <class CT,typename T,int A,int B,int C>
class swizzle3
	{
	T v[3];
	public:
		CT& operator=(const CT &R)
		{
		v[A]=R.x;
		v[B]=R.y;
		v[C]=R.z;
		return(*(CT*)this);
		}

		operator CT() const
		{
		return(CT(v[A],v[B],v[C]));
		}
	};

template <class CT,typename T,int A,int B,int C,int D>
class swizzle4
	{
	T v[4];
	public:
		CT& operator=(const CT &R)
		{
		v[A]=R.x;
		v[B]=R.y;
		v[C]=R.z;
		v[D]=R.w;
		return(*(CT*)this);
		}

		operator CT() const
		{
		return(CT(v[A],v[B],v[C],v[D]));
		}
	};
#endif
