#include <stc12.h>
#include "gcode/gcode.h"

millis_t millis=0;

//do a millisecond timer on timer0
void Timer0(void) __interrupt 1
{
    millis++;
    TH0=0xFC;
    TL0=0x18;
}

void main(void){
    TMOD=1;
    ET0=1;
    EA=1;
    TR0=1;
    GcodeSuite_reset_stepper_timeout();
    while(1){;}
}
