/*
 * moteurImpression.h
 *
 *  Created on: 14 févr. 2021
 *      Author: Yann
 */

#ifndef INC_MOTEURIMPRESSION_H_
#define INC_MOTEURIMPRESSION_H_

#include "stm32f4xx_hal.h"

/*----Fonction qui vas faire le dessin----*/
void impressionDessin(int);

/*----Stockage des coordonnées des dessins----*/
int* stockDessin(int dessinsChoisis);
#endif /* INC_MOTEURIMPRESSION_H_ */
