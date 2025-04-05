/*
 * Project Name: Komodo Toolchain
 * Project File: Komodo/utils.h
 * Copyright (C) Komodo/Contributors
 *
 * This program is distributed under the terms of the GNU General Public License v2.0.
 * See the LICENSE file for details.
 *
 */
 
#ifndef UTILS_H
#define UTILS_H

int komodo_TOML(void);
extern char *komodo_os;
int komodo_cmds_distance(const char *str1, const char *str2);
void printf_color(const char *color, const char *format, ...);
void println(const char* fmt, ...);
int call_extract_tar_gz(const char *fname);
int call_extract_zip(const char *zip_path, const char *dest_path);
size_t write_file(void *ptr, size_t size, size_t nmemb, FILE *stream);
int progress_callback(void *ptr, double dltotal, double dlnow, double ultotal, double ulnow);
void call_download_file(const char *url, const char *fname);

#endif