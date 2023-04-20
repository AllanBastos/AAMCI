/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"            //bibliotecas padrão STM32F4
#include <stdio.h>
#include "Utility.h"        //biblioteca de funções utilitárias

#define existeNovoDadoAleatorio (RNG->SR & RNG_SR_DRDY)
//#define aguardaK (USART1->DR != "k")
#define buscaValorAleatorio (RNG->DR%6) + 1


uint8_t pontuacao_jogador= 0;
uint8_t pontuacao_computador = 0;
uint8_t rodada = 0;
uint8_t recebido = 0;

unsigned int valorAleatorioJogador;
unsigned int valorAleatorioComputador;


void USART1_IRQHandler(void)
{
	  // so pra nao ficar dando eco no terminal
	int dado = USART1->DR;
	if(dado == 'k'){
		recebido = 1;
	}
}

void analisa_ganhador(){
	if(pontuacao_jogador == 2 || pontuacao_computador == 2) {
				if (pontuacao_jogador == 2 ){
					printf("\nParabéns! Você é o vencedor da melhor de três!!!\n");
				}
				else{
					printf("\nVocê perdeu :(\n");
				}
				pontuacao_jogador = 0;
				pontuacao_computador = 0;
				rodada = 0;

				printf("-\n");
				Delay_ms(500);
				printf("-\n");
				Delay_ms(500);
				printf("-\n\n\n\n");
				Delay_ms(500);

				printf("Iniciando um novo jogo\n\n");


			}
}

void analisa_ganhador_rodada(){
	// mostrando prints em tela
			printf("Jogador: %d\n",valorAleatorioJogador);
			printf("Computador: %d\n\n",valorAleatorioComputador);

			if (valorAleatorioJogador == valorAleatorioComputador) {
				printf("--- Ocorreu empate no lançamento, ninguém pontuou\n\n");
			}

			if(pontuacao_computador > pontuacao_jogador){
				printf("%d X %d para o computador\n", pontuacao_computador, pontuacao_jogador);
			}

			else if(pontuacao_computador < pontuacao_jogador){
				printf("%d X %d para o jogador\n", pontuacao_jogador, pontuacao_computador);
			}
			else {
				printf("%d X %d jogo empatado\n", pontuacao_jogador, pontuacao_computador);
			}

			rodada++;
}

//função principal
int main(void)
{
    Configure_Clock();                //configura o sistema de clock
    USART1_Init();
    Delay_Start();

    Delay_ms(2000);

    RCC->AHB2ENR |= RCC_AHB2ENR_RNGEN;    //habilita o clock do RNG
    RNG->CR |= RNG_CR_RNGEN;            //liga o RNG

    while(1)
    {

    	if (rodada == 0) {
			printf("-------- Bem vindo ao programa de rolar dados! --------\n");
			printf("Para que o jogo inicie precisamos que você insira \"k\"\n");
		}
		else {
			printf("\n-----------------------------------------------------------------------------------------------------------\n\n");
			printf("Pressione \"k\" para a proxima rolagem de dados\n");
		}


    	while(!recebido);
    	printf("-----------------------------------------------------------------------------------------------------------\n\n");


		while(!existeNovoDadoAleatorio);

		valorAleatorioJogador = buscaValorAleatorio;
		Delay_ms(32);
		while(!existeNovoDadoAleatorio);
		valorAleatorioComputador = buscaValorAleatorio;

		if(valorAleatorioJogador > valorAleatorioComputador){
			pontuacao_jogador++;
		}
		else if(valorAleatorioJogador < valorAleatorioComputador){
			pontuacao_computador++;
		}

		analisa_ganhador_rodada();
		analisa_ganhador();
		recebido = 0;



    }

}


