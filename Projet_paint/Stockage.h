#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>

#include<gl/GL.h>
#include<GLUT.H>
using namespace std;

//Stockage d'une couleur
typedef struct {
    float r;
    float g;
    float b;
    float a;
} couleur;

//Stockage des données à dessiner b
typedef struct {
    float x;
    float y;
    couleur c;
    float size;
} point;

point npoint(int x, int y);