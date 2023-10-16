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
public:
	GLboolean est_sur(int x, int y);
	Icone(int hg, int bd);
	point getHG() { return coin_hg; };
	point getBD() { return coin_bd; };
};

GLvoid create_icons();