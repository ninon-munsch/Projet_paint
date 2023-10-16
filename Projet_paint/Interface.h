#pragma once
#include <Windows.h>
#include <iostream>

#include<gl/GL.h>
#include<GLUT.H>
using namespace std;

class Icone {
	int coin_hg;
	int coin_bd;
public:
	GLboolean est_sur(int x, int y);
	Icone(int hg, int bd);
};
