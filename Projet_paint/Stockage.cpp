#include <Windows.h>
#include <iostream>
#include <vector>
#include "Stockage.h"

#include<gl/GL.h>
#include<GLUT.H>
using namespace std;
float ylim = 110;

point npoint(int x, int y) {
    point p;
    p.x = x;
    p.y = y;
    return p;
}