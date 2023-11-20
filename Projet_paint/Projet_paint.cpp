#include <Windows.h>
#include <iostream>
#include<gl/GL.h>
#include<GLUT.H>
#include<string>
#include "Interface.h"
#include "Stockage.h"
#include "Forme.h"
#include"texte.h"
using namespace std;

GLboolean boutonClick = false;
GLboolean boutonClickZ = false;
GLboolean writing = false;
double x_draw, y_draw;

//Mode de dessin. O = pinceau, 1 = rectangle, 2 = cercle, 3= triangle, 4= Texte
int mode = 4;

bool supp = false;

//Initialisation des vecteurs d'icones
vector<Icone> palette = create_slide();
vector<Icone> ico_coul = create_icons_coul();      //vecteur des icones de couleurs
vector<Icone> ico_forme = create_icons_forme();
Icone ico_size = create_icon_size();
vector<Icone> ico_funcs = create_icons_funcs();
double x_text, y_text;//coordonnées pour mettre le texte a jour avec des clics (probablement pas necessaire)
vector<Texte> tex; //vecteur contenant les textes à afficher
vector < char > texte_temp;//variable temporaire pour le texte en cours de création

//Initialisation du vecteur de stockage
vector<Forme> stockage;
vector<Forme> corbeille; //permet de stocker les éléments récemment annulés

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
 
    //Valeurs par défaut
    glPointSize(1);

     //DESSIN
    switch (mode) {
    case 0: //Points
        if (boutonClickZ== true) {
            clicks.push_back(npoint(x_draw, y_draw));
            clicks[0].c = c;
            stockage.push_back(Forme(0, taille, clicks));
        }
    break;
    case 1: //Rectangles
        if (boutonClickZ == true && clicks.empty()) {
            clicks.push_back(npoint(x_draw, y_draw));
            clicks[0].c = c;
        }
    break;
    case 2: //Cercles
        if (boutonClickZ == true && clicks.empty()) {
            clicks.push_back(npoint(x_draw, y_draw));
            clicks[0].c = c;
        }
        break;
    case 3: //Triangles
        if (boutonClickZ == true && clicks.empty()) {
            clicks.push_back(npoint(x_draw, y_draw));
            clicks[0].c = c;
            
        }
        break;

    }
    if (supp) 
    {
        stockage.clear();
        supp = false;
    }
     
    //Dessin des formes
    for (Forme f : stockage) {
        f.draw_form();
    };

    //Actualisation de la couleur
    coul_actu(c);

    //Dessin des icônes
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    draw_colors(ico_coul);
    draw_colors(palette);
    curseur_palette(c);
    draw_forme(ico_forme);
    draw_size(ico_size);
    curseur_size(taille);
    draw_forme(ico_funcs);

    //dessine les textes
    Texte(c, npoint(x_text, y_text), texte_temp).draw_text();
    draw_texts(tex);

    // Forcer l‘affichage d‘OpenGL
    glFlush();
}

// Définition de la fonction gérant les interruptions clavier
GLvoid clavier(unsigned char touche, int x, int y) 
{
    if (writing)
    {
        if (touche == 13||mode!=4)
        {
            writing = false;
            tex.push_back(Texte(c,npoint(x_text,y_text), texte_temp));
            texte_temp.clear();  
        }
        else if (touche==8 && !texte_temp.empty())
        {
            texte_temp.pop_back();
               Texte(c, npoint(x_text, y_text), texte_temp).draw_text();
        }
        else
        {
            texte_temp.push_back(touche);
            Texte(c, npoint(x_text, y_text), texte_temp).draw_text();
        }
    }
    // Demande a GLUT de réafficher la scene
    glutPostRedisplay();
}

// Fonction de rappel de la souris
GLvoid souris(int bouton, int etat, int x, int y) {

    //test en cas de clic sur une icone
    if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_DOWN) 
    {
        for (int i = 0; i < ico_coul.size(); i++)
        {
            if (ico_coul[i].est_sur(x, y))
            {
                c = ico_coul[i].getC();
            }
        }
        if (ico_size.est_sur(x, y)) {
            taille = (x - 500)/20;
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
        if (ico_funcs[0].est_sur(x, y)) {
            if (!stockage.empty()) {
                if ((stockage.back().getF().size() == 1) && (stockage.size() != 1)) {
                    while ((stockage.back().getF().size() == 1) && (stockage.size() != 1)) {
                        stockage.pop_back();
                    }
                }
                else {
                    stockage.pop_back();
                }
            }
        }
    }

    if (zonedessin(y))
    {
        // Test pour voir si le bouton gauche de la souris est appuyé, pour commencer à dessiner
        if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_DOWN) {
            boutonClickZ = true;

            x_draw = x;
            y_draw = y;

        }

        // si on relache le bouton gauche
        if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_UP)
        {

            switch (mode) {
            case 0: //Dessin à la souris, si on relâche le bouton gauche on arrête de dessiner
                boutonClickZ = false;
                break;
            case 1:
                if (boutonClickZ) {
                    clicks.push_back(npoint(x, y));
                    stockage.push_back(Forme(1, taille, clicks));
                }
                boutonClickZ = false;
                break;
            case 2:
                if (boutonClickZ) {
                    clicks.push_back(npoint(x, y));
                    stockage.push_back(Forme(2, taille, clicks));
                }
                boutonClickZ = false;
                break;
            case 3:
                if (boutonClickZ) {
                    clicks.push_back(npoint(x, y));
                    stockage.push_back(Forme(3, taille, clicks));
                }
                boutonClickZ = false;
                break;
            case 4:
                if (boutonClickZ) {
                    writing = true;
                    x_text = x;
                    y_text = y;
                    
                }
                boutonClickZ = false;
                break;
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
    if (zonedessin(y) && boutonClickZ) {
        switch (mode) {
        case 0:
            x_draw = x;
            y_draw = y;
            break;
        }
    }
    if (boutonClick){
        if (ico_size.est_sur(x, y)) {
            taille = (x - 500) / 20;
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

    clicks.clear();
    // Lancement de la boucle infinie GLUT
    glutMainLoop();

}





