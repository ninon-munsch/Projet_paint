#pragma once
#include <Windows.h>
#include <iostream>
#include "Element.h"
#include<gl/GL.h>
#include<GLUT.H>
using namespace std;



class Forme: public Element {
	vector<point> forme;
public:
	vector<point> getF() { return forme; };
	void setF(vector<point> fo) { forme=fo; };
	GLvoid draw();
	Forme(int mode, float epaisseur, vector<point>& clicks);
	Forme();
};