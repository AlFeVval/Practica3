
#include "pin_manager.h"
#include "mcc.h"

void PIN_MANAGER_Initialize(void)
{
    //configure ports below this line
    TRISBbits.TRISB5=0; //trigger salida
    TRISBbits.TRISB0=1; //echo entrada
    //Inicializacion de los puertos del pic para aceptar interrupciones externas.
    INTCON2bits.INTEDG0=1;
    INTCONbits.INT0F=0;
    INTCONbits.INT0IE=1;
    //PORTA, PORTB and PORTE are digital
    ADCON1bits.PCFG = 0xF; 
}

void PIN_MANAGER_IOC(void)
{
    
    
}

void PIN_MANAGER_INT0(void) //Al realizarse la interrupcion 0 se realia el codigo descrito debajo.
{
    if(INTCON2bits.INTEDG0==1) //Al llamarse la interrupcion si fuera de flanco de subida entonces seria igual a 1.
    {
        TMR0_Write8bitTimer(1); //Coloca el timer 0 en su inicio.
        TMR0_StartTimer(); //Se inicia el timer 0.
        INTCON2bits.INTEDG0=0; //Se configura para detectar flanco de bajada.
    }
    else //Si no fuera igual a 1 significa que esta en flanco de bajada.
        {
         TMR0_StopTimer(); //Se detiene el timer iniciado previamente.
         t=TMR0_Read8bitTimer(); //Se almacena el valor del timer en la variable global t.
         distancia=t; //Se multiplica el valor de tiempoi dle timer, la velocidad dle sonido en cm y el valor de desborde del timer en microsegudnos
         //calculado al contar con un timer de 8 bits y un preescaler de 256 a 1.
         INTCON2bits.INTEDG0=1; //Se configura para detectar el flanoc de subida nuevamente.
        }
}

void PIN_MANAGER_INT1(void)
{

}
void PIN_MANAGER_INT2(void)
{
    
}