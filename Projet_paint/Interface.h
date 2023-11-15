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
	vector<point> forme; //Ensemble de points à tracer dans l'ordre formant le symbole de l'icône
public:
	GLboolean est_sur(int x, int y);
	Icone(point hg, point bd);
	Icone(point hg, point bd,couleur co);
	Icone(point hg, point bd, couleur co, int m);
	Icone(point hg, point bd, couleur co, int m,vector<point> forme);
	point getHG() { return coin_hg; };
	point getBD() { return coin_bd; };
	couleur getC() { return c; };
	int getM() { return m; };
	vector<point> getForme() { return forme; };

};

//Permet de créer facilement une structure point
point npoint(int x, int y);

//CREATION des différentes icônes et sliders
vector<Icone> create_icons_coul();
vector<Icone> create_icons_forme();
vector<Icone> create_slide();
Icone create_icon_size();
vector<Icone> create_icons_funcs(); //icônes fonctionnelles s'activant en un click : undo, redo, save, clear

//DESSIN des icônes/sliders
GLvoid draw_colors(vector<Icone> ico);
GLvoid draw_forme(vector<Icone> ico);
GLvoid draw_size(Icone ico);
GLvoid coul_actu(couleur c) ;
GLvoid curseur_palette(couleur c);
GLvoid curseur_size(float taille);