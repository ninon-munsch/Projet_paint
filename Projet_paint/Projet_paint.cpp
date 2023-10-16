#include <Windows.h>
#include <iostream>

#include<gl/GL.h>
#include<GLUT.H>

#include "Interface.h"
#include "Stockage.h"
using namespace std;

GLboolean boutonClick = false;
double x_draw, y_draw;

//Mode de dessin. O = pinceau, 1 = rectangle, 2 = cercle
int mode = 1;

//Initialisation des vecteurs de stockage
vector<point> points;
vector<rectangle> rectangles;
vector<cercle> cercles;

// Variable temporaire pour dessiner les formes
rectangle r;
cercle ce;

// Taille de la fenêtre
int windowW = 1500;
int windowH = 900;
float focale = 65.0f;
float nearW = 0.1f;
float farW = 100.0f;

//Caraxtéristiques graphiques
couleur c;
float taille;

// Déclarations des fonctions de rappel (callbacks)
GLvoid affichage();
GLvoid clavier(unsigned char touche, int x, int y);
GLvoid souris(int bouton, int etat, int x, int y);
GLvoid deplacementSouris(int x, int y);
GLvoid redimensionner(int w, int h);

//Zone debut dessin y=100

GLboolean zonedessin(int y)
{
    return y > 100;
}

// Définition de la fonction d'affichage
GLvoid affichage() {

    // Définition de la couleur d'effacement
    // du framebuffer OpenGL
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    // Effacement du frame buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Projection
    glMatrixMode(GL_PROJECTION);

    // Resetting matrix
    glLoadIdentity();

    // Viewport
    glViewport(0, 0, windowW, windowH);

    // Vue ortho
    gluOrtho2D(0, windowW, windowH, 0);

    //Interface
    //create_icons();
 
    switch (mode) {
    case 0:
        if (boutonClick == true) {
            point p;
            p.x = x_draw;
            p.y = y_draw;
            p.c = c;
            p.size = taille;
            points.push_back(p);
        }
    break;
    case 1:
        if (boutonClick == true) {
            point p;
            p.x = x_draw;
            p.y = y_draw;
            r.c = c;
            r.epaisseur = 0;
            r.hg = p;
        }
    break;
    case 2:
        if (boutonClick == true) {
            point p;
            p.x = x_draw;
            p.y = y_draw;
            ce.c = c;
            ce.o = p;
        }
    }

    //Dessin à la souris
    

    //Dessin des formes
    draw_points(points);
    draw_rectangles(rectangles);

    // Forcer l‘affichage d‘OpenGL
    glFlush();
}

// Définition de la fonction gérant les interruptions clavier
GLvoid clavier(unsigned char touche, int x, int y) {

    // Demande a GLUT de réafficher la scene
    glutPostRedisplay();
}

// Fonction de rappel de la souris
GLvoid souris(int bouton, int etat, int x, int y) {

    if (zonedessin(y)) {
        // Test pour voir si le bouton gauche de la souris est appuyé, pour commencer à dessiner
        if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_DOWN) {
            boutonClick = true;

            x_draw = x;
            y_draw = y;
        }

        // si on relache le bouton gauche
        if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_UP) {

            switch (mode) {
            case 0 : //Dessin à la souris, si on relâche le bouton gauche on arrête de dessiner
                boutonClick = false;
                break;
            case 1 :
                if (boutonClick) {
                    r.bd.x = x;
                    r.bd.y = y;
                    rectangles.push_back(r);
                }
                
                
                boutonClick = false;
                break;
            }
        }
    }
    else {
        boutonClick = false;
    }
    glFlush();
    glutPostRedisplay();
}

GLvoid deplacementSouris(int x, int y) {
    // si le bouton gauche est appuye et qu'on se deplace, on veut dessiner des points en continu
    if (zonedessin(y) && boutonClick) {
        switch (mode) {
        case 0:
            x_draw = x;
            y_draw = y;
            break;
        }
        
    }

    // Appeler le re-affichage de la scene OpenGL
    glFlush();
    glutPostRedisplay();
}

// Callback de redimensionnement de la fenêtre
GLvoid redimensionner(int w, int h) {
    // Garde les valeurs
    windowW = w;
    windowH = h;
    // eviter une division par 0
    if (windowH == 0)
        windowH = 1;

    float ratio = (float)windowW / (float)windowH;
    std::cout << "Ratio : " << ratio << std::endl;


    // Projection
    glMatrixMode(GL_PROJECTION);

    // Resetting matrix
    glLoadIdentity();

    // Viewport
    glViewport(0, 0, windowW, windowH);

    //Perspective
    gluPerspective(45, ratio, nearW, farW);

    // New projection matrix
    glOrtho(0, windowW, 0, windowH, -1.0, 1.0);

    // Retourne a la pile modelview
    glMatrixMode(GL_MODELVIEW);

    //Resetting model matrix
    glLoadIdentity();
    glFlush();
}

GLvoid test() {
    //c.r = 1;
    //c.g = 0;
    //c.b = 0;
    //taille = 7;
    //rectangle r;
    //r.hg.x = 200;
    //r.hg.y = 200;
    //r.bd.x = 600;
    //r.bd.y = 600;
    //r.c = c;
    //r.epaisseur = 0;
    //rectangles.push_back(r);
}

int main(int argc, char** argv)
{

    //Fonction test
    test();

    // Initialisation de GLUT
    glutInit(&argc, argv);
    // Choix du mode d'affichage (ici RVB)
    glutInitDisplayMode(GLUT_RGB);
    // Position initiale de la fenêtre GLUT
    glutInitWindowPosition(150, 100);
    // Taille initiale de la fenêtre GLUT
    glutInitWindowSize(windowW, windowH);
    // Création de la fenêtre GLUT
    glutCreateWindow("Paint");

    // Définition de la couleur d'effacement
    // du framebuffer OpenGL
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    // Effacement du frame buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Définition des fonctions de callbacks
    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);
    glutMouseFunc(souris);
    glutMotionFunc(deplacementSouris);
    glutReshapeFunc(redimensionner);

    // Lancement de la boucle infinie GLUT
    glutMainLoop();

}





