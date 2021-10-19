/*********************************************************
   Simple program to test equality functions of the
   quaternion number class.
   Copyright © 2021 Mark Craig

   https://www.youtube.com/MrMcSoftware
**********************************************************/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

//#define EULER2QUAT_METHOD 0
//#define EULER2QUAT_METHOD 1
//#define EULER2QUAT_METHOD 2

using std::cout;
using std::endl;

#define EPSILONCOMP .000002

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat2.h"
#include "mat3.h"
#include "mat4.h"
#include "quat.h"
#include "comp.h"

int main(int argc,char *argv[])
{
quat v1c(1.0,2.0,3.5,4.0);
quat v1ce; v1ce.x=v1c.x; v1ce.y=v1c.y; v1ce.z=v1c.z; v1ce.w=v1c.w;
quat v1cne; v1cne.x=v1c.x; v1cne.y=v1c.y*2.0; v1cne.z=v1c.z; v1cne.w=v1c.w;
v1ce.y+=.000001;
v1cne.y=v1c.y+.000001;
v1cne.y+=2.0;
if (v1c==v1ce) { printf("v1ce equals v1c\n"); } else { printf("v1ce doesn't equal v1c\n"); }
if (v1c==v1cne) { printf("v1cne equals v1c\n"); } else { printf("v1cne doesn't equal v1c\n"); }
if (v1c!=v1ce) { printf("v1ce doesn't equal v1c\n"); } else { printf("v1ce equals v1c\n"); }
if (v1c!=v1cne) { printf("v1cne doesn't equal v1c\n"); } else { printf("v1cne equals v1c\n"); }
return(0);
}
