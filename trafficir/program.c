#include <reg51.h>

sbit entry = P1^0;
sbit exit = P1^1;
sbit parkingfull = P2^0;
sbit parkingfree = P2^1;
char availableSpaces = 5;
int i;

void updateLEDs();

void delay() {
    for (i = 0; i < 3000; i++);
}

void main() {
    while (1) {
        if (entry == 0) {
            delay();
            if (availableSpaces > 0 && availableSpaces <= 5) {
                availableSpaces--;
            }
        }

        if (exit == 0 && availableSpaces < 5) {
            delay();
            availableSpaces++;
        }

        updateLEDs();
        delay();
    }
}

void updateLEDs() {
    if (availableSpaces == 0) {
        parkingfull = 1;
        parkingfree = 0;
    } else {
        parkingfull = 0;
        parkingfree = 1;
    }
}
