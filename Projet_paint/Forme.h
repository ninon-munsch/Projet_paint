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
	vector<string> texte;
public:
	couleur getCouleur() { return c; };
	float getEpaisseur() { return epaisseur; };
	vector<point> getF() { return forme; };
	vector<string> getTexte() { return texte; };
	void setCouleur(couleur co) {  c=co; };
	void setEpaisseur(float ep) { epaisseur=ep; };
	void setF(vector<point> fo) { forme=fo; };
	void setTexte(vector<string> te) { texte=te; };
	GLvoid draw_form();
	Forme(int mode, float epaisseur, vector<point>& clicks);
	Forme();
};
GLvoid draw_text(vector<char> text, int x, int y);