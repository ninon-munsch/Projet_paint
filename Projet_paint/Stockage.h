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

//Stockage des données à dessiner
typedef struct {
    float x;
    float y;
    couleur c;
    float size;
} point;

typedef struct {
    point hg;
    point bd;
    couleur c;
    float epaisseur;
} rectangle;

GLvoid draw_points(vector<point> points);
GLvoid draw_rectangles(vector<rectangle> rectangles);