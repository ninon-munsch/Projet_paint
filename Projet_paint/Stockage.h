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

typedef struct {
    point hg;
    point bd;
    couleur c;
    float epaisseur;
} rectangle;

typedef struct {
    point so;
    point ba;
    couleur c;
    float epaisseur;
} triangle;

typedef struct {
    point o;
    float r;
    couleur c;
    float epaisseur;
} cercle;

GLvoid draw_points(vector<point> points);
GLvoid draw_rectangles(vector<rectangle> rectangles);
GLvoid draw_circles(vector<cercle> cercles);
GLvoid draw_triangles(vector<triangle> triangles);