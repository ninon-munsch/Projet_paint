#include <Windows.h>
#include <iostream>
#include <vector>
#include "Stockage.h"

#include<gl/GL.h>
#include<GLUT.H>
using namespace std;
float ylim = 110;

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
        if ((c.o.y - c.r) > ylim) {
            glMatrixMode(GL_MODELVIEW);
            int nbreSeg = 10000; //nombre de segments définissant notre cercle
            float pi = 3.14159f;
            float theta = 2 * pi / nbreSeg;
            glBegin(GL_LINES);
            glColor4f(c.c.r, c.c.g, c.c.b, c.c.a);
            for (int i = 0; i < nbreSeg; i++) {
                glVertex3f(c.o.x + c.r * cos(i * theta), c.o.y + c.r * sin(i * theta), 0);
                glVertex3f(c.o.x - c.r * cos(i * theta), c.o.y + c.r * sin(i * theta), 0);
            }
            glEnd();
        }
        
    }
};
GLvoid draw_triangles(vector<triangle> triangles)
{
for (triangle& t : triangles) {
    glMatrixMode(GL_MODELVIEW);
    glBegin(GL_TRIANGLES);
    glColor4f(t.c.r, t.c.g, t.c.b, t.c.a);
    glVertex2f(t.so.x, t.so.y);
    glVertex2f(t.ba.x, t.ba.y);
    glVertex2f(2*t.so.x- t.ba.x, t.ba.y);
    //if (t.epaisseur != 0) {
    //    glColor4f(1, 1, 1, 0);
    //    glRectf(t.hg.x + t.epaisseur, r.hg.y + r.epaisseur, r.bd.x - r.epaisseur, r.bd.y - r.epaisseur);
    //}
    glEnd();
}
};