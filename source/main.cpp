#include "c:/devkitPro/libogc/include/gccore.h"
#include "C:/devkitPro/portlibs/wii/include/grrlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <experimental/random>
#include "BMfont5_png.h"
#include "menu_png.h"
#include "button_png.h"
#include "ball_png.h"
#include "cursor_png.h"
#include "racket_png.h"
#include "C:/devkitPro/libogc/include/wiiuse/wpad.h"


int main(int argc, char **argv) {

    GRRLIB_texImg *tex_BMfont5 = GRRLIB_LoadTexture(BMfont5_png);
    GRRLIB_InitTileSet(tex_BMfont5, 8, 16, 0);

    GRRLIB_texImg *menuTexture = GRRLIB_LoadTexture(menu_png);
    GRRLIB_texImg *playButtonTexture = GRRLIB_LoadTexture(button_png);
    GRRLIB_texImg *quitButtonTexture = GRRLIB_LoadTexture(button_png);
    GRRLIB_texImg *cursorTexture = GRRLIB_LoadTexture(cursor_png);

    VIDEO_Init();

    GRRLIB_Init();

    GRRLIB_texImg *racketTexture = GRRLIB_LoadTexture(racket_png);

    GRRLIB_texImg *ballTexture = GRRLIB_LoadTexture(ball_png);

    
    // Left Racket
    int leftRacketY = 0;

    // Right Racket
    int rightRacketY = 350;

    // Ball Velocity/Position
    int ballSpeedX = -6.0f;
    int ballSpeedY = 6.0f;
    int ballX = 600/2;
    int ballY = 400/2;

    // Score
    int leftScore = 0;
    int rightScore = 0;

    // Get the preferred video mode from the system
    GXRModeObj *rmode = VIDEO_GetPreferredMode(NULL);

    // Allocate memory for the display
    void *framebuffer = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));

    // Initialize the console, required for printf
    console_init(framebuffer, 20, 20, rmode->fbWidth, rmode->xfbHeight, rmode->fbWidth * VI_DISPLAY_PIX_SZ);

    // Set up the video registers with the chosen mode
    VIDEO_Configure(rmode);

    // Set the frame buffer to the one allocated earlier
    VIDEO_SetNextFramebuffer(framebuffer);

    // Make the display visible
    VIDEO_SetBlack(FALSE);

    // Flush the video register changes to the hardware
    VIDEO_Flush();

    int state = 0;

    // Wait for the video setup to complete
    VIDEO_WaitVSync();
    if (rmode->viTVMode & VI_NON_INTERLACE) VIDEO_WaitVSync();
    // Initialize the Wii Remote subsystem
    WPAD_Init();
    WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);
    WPAD_SetDataFormat(WPAD_CHAN_1, WPAD_FMT_BTNS_ACC_IR);
    while (1) {
        // Scan the Wii Remote
        WPAD_ScanPads();

        GRRLIB_FillScreen(0x0000000);

        GRRLIB_Printf(15, 15, tex_BMfont5, 0xFFFFFFFF, 1, "Left Side Points: %i", leftScore);
        GRRLIB_Printf(15, 30, tex_BMfont5, 0xFFFFFFFF, 1, "Right Side Points: %i", rightScore);

        ir_t ir1; 
        ir_t ir2; 
		WPAD_IR(WPAD_CHAN_0, &ir1); 
		WPAD_IR(WPAD_CHAN_1, &ir2); 
		
        // Move ball acording to velocity
        if (state == 1){
            ballX += ballSpeedX;
            ballY += ballSpeedY;
        }

        // Check on rightRacket to not pass the screen(up direction)
        if (ir1.sy <= 0){} else {
            leftRacketY = (int)ir1.sy;
        }
        // Check on rightRacket to not pass the screen(down direction)
        if (ir1.sy <= 416){} else {
            leftRacketY = (int)ir1.sy;
        }
        // Check on leftRacket to not pass the screen(down direction)
        if (ir2.sy <= 416){} else {
            rightRacketY = (int)ir2.sy;
        }
        // Check on leftRacket to not pass the screen(up direction)
        if (ir2.sy <= 0){} else {
            rightRacketY = (int)ir2.sy;
        }

        if (state == 1){
            // Render left racket
            GRRLIB_DrawImg(0, leftRacketY, racketTexture, 0, 1, 1, 0xFFFFFFFF);

            // Render Ball
            GRRLIB_DrawImg(ballX, ballY, ballTexture, 0, 1, 1, 0xFFFFFFFF);

            // Render right racket
            GRRLIB_DrawImg(625, rightRacketY, racketTexture, 0, 1, 1, 0xFFFFFFFF);
        } else if (state == 0) {
            // MENU:
            GRRLIB_DrawImg(0, 0, menuTexture, 0, 1, 1, 0xFFFFFFFF);
            GRRLIB_DrawImg(340, 262, playButtonTexture, 0, 1, 1, 0xFFFFFFFF);
            GRRLIB_DrawImg(107, 262, quitButtonTexture, 0, 1, 1, 0xFFFFFFFF);
            GRRLIB_DrawImg(ir1.sx, ir1.sy, cursorTexture, 0, 1, 1, 0xFFFFFFFF);
            GRRLIB_Plot(ir1.sx, ir1.sy, 0x800080FF);
            GRRLIB_Plot(ir1.sx + 1, ir1.sy, 0x800080FF);
            GRRLIB_Plot(ir1.sx, ir1.sy + 1, 0x800080FF);
            GRRLIB_Plot(ir1.sx + 1, ir1.sy + 1, 0x800080FF);

            if(ir1.sx < 340 + 200 &&
               ir1.sx > 340 &&
               ir1.sy < 262 + 64 &&
               ir1.sy > 262)
                {   
                    if (WPAD_ButtonsDown(0) & WPAD_BUTTON_A)
                    {
                        if (WPAD_ButtonsDown(1) != 0){
                            // If connected, allow to start.
                            state = 1;
                        }
                    }
                }
            if(ir1.sx < 107 + 200 &&
               ir1.sx > 107 &&
               ir1.sy < 262 + 64 &&
               ir1.sy > 262)
                {   
                    if (WPAD_ButtonsDown(0) & WPAD_BUTTON_A)
                    {
                        VIDEO_Flush();
                        GRRLIB_FreeTexture(racketTexture);
                        GRRLIB_FreeTexture(ballTexture);
                        GRRLIB_Exit();
                        exit(0);
                    }
                }
        }
        if (ballY <= 0){
            ballSpeedY = 2;
        }

        if (ballX <= 0){
            rightScore += 1;
            ballX = 600/2;
            ballY = 400/2;
            int value = std::experimental::randint(0, 1);
            if (value == 0){
                ballSpeedX = -6.0;
                ballSpeedY = -2;
            } else {
                ballSpeedX = 6.0;
                ballSpeedY = 2;
            }
        }
        if (ballX >= 640 - 32){
            leftScore += 1;
            ballX = 600/2;
            ballY = 400/2;
            int value = std::experimental::randint(0, 1);
            if (value == 0){
                ballSpeedX = -6.0;
                ballSpeedY = -2;
            } else {
                ballSpeedX = 6.0;
                ballSpeedY = 2;
            }}

        if (ballY >= 450){
            ballSpeedY = -2;
        }

        // AABB COLLISION FOR LEFT RACKET
        if(16 < ballX + 32 &&
        16 > ballX &&
        leftRacketY < ballY + 32 &&
        leftRacketY + 64 > ballY)
        {
            ballSpeedX = 6.0;
            int value = std::experimental::randint(0, 1);
            if (value == 0){
                ballSpeedY = -2;
            } else {
                ballSpeedY = 2;
            }
        }

        // AABB COLLISION FOR RIGHT RACKET
        if(625 - 8 < ballX + 32 &&
        625 - 8 > ballX &&
        rightRacketY < ballY + 32 &&
        rightRacketY + 64 > ballY)
        {
            ballSpeedX = -6.0;
            int value = std::experimental::randint(0, 1);
            if (value == 0){
                ballSpeedY = -2;
            } else {
                ballSpeedY = 2;
            }
        }

        auto pressed = WPAD_ButtonsHeld(0);
        // If the Home button is pressed, exit the application
        if (pressed & WPAD_BUTTON_HOME) exit(0);
        // Wait for the next frame
        VIDEO_WaitVSync();
        GRRLIB_Render();
    }
    
    VIDEO_Flush();
    GRRLIB_FreeTexture(racketTexture);
    GRRLIB_FreeTexture(ballTexture);
    GRRLIB_Exit();
    exit(0);
    return 0;
}