/*
 * libBouton.c
 *
 *  Created on: Feb 15, 2021
 *      Author: Yann
 */
#include "libBouton.h"
#include "i2c_lcd.h"

/*----VARIABLES EXTERNES----*/
extern int onePushInterface;
extern int pushInterface;
extern int onePushDroit;
extern int onePushGauche;
extern int buttonPosition;
extern int onePushInc;
extern int pushMouvement;
extern int onePushDec;
extern int onePushValide;
extern int buttonValide;
void boutonInterface()
{
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == 1 && onePushInterface == 0)
	{
		lcd_clear();
		onePushInterface++;
		pushInterface = pushInterface +1;
	}
	else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == 0)
	{
		/*----ON RELACHE LE SEMAPHORE----*/
		onePushInterface = 0;
	}
}
void boutonDroit()
{
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) == 1 && onePushDroit == 0)
	{
		lcd_clear();
		/*----RECUPERE VALEUR A MOMENT T----*/
		onePushDroit++;
		buttonPosition = buttonPosition - 1;
	}
	else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) == 0){
		onePushDroit = 0;
	}
}
void boutonGauche()
{
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == 1 && onePushGauche == 0)
	{
		lcd_clear();
		/*----RECUPERE VALEUR A MOMENT T----*/
		onePushGauche ++;
		buttonPosition = buttonPosition +1;

	}
	else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == 0){
		onePushGauche = 0;
	}
}
void boutonIncrement()
{
	/*----Incrementation----*/
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == 1 && onePushInc == 0)
	{
		/*----ON SE SERT LARGEMENT DU SEMAPHORE----*/
		onePushInc ++;
		if(pushMouvement == 100)
		{
			pushMouvement = 99;
		}
		else{
				pushMouvement = pushMouvement +1;
		}
	}
	else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == 0){
		/*----ON RELACHE LE SEMAPHORE----*/
		onePushInc = 0;
	}
}
void boutonDecrement()
{
	/*----Decremente----*/
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) == 1 && onePushDec == 0 )
	{
		/*----ON SE SERT LARGEMENT DU SEMAPHORE POUR NOTRE TACHE----*/
		onePushDec ++;
		/*----EMPECHER LA DECREMENTATION NEGATIVE----*/
		if(pushMouvement== 0 )
		{
			pushMouvement = 0;
		}
		else
		{
			pushMouvement = pushMouvement -1;
		}
	}
	else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) == 0){
		/*----ON RELACHE LE SEMAPHORE----*/
		onePushDec = 0;
	}
}
void boutonValide(void)
{
	/*LIRE LE PIN ET LE ONEPUSH2 POUR SAVOIR SI ON CLIC*/
	/*ON A DONC UNE DOUBLE CLE POUR EVITER L'APPUI CONTINU*/
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == 1 && onePushValide == 0)
	{
		lcd_clear();
		onePushValide++;
		buttonValide = buttonValide +1;
	}
	else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == 0){
		onePushValide = 0;
	}
}
