
#pragma once
#include <Windows.h>
#include <iostream>
#include "Element.h"
#include<gl/GL.h>
#include<GLUT.H>
using namespace std;

class Element;


//Pour mettre fin a l'écriture du texte il faut appuyer sur entrer
class Texte : public Element {
	point position;
	vector<char> text;
public:
	point getPos() { return position; };
	vector<char> getTexte() { return text; };
	void setPos(point pos) { position = pos; };
	void setText(vector<char> te) { text = te; };
	GLvoid draw();
	Texte(couleur c,point position,vector<char> text);
	Texte();
};
GLvoid draw_texts(vector<Texte> tex);