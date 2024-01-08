#include <Windows.h>
#include <iostream>
#include <vector>
#include "Interface.h"
#include "Stockage.h"
#include<gl/GL.h>
#include<GLUT.H>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include<stb_image_write.h>
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

Icone::Icone(point hg, point bd, couleur co, int m)
{
	this->coin_hg = hg;
	this->coin_bd = bd;
	this->c = co;
	this->m = m;
	this->tex = false;
}

Icone::Icone(point hg, point bd, couleur co, int m,vector<point> forme)
{
	this->coin_hg = hg;
	this->coin_bd = bd;
	this->c = co;
	this->m = m;
	this->forme = forme;
	this->tex = false;
}

Icone::Icone(point hg, point bd, couleur co, int m, bool tex,string nomtex)
{
	this->coin_hg = hg;
	this->coin_bd = bd;
	this->c = co;
	this->m = m;
	this->tex = tex;
	this->nomtex = nomtex;
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
vector<Icone> create_icons_coul() {
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

//Cree les icônes pour les différents modes de dessins
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

		//Texte

		point hg_txt;
		point bd_txt;
		int m_txt = 4;
		hg_txt.x = 550;
		hg_txt.y = 40;
		bd_txt.x = 590;
		bd_txt.y = 80;
		vector<point> forme_txt = { npoint(bd_txt.x-20,bd_txt.y-5),npoint(bd_txt.x - 20,hg_txt.y + 5),npoint(bd_txt.x - 5,hg_txt.y + 5),npoint(hg_txt.x + 5,hg_txt.y + 5) };
		Icone txt(hg_txt, bd_txt, fond, m_txt, forme_txt);

		//PIPETTE
		point hg_pip;
		point bd_pip;
		int m_pip = 5;
		hg_pip.x = 650;
		hg_pip.y = 40;
		bd_pip.x = 690;
		bd_pip.y = 80;


		
		//vector<point> forme_redo = { npoint(hg_redo.x + 13,hg_redo.y + 35),npoint(hg_redo.x + 10,hg_redo.y + 25),npoint(hg_redo.x + 15,hg_redo.y + 15),npoint(hg_redo.x + 20,hg_redo.y + 12),npoint(hg_redo.x + 30,hg_redo.y + 15),npoint(hg_redo.x + 25,hg_redo.y + 5),npoint(hg_redo.x + 30,hg_redo.y + 15),npoint(hg_redo.x + 20,hg_redo.y + 22) };
		Icone pip(hg_pip, bd_pip, fond,m_pip,true,"Pipette.jpg");
		//Remplissage
		point hg_remp;
		point bd_remp;
		int m_remp = 6;
		hg_remp.x = 750;
		hg_remp.y = 40;
		bd_remp.x = 790;
		bd_remp.y = 80;
		vector<point> forme_remp = {};
		//vector<point> forme_remp = { npoint(hg_remp.x + 13,hg_remp.y + 35),npoint(hg_remp.x + 10,hg_remp.y + 25),npoint(hg_remp.x + 15,hg_remp.y + 15),npoint(hg_remp.x + 20,hg_remp.y + 12),npoint(hg_remp.x + 30,hg_remp.y + 15),npoint(hg_remp.x + 25,hg_remp.y + 5),npoint(hg_remp.x + 30,hg_remp.y + 15),npoint(hg_remp.x + 20,hg_remp.y + 22) };
		Icone remp(hg_remp, bd_remp, fond, m_remp, true, "remplissage.jpg");


		//LISTE D'ICONES
		res.push_back(cra);
		res.push_back(ca);
		res.push_back(ce);
		res.push_back(tr);
		res.push_back(txt);
		res.push_back(remp);
		res.push_back(pip);
		return res;
}

vector<Icone> create_icons_funcs() {
	//FOND COULEUR
	couleur fond;
	fond.r = 0;
	fond.g = 0;
	fond.b = 0;
	fond.a = 0;
	vector<Icone> res;

	//UNDO
	point hg_undo;
	point bd_undo;
	int m_undo = 999;
	hg_undo.x = 500;
	hg_undo.y = 40;
	bd_undo.x = 540;
	bd_undo.y = 80;
	vector<point> forme_undo = { npoint(hg_undo.x + 27,hg_undo.y + 35),npoint(hg_undo.x + 30,hg_undo.y + 25),npoint(hg_undo.x + 25,hg_undo.y + 15),npoint(hg_undo.x + 20,hg_undo.y + 12),npoint(hg_undo.x + 10,hg_undo.y + 15),npoint(hg_undo.x + 15,hg_undo.y + 5),npoint(hg_undo.x + 10,hg_undo.y + 15),npoint(hg_undo.x + 20,hg_undo.y + 22) };
	Icone undo(hg_undo, bd_undo, fond, m_undo, forme_undo);

	//REDO
	point hg_redo;
	point bd_redo;
	int m_redo = 999;
	hg_redo.x = 600;
	hg_redo.y = 40;
	bd_redo.x = 640;
	bd_redo.y = 80;
	vector<point> forme_redo = { npoint(hg_redo.x + 13,hg_redo.y + 35),npoint(hg_redo.x + 10,hg_redo.y + 25),npoint(hg_redo.x + 15,hg_redo.y + 15),npoint(hg_redo.x + 20,hg_redo.y + 12),npoint(hg_redo.x + 30,hg_redo.y + 15),npoint(hg_redo.x + 25,hg_redo.y + 5),npoint(hg_redo.x + 30,hg_redo.y + 15),npoint(hg_redo.x + 20,hg_redo.y + 22) };
	Icone redo(hg_redo, bd_redo, fond, m_redo, forme_redo);

	//CLEAR
	point hg_clear;
	point bd_clear;
	int m_clear = 999;
	hg_clear.x = 700;
	hg_clear.y = 40;
	bd_clear.x = 740;
	bd_clear.y = 80;
	vector<point> forme_clear = {};
	//vector<point> forme_clear = { npoint(hg_clear.x + 13,hg_clear.y + 35),npoint(hg_clear.x + 10,hg_clear.y + 25),npoint(hg_clear.x + 15,hg_clear.y + 15),npoint(hg_clear.x + 20,hg_clear.y + 12),npoint(hg_clear.x + 30,hg_clear.y + 15),npoint(hg_clear.x + 25,hg_clear.y + 5),npoint(hg_clear.x + 30,hg_clear.y + 15),npoint(hg_clear.x + 20,hg_clear.y + 22) };
	Icone clear(hg_clear, bd_clear, fond, m_clear, true, "gomme.jpg");

	//EXPORT
	point hg_expo;
	point bd_expo;
	int m_expo = 999;
	hg_expo.x = 800;
	hg_expo.y = 40;
	bd_expo.x = 840;
	bd_expo.y = 80;
	vector<point> forme_expo = {};
	Icone expo(hg_expo, bd_expo, fond, m_expo, true, "save.jpg");


	//LISTE D'ICONES
	res.push_back(undo);
	res.push_back(redo);
	res.push_back(clear);
	res.push_back(expo);
	return res;
}


//Cree les sliders de la palette
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

//Crée le slider pour la taille des traits
Icone create_icon_size() {
	//Slider taille des traits
	couleur noir = { 0,0,0 };
	Icone taille(npoint(500, 10), npoint(755, 30));
	return taille;
}

//Dessine des icônes rectangulaires
GLvoid draw_colors(vector<Icone> ico) {

	for (Icone& i : ico) {
		couleur c = i.getC();
		point hg = i.getHG();
		point bd = i.getBD();
		glMatrixMode(GL_MODELVIEW);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor4f(c.r, c.g, c.b, c.a);
		glRectf(hg.x, hg.y, bd.x, bd.y);

		glEnd();
	}
}

//Crée une icône affichant la couleur actuellement sélectionnée
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

//Dessine les symboles au sein des icônes de modes de dessins
GLvoid draw_forme(vector<Icone> ico) {

	for (Icone& i : ico)
	{
		if (i.gettex())
		{
			tex_ico(i);
		}
		else 
		{

			couleur c = i.getC();
			point hg = i.getHG();
			point bd = i.getBD();
			glMatrixMode(GL_MODELVIEW);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glColor4f(c.r, c.g, c.b, c.a);
			glRectf(hg.x, hg.y, bd.x, bd.y);

			glColor4f(255, 255, 255, 0);
			glLineWidth(1);
			glBegin(GL_LINE_STRIP);
			for (point& p : i.getForme()) {
				glVertex2f(p.x, p.y);
			}
		}
		glEnd();
	}
};

//Dessine le slider pour la taille des traits
GLvoid draw_size(Icone ico) {
	glMatrixMode(GL_MODELVIEW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	couleur c = ico.getC();
	point hg = ico.getHG();
	point bd = ico.getBD();
	glColor4f(c.r, c.g, c.b, c.a);

	glBegin(GL_POLYGON);
	glVertex2f(hg.x, (hg.y + bd.y) / 2);
	glVertex2f(bd.x, hg.y);
	glVertex2f(bd.x, bd.y);
	glEnd();
}

//permet d'afficher des curseurs sur les barres de couleurs
GLvoid curseur_palette(couleur c) 
{
	glMatrixMode(GL_MODELVIEW);
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	
	glVertex2f(210 + (c.r*255), 10);
	glVertex2f(210 +( c.r*255 ), 30);
	glVertex2f(210 +(c.g*255) ,40 );
	glVertex2f(210 +(c.g*255) , 60);
	glVertex2f(210 +( c.b*255) ,70 );
	glVertex2f(210 + (c.b * 255) ,90 );
	glLineWidth(1);
	glEnd();
};

GLvoid curseur_size(float taille) {
	glMatrixMode(GL_MODELVIEW);
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(0, 0, 255);

	glVertex2f(500 + (taille * 20), 10);
	glVertex2f(500 + (taille * 20), 30);

	glLineWidth(1);
	glEnd();
}

couleur pipetteMarie(int x,int y)
{
	
	couleur coul;
	float pixel[4];
	glReadPixels(x,y, 1, 1, GL_RGBA, GL_FLOAT, pixel);
	coul.r = pixel[0] ;
	coul.g = pixel[1] ;
	coul.b = pixel[2] ;
	return coul;
}


GLvoid exportation(int width, int height)
{
	string chemin;
	cout << "Entrez : Chemin/NomDuFichier.png" << endl;
	cin >> chemin;
	int stride = 3 * width;
	int bufferSize = stride * height;
	std::vector<char> buffer(bufferSize);
	glPixelStorei(GL_PACK_ALIGNMENT, 4);
	glReadBuffer(GL_FRONT);
	glReadPixels(0, 0, width, height-110, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());
	stbi_flip_vertically_on_write(true);
	stbi_write_png(chemin.c_str(), width, height, 3, buffer.data(), stride);
	return;
}

GLvoid tex_ico(Icone i)
{
	int width, height, nrChannels;
	
	unsigned char* data = stbi_load(i.getnomtex().c_str(), &width, &height, &nrChannels, 0);
	unsigned int texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	couleur c = i.getC();
	point hg = i.getHG();
	point bd = i.getBD();
	glMatrixMode(GL_MODELVIEW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	

	glTexCoord2f(1, 1);
	glVertex2f(bd.x, bd.y);

	glTexCoord2f(0, 1);
	glVertex2f(hg.x, bd.y);

	glTexCoord2f(0, 0);
	glVertex2f(hg.x, hg.y);

	glTexCoord2f(1, 0);
	glVertex2f(bd.x, hg.y);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}