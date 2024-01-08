#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include "stockage.h"
#include<gl/GL.h>
#include<GLUT.H>
using namespace std;
class Element;
GLvoid remplissage(int x, int y, couleur cd/*couleur de remplissage*/, couleur cb/*couleur sur laquelle on doit remplir*/, int width, int height, vector<point> &clicks, vector<Element*>& stockage);
