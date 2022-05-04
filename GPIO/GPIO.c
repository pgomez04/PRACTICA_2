

#include "lib/include.h"

extern void Configurar_GPIO_P(void)
{
    /////////////////////////////////HABILITAR PUERTO
    /*
        Modulo del puerto P en pagina 382
        0010 0000 0000 0000 = 2000 -> en hexadecimal
        Puerto P es el bit 13
    */
   SYSCTL->RCGCGPIO |= 0x00002000;
   //SYSCTL->RCGCGPIO |= (1<<13); //Otra forma de habilitarlo
   while ((SYSCTL->PRGPIO&0x00002000) == 0){;} //permite al reloj estabilizarse
                                               //indica si ya esta listo

    ///////////////////////////////////ENTRADAS Y SALIDAS
    //              PP5      PP0
    GPIOP->DIR |= (0<<5) | (1<<0); //PP0 salida (1), PP5 entrada (0)
    GPIOP->PUR |= (1<<5); //1 inicio en estado alto

    ///////////////////////////////////FUNCIONES ALTERNATIVAS
    GPIOP->AFSEL |= 0x00; //0 controlado por registros GPIO, 1 por periferico
    GPIOP->PCTL |= 0x00; //asocia cada GPIO con un periferico
    GPIOP->DEN |= (0<<5) | (1<<0); //Habilita como digitales

    //////////////////////////////////HABILITAR INTERRUPCION
    GPIOP-> IM |= (0<<5); // 0 desactiva la interrupcion
    GPIOP-> IS |= (0<<5); //0 interrumpe cuando sea sensible al borde
    GPIOP-> IBE |= (0<<5); //la interrupcion esta controlado por IEV
    GPIOP-> IEV |= (1<<5); //1 detetcta bordes de subida
    //GPIOP-> RIS |= (0<<0); //0 la int ni ha ocurido //registro de estado
    GPIOP-> IM |= (1<<5);  // se le ordena enviar la int al micrco

    /*
        Puerto P, int 76, prioridad 19, nivel 1
        pag. 116 y 159
        4n+3   4n+2   4n+1   4n
         79     78     77    76
         FF     FF     FF    00
        Tabla de registros NVIC en pagn 146, EN2
    */
    NVIC->IP[19] = (NVIC->IP[19]) & 0xFFFFFF00 | (0x00000010);
    NVIC->ISER[2] = 0x00001000; //76 se excede y queda en el bit 12 //hexadecimal
}

extern void GPIOP_ISR(void)
{
    uint32_t i;
    GPIOP->DATA = (1<<0); //LED EXTERNO P0, prender
    for (i=0; i<1000000; i++){}
    GPIOP->DATA = (0<<0); //LED EXTERNO P0, apagar
    for (i=0; i<1000000; i++){}

    GPIOP->ICR |= (1<<5); //limpia la interrupcion
        //si no solo se interrupe una vez

}