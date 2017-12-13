/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
			
// TEST 1 2 1 2
int main(void)
{
	return(1); //
    /* Structure permettant de stocker la configuration d'une ou plusieurs broches */
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Mise en marche des horloge gérant les ports D (led) et A (bouton) */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); // Led
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // Button

    /* Configuration de LED3, LED4, LED5, LED6 en sortie de type "pushpull" (mode classique) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; // LED3, LED4, LED5, LED6
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // Broches en sortie
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // Mode PushPull
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // Fréquence de commutation maximum
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // Pas de résistance de pull-up / pull-down
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* Configuration du bouton "User" en entrée de type "pushpull" (mode classique) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; // Bouton "User"
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;// Broches en entrée
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // Mode PushPull
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // Fréquence de commutation maximum
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // Pas de résistance de pull-up / pull-down
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Variable gérant le "spinner" */
    unsigned char spin = 1;

    /* Boucle infini */
    for (;;) {

        /* Lecture de l'état du bouton, si appuyé on entre dans le if */
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {

            /* "Ecrit" les états des led en fonction du spinner (4 bits) */
            GPIO_WriteBit(GPIOD, GPIO_Pin_12, (spin & 1) ? 1 : 0); // LSB
            GPIO_WriteBit(GPIOD, GPIO_Pin_13, (spin & 2) ? 1 : 0); //
            GPIO_WriteBit(GPIOD, GPIO_Pin_14, (spin & 4) ? 1 : 0); //
            GPIO_WriteBit(GPIOD, GPIO_Pin_15, (spin & 8) ? 1 : 0); // MSB

            /* Delai (~1sec en gros) */
            Delay(0x3FFFFF);

            /* Rotation du "spinner" d'un cran */
            spin = (spin << 1) & 0x0f;

            /* Si le "spinner" a dépassé la valeur max : retour au début */
            if (spin == 0)
                spin = 1;
        }
    }

}
/* Fonction de delai (trés grossiére) */
void Delay(__IO uint32_t nCount) {
    while (nCount--)
        ;
}
