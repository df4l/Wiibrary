/*===========================================
    NoNameNo simple Gradient Sinusoid
        A good start to code a nice plasma
============================================*/
#include <grrlib.h>

#include <stdlib.h>
#include <math.h>
#include <wiiuse/wpad.h>
#include <stdio.h>
#include <fat.h>
#include <dirent.h>

#include "graphics.h"
#include "epub.h"

#include "Roboto_ttf.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <grrlib.h>

void list_directory(const char *path, GRRLIB_ttfFont *font) {
    DIR *pdir = opendir(path);
    if (!pdir) 
    {
        char error_msg[1024];
        snprintf(error_msg, sizeof(error_msg), "Error: unable to open %.1001s", path);
        GRRLIB_PrintfTTF((640 - (16 * strlen(error_msg))) / 2, 20, font, error_msg, 12, 0x000000FF);
        return;
    }

    struct dirent *pent;
    struct stat statbuf;
    char fullpath[1024];
    int y_offset = 40; 

    while ((pent = readdir(pdir)) != NULL) 
    {
        if (strcmp(".", pent->d_name) == 0 || strcmp("..", pent->d_name) == 0)
            continue;

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, pent->d_name);
        if (stat(fullpath, &statbuf) == -1) {
            char error_msg[256];
            snprintf(error_msg, sizeof(error_msg), "Error reading %.241s", fullpath);
            GRRLIB_PrintfTTF(20, y_offset, font, error_msg, 12, 0x000000FF);
            y_offset += 20;
            continue;
        }

        char output[1024];
        if (S_ISDIR(statbuf.st_mode)) {
            snprintf(output, sizeof(output), "%.1017s <dir>", fullpath);
            GRRLIB_PrintfTTF(20, y_offset, font, output, 12, 0x000000FF);
            y_offset += 20;
            list_directory(fullpath, font);
        } else {
            snprintf(output, sizeof(output), "%.973s %lld KB", fullpath, (long long)(statbuf.st_size / 1024));
            GRRLIB_PrintfTTF(20, y_offset, font, output, 12, 0x000000FF);
            y_offset += 20;
        }
    }

    closedir(pdir);
}

int main() {
    // Initialise the Graphics & Video subsystem
    GRRLIB_Init();
    GRRLIB_Settings.antialias = true;

    GRRLIB_ttfFont *Roboto = GRRLIB_LoadTTF(Roboto_ttf, Roboto_ttf_size);

    // Initialise the Wii Remotes
    WPAD_Init();

    // Initialise the SD card
    if (!fatInitDefault()) 
    {
        printf("fatInitDefault failure: terminating\n");
        goto error;
    }

    GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);
    GRRLIB_Camera3dSettings(0.0f,0.0f,13.0f, 0,1,0, 0,0,0);

    float a = 0;

error:
    while (1) 
    {
        GRRLIB_2dMode();

        WPAD_ScanPads();  // Scan the Wii Remotes
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)  break;
        
        render_background();

        GRRLIB_3dMode(0.1,1000,45,0,0);
        GRRLIB_ObjectView(0,0,0, 0,a*2,0,1,1,1);
        draw_selected_book();

        a-=0.2f;   

        //Switch to 2D Mode to display text
        GRRLIB_2dMode();

        list_directory("sd:/ebooks/", Roboto);

        GRRLIB_Render();  // Render the frame buffer to the TV
    }

    GRRLIB_FreeTTF(Roboto);
    GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB

    exit(0);  // Use exit() to exit a program, do not use 'return' from main()
}
