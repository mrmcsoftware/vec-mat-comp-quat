/*********************************************************
   Config and include all
   Copyright © 2024 Mark Craig

   https://www.youtube.com/MrMcSoftware
**********************************************************/

// Config options

#undef VEC_USE_SWIZZLE
#undef VEC_USE_MAT
//#define EPSILONCOMPREL
//#define VMCQ_NEEDMAX
//#define EPSILONCOMP .00003 // for example
//#define VMCQ_NO_NAMESPACE
//#define VMCQ_USING_NAMESPACE
//#define EULER2QUAT_METHOD 0 // (Euler to Quaternion rotation method default)
//#define EULER2QUAT_METHOD 1
//#define EULER2QUAT_METHOD 2
//#define DONT_SWAP_PITCH_ROLL // Default not defined (Swap pitch and roll)
//#define DONT_SWAP_YAW_PITCH // Default not defined (Swap yaw and pitch)
//#define Q_DISPLAY_FORMAT 0 // 1,2i,3j,4k (Quaterion display format default)
//#define Q_DISPLAY_FORMAT 1 // 1+2i+3j+4k
//#define Q_DISPLAY_FORMAT 2 // 1,2,3,4
//#define C_DISPLAY_FORMAT 0 // 1+j2 (Complex number display format default)
//#define C_DISPLAY_FORMAT 1 // 1,2i
//#define C_DISPLAY_FORMAT 2 // 1+2i
//#define C_DISPLAY_FORMAT 3 // 1,2

// Include these here so they won't be within vmcq namespace (include guards)

#include <cstdio>
#include <cmath>
#include <iostream>
#include <cassert>
#include <iomanip>

// Include all vmcq headers (comment out as desired)

#ifndef VMCQ_NO_NAMESPACE
namespace vmcq
{
#endif
#ifdef VEC_USE_SWIZZLE
#include "swizzle.h"
#endif
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat2.h"
#include "mat3.h"
#include "mat4.h"
#include "quat.h"
#include "comp.h"
#include "matfunc.h"
#ifndef VMCQ_NO_NAMESPACE
}

#ifdef VMCQ_USING_NAMESPACE
using namespace vmcq;
#endif
#endif
