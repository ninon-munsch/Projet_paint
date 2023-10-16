#include <Windows.h>
#include <iostream>
#include <vector>
#include "Stockage.h"

#include<gl/GL.h>
#include<GLUT.H>
using namespace std;

//Dessine tous les points
GLvoid draw_points(vector<point> points) {

    for (point& p : points) {
        glMatrixMode(GL_MODELVIEW);
        glPointSize(p.size);
        glBegin(GL_POINTS);
        glColor4f(p.c.r, p.c.g, p.c.b, p.c.a);
        glVertex2f(p.x, p.y);
        glEnd();
    }
}

//Dessine tous les rectangles
GLvoid draw_rectangles(vector<rectangle> rectangles) {

    for (rectangle& r : rectangles) {
        glMatrixMode(GL_MODELVIEW);
        glColor4f(r.c.r, r.c.g, r.c.b, r.c.a);
        glRectf(r.hg.x, r.hg.y, r.bd.x, r.bd.y);


        if (r.epaisseur != 0) {
            glColor4f(1, 1, 1, 0);
            glRectf(r.hg.x + r.epaisseur, r.hg.y + r.epaisseur, r.bd.x - r.epaisseur, r.bd.y - r.epaisseur);
        }
        glEnd();
    }
};

//Dessine tous les cercles
GLvoid draw_circles(vector<cercle> cercles) {

    for (cercle c : cercles) {
        glMatrixMode(GL_MODELVIEW);
        glColor4f(c.c.r, c.c.g, c.c.b, c.c.a);
        GLUquadric *obj;
        obj = gluNewQuadric();
        glTranslatef(c.o.x, c.o.y,0);
        if (c.epaisseur != 0) {
            gluDisk(obj, 0, c.r, 0, 0);
        }
        else {
            gluDisk(obj, c.r - c.epaisseur, c.r, 0, 0);
        }
        glEnd();
    }
};