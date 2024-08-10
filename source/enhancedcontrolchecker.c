#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <stdio.h>
#include <stdlib.h>

#define RGB15(r, g, b) ((r) | ((g) << 5) | ((b) << 10))


#define REG_SOUND1CNT_L  (*(volatile u16*)0x04000060)  
#define REG_SOUND1CNT_H  (*(volatile u16*)0x04000062)  
#define REG_SOUND1CNT_X  (*(volatile u16*)0x04000064)  
#define REG_SOUNDCNT_X   (*(volatile u16*)0x04000084)  
#define REG_SOUNDCNT_L   (*(volatile u16*)0x04000080)  


void setBackgroundColor(u16 color) {
    BG_COLORS[0] = color;  // 
}


void updateButtonTally(int row, int count) {
    iprintf("\x1b[%d;22H%2d", row, count);  
}


void playTone() {
    static int dutyCycleIndex = 0;  
    u16 dutyCycleSettings[] = {
        0xF700,  // 12.5% duty cycle
        0xF740,  // 25% duty cycle
        0xF780,  // 50% duty cycle
        0xF7C0   // 75% duty cycle
    };

    REG_SOUNDCNT_X = 0x0080;  
    REG_SOUNDCNT_L = 0x1177; 

    REG_SOUND1CNT_L = 0x8000;  
    REG_SOUND1CNT_H = dutyCycleSettings[dutyCycleIndex]; 
    REG_SOUND1CNT_X = 0x8400 | 1200;  
 
    for (volatile int i = 0; i < 5000; i++);

    REG_SOUND1CNT_X = 0x0000;  

    dutyCycleIndex = (dutyCycleIndex + 1) % 4;  
}

int main(void) {

    int countL = 0;
    int countR = 0;
    int countUp = 0;
    int countDown = 0;
    int countLeft = 0;
    int countRight = 0;
    int countStart = 0;
    int countSelect = 0;
    int countA = 0;
    int countB = 0;

    irqInit();
    irqEnable(IRQ_VBLANK);

    consoleDemoInit();

    // Set the background color (use RGB15 format, 0-31 per channel)
    setBackgroundColor(RGB15(17, 11, 24)); 

    iprintf("\x1b[1;0H Enhanced Control Checker GBA");

    iprintf("\x1b[4;2HL: ");
    iprintf("\x1b[5;2HR: ");
    iprintf("\x1b[6;2HUP: ");
    iprintf("\x1b[7;2HDOWN: ");
    iprintf("\x1b[8;2HLEFT: ");
    iprintf("\x1b[9;2HRIGHT: ");
    iprintf("\x1b[10;2HSTART: ");
    iprintf("\x1b[11;2HSELECT: ");
    iprintf("\x1b[12;2HA: ");
    iprintf("\x1b[13;2HB: ");
	
	iprintf("\x1b[16;6H Join the Club");
	iprintf("\x1b[17;4H moddedgameboy.club");


    while (1) {
        VBlankIntrWait();
        scanKeys();
        u16 keys = keysDown();
        if (keys & KEY_L) {
            countL++;
            updateButtonTally(4, countL);
            playTone();
        }
        if (keys & KEY_R) {
            countR++;
            updateButtonTally(5, countR);
            playTone();
        }
        if (keys & KEY_UP) {
            countUp++;
            updateButtonTally(6, countUp);
            playTone();
        }
        if (keys & KEY_DOWN) {
            countDown++;
            updateButtonTally(7, countDown);
            playTone();
        }
        if (keys & KEY_LEFT) {
            countLeft++;
            updateButtonTally(8, countLeft);
            playTone();
        }
        if (keys & KEY_RIGHT) {
            countRight++;
            updateButtonTally(9, countRight);
            playTone();
        }
        if (keys & KEY_START) {
            countStart++;
            updateButtonTally(10, countStart);
            playTone();
        }
        if (keys & KEY_SELECT) {
            countSelect++;
            updateButtonTally(11, countSelect);
            playTone();
        }
        if (keys & KEY_A) {
            countA++;
            updateButtonTally(12, countA);
            playTone();
        }
        if (keys & KEY_B) {
            countB++;
            updateButtonTally(13, countB);
            playTone();
        }
    }
}
