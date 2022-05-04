/*
    PRACTICA 2. GPIO - LED Y BOTON EXTERNO
    PAULINA GOMEZ FABELA
*/

/*
    1. Crear folder GPIO con archivos .h y .c
    2. poner en include.h    #include "../GPIO/GPIO.h"
    3. Los metodos van en GPIO.h
    4. Agregar metodo GPIOP_ISR en el startup
*/

#include "lib/include.h"

int main(void)
{
    Configurar_GPIO_P();
    while(1U){}
}