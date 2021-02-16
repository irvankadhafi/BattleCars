#ifndef IRVANKDHF
#define IRVANKDHF

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <iostream>

#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))

/*  Texture definitions  */
#define TEX_WOODFENCE 0
#define TEX_METAL 1
#define TEX_GLASS 2
#define TEX_CARWHEEL 3
#define TEX_TIRETREAD 4
#define TEX_CARGRILL 5
#define TEX_HEADLAMP 6
#define TEX_CARBONFIBER 7
#define TEX_SIDEWALK 8
#define TEX_GARAGEDOOR 9
#define TEX_WALKWAY 10
#define TEX_HEDGE 11
#define TEX_GRASS 12
#define TEX_GREYBRICK 13
#define TEX_WOODBEAM 14
#define TEX_FRONTDOOR 15
#define TEX_WINDOW 16
#define TEX_SKYBOXFRONT 17
#define TEX_SKYBOXBACK 18
#define TEX_SKYBOXRIGHT 19
#define TEX_SKYBOXLEFT 20
#define TEX_SKYBOXTOP 21
#define TEX_ASPALTH 22
#define TEX_BROWNBRICK 23
#define TEX_WHITEBRICK 24
#define TEX_METALROOF 25
#define TEX_WAREHOUSEWINDOW 26
#define TEX_CHINDERBLOCK 27
#define TEX_DESERT 28


#ifdef __cplusplus
extern "C++" {
#endif

void Print(const char* format , ...);
void Fatal(const char* format , ...);
unsigned int LoadTexBMP(const char* file);
void Project(double fov,double asp,double dim);
void ErrCheck(const char* where);
int  LoadOBJ(const char* file);

#ifdef __cplusplus
}
#endif

#endif