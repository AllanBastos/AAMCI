/* Descrição:
 Implementação de uma comunicação serial simples controlada por software:
 - O pino PA0 opera em dreno aberto como pino de comunicação entre duas placas
 - Os pinos PA0 de duas placas devem ser interligados juntamente com o GND
 - Os botões K0 e K1 acionam, respectivamente, os LEDs D2 e D3 da outra placa (operação remota)
 - Há um buzzer no pino PA1 para sinalizar o envio de um dado
 - Velocidade de comunicação de 100 kbps
*/

#include "stm32f4xx.h"
#include "stdio.h"
#include "Utility.h"


int flag = 0;

void alternarLed1(){
	GPIOA->ODR ^= 1 << 6;			//alterna o estado do LED em PA6
}

void alternarLed2(){
	GPIOA->ODR ^= 1 << 7;
}

int botao1(){
	return !(GPIOE->IDR & (1 << 3));
}

int botao2(){
	return !(GPIOE->IDR & (1 << 4));
}

enviaCMD(int dado){
	USART1->DR = dado;
	flag = 0;
	Delay_ms(15);
	if(flag == 0){
		if(dado == 0){
			alternarLed1();
		}else if(dado == 1){
			alternarLed2();
		}
	}

}



void USART1_IRQHandler(void)
	{
		char recebido = USART1->DR;
		USART1->DR = 2;
//		__io_putchar(recebido);	//lê o dado e reenvia pela USART1
		if(recebido == 0){
			alternarLed1();
		}else if(recebido == 1){
			alternarLed2();
		}else if(2){
			flag = 1;
		}

	}

int main(void)
{
	Utility_Init();	//inicializa funções úteis
	USART1_Init();


	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOEEN;

	GPIOA->ODR |= (1<<7) | (1<<6);
	GPIOA->MODER |= (0b01 << 14) | (0b01 << 12);
	GPIOE->PUPDR |= (0b01 << 8) | (0b01 << 6);

	Delay_ms(100);	//aguarda sinais estabilizarem


	while(1)	//loop infinito
		{
			flag = 0;
			if(botao1())
			{
				enviaCMD(0);
				Delay_ms(10);
				while(botao1());
			}

			if(botao2())
			{
				enviaCMD(1);
				Delay_ms(10);
				while(botao2());
			}
		}
}

