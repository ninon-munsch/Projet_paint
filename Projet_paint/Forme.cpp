#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include "Forme.h"
#include<gl/GL.h>
#include<GLUT.H>
using namespace std;

float pi = 3.14159;
float nbSegCercle = 32;


GLvoid Forme::draw() {
	glColor3f(c.r, c.g, c.b);
	glMatrixMode(GL_MODELVIEW);
	if (mode==0) {
		if (forme.size()==1) {
			if (epaisseur != 0) {
				glPointSize(epaisseur);
			}
			else {
				glPointSize(1);
			}
			glBegin(GL_POINTS);
			glVertex2f(forme[0].x, forme[0].y);
		}
		else {
			if (epaisseur == 0) {
				glLineWidth(1);
			}
			else {
				glLineWidth(epaisseur);
			}
			glBegin(GL_LINE_STRIP);

			for (point& p : forme) {
				glVertex2f(p.x, p.y);
			}
		}

	}
	else {
		if (epaisseur != 0) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //en mode contour
			glLineWidth(epaisseur);
		}
		else { //si epaisseur =0, on considère que l'epaisseur n'est pas spécifiée et on trace une forme pleine
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //en mode surface pleine
		}
		glBegin(GL_POLYGON);

		for (point& p : forme) {
			glVertex2f(p.x, p.y);
		}
	};
	glEnd();
}

Forme::Forme(int mode, float epaisseur, vector<point> &clicks) {
	this->mode = mode;
	this->c = clicks[0].c;
	this->epaisseur = epaisseur;
	float rayon, theta;
	switch (mode) {
	case 0: //dessin à la main
		forme.push_back(clicks[0]);
		break;
	case 1: //dessin rectangle
		forme.push_back(clicks[0]);
		forme.push_back(npoint(clicks[1].x, clicks[0].y));
		forme.push_back(clicks[1]);
		forme.push_back(npoint(clicks[0].x, clicks[1].y));
		break;
	case 2: //dessin cercle
		rayon =sqrt(pow(clicks[0].x-clicks[1].x, 2) + pow(clicks[0].y - clicks[1].y, 2));
		theta = 2 * pi / nbSegCercle;
		if ((clicks[0].y-rayon)> 110) {
			for (int i = 0; i < nbSegCercle; i++) {
				forme.push_back(npoint(clicks[0].x + rayon * cos(i * theta), clicks[0].y + rayon * sin(i * theta)));
			}
		}
		break;
	case 3: // dessin triangle
		forme.push_back(clicks[0]);
		forme.push_back(clicks[1]);
		forme.push_back(npoint(2 * clicks[0].x - clicks[1].x, clicks[1].y));
		break;
	}
}

Forme::Forme()
{
	vector<point> f(1);
	forme = f;
}

