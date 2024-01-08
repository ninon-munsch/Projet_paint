#include "Dessin.h"
#include "Forme.h"


GLvoid affichage();
//GLvoid remplissage(int x, int y, couleur cd, couleur cb,int width,int height, vector<point>& clicks, vector<Forme>& stockage)
//{
//	if (x>0 && y>110 && y<height &&x<width)
//	{
//		
//		couleur coul;
//		float pixel[4];
//		glReadPixels(x,abs(y-height), 1, 1, GL_RGBA, GL_FLOAT, pixel);
//		coul.r = pixel[0];
//		coul.g = pixel[1];
//		coul.b = pixel[2];
//		if (coul.r == cb.r && coul.g == cb.g && coul.b == cb.b)
//		{
//			clicks.push_back(npoint(x, y));
//			clicks[0].c = cd;
//			stockage.push_back(Forme(0, 1, clicks));
//			clicks.clear();
//			
//
//			remplissage(x + 1, y, cd, cb,width,height, clicks, stockage);
//			affichage();
//			remplissage(x - 1, y, cd, cb, width, height, clicks, stockage);
//			affichage();
//			remplissage(x, y + 1, cd, cb, width, height, clicks, stockage);
//			affichage();
//			remplissage(x, y - 1, cd, cb, width, height, clicks, stockage);
//			affichage();
//		}
//	}
//
//	return ;
//}

bool testcoul(int x, int y, int height, couleur test)
{
	couleur coul;
	float pixel[4];
	glReadPixels(x, abs(y - height), 1, 1, GL_RGBA, GL_FLOAT, pixel);
	coul.r = pixel[0];
	coul.g = pixel[1];
	coul.b = pixel[2];
	return (coul.r == test.r && coul.g == test.g && coul.b == test.b);
}

GLvoid remplissage(int x, int y, couleur cd, couleur cb, int width, int height, vector<point>& clicks, vector<Forme>& stockage)
{
	vector<point> aPeindre;
	aPeindre.push_back(npoint(x, y));
	point temp;
	int distd=1;
	int distg=1;
	couleur coulg;
	couleur could;
	while (!aPeindre.empty())
	{
		temp = aPeindre.back();
		aPeindre.pop_back();
		if (temp.x > 0 && temp.y > 110 && temp.y < height && temp.x < width)
		{
		
		
			if (testcoul(temp.x,temp.y,height,cb))
			{

				while (testcoul(temp.x-distg, temp.y, height, cb) && temp.x-distg > 0 )
				{
					/*clicks.push_back(npoint(temp.x - distg, temp.y));
					clicks[0].c = cd;
					stockage.push_back(Forme(0, 1, clicks));
					clicks.clear();*/
					if (testcoul(temp.x - distg, temp.y - 1, height, cb))
					{
						//aPeindre.push_back(npoint(temp.x - distg, temp.y - 1));
					}
					if (testcoul(temp.x - distg, temp.y + 1, height, cb) )
					{
						aPeindre.push_back(npoint(temp.x - distg, temp.y + 1));
					}
	
					distg++;

				}
				while (testcoul(temp.x+ distd, temp.y, height, cb) && temp.x + distd < width)
				{
					/*clicks.push_back(npoint(temp.x + distd, temp.y));
					clicks[0].c = cd;
					stockage.push_back(Forme(0, 1, clicks));
					clicks.clear()*/
					if (testcoul(temp.x + distd, temp.y - 1, height, cb))
					{
						//aPeindre.push_back(npoint(temp.x + distd, temp.y - 1));
					}
					if (testcoul(temp.x + distd, temp.y+1, height, cb) )
					{
						aPeindre.push_back(npoint(temp.x + distd, temp.y + 1));
					}

					
					distd++;

				}
				clicks.push_back(npoint(temp.x + distd, temp.y));
				clicks[0].c = cd;

				//clicks.clear();
				clicks.push_back(npoint(temp.x - distg, temp.y));
				stockage.push_back(Forme(0, 0, clicks));
				clicks.clear();
				//clicks.push_back(temp);
				//clicks[0].c = cd;
				//stockage.push_back(Forme(0, 1, clicks));
				//clicks.clear();
				distd = 1;
				distg = 1;
				//aPeindre.push_back(npoint(temp.x, temp.y - 1));
				aPeindre.push_back(npoint(temp.x, temp.y + 1));
				
				
			}
		}
		affichage();
	}
	return;
}
