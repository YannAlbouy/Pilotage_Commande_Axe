/*
 * i2c_lcd.c
 *
 *  Created on: Feb 9, 2021
 *      Author: Yann
 */
#include "i2c_lcd.h"
#include "libBouton.h"
#include "moteurImpression.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*----Bouton choix affichage----*/
extern int pushInterface;
extern int onePushInterface;
/*----Position glissiere----*/
extern int percent;

/*----Pourcentage à afficher----*/
extern char mot[4];

/*----Taille de ce qu'on veut afficher----*/
extern int lengthTab;

/*----BLOQUER / DEBLOQUER BOUTONS----*/
extern int onePushDroit;
extern int onePushGauche;
extern int buttonPosition;
extern int onePushInc;
extern int onePushDec;
extern int onePushValide;
extern int refresh;
extern int buttonValide;

/*----NOM DU DESSIN----*/
extern int nomDessinNb;

/*----FLAG POUR L'IMPRESSION---*/
extern int flagImp;
extern int taille;
/*----A ENLEVER A LA FIN ---*/
extern int reste;
extern int placeVide;
/*----Stockage nom du dessin----*/
extern char nomRecu;
/*----------Adresse de mon ecran LCD sur I2C----------*/
#define LCD_ADD 0x00 <<1

#define NBDESSINS 2
extern I2C_HandleTypeDef hi2c1;

void lcd_clear(void)
{
	uint8_t cmdLCDCLEAR[2]={0x1B, 0x43};
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdLCDCLEAR,2,100);
	HAL_Delay(15);
}

/*----Affichage de la postion de la glissiere----*/
void lcd_Position()
{
	boutonInterface();
	boutonDecrement();
	boutonIncrement();
	uint8_t carreNoir[1]={0xFF};
	uint8_t space[1]={0xFE};

	/*----AFFICHAGE DE LA POSITION EN FONCTION DU POURCENTAGE----*/
	int adresses[20] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13};

	/*----DESACTIVER LE CURSEUR----*/
	uint8_t cmdCursOFF[2]={0x1B, 0x73};
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdCursOFF,2,100);
	HAL_Delay(1);
	/*----TAILLE DE CE QU'ON AFFICHE----*/

	/*----AFFICHAGE DE LA PREMIERE LIGNE DE L'ECRAN LCD----*/
	HAL_I2C_Mem_Write(&hi2c1,LCD_ADD,0x01,1,carreNoir,1,100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,carreNoir,1,100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,carreNoir,1,100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,carreNoir,1,100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,carreNoir,1,100);
	HAL_Delay(1);
	/*----Deplacement pour ecriture----*/
	uint8_t cmdTPEcriture1[4]={0x1B, 0x4C, 0x06, 0x00};
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdTPEcriture1,4,100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,(uint8_t *) "POSITION ",9,100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,carreNoir,1,100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,carreNoir,1,100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,carreNoir,1,100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,carreNoir,1,100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,carreNoir,1,100);
	HAL_Delay(1);


	/*----ECRITURE SUR L'ECRAN DU POURCENTAGE----*/
	if(percent == 0)
	{
		/*----DEPLACE A LA POSITION VOULUE----*/
		uint8_t cmdTPECRIREMOT[4]={0x1B, 0x4C, 0x08, 0x03};
		HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdTPECRIREMOT,4,100);
		HAL_Delay(1);
		/*----SPACE AND SPACE----*/
		HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,space,1,100);
		HAL_Delay(1);
		HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,space,1,100);
		HAL_Delay(1);
		HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD, (uint8_t *)"0",1,100);
		HAL_Delay(1);
		/*----AUCUNE BARRE A L'ECRAN----*/
		uint8_t cmdTVIDE[5]={0x1B, 0x4C, adresses[0], 0x02, 0xFE};
		HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdTVIDE,5,100);
		HAL_Delay(1);

	}
	else{
		if(lengthTab == 1)
			{
				/*----DEPLACE A LA POSITION VOULUE----*/
				uint8_t cmdTPECRIREMOT[4]={0x1B, 0x4C, 0x08, 0x03};
				HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdTPECRIREMOT,4,100);
				HAL_Delay(1);
				/*----SPACE AND SPACE----*/
				HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,space,1,100);
				HAL_Delay(1);
				HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,space,1,100);
				HAL_Delay(1);
				HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD, (uint8_t *)mot,lengthTab,100);
				HAL_Delay(1);
			}
			else if(lengthTab == 2)
			{
				uint8_t cmdTPECRIREMOT[4]={0x1B, 0x4C, 0x08, 0x03};
				HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdTPECRIREMOT,4,100);
				HAL_Delay(1);
				HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,space,1,100);
				HAL_Delay(1);
				HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD, (uint8_t *)mot,lengthTab,100);
				HAL_Delay(1);
			}
			else if(lengthTab == 3)
			{
				uint8_t cmdTPECRIREMOT[4]={0x1B, 0x4C, 0x08, 0x03};
				HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdTPECRIREMOT,4,100);
				HAL_Delay(1);
				HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD, (uint8_t *)mot,lengthTab,100);
				HAL_Delay(1);
			}
	}

	uint8_t cmdTPPOURCENTAGE[5]={0x1B, 0x4C, 0x0B, 0x03, 0x25};
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdTPPOURCENTAGE,5,100);
	HAL_Delay(1);

	/*----MISE EN PLACE BARRE DE POSTION DE LA GLISSIERE----*/

	/*----CREATION DES BLOCKS DE CHARGEMENT----*/
	uint8_t cmdOnePercent[13]={0x1B, 0x44,0x08, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10};
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdOnePercent,13,100);
	HAL_Delay(1);

	uint8_t cmdTwoPercent[13]={0x1B, 0x44,0x09, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18};
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdTwoPercent,13,100);
	HAL_Delay(1);

	uint8_t cmdThreePercent[13]={0x1B, 0x44,0x0A, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C};
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdThreePercent,13,100);
	HAL_Delay(1);

	uint8_t cmdFourPercent[13]={0x1B, 0x44,0x0B, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E};
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdFourPercent,13,100);
	HAL_Delay(1);

	/*----Nous donne un résultat compris entree 0 et 20 soit le nombre de pixels de l'écran----*/
	int i = percent / 5;
	/*----Reste sera compris entre 1 et 4----*/
	reste = percent - ( i * 5 );
	/*----DEPLACEMENT A L'ENDROIT VOULU POUR METTRE LES BLOCS----*/

	for(int j = 0; j<i ;j++)
	{
		/*----AFFICHAGE DES DIZAINES POUR LES POURCENTAGES----*/
		uint8_t cmdTPPOURCENTAGE[5]={0x1B, 0x4C, adresses[j], 0x02, 0xFF};
		HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdTPPOURCENTAGE,5,100);
		HAL_Delay(1);
	}


	/*----MISE EN BLANC DE CE QUI RESTE----*/

	/*----C'EST LE NBR DE CARRE VIDE QU'IL Y A----*/
	placeVide = 20-i;
	/*----ON FAIT i+1 SINON CLIGNOTEMENT CARRE EN [0x00,0x12]----*/
	for(int j = i+1; j<20;j++)
	{
		uint8_t cmdPOURCENTVIDE[5]={0x1B, 0x4C, adresses[j], 0x02, 0xFE};
		HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdPOURCENTVIDE,5,100);
		HAL_Delay(1);
	}

	/*----AFFICHAGE DES UNITES POUR LES POURCENTAGES----*/
	int adressesUnite[4] = {0x08, 0x09, 0x0A, 0x0B};
	if(reste > 0)
	{
		/*----ON AFFICHE L'UNITE CORRESPONDANTE----*/
		uint8_t cmdTPPOURCENTAGE[5]={0x1B, 0x4C, adresses[i], 0x02, adressesUnite[reste-1]};
		HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdTPPOURCENTAGE,5,100);
		HAL_Delay(1);
	}



}

void impression()
{
	uint8_t carreNoir[1]={0xFF};

	/*----NOM DES DESSINS----*/
	char tabNom[NBDESSINS][10] = {
			"Poisson",
			"Dessin2"
	};
	char dest[10] = "";
	strcat(dest, tabNom[nomDessinNb]);

	/*----CHOIX IMPRESSION----*/
	/*----NE SURTOUT PAS ENLEVER MEME SI EST CONSIDERER COMME UNUSED----*/
	int numDessin = 0;

	/*----Bouton que j'utilise----*/
	boutonDroit();
	boutonGauche();
	boutonValide();

	/*----TEST----*/
	if(refresh == 0)
	{
		lcd_clear();
		refresh = 1;
	}

	/*----DESACTIVER LE CURSEUR----*/
	uint8_t cmdCursOFF[2]={0x1B, 0x73};
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdCursOFF,2,100);
	HAL_Delay(1);

	/*----INTERFACE----*/
	HAL_I2C_Mem_Write(&hi2c1,LCD_ADD,0x01,1,carreNoir,1,100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,carreNoir,1,100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,carreNoir,1,100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,carreNoir,1,100);
	HAL_Delay(1);

	/*----Deplacement pour ecriture----*/
	uint8_t cmdTPEcriture1[4]={0x1B, 0x4C, 0x05, 0x00};
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdTPEcriture1,4,100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,(uint8_t *) "IMPRESSION ",11,100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,carreNoir,1,100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,carreNoir,1,100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,carreNoir,1,100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,carreNoir,1,100);
	HAL_Delay(1);

	/*----AJOUT DES FLECHES SUR L'ECRAN----*/
	uint8_t cmdTPFLECHEG[5]={0x1B, 0x4C, 0x01, 0x02,0x7F};
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdTPFLECHEG,5,100);
	HAL_Delay(1);
	uint8_t cmdTPFLECHED[5]={0x1B, 0x4C, 0x12, 0x02,0x7E};
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdTPFLECHED,5,100);
	HAL_Delay(1);

	/*----CREATION DE MA PORTE DE SORTIE----*/
	uint8_t cmdPixPorte[13]={0x1B, 0x44,0x08, 0x1F, 0x11, 0x11, 0x11, 0x1F, 0x1D, 0x1F, 0x1F};
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdPixPorte,13,100);
	HAL_Delay(1);

	/*----AJOUT DE LA PORTE DE SORTIE----*/
	uint8_t cmdTPPorte[5]={0x1B, 0x4C, 0x0C, 0x03, 0x08};
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdTPPorte,5,100);
	HAL_Delay(1);

	/*----AJOUT SIGNE VALIDER----*/
	uint8_t cmdTPVALID[5]={0x1B, 0x4C, 0x08, 0x03,0x76};
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdTPVALID,5,100);
	HAL_Delay(1);

	/*----CREATION DE MA FLECHE----*/
	uint8_t cmdPixFleche[13]={0x1B, 0x44,0x0D, 0x04, 0x0A, 0x15, 0x04, 0x04, 0x04, 0x00, 0x00};
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdPixFleche,13,100);
	HAL_Delay(1);

	/*----AFFICHAGE NOM DU DESSIN----*/
	/*----DEPLACEMENT POUR METTRE TEXTE DESSIN----*/
	uint8_t cmdTPTxtDessin[4]={0x1B, 0x4C, 0x07, 0x02};
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdTPTxtDessin,4,100);
	HAL_Delay(1);
	/*----ECRITURE----*/
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD, (uint8_t *)dest,strlen(dest),100);
	HAL_Delay(1);

	/*----TABLEAU ADRESSES----*/
	int adresse[4] = {0x01, 0x07, 0x0B, 0x012};

	/*----PLACER LE CURSEUR EN FONCTION DU CHOIX----*/
	if(buttonPosition>=0 && buttonPosition<=3)
	{
			if(buttonPosition == 1 || buttonPosition == 2)
			{
				/*----EN FACE DU BOUTON DE LANCEMENT DE L'IMPRESSION----*/
				uint8_t cmdTPFLECHESELECT[5]={0x1B, 0x4C, adresse[buttonPosition], 0x03,0x7E};
				HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdTPFLECHESELECT,5,100);
				HAL_Delay(1);
			}
			else{
				uint8_t cmdTPFLECHESELECT[5]={0x1B, 0x4C, adresse[buttonPosition], 0x03,0x0d};
				HAL_I2C_Master_Transmit(&hi2c1,LCD_ADD,cmdTPFLECHESELECT,5,100);
				HAL_Delay(1);
			}
	}
	else if(buttonPosition<0){
		/*----FAIRE LE TOUR COMPLET----*/
		buttonPosition = 3;
	}
	else{
		/*----SINON ON RETOURNE AU DEBUT----*/
		buttonPosition = 0;
	}

	/*----VERIFICATION CHOIX DESSIN----*/
	if(nomDessinNb> NBDESSINS -1)
	{
		nomDessinNb = 0;
	}
	else if(nomDessinNb<0)
	{
		nomDessinNb = NBDESSINS-1;
	}

	if(buttonValide == 1)
	{
		if(buttonPosition == 0)
		{
			/*----REVENIR VERS 1 POUR LE CHOIX DE L'IMPRESSION----*/
			nomDessinNb = nomDessinNb - 1;
			buttonValide = 0;
		}
		else if(buttonPosition == 1)
		{
			/*----LANCER L'IMPRESSION----*/
			impressionDessin(nomDessinNb);
			buttonValide = 0;
			taille = 0;
		}
		else if(buttonPosition == 2)
		{
			/*----QUITTER MODE IMPRESSION----*/
			buttonValide = 0;
			buttonPosition = 0;
			refresh = 0;
			pushInterface = 0;
			lcd_clear();
		}
		else if(buttonPosition == 3)
		{
			/*----ALLER VERS +1 POUR LE CHOIX DE L'IMPRESSION----*/
			nomDessinNb = nomDessinNb +1;
			buttonValide = 0;
		}
	}
}
