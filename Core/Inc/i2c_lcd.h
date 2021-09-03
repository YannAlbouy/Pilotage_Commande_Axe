/*
 * i2c_lcd.h
 *
 *  Created on: Feb 9, 2021
 *      Author: Yann
 */

#ifndef INC_I2C_LCD_H_
#define INC_I2C_LCD_H_
#include "stm32f4xx_hal.h"

void lcd_clear(void);

/*----Affichage de la postion de la glissiere----*/
void lcd_Position();

/*----Interface que l'utilisateur verra pour l'impression----*/
void impression();
#endif /* INC_I2C_LCD_H_ */
