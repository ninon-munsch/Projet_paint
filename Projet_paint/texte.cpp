#pragma once
#include "texte.h"
#include "Element.h"



Texte::Texte(couleur co, point pos, vector<char> te)
{
	text = te;
	c = co;
	position = pos;
}

GLvoid Texte::draw()
{
	int x_temp = position.x;
	for (int i = 0; i < text.size(); i++)
	{
		glColor3f(c.r, c.g, c.b);
		x_temp += glutBitmapWidth(GLUT_BITMAP_8_BY_13, text[i]) + 1;
		glRasterPos2f(x_temp, position.y);
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);

	}
	return;
}


GLvoid draw_texts(vector<Texte> tex) {

	for (Texte& t : tex) {
		t.draw();
		glEnd();
	}
}