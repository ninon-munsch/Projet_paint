#pragma once
#include "Stockage.h"

class Element
{
protected:
	int mode;
	couleur c;
	float epaisseur;
public:
	couleur getCouleur() { return c; };
	float getEpaisseur() { return epaisseur; };
	int getMode() { return mode; }

	void setCouleur(couleur co) { c = co; };
	void setEpaisseur(float ep) { epaisseur = ep; };
	void setMode(int m) { mode=m; }

	virtual GLvoid draw()=0;
};
