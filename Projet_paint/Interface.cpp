#include <Windows.h>
#include <iostream>
#include <vector>
#include "Interface.h"
#include "Stockage.h"
#include<gl/GL.h>
#include<GLUT.H>
using namespace std;


Icone::Icone(point hg, point bd)
{
	this->coin_hg = hg;
	this->coin_bd = bd;
}

Icone::Icone(point hg, point bd, couleur co)
{
	this->coin_hg = hg;
	this->coin_bd = bd;
	this->c = co;
}


GLboolean Icone::est_sur(int x, int y)
{	
	int x1 = (this->coin_hg).x;
	int x2= (this->coin_bd).x;
	int y1= (this->coin_hg).y;
	int y2= (this->coin_bd).y;
	if (x1<x && x<x2)
	{
		if (y1 < y && y < y2)
		{
			return  true;
		}
		else 
		{
			return false;
		}
	}
	return false;
}

//creer les icones de différentes couleurs
vector<Icone> create_icons() {
	//Icône rectangle
	//point i_rect_hg;
	//i_rect_hg.x = 10;
	//i_rect_hg.y = 10;
	//point i_rect_bd;
	//i_rect_bd.x = 150;
	//i_rect_bd.y = 150;
	vector<Icone> res;
	couleur rouge;
	point hgr;
	point bdr;
	rouge.r = 1;
	rouge.g = 0;
	rouge.b = 0;
	rouge.a = 0;
	hgr.x = 10;
	hgr.y = 10;
	bdr.x = 50;
	bdr.y = 50;
	Icone r(hgr,bdr,rouge);
	couleur vert;
	point hgv;
	point bdv;
	vert.r = 0;
	vert.g = 1;
	vert.b = 0;
	vert.a = 0;
	hgv.x = 60;
	hgv.y = 10;
	bdv.x = 100;
	bdv.y = 50;
	Icone v(hgv, bdv, vert);
	couleur bleu;
	point hgb;
	point bdb;
	bleu.r = 0;
	bleu.g = 0;
	bleu.b = 1;
	bleu.a = 0;
	hgb.x = 110;
	hgb.y = 10;
	bdb.x = 150;
	bdb.y = 50;
	Icone b(hgb, bdb, bleu);
	res.push_back(r);
	res.push_back(b);
	res.push_back(v);
	return res;
}


	vector<Icone> create_icons_forme() {
		//FOND COULEUR
		couleur fond;
		fond.r = 0;
		fond.g = 0;
		fond.b = 0;
		fond.a = 0;
		vector<Icone> res;
		//CRAYON CLASSIQUE
		point hgcra;
		point bdcra;
		int mcra = 0;
		hgcra.x = 10;
		hgcra.y = 60;
		bdcra.x = 50;
		bdcra.y = 100;
		vector<point> forme = { npoint(10 + 15,60 + 32),npoint(10 + 10,60 + 25),npoint(10 + 20,60 + 20),npoint(10 + 30,60 + 15),npoint(10 + 25,60 + 7) };
		Icone cra(hgcra, bdcra, fond,mcra,forme);
		//CARRE
		point hgca;
		point bdca;
		int mca = 1;
		hgca.x = 60;
		hgca.y = 60;
		bdca.x = 100;
		bdca.y = 100;
		vector<point> formeca = { npoint(hgca.x+10,hgca.y+10),npoint(hgca.x+30,hgca.y+10),npoint(hgca.x+30,hgca.y+30),npoint(hgca.x+10,hgca.y+30),npoint(hgca.x + 10,hgca.y + 10)};
		Icone ca(hgca, bdca, fond, mca, formeca);
		//CERCLE
		int mce = 2;
		point hgce;
		point bdce;
		hgce.x = 110;
		hgce.y = 60;
		bdce.x = 150;
		bdce.y = 100;
		vector<point> formece;
		float angle = (2 * 3.14 )/ 32;
		for (int i = 0; i < 32; i++) {
			formece.push_back(npoint(hgce.x+20+10 * cos(i * angle), hgce.y+20+10 * sin(i * angle)));
		}
		formece.push_back(npoint(hgce.x + 20 + 10 * cos(0 * angle), hgce.y + 20 + 10 * sin(0 * angle)));
		Icone ce(hgce, bdce, fond,mce,formece);
		//TRIANGLE
		int mtr = 3;
		point hgtr;
		point bdtr;
		hgtr.x = 160;
		hgtr.y = 60;
		bdtr.x = 200;
		bdtr.y = 100;
		vector<point> formetr = { npoint(hgtr.x + 20,hgtr.y + 10),npoint(hgtr.x + 30,hgtr.y + 30),npoint(hgtr.x + 10,hgtr.y + 30),npoint(hgtr.x + 20,hgtr.y + 10) };
		Icone tr(hgtr, bdtr, fond, mtr, formetr);
		//LISTE D'ICONES
		res.push_back(cra);
		res.push_back(ca);
		res.push_back(ce);
		res.push_back(tr);
		return res;
}

vector<Icone> create_slide()
{
	vector<Icone> liste;
	couleur rouge;
	point hgr;
	point bdr;
	rouge.r = 1;
	rouge.g = 0;
	rouge.b = 0;
	rouge.a = 0;
	hgr.x = 210;
	hgr.y = 10;
	bdr.x = 465;
	bdr.y = 30;
	Icone r(hgr, bdr, rouge);
	couleur vert;
	point hgv;
	point bdv;
	vert.r = 0;
	vert.g = 1;
	vert.b = 0;
	vert.a = 0;
	hgv.x = 210;
	hgv.y = 40;
	bdv.x = 465;
	bdv.y = 60;
	Icone v(hgv, bdv, vert);
	couleur bleu;
	point hgb;
	point bdb;
	bleu.r = 0;
	bleu.g = 0;
	bleu.b = 1;
	bleu.a = 0;
	hgb.x = 210;
	hgb.y = 70;
	bdb.x = 465;
	bdb.y = 90;
	Icone b(hgb, bdb, bleu);
	liste.push_back(r);
	
	liste.push_back(v);
	liste.push_back(b);
	return(liste);
}



GLvoid draw_colors(vector<Icone> ico) {

	for (Icone& i : ico) {
		couleur c = i.getC();
		point hg = i.getHG();
		point bd = i.getBD();
		glMatrixMode(GL_MODELVIEW);
		glColor4f(c.r, c.g, c.b, c.a);
		glRectf(hg.x, hg.y, bd.x, bd.y);

		glEnd();
	}
}
GLvoid coul_actu(couleur c)
{
	vector<Icone> liste;
	point hgb;
	point bdb;
	hgb.x = 160;
	hgb.y = 10;
	bdb.x = 200;
	bdb.y = 50;
	Icone ico(hgb, bdb, c);
	liste.push_back(ico);
	draw_colors(liste);
}

GLvoid draw_forme(vector<Icone> ico) {

	for (Icone& i : ico) {
		couleur c = i.getC();
		point hg = i.getHG();
		point bd = i.getBD();
		glMatrixMode(GL_MODELVIEW);
		glColor4f(c.r, c.g, c.b, c.a);
		glRectf(hg.x, hg.y, bd.x, bd.y);
		glColor4f(255, 255, 255, 0);
		glBegin(GL_LINE_STRIP);
		for (point p : i.getForme()) {
			glVertex2f(p.x, p.y);
		}


		glEnd();
	}
};