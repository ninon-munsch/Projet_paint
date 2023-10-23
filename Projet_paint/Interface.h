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
	vector<point> forme;
public:
	GLboolean est_sur(int x, int y);
	Icone(point hg, point bd);
	Icone(point hg, point bd,couleur co);
	point getHG() { return coin_hg; };
	point getBD() { return coin_bd; };
	couleur getC() { return c; };

};

vector<Icone> create_icons_coul();
vector<Icone> create_icons_forme();
GLvoid draw_colors(vector<Icone> ico);
GLvoid draw_forme(vector<Icone> ico);
point npoint(int x, int y);
vector<Icone> create_slide();
GLvoid coul_actu(couleur c) ;