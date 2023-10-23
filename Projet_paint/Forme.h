#pragma once
#include <Windows.h>
#include <iostream>
#include "Stockage.h"

#include<gl/GL.h>
#include<GLUT.H>
using namespace std;


class Forme {
	couleur c;
	float epaisseur;
	vector<point> forme;
public:
	couleur getCouleur() { return c; };
	float getEpaisseur() { return epaisseur; };
	vector<point> getF() { return forme; };
	GLvoid draw_form();
	Forme(int mode, float epaisseur, vector<point>& clicks);
};