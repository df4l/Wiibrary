/*===========================================
    NoNameNo simple Gradient Sinusoid
        A good start to code a nice plasma
============================================*/
#include <grrlib.h>

#include <stdlib.h>
#include <math.h>
#include <wiiuse/wpad.h>
#include <stdio.h>

#include "epub.h"

#include "graphics.h"

int main() {
    // Initialise the Graphics & Video subsystem
    GRRLIB_Init();

    // Initialise the Wii Remotes
    WPAD_Init();

    GRRLIB_Settings.antialias = true;

    GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);

    GRRLIB_Camera3dSettings(0.0f,0.0f,13.0f, 0,1,0, 0,0,0);

    float a = 0;

    while (1) {
        GRRLIB_2dMode();
        GRRLIB_FillScreen(0x000000FF);

        WPAD_ScanPads();  // Scan the Wii Remotes
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)  break;
        
        render_background();

        GRRLIB_3dMode(0.1,1000,45,0,0);
        GRRLIB_ObjectView(0,0,0, 0,a*2,0,1,1,1);
        draw_book();
        a-=0.2f;   

        //Switch to 2D Mode to display text
        //GRRLIB_2dMode();
        //GRRLIB_Printf((640-(16*29))/2, 20, tex_font, 0xFFFFFFFF, 1, "PRESS A OR B TO ZOOM THE CUBE");
        

        GRRLIB_Render();  // Render the frame buffer to the TV
    }

    GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB

    exit(0);  // Use exit() to exit a program, do not use 'return' from main()
}
