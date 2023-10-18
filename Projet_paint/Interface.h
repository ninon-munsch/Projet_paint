#pragma once
#include <Windows.h>
#include <iostream>
#include "Stockage.h"

#include<gl/GL.h>
#include<GLUT.H>
using namespace std;


class Icone {
	point coin_hg;
	point coin_bd;
	couleur c;
	vector<point> forme; //Ensemble de points à tracer dans l'ordre formant le symbole de l'icône
public:
	GLboolean est_sur(int x, int y);
	Icone(point hg, point bd);
	Icone(point hg, point bd,couleur co);
	point getHG() { return coin_hg; };
	point getBD() { return coin_bd; };
	couleur getC() { return c; };

};

vector<Icone> create_icons();
GLvoid draw_colors(vector<Icone> ico);