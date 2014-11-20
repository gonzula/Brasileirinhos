
#ifndef _FILEMANAGER_H_
#define _FILEMANAGER_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct file_manager {
	char *f_name;
	FILE *f_pointer;
	long f_size;
} file_manager;

void create_file(file_manager *fm);

void set_file_size(file_manager *fm);

file_manager *construct_file_manager(char *f_name);

void destroy_file_manager(file_manager *fm);

int open_file(file_manager *fm, int readonly, int binary, int overwrite);

int close_file(file_manager *fm);

int seek(file_manager *fm, long offset);

int seek_back(file_manager *fm, long minus);

int seek_foward(file_manager *fm, long plus);

#endif
