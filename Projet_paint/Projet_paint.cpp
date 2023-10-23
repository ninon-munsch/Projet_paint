#include <Windows.h>
#include <iostream>

#include<gl/GL.h>
#include<GLUT.H>

#include "Interface.h"
#include "Stockage.h"
#include "Forme.h"
using namespace std;

GLboolean boutonClick = false;
double x_draw, y_draw;
vector<Icone> ico_coul=create_icons_coul();      //vecteur des icones de couleurs
vector<Icone> ico_forme = create_icons_forme();
//Mode de dessin. O = pinceau, 1 = rectangle, 2 = cercle

int mode = 3;
bool supp = false;
//Initialisation des vecteurs de stockage

vector<Icone> palette = create_slide();

//Initialisation du vecteur de stockage
vector<Forme> stockage;

// Variable temporaire pour dessiner les formes
vector<point> clicks;

// Taille de la fenêtre
int windowW = 1500;
int windowH = 900;
float focale = 65.0f;
float nearW = 0.1f;
float farW = 100.0f;

//Caraxtéristiques graphiques
couleur c; // couleur a modifier
float taille;

// Déclarations des fonctions de rappel (callbacks)
GLvoid affichage();
GLvoid clavier(unsigned char touche, int x, int y);
GLvoid souris(int bouton, int etat, int x, int y);
GLvoid deplacementSouris(int x, int y);
GLvoid redimensionner(int w, int h);

//Zone debut dessin y=110

GLboolean zonedessin(int y)
{
    return y > 110;
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
    if (zonedessin(y_draw)) {
        switch (mode) {
        case 0:
            if (boutonClick == true) {
                clicks.push_back(npoint(x_draw, y_draw));
                clicks[0].c = c;
                stockage.push_back(Forme(0, taille, clicks));
            }
            break;
        case 1:
            if (boutonClick == true && clicks.empty()) {
                clicks.push_back(npoint(x_draw, y_draw));
                clicks[0].c = c;
            }
            break;
        case 2:
            if (boutonClick == true && clicks.empty()) {
                clicks.push_back(npoint(x_draw, y_draw));
                clicks[0].c = c;
            }
            break;
        case 3:
            if (boutonClick == true && clicks.empty()) {
                clicks.push_back(npoint(x_draw, y_draw));
                clicks[0].c = c;

            }
        }
    }

    if (supp) 
    {
        stockage.clear();
        supp = false;
    }
    //Dessin à la souris
    
    //Dessin des icônes

    draw_colors(ico_coul);
     
    //Dessin des formes
    for (Forme f : stockage) {
        f.draw_form();
    }
    coul_actu(c);
    //Dessin des icônes
    draw_colors(ico_coul);
    draw_colors(palette);
    curseur_palette(c);
    draw_forme(ico_forme);
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

    //test en cas de clic sur une icone couleur
    if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_DOWN) 
    {
        for (int i = 0; i < ico_coul.size(); i++)
        {
            if (ico_coul[i].est_sur(x, y))
            {
                c = ico_coul[i].getC();
            }
        }
        for (int i = 0; i < palette.size(); i++)
        {
            if ((palette[i].est_sur(x, y)) && (i == 0))
            {
                c.r = (x - 210.0) / 255.0;
            }
            if ((palette[i].est_sur(x, y)) && (i == 1))
            {
                c.g = (x - 210.0) / 255.0;
            }

            if ((palette[i].est_sur(x, y)) && (i == 2))
            {
                c.b = (x - 210.0) / 255.0;
            }
        }
        for (int i = 0; i < ico_forme.size(); i++)
        {
            if (ico_forme[i].est_sur(x, y))
            {
                mode = ico_forme[i].getM();
            }
        }
    }

    if (zonedessin(y))
    {
        // Test pour voir si le bouton gauche de la souris est appuyé, pour commencer à dessiner
        if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_DOWN) {
            boutonClick = true;

            x_draw = x;
            y_draw = y;
        }

        // si on relache le bouton gauche
        if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_UP)
        {

            switch (mode) {
            case 0: //Dessin à la souris, si on relâche le bouton gauche on arrête de dessiner
                boutonClick = false;
                break;
            case 1:
                if (boutonClick) {
                    clicks.push_back(npoint(x, y));
                    stockage.push_back(Forme(1, taille, clicks));
                }
                boutonClick = false;
                break;
            case 2:
                if (boutonClick) {
                    clicks.push_back(npoint(x, y));
                    stockage.push_back(Forme(2, taille, clicks));
                }
                boutonClick = false;
                break;
            case 3:
                if (boutonClick) {
                    clicks.push_back(npoint(x, y));
                    stockage.push_back(Forme(3, taille, clicks));
                }
                boutonClick = false;
            }
        }
    }
        else {
        if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_DOWN) {
            boutonClick = true;
            clicks.clear();
        }
        if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_UP)
        {
            boutonClick = false ; 
            clicks.clear();
        }
        }

    
   
       
    

    glFlush();
    glutPostRedisplay();
}

GLvoid deplacementSouris(int x, int y) {
    // si le bouton gauche est appuye et qu'on se deplace, on veut dessiner des points en continu
    if (not(zonedessin(y))) {
        clicks.clear();
    }
    if (zonedessin(y) && boutonClick) {
        switch (mode) {
        case 0:
            x_draw = x;
            y_draw = y;
            break;
        }
        
    }
    if (boutonClick){
    for (int i = 0; i < palette.size(); i++)
    {
        if ((palette[i].est_sur(x, y)) && (i == 0))
        {
            c.r = (x - 210.0) / 255.0;
        }
        if ((palette[i].est_sur(x, y)) && (i == 1))
        {
            c.g = (x - 210.0) / 255.0;
        }

        if ((palette[i].est_sur(x, y)) && (i == 2))
        {
            c.b = (x - 210.0) / 255.0;
        }
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
    //glMatrixMode(GL_MODELVIEW);
    //glColor4f(0, 0, 0, 0);
    //GLUquadric* obj;
    //obj = gluNewQuadric();
    //glTranslatef(600,600, 0);
    //gluDisk(obj, 0, 100, 0, 0);
}

int main(int argc, char** argv)
{
    //create_icons();
    //Fonction test
    //test();
    
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





