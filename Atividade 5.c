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
#include <stdio.h>
#include "Utility.h"

#define existeNovoDadoAleatorio (RNG->SR & RNG_SR_DRDY)

#define buscaValorAleatorio (RNG->DR)

//função principal
int main(void)
{
    Configure_Clock();                //configura o sistema de clock
    USART1_Init();
    Delay_Start();

    Delay_ms(2000);

    RCC->AHB2ENR |= RCC_AHB2ENR_RNGEN;    //habilita o clock do RNG
    RNG->CR |= RNG_CR_RNGEN;

    int i, count = 0, num_points = 1000000;
	double x, y, pi_estimate;
	printf("Iniciando estimativa de PI com MMC...\n");

    for ( i = 1; i < num_points; i++){

    	x = (double) buscaValorAleatorio / (0xFFFFFFFF);
		y = (double) buscaValorAleatorio / (0xFFFFFFFF);

		if (x * x + y * y <= 1) {

			count++;
		}


    }
    pi_estimate = 4.0 * (double) count / (double) num_points;

	printf("Estimativa de pi = %lf\n", pi_estimate);

	return 0;

}


