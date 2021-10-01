/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 3.15.0
        Device            :  PIC18F4550
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.20
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include "mcc.h"
#include "stdio.h"
#include "stdlib.h"
#include <xlcd.h>

/*
                         Main application
 */


void main(void)
{
    unsigned char dist[10]; //Delaramos la variable de dsitancia como un arreglo de 10 caracteres sin signo.
    // Initialize the device
    SYSTEM_Initialize();
    
    
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable(); //Habilitamos las interrupciones globales.

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable(); //Habilitamos las interrupciones por medio de perifericos.

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    //first message on LCD
    while(BusyXLCD()); //Se mantiene en este while mientras el LCD no este listo para realizar la siguiente accion.
    putrsXLCD("Distancia: "); //Se imprime permanentemente el mensaje de "Distancia: " en la primera linea del LCD.
    while(BusyXLCD()); //Se mantiene en este while mientras el LCD no este listo para realizar la siguiente accion.
    SetDDRamAddr(0x40); //Se mueve el cursor del LCD a su siguiente renglon preparandolo para la siguiente escritura.
    
    //cursor points to address 0x40

    while (1)
    {
               
        PORTBbits.RB5=1; //Encendemos el puerto del trigger.
        __delay_us(10); //Realizamos un retraso de 20 microsegundos, siendo 10 el minimo posterior a encender el trigger del sensor antes de apagarlo.
        PORTBbits.RB5=0; //Apagamos el puerto del trigger.
        
        /*INTCONbits.INT0IF = 1; //Para simular la senial del puerto del echo, prendemos la bandera de interrupcion.
        __delay_us(2); //Modificamos el ancho de la senial del trigger al causar un retardo de 56.42 microsegundos equivalente a 1 cm de distancia.
        INTCONbits.INT0IF = 1; //Volvemos a levantar la bandera de interrupcion con el fin de indicar que ya termino.*/
        
        while(BusyXLCD()); //Se mantiene en este while mientras el LCD no este listo para realizar la siguiente accion.
        SetDDRamAddr(0x40); //Mueve el cursor del LCD a la siguiente linea para empezar a escribir el siguiente valor.
        sprintf(dist, "%.2f cm   ", distancia); //Almacena en la variable dist el formato completo a impirmir de la variable distancia contando con
        //los caracteres que le agrega, los decimales que debe impirmir junto al valor entero de distancia, etc.
        while (BusyXLCD()); //Se mantiene en etse while mientras el LCD no este listo para realizar la siguiente accion.
        putsXLCD(dist); //Imprime el mensaje a cambiar de la distancia en cm.
        
    __delay_ms(250); //Realiza un delay de 250 ms antes de volver a reiniciar todo el proceso.
    }
}

/**
 End of File
*/