#include <gccore.h>
#include <wiiuse/wpad.h>
#include <fat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static void *xfb = NULL;
static GXRModeObj *rmode = NULL;

// Fonction pour lister les fichiers et dossiers récursivement
void list_directory(const char *path) {
    DIR *pdir = opendir(path);
    if (!pdir) {
        printf("Erreur : impossible d'ouvrir %s\n", path);
        return;
    }

    struct dirent *pent;
    struct stat statbuf;
    char fullpath[1024];

    while ((pent = readdir(pdir)) != NULL) {
        if (strcmp(".", pent->d_name) == 0 || strcmp("..", pent->d_name) == 0)
            continue;

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, pent->d_name);
        if (stat(fullpath, &statbuf) == -1) {
            printf("Erreur lors de la lecture de %s\n", fullpath);
            continue;
        }

        if (S_ISDIR(statbuf.st_mode)) {
            printf("%s <dir>\n", fullpath);
            list_directory(fullpath); // Appel récursif pour explorer les sous-dossiers
        } else {
            printf("%s %lld KB\n", fullpath, statbuf.st_size / 1024); // Affiche la taille en KB
        }
    }

    closedir(pdir);
}

int main(int argc, char **argv) {
    // Initialise le système vidéo
    VIDEO_Init();

    // Initialise les manettes
    WPAD_Init();

    // Obtient le mode vidéo préféré
    rmode = VIDEO_GetPreferredMode(NULL);

    // Alloue de la mémoire pour l'affichage
    xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));

    // Initialise la console, nécessaire pour printf
    console_init(xfb, 20, 20, rmode->fbWidth, rmode->xfbHeight, rmode->fbWidth * VI_DISPLAY_PIX_SZ);

    // Configure le registre vidéo avec le mode choisi
    VIDEO_Configure(rmode);

    // Indique à l'hardware vidéo où se trouve la mémoire d'affichage
    VIDEO_SetNextFramebuffer(xfb);

    // Rend l'affichage visible
    VIDEO_SetBlack(false);

    // Applique les changements vidéo à l'hardware
    VIDEO_Flush();

    // Attend que la configuration vidéo soit terminée
    VIDEO_WaitVSync();
    if (rmode->viTVMode & VI_NON_INTERLACE) {
        VIDEO_WaitVSync();
    }

    // Message de bienvenue
    printf("\x1b[2;0H");

    // Initialisation de la carte SD
    if (!fatInitDefault()) {
        printf("fatInitDefault failure: terminating\n");
        goto error;
    }

    // Lister les fichiers dans le répertoire de la carte SD
    list_directory("sd:/ebooks/");

error: 
    // Boucle principale pour maintenir l'application en marche
    while (1) {
        // Lecture des entrées de la manette
        WPAD_ScanPads();

        // Vérifie les boutons pressés
        u32 pressed = WPAD_ButtonsDown(0);

        // Quitte l'application via le bouton Home
        if (pressed & WPAD_BUTTON_HOME) {
            exit(0);
        }

        // Attendre la synchronisation avec la VSync
        VIDEO_WaitVSync();
    }

    return 0;
}
