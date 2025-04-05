/*
 * Project Name: Komodo Toolchain
 * Project File: Komodo/komodo.c
 * Copyright (C) Komodo/Contributors
 *
 * This program is distributed under the terms of the GNU General Public License v2.0.
 * See the LICENSE file for details.
 *
 * Compile with GCC or CLANG
 * GCC: gcc -D_GNU_SOURCE -g komodo.c utils.c package.c tomlc99/toml.c -o komodo -lm -lcurl -lncurses -lreadline -lz -lzip -larchive
 * CLANG: clang -D_GNU_SOURCE -g komodo.c utils.c package.c tomlc99/toml.c -o komodo -lm -lcurl -lncurses -lreadline -lz -lzip -larchive
 *
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <limits.h>
#include <ncurses.h>
#include <dirent.h>
#include <time.h>
#include <ftw.h>
#include <sys/file.h>
#include <curl/curl.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <archive.h>
#include <archive_entry.h>

static inline int komo_sys(const char *cmd) {
    return system(cmd);
}

#include "color.h"
#include "utils.h"
#include "package.h"

int komodo_title(
    const char *custom_title)
 {
    const char *title = custom_title ? custom_title : "Komodo Toolchain";
    printf("\033]0;%s\007", title);
    return 0;
}

struct struct_of {
    int (*title)(const char *);
};

struct struct_of init_komodo(void) {
    struct struct_of komodo;
    komodo.title = komodo_title;
    return komodo;
}

void _komodo_ () {
    struct struct_of komodo = init_komodo();
    komodo.title(NULL);

    char
        *ptr_cmds;

    using_history();

    printf
        ("\033[4mWelcome to Komodo!\033[0m\n");

    char *__vcommands__[] =
    /* valid commands. */
        {
            "exit", "clear", "kill", "title", "help",
            "gamemode", "pawncc"
        };
    int num_cmds =
        sizeof(__vcommands__) /
            sizeof(__vcommands__[0]);

    while (1) {
        ptr_cmds =
            readline("user:~$ ");
        
        char *malloc_dynamic_str =
            (char *)malloc(256 * sizeof(char));
        if (malloc_dynamic_str == NULL) {
            printf_color(COL_RED, "Memory allocation failed!");
            break;
        }

        if (ptr_cmds == NULL) {
            _komodo_();
        }

        if (strlen(ptr_cmds) > 0) {
            add_history(ptr_cmds);
        }

        int c_distance =
            INT_MAX;
        char *c_command =
            NULL;

        for (int i = 0; i < num_cmds; i++) {
            int distance = call_kom_undefined_sizeof(ptr_cmds, __vcommands__[i]);
            if (distance < c_distance) {
                c_distance = distance;
                c_command = __vcommands__[i];
            }
        }

        if (strncmp(ptr_cmds, "help", 4) == 0) {
            komodo_title("Komodo Toolchain | @ help");

            char *arg =
                ptr_cmds + 4;
            while (*arg == ' ') arg++;

            if (strlen(arg) == 0) {
                println("usage: help | help [<cmds>]");
                println("cmds:");
                println(" clear, exit, kill, title");
                println(" gamemode, pawncc");
            } else if (strcmp(arg, "exit") == 0) {
                println("exit: exit from Komodo. | \
Usage: \"exit\"");
            } else if (strcmp(arg, "clear") == 0) {
                println("clear: clear screen Komodo. | \
Usage: \"clear\"");
            } else if (strcmp(arg, "kill") == 0) {
                println("kill: kill - restart terminal Komodo. | \
Usage: \"kill\"");
            } else if (strcmp(arg, "title") == 0) {
                println("title: set-title Terminal Komodo. | \
Usage: \"title\" | [<args>]");
            } else {
                println("help not found for: '%s'", arg);
            }
            
            continue;
        } else if (strcmp(ptr_cmds, "pawncc") == 0) {
            komodo_title("Komodo Toolchain | @ pawncc");

            char platform;
            printf("Select platform:\n");
            printf("[L/l] Linux\n");
            printf("[W/w] Windows\n");
            printf(">> ");
            scanf(" %c", &platform);

            if (platform == 'L' || platform == 'l') {
                call_download_pawncc("linux");
            } else if (platform == 'W' || platform == 'w') {
                call_download_pawncc("windows");
            } else {
                printf("Invalid platform selection.\n");
            }

            continue;
        } else if (strcmp(ptr_cmds, "gamemode") == 0) {
            komodo_title("Komodo Toolchain | @ gamemode");

            char platform;
            printf("Select platform:\n");
            printf("[L/l] Linux\n");
            printf("[W/w] Windows\n");
            printf(">> ");
            scanf(" %c", &platform);

            if (platform == 'L' || platform == 'l') {
                call_download_samp("linux");
            } else if (platform == 'W' || platform == 'w') {
                call_download_samp("windows");
            } else {
                printf("Invalid platform selection.\n");
            }

            continue;
        } else if (strcmp(ptr_cmds, "clear") == 0) {
            komodo_title("Komodo Toolchain | @ clear");

            clear:
                komo_sys("clear");
        } else if (strcmp(ptr_cmds, "exit") == 0) {
            komodo_title("Komodo Toolchain | @ exit");

            printf("exit\n");

            char
                *ptr_sigexit;
            ptr_sigexit =
                readline("user:~$ ");

            while (1) {
                if (strcmp(ptr_sigexit, "exit") == 0) {
                    exit(1);
                } else {
                    break;
                }
            }
        } else if (strcmp(ptr_cmds, "kill") == 0) {
            komodo_title("Komodo Toolchain | @ kill");

            goto clear;
        } else if (strncmp(ptr_cmds, "title", 5) == 0) {
            char *arg = ptr_cmds + 6;
            while (*arg == ' ') arg++;
        
            if (*arg == '\0') {
                println("usage: title [<title>]");
            } else {
                printf("\033]0;%s\007", arg);
            }
        
            continue;
        } else if (strcmp(ptr_cmds, c_command) != 0 && c_distance <= 1) {
            komodo_title("Komodo Toolchain | @ undefined");
            println("Did you mean: '%s'?", c_command);
            continue;
        } else {
            if (strlen(ptr_cmds) > 0) {
                komodo_title("Komodo Toolchain | @ not found");
                println("%s not found!", ptr_cmds);
            }
        }

        if (ptr_cmds) free(ptr_cmds);
        free(malloc_dynamic_str);
    }
}

int main(void) {
    /* main is not using. */
    /// @ load komodo.toml
    kom_toml_data();
    /// @ komodo commands call.
    _komodo_();
    return 0;
}