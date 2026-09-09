// PIC16F887 timed LED flasher (RB0) with button and timer selection.

// BP1 (wired to RC3) pressed: the system will be off.
// BP1 released: the system will be controlled by BP2 (wired to RC4), allows you to select the flashing frequency: 1Hz if pressed, 5Hz if released.

#include "config_bits.h"

#define _XTAL_FREQ 4000000 // system frequency

void init_ES(){
    TRISB = 0xFE; // RB0 LED output
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
    tempo_X10ms(tempo/2); // pause
    RB0 = 0; // LED off
    tempo_X10ms(tempo/2);
}

// lights LED and turns off the other 4
void light_LED(short int LED){
    
    switch(LED){ // light LED axxording to input, others off
        case 1: PORTB = 0x01; break; // LED 1 on
        case 2: PORTB = 0x02; break; // LED 2 on
        case 3: PORTB = 0x04; break; // LED 3 on
        case 4: PORTB = 0x08; break; // LED 4 on
        case 5: PORTB = 0x10; break; // LED 5 on
    }
}

void main(void){
    init_ES();
 
    while(1){ // infinite loop
        if(RC3 == 1){ // if BP1 released
            RB0 = 0; // LED off
        }
        
        else{ // BP1 pushed
            if(RC4 == 0){ // BP2 pushed
                for(int i=1; i<=5; i++){
                light_LED(i); // 1Hz flashing
                tempo_X100ms(100/2); // pause
                } 
            }
            else{ // BP2 not pushed
                for(int i=1; i<=5; i++){
                light_LED(i); 
                tempo_X100ms(12/2); // pause 5Hz = 120ms
                } 
            }
        }
    }
}
