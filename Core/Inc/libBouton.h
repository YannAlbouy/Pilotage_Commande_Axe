/*
 * libBouton.h
 *
 *  Created on: Feb 15, 2021
 *      Author: Yann
 */

#ifndef INC_LIBBOUTON_H_
#define INC_LIBBOUTON_H_

#include "stm32f4xx_hal.h"

/*----PASSER D'UNE INTERFACE A L'AUTRE----*/
void boutonInterface();

/*----PERMET DE DEPLACER LE CURSEUR VERS LA DROITE DANS L'INTERFACE IMPRESSION----*/
void boutonDroit();

/*----PERMET DE DEPLACER LE CURSEUR VERS LA GAUCHE DANS L'INTERFACE IMPRESSION----*/
void boutonGauche();

/*----DEPLACER LA GLISSIERE VERS 0----*/
void boutonDecrement();

/*----DEPLACER LA GLISSIERE VERS 100----*/
void boutonIncrement();

/*----VALIDER LE CHOIX DE L'UTILISATEUR----*/
void boutonValide(void);
#endif /* INC_LIBBOUTON_H_ */
