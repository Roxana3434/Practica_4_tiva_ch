#include "lib/include.h"

int main(void)
{


    char valor1[4]; //Para enviar los valores del ADC en carácteres, es de 4 porque son cuatro digitos de 4096 
    char valor2[4];
    char valor3[4];
    char valor4[4];
    char valor5[4];
    char valor6[4];

    Configurar_PLL(_20MHZ);  //**Confiuracion de velocidad de reloj
    Configura_Reg_ADC();
    Configurar_UART0();
    Configurar_GPIO();

    /*Usando el modulo 0 y 1 , configurar la tarjeta a la frecuencia asignada, para adquirir 6 señales analógicas 
    a una velocidad de 1 millón de muestras por segundo, por los canales asignados  y guardar los valores en un 
    arreglo para ser enviados con un botones  externos asociado al gpio A a través del protocolo de comunicación 
    asíncrona a una velocidad todo esto usando interrupciones.*/

    while(1)
    {   
        /*SIN INTERRUPCIONES
        ADC0_InSeq1(Result); //llamada a la conversion 
        valor1=(float)(((Result[0]))*3.3)/4096; //1
        valor2=(float)(((Result[1]))*3.3)/4096; //2
        valor3=(float)(((Result[2]))*3.3)/4096; //3

        ADC1_InSeq2(Result_2); //llamada a la conversion 
        valor4=(float)(((Result_2[0]))*3.3)/4096; //4
        valor5=(float)(((Result_2[1]))*3.3)/4096; //5

        ADC1_InSeq3(Result_3); //llamada a la conversion 
        valor6=(float)(((Result_3[0]))*3.3)/4096; //6 */
     

    }
}

/// Falta comunicación del UART con MATLAB para hacer gráficas 
