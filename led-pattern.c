// PIC16F887 timed flashing LEDs with button and timer selection.

// BP1 (wired to RC3) pressed: the system will be off.
// BP1 released: the system will be stopped. BP1 pressed: five LEDs connected from RB0 to RB4 will flash in an ordered pattern.

#include "config_bits.h"

#define _XTAL_FREQ 4000000 // system frequency

void init_ES(){
    TRISB = 0xE0; // RB0 LED output
    TRISC = 0xFF; // all inputs
    ANSELH = 0; // no analog
    PORTB = 0x00; // off at startup
}

// inputs integer duration in 1/10 seconds
void tempo_X10ms(short int X){ // tempo of X00 ms
    for(int i=0; i<X; i++){ // use for loop bc delay argument must be constant
        __delay_ms(10); // pause 1/10 s = 100 ms
    }
}

void led_flash(short int tempo){ // input tempo in 1/100 s
    RB0 = 1; // LED on
    tempo_X10ms(tempo); // pause
    RB0 = 0; // LED off
    tempo_X10ms(tempo);
}

// lights LED and turns off the other 4
void light_LED(short int LED){
    
    switch(LED){ // light LED axxording to input, others off
        case 0: PORTB = 0; break; 
        case 1: PORTB = 0x01; break; // LED 1 on
        case 2: PORTB = 0x02; break; // LED 2 on
        case 3: PORTB = 0x04; break; // LED 3 on
        case 4: PORTB = 0x08; break; // LED 4 on
        case 5: PORTB = 0x10; break; // LED 5 on
    }
}

void main(void){
    init_ES();
    
    short int current = 0; // keep track of which led is lit
 
    while(1){ // infinite loop
        if(RC3 ==1){ // if BP1 released
            PORTB = 0; // LEDs off
        }
        
        else{ // BP1 pushed
            if(RC4 == 0){ // BP2 pushed, forward direction
                for(int i=0; i<5; i++){
                    light_LED(current+i); // 1Hz flashing
                    tempo_X10ms(50); // pause
                } 
            }
            else{ // BP2 not pushed, backwards direction
                for(int i=0; i<=5; i++){
                    light_LED(current-i); // backwards pattern
                    tempo_X10ms(6); // pause 5Hz = 120ms
                } 
            }
        }
    }
}
