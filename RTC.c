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


char dias[8][20] = {
	"",
	"segunda-feira",
	"terça-feira",
	"quarta-feira",
	"quinta-feira",
	"sexta-feira",
	"sábado",
	"domingo"
};

char meses[13][20] = {
	"",
	"janeiro",
	"fevereiro",
	"março",
	"abril",
	"maio",
	"junho",
	"julho",
	"agosto",
	"setembro",
	"outubro",
	"novembro",
	"dezembro"
};


#define DU RTC->DR & (RTC_DR_DU) //unidade do dia
#define DT (RTC->DR & (RTC_DR_DT)) >> 4 // dezena do dia
#define MU (RTC->DR & (RTC_DR_MU)) >> 8 // unidade do mes
#define MT (RTC->DR & (RTC_DR_MT)) >> 12 // dezena do mes
#define WDU ((RTC->DR & (RTC_DR_WDU)) >> 13) //Dia da Semana unidade
#define YU (RTC->DR & (RTC_DR_YU)) >> 16 // unidade ano
#define YT (RTC->DR & (RTC_DR_YT)) >> 20 // dezena ano

#define SU RTC->TR & (RTC_TR_SU) // unidade segundo
#define ST (RTC->TR & (RTC_TR_ST)) >> 4 // dezena segundo
#define MNU (RTC-> TR & (RTC_TR_MNU)) >> 8 // unidade minuto
#define MNT (RTC-> TR & (RTC_TR_MNT)) >> 12 // dezena minuto
#define HU (RTC-> TR & (RTC_TR_HU)) >> 16 // unidade hora
#define HT (RTC-> TR & (RTC_TR_HT)) >> 20 // dezena hora


#define MES (10 * ((RTC->DR & (RTC_DR_MT)) >> 12) + ((RTC->DR & (RTC_DR_MU)) >> 8))


//função principal
int main(void)
{
    Configure_Clock();                //configura o sistema de clock
    USART1_Init();
    Delay_Start();
    RTC_Config();

    //inicializando a estrutura do calendário
    RTC_Calendar.formato = 0; //definição do formato da hora (24h)
    RTC_Calendar.dia = 4; //definição do dia
    RTC_Calendar.data = 30; //definição da data (dia do mês)
    RTC_Calendar.mes = 11; //definição do mês (dezembro)
    RTC_Calendar.ano = 23; //definição do ano (2025)
    RTC_Calendar.horas = 23; //definição da hora
    RTC_Calendar.minutos = 59; //definição dos minutos
    RTC_Calendar.segundos = 55; //definição dos segundos

    RTC_SetCalendar(&RTC_Calendar); //atualização do calendário

    int registador_segundos_anteior = RTC->TR;
   	while(1) {
   		while (registador_segundos_anteior == RTC->TR);
   		registador_segundos_anteior = RTC->TR;


   		printf("Hoje é %s, %d%d de %s de 20%d%d.\n",dias[WDU], DT, DU, meses[MES], YT, YU);
   		printf("A hora atual é %d%d:%d%d:%d%d.\n\n", HT, HU, MNT, MNU, ST, SU);
   	}



	return 0;

}


