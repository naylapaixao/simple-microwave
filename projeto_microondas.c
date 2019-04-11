#include ".\projeto_microondas.h"
#include ".\visor.h"

#define linha1 PIN_B4
#define linha2 PIN_B5
#define linha3 PIN_B6
#define linha4 PIN_B7
#define coluna1 PIN_B1
#define coluna2 PIN_B2
#define coluna3 PIN_B3

char botao;
int8 i,pd,tempo;


#use delay(clock=20000000)
#int_RB
void RB_isr() 
{
   output_high(coluna1);
   output_low(coluna2);
   output_low(coluna3);
   if(input(linha1)){
      botao='1';
      goto fim;
   }
   if(input(linha2)){
      botao='4';
      goto fim;
   }
   if(input(linha3)){
      botao='7';
      goto fim;
   }
   if(input(linha4)){
      botao='*';
      goto fim;
   }
   output_low(coluna1);
   output_high(coluna2);
   output_low(coluna3);
    if(input(linha1)){
      botao='2';
      goto fim;
    }
    if(input(linha2)){
      botao='5';
      goto fim;
    }
    if(input(linha3)){
      botao='8';
      goto fim;
    }
    if(input(linha4)){
      botao='0';
      goto fim;
    }  
    output_low(coluna1);
    output_low(coluna2);
    output_high(coluna3);
    if(input(linha1)){
      botao='3';
      goto fim;
    } 
    if(input(linha2)){
      botao='6';
      goto fim;
    }   
    if(input(linha3)){
      botao='9';
      goto fim;
    }
    if(input(linha4)){
      botao='#';
      goto fim;
    }
    
    fim:
    output_high(coluna1);
    output_high(coluna2);
    output_high(coluna3);
    delay_ms(0.2);
    clear_interrupt(INT_RB);
}

void preparo();

#use delay(clock=20000000)
void main()
{

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_psp(PSP_DISABLED);
   setup_spi(FALSE);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   clear_interrupt(INT_RB);
   enable_interrupts(INT_RB);
   enable_interrupts(GLOBAL);

   // TODO: USER CODE!!
   tempo=0;
   i=0;
   pd=0;
   lcd_ini();
   delay_ms(10);
   liga_display();
   
   output_high(coluna1);
   output_high(coluna2);
   output_high(coluna3);
   
   while(true){
      preparo();
} //Fim while
}

void preparo(){
    switch(botao){
            case '1':
               pos_linha(1);
               printf(lcd_escreve,"Pipoca   ");
               pd=20;
               break;
            case '2':
                pos_linha(1);
                printf(lcd_escreve,"Brigadeiro   ");
                pd=10;
                break;
            case '3':
               pos_linha(1);
               printf(lcd_escreve,"Hot Dog   ");
               pd=15;
               break;
            case '4':
                pos_linha(1);
                printf(lcd_escreve,"Arroz   ");
                pd=40;
                break;
            case '5':
               pos_linha(1);
               printf(lcd_escreve,"Macarrao   ");
               pd=30;
               break;
            case '6':
                pos_linha(1);
                printf(lcd_escreve,"Omelete   ");
                pd=5;
                break;
            case '7':
               pos_linha(1);
               printf(lcd_escreve,"Bolo   ");
               pd=50;
               break;
            case '8':
                pos_linha(1);
                printf(lcd_escreve,"Refeicao   ");
                pd=25;
                break;
            case '9':
                pos_linha(1);
                printf(lcd_escreve,"Descongelar   ");
                pd=30;
                break; 
        	case '*':
        		if(pd !=0){
        			for(i=pd;i>0;i--){
        				pos_linha(2);
        				delay_ms(1000);
        				printf(lcd_escreve,"Tempo: %d    ",i);
        			} 
        		}
        		else{
        			pos_linha(1);
        			delay_ms(1);
        			printf(lcd_escreve,"Escolha uma opção  ");
        		}
        		break;
        	case '#':
        		pos_linha(1);
                printf(lcd_escreve,"Processo Interrompido   ");
                delay_ms(2);
                break;    		                  
      } //Fim do switch
}
