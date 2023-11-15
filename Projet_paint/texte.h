
#pragma once
#include <Windows.h>
#include <iostream>
#include "Stockage.h"

#include<gl/GL.h>
#include<GLUT.H>
using namespace std;

//Pour mettre fin a l'écriture du texte il faut appuyer sur entrer
class Texte {
	couleur c;
	float epaisseur;
	point position;
	vector<char> text;
public:
	couleur getCouleur() { return c; };
	float getEpaisseur() { return epaisseur; };
	point getPos() { return position; };
	vector<char> getTexte() { return text; };
	void setCouleur(couleur co) { c = co; };
	void setEpaisseur(float ep) { epaisseur = ep; };
	void setPos(point pos) { position = pos; };
	void setText(vector<char> te) { text = te; };
	GLvoid draw_text();
	Texte(couleur c,point position,vector<char> text);
	Texte();
};
GLvoid draw_texts(vector<Texte> tex);