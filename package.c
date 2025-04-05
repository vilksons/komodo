/*
 * Project Name: Komodo Toolchain
 * Project File: Komodo/package.c
 * Copyright (C) Komodo/Contributors
 *
 * This program is distributed under the terms of the GNU General Public License v2.0.
 * See the LICENSE file for details.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stddef.h>

#include "utils.h"
#include "package.h"

typedef struct {
    char key;
    const char *name;
    const char *linux_url;
    const char *linux_file;
    const char *windows_url;
    const char *windows_file;
} VersionInfo;

void call_download_pawncc(const char *platform) {
    char selection, version_selection;
    char url[256], fname[256];

    const char *versions[] = {
        "3.10.10", "3.10.9", "3.10.8", "3.10.7", "3.10.6",
        "3.10.5", "3.10.4", "3.10.3", "3.10.2", "3.10.1"
    };

    printf(":: Do you want to continue downloading PawnCC? (Yy/Nn)\n>> ");
    scanf(" %c", &selection);
    if (selection != 'Y' && selection != 'y') {
        void _komodo_();
        return;
    }

    printf("Select the PawnCC version to download:\n");
    for (int i = 0; i < 10; i++) {
        printf("[%c/%c] PawnCC %s\n", 'A'+i, 'a'+i, versions[i]);
    }

    printf(">> ");
    scanf(" %c", &version_selection);
    int index = (version_selection >= 'A' && version_selection <= 'J') ? version_selection - 'A'
               : (version_selection >= 'a' && version_selection <= 'j') ? version_selection - 'a' : -1;

    if (index < 0 || index >= 10) {
        printf("Invalid selection.\n");
        return;
    }

    const char *ext = strcmp(platform, "linux") == 0 ? "tar.gz" : "zip";

    sprintf(url, "https://github.com/pawn-lang/compiler/releases/download/v%s/pawnc-%s-%s.%s",
            versions[index], versions[index], platform, ext);
    sprintf(fname, "pawnc-%s-%s.%s", versions[index], platform, ext);

    call_download_file(url, fname);
}

void call_download_samp(const char *platform) {
    char sel_c;
    printf(":: Do you want to continue downloading SA-MP? (Yy/Nn): ");
    scanf(" %c", &sel_c);
    if (sel_c != 'Y' && sel_c != 'y') {
        void _komodo_();
        return;
    }

    VersionInfo versions[] = {
        { 'A', "SA-MP 0.3.DL R1", 
            "https://github.com/vilksons/files.sa-mp.com-Archive/raw/refs/heads/master/samp03DLsvr_R1.tar.gz",
            "samp03DLsvr_R1.tar.gz",
            "https://github.com/vilksons/files.sa-mp.com-Archive/raw/refs/heads/master/samp03DL_svr_R1_win32.zip",
            "samp03DL_svr_R1_win32.zip"
        },
        { 'B', "SA-MP 0.3.7 R3", 
            "https://github.com/vilksons/files.sa-mp.com-Archive/raw/refs/heads/master/samp037svr_R3.tar.gz",
            "samp037svr_R3.tar.gz",
            "https://github.com/vilksons/files.sa-mp.com-Archive/raw/refs/heads/master/samp037_svr_R3_win32.zip",
            "samp037_svr_R3_win32.zip"
        },
        { 'C', "SA-MP 0.3.7 R2-2-1", 
            "https://github.com/vilksons/files.sa-mp.com-Archive/raw/refs/heads/master/samp037svr_R2-2-1.tar.gz",
            "samp037svr_R2-2-1.tar.gz",
            "https://github.com/vilksons/files.sa-mp.com-Archive/raw/refs/heads/master/samp037_svr_R2-1-1_win32.zip",
            "samp037_svr_R2-2-1_win32.zip"
        },
        { 'D', "SA-MP 0.3.7 R2-1-1", 
            "https://github.com/vilksons/files.sa-mp.com-Archive/raw/refs/heads/master/samp037svr_R2-1.tar.gz",
            "samp037svr_R2-1.tar.gz",
            "https://github.com/vilksons/files.sa-mp.com-Archive/raw/refs/heads/master/samp037_svr_R2-1-1_win32.zip",
            "samp037_svr_R2-1-1_win32.zip"
        },
        { 'E', "OpenMP v1.4.0.2779", 
            "https://github.com/openmultiplayer/open.mp/releases/download/v1.4.0.2779/open.mp-linux-x86.tar.gz",
            "open.mp-linux-x86.tar.gz",
            "https://github.com/openmultiplayer/open.mp/releases/download/v1.4.0.2779/open.mp-win-x86.zip",
            "open.mp-win-x86.zip"
        },
        { 'F', "OpenMP v1.3.1.2748", 
            "https://github.com/openmultiplayer/open.mp/releases/download/v1.3.1.2748/open.mp-linux-x86.tar.gz",
            "open.mp-linux-x86.tar.gz",
            "https://github.com/openmultiplayer/open.mp/releases/download/v1.3.1.2748/open.mp-win-x86.zip",
            "open.mp-win-x86.zip"
        },
        { 'G', "OpenMP v1.2.0.2670", 
            "https://github.com/openmultiplayer/open.mp/releases/download/v1.2.0.2670/open.mp-linux-x86.tar.gz",
            "open.mp-linux-x86.tar.gz",
            "https://github.com/openmultiplayer/open.mp/releases/download/v1.2.0.2670/open.mp-win-x86.zip",
            "open.mp-win-x86.zip"
        },
        { 'H', "OpenMP v1.1.0.2612", 
            "https://github.com/openmultiplayer/open.mp/releases/download/v1.1.0.2612/open.mp-linux-x86.tar.gz",
            "open.mp-linux-x86.tar.gz",
            "https://github.com/openmultiplayer/open.mp/releases/download/v1.1.0.2612/open.mp-win-x86.zip",
            "open.mp-win-x86.zip"
        }
    };

    printf("Select the SA-MP version to download:\n");
    for (int i = 0; i < sizeof(versions)/sizeof(versions[0]); i++) {
        printf("[%c/%c] %s\n", versions[i].key, versions[i].key + 32, versions[i].name);
    }

    printf(">> ");
    char version_choice;
    scanf(" %c", &version_choice);

    VersionInfo *chosen = NULL;
    for (int i = 0; i < sizeof(versions)/sizeof(versions[0]); i++) {
        if (version_choice == versions[i].key || version_choice == versions[i].key + 32) {
            chosen = &versions[i];
            break;
        }
    }

    if (!chosen) {
        printf("Invalid selection\n");
        void _komodo_();
        return;
    }

    const char *url = strcmp(platform, "linux") == 0 ? chosen->linux_url : chosen->windows_url;
    const char *fname = strcmp(platform, "linux") == 0 ? chosen->linux_file : chosen->windows_file;

    call_download_file(url, fname);
}