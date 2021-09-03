/*
 * moteurImpression.c
 *
 *  Created on: 14 févr. 2021
 *      Author: Yann
 */
#include "moteurImpression.h"
#include <stdio.h>
#include <stdlib.h>
#define tailleTab 2000

extern int percent;
extern int pushMouvement;
extern int posMin, posMax, i;
extern int flagImp;

/*----POUR LA TAILLE DE MES DESSINS----*/
extern int taille;
extern int nomDessinNb;

/*----TEMP A ENLEVER----*/
extern int tailleTableau;

extern int total ;
extern int colonne ;
extern int ligne;

void impressionDessin(int nbChoix)
{
	int min,max;
	/*----A terme prendra un entier en parametre----*/
	/*----Cet entier ira chercher le dessin correspondant dans un tableau----*/

	int * tabChoisis;
	tabChoisis = stockDessin(nbChoix);

	/*----DIVISION PAR 4 EN GROS CAR INT = 4 OCTETS----*/
	tailleTableau = taille;

	/*----LECTURE DE 2 EN 2 DES POSITIONS----*/
	while(i != tailleTableau )
	{
		/*----RECUPERATION DU MIN ET DU MAX----*/
		min = tabChoisis[i];
		max = tabChoisis[i+1];

		/*----ATTEINDRE EN PREMIER LIEU LE MIN----*/

		if(pushMouvement != min && posMin == 0)
		{
			pushMouvement = min;
		}
		else if(percent == min){
			/*----ON EST ARRIVE AU MIN----*/
			posMin = 1;
		}
		if(posMin == 1)
		{
			if(pushMouvement != max && posMax == 0)
			{
					pushMouvement = max;
			}
			else if(percent == max)
			{
				posMax = 1;
			}
		}
		if(posMin == 1 && posMax == 1)
		{
			posMin = 0;
			posMax = 0;
			i = i+2;
		}
		if(i >= tailleTableau)
		{
			flagImp = 0;
			pushMouvement = 0;
			i = 0;
			break;
		}
	}
}

int * stockDessin(int dessinsChoisis)
{
	/*----ARRAY AVEC LIGNE DIFFERENTES----*/
	int *tabDessin[] = {
			(int[]){10,50,30,40,80,23,-1},
			(int[]){0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,44,66,45,66,45,66,45,66,45,66,45,66,45,66,45,66,45,66,45,66,45,66,44,66, 33,79,33,79,33,79,33,79,33,79,33,79,33,79,33,79,33,79,33,79,33,79,33,79,33,43,33,91,33,91,33,91,33,91,33,91,33,91,33,91,33,91,33,91,33,91,33,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,91,20,31,20,79,20,79,20,79,20,79,20,79,20,79,20,79,20,79,20,79,20,79,20,79,68,79,33,79,33,79,33,79,33,79,33,79,33,79,33,79,33,79,33,79,33,79,33,79,33,43,33,66,33,66,33,66,33,66,33,66,33,66,33,66,33,66,33,66,33,66,43,66,20,79,20,79,20,79,20,79,20,79,20,79,20,79,20,79,20,79,20,79,20,79,20,0,8,91,8,91,8,91,8,91,8,91,8,91,8,91,8,91,8,91,8,91,8,91,8,91,20,79,20,79,20,79,20,79,20,79,20,79,20,79,20,79,20,79,20,79,20,79,20,79,20,0,20,0,20,0,20,0,20,0,20,0,20,0,20,0,-1},
	};
	for(int i = 0; tabDessin[dessinsChoisis][i] != -1 ; i++)
	{
		taille = taille +1;
	}
	/*----UNE FOIS QUE L'ON CONNAIT LA TAILLE----*/
	int *tabRetour = malloc(taille*sizeof(int));
	for(int i = 0; i<taille; i++)
	{
		tabRetour[i] = tabDessin[dessinsChoisis][i];
	}
	return tabRetour;
}
