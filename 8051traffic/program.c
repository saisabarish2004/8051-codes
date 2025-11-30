#include <reg51.h>

#define display P3

sbit rs = P2^2;
sbit rw = P2^3;
sbit e = P2^4;

sbit EntrySwitch = P1^0;
sbit ExitSwitch = P1^1;

char availableSpaces = 5;
bit parkingFull = 0;  // Initially, parking is free

unsigned char parkingFullMessage[13] = "Parking Full ";
unsigned char parkingFreeMessage[13] = "Parking Free ";

void lcdint();
void lcdcmd(char command);
void lcddata(char d);
void updateDisplay();

void delay(int time) {
    while (time--);
}

void main() {
    lcdint();
    while (1) {
        if (EntrySwitch == 0) {
            delay(50000);
            if (availableSpaces > 0 && availableSpaces <= 5) {
                availableSpaces--;
            }
        }

        if (ExitSwitch == 0) {
            delay(50000);
            if (availableSpaces < 5 && !parkingFull) {
                availableSpaces++;
            }
        }

        // Check if 5 button presses have occurred
        if (availableSpaces == 0 && !parkingFull) {
            parkingFull = 1;
            updateDisplay();  // Update display when parking becomes full
        } else if (availableSpaces > 0 && parkingFull) {
            parkingFull = 0;
            updateDisplay();  // Update display when parking becomes free
        }

        delay(50000);  // Add a delay at the end of the loop
    }
}

void lcdint() {
    lcdcmd(0X38);
    lcdcmd(0X0C);
    lcdcmd(0X06);
    lcdcmd(0X10);
    lcdcmd(0X01);
    lcdcmd(0X80);
}

void lcdcmd(char command) {
    display = command;
    rs = 0;
    rw = 0;
    e = 1;
    delay(100);
    e = 0;
    delay(5000);
}

void lcddata(char d) {
    display = d;
    rs = 1;
    rw = 0;
    e = 1;
    delay(100);
    e = 0;
    delay(5000);
}

void updateDisplay() {
    lcdcmd(0x01);  // Clear display
    delay(2000);
int i;
    if (parkingFull) {
        // Parking is full
        for (i = 0; i < 12 && parkingFullMessage[i] != '\0'; i++) {
            lcddata(parkingFullMessage[i]);
        }
    } else {
        // Parking is free
        for (i = 0; i < 13 && parkingFreeMessage[i] != '\0'; i++) {
            lcddata(parkingFreeMessage[i]);
        }
    }
}
