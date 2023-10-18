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
	int m;
	vector<point> forme;
public:
	GLboolean est_sur(int x, int y);
	Icone(point hg, point bd);
	Icone(point hg, point bd,couleur co);
	Icone(point hg, point bd, couleur co, int m);
	point getHG() { return coin_hg; };
	point getBD() { return coin_bd; };
	couleur getC() { return c; };
	int getM() { return m; };
	vector<point> getForme() { return forme; };

};

vector<Icone> create_icons_coul();
vector<Icone> create_icons_forme();
GLvoid draw_colors(vector<Icone> ico);