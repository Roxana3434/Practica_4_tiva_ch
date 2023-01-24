/*
 * GPIO.c
 *
 *  Created on: 20/11/2022
 *      Author: Ashley Roxana Reséndiz Sánchez
 */

//Configura puerto A para usar los 6 botones como interrupciones externas 

#include "lib/include.h"
extern void Configurar_GPIO(void)

{
    //Se habilita el puerto a usar 
    SYSCTL->RCGCGPIO |=(1<<0);  //pueto A

    /*GPIOF->LOCK= 0x4C4F434B;  Es para desbloquear los puertos F, D y C que están bloqueado en la tiva ch 
    GPIOF->CR = 0x1F;           // Para permitir cambios en los pines PF4-0 */
    
    //Desabilita la función analogica del puerto, para funcionar como GPIO pag. 687
    GPIOA->AMSEL = 0x00; 

    //Indicar que los pines a trabajan como GPIO son PA7-0
    GPIOA->PCTL = 0x00000000;   

    //Para indicar que pines son entradas y cuales son salida 0 -> entrada, 1 -> salida 
    GPIOA->DIR = (0<<2) | (0<<3) | (0<<4) | (0<<5) | (0<<6) | (0<<7); // PA2 - PA7 son entradas 

    //Se desabilita la función alternativa  PA7-0
    GPIOA->AFSEL = 0x00;   

    // Para habilitar que el edo. inicial de los pines sea pull-up O pull-down pag. 678
    GPIOA->PUR = (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7);// PA2 - PA7

    //Se habilitan los pines como digitales PA5-PA0
    GPIOA->DEN = (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7);     

    //pag. 667 Se limpian los pines a los que se asocian las interrupciones para poderlas configurar 
    GPIOA -> IM |= (0<<2) | (0<<3) | (0<<4) | (0<<5) | (0<<6) | (0<<7);

    //pag. 664 Configurar que sea sensible al borde 
     GPIOA -> IS |= (0<<2) | (0<<3) | (0<<4) | (0<<5) | (0<<6) | (0<<7);

    //pag. 665 registro para indicar que el IEV va a configurar que flancos detectar
    GPIOA -> IBE |= (0<<2) | (0<<3) | (0<<4) | (0<<5) | (0<<6) | (0<<7);

    //pag. 666 Indicar con que flanco trabaja 
    GPIOA -> IEV |= (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7); //es con flanco de subida

    //pag. 668 establecer que no ha ocurrido ninguna interrupción en esos pines (edo inicial)
    GPIOA -> RIS |= (0<<2) | (0<<3) | (0<<4) | (0<<5) | (0<<6) | (0<<7);

    //PAG. 667 La interrupción del pin es enviada al controlador de interrup.
    GPIOA -> IM |= (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7);
 
    //pag. 104 Configurar la interrupción correspondiente al puerto A -> int 0
    // bloque de int. 3       2      1    0
    //              [4n+3] [4n+2] [4n+1] [4n] ---> [4n] = 0(valor de la int) : n=0
    //                FF     FF     FF    00    (los 00 indica lo que se le suma)
    NVIC -> IP[0] = (NVIC ->IP[0]&0xFFFFFF00) | 0x00000002; //0 es el numero de prioridad (n)

    // Habilitar interrupción pag. 142 
    NVIC -> ISER[0] = 0x00000001; //se pone 1 en la interrupción 0 y es ISER[0] porque no se ocupa el 2do nivel, la int. está dentro de las 19 int del 1er nivel 
}


extern void GPIOA_INT_ISR(void)
{
    if (GPIOA ->RIS == (1<<2))//A2  el DOS representara que se presiono el boton 2
    {
      //Metodo de adquisición del ADC 0 y sec. 1 
      ADC0->PSSI |= (1<<1); //se habilita el modo de configuración para sec. 1
      while((ADC0->RIS&0x02)==0){}; // *** espera a que el convertidor termine  (RIS = registro de edo. muestra el edo de la señal de interrupción sin procesar)
      Result[0] = ADC0->SSFIFO1&0xFFF; //  En el FIF01 se almacenan las muestras, por lo que se lee, pag 860
      ADC0->ISC = 0x0002;  //Conversion finalizada, se limpia para volver a convertir 
    }

    if (GPIOA ->RIS == (1<<3))//A3 el tres representara que se presiono el boton 3
    {
      //Metodo de adquisición del ADC 0 y sec. 1  
      ADC0->PSSI |= (1<<1); //se habilita el modo de configuración para sec. 1
      while((ADC0->RIS&0x02)==0){}; // *** espera a que el convertidor termine  (RIS = registro de edo. muestra el edo de la señal de interrupción sin procesar)
      Result[1] = ADC0->SSFIFO1&0xFFF; 
      ADC0->ISC = 0x0002;  //Conversion finalizada, se limpia para volver a convertir
    }

    if (GPIOA ->RIS == (1<<4))//A4 representara que se presiono el boton 4
    {
      //Metodo de adquisición del ADC 0 y sec. 1  
      ADC0->PSSI |= (1<<1); //se habilita el modo de configuración para sec. 1
      while((ADC0->RIS&0x02)==0){}; // *** espera a que el convertidor termine  (RIS = registro de edo. muestra el edo de la señal de interrupción sin procesar)
      Result[2] = ADC0->SSFIFO1&0xFFF;
      ADC0->ISC = 0x0002;  //Conversion finalizada, se limpia para volver a convertir
    }
 
    if (GPIOA ->RIS == (1<<5))//A5 representara que se presiono el boton 5
    {
      //  Metodo de adquisición del ADC 1 y sec. 2 
      ADC1->PSSI |= (1<<2); //se habilita el modo de configuración para sec. 2
      while((ADC1->RIS&0x04)==0){}; // espera al convertidor
      Result[3] = ADC1->SSFIFO2&0xFFF; //  Leer  el resultado almacenado
      ADC1->ISC = 0x0004;  //Conversion finalizada se limpia para volver a convertir

    }
    
    if (GPIOA ->RIS == (1<<6))//A6 representara que se presiono el boton 6
    {
      //  Metodo de adquisición del ADC 1 y sec. 2 
      ADC1->PSSI |= (1<<2); //se habilita el modo de configuración para sec. 2
      while((ADC1->RIS&0x04)==0){}; // espera al convertidor
      Result[4] = ADC1->SSFIFO2&0xFFF; //  Leer  el resultado almacenado
      ADC1->ISC = 0x0004;  //Conversion finalizada se limpia para volver a convertir
      
    }

    if (GPIOA ->RIS == (1<<7))//A7 representara que se presiono el boton 7
    {
      //  Metodo de adquisición del ADC 1 y sec. 3 
      ADC1->PSSI |= (1<<3); //se habilita el modo de configuración para sec. 3
      while((ADC1->RIS&0x08)==0){}; // espera al convertidor
      Result[5] = ADC1->SSFIFO3&0xFFF; //  Leer  el resultado almacenado
      ADC1->ISC = 0x0008;  //Conversion finalizada, se limpia para volver a convertir 
    }

    GPIOA ->ICR |=(1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7); //para limpiar el edo de la interrupción
}





