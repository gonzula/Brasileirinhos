
#include "file_manager.h"

void set_file_size(file_manager *fm, FILE *fp) {
    rewind(fp);
    fseek(fp, 0L, SEEK_END);
    fm->f_size = ftell(fp);
    rewind(fp);
}

void create_file(file_manager *fm) {
    FILE *fp = NULL;
    fp = fopen((const char *)fm->f_name, "r");
    if(!fp) fp = fopen((const char *)fm->f_name, "w");

    set_file_size(fm, fp);

    fclose(fp);
}

file_manager *construct_file_manager(char *f_name) {
    file_manager *fm = (file_manager *) malloc(sizeof(file_manager));

    fm->f_name = (char *) malloc(sizeof(char)*(strlen(f_name)+1));
    strcpy(fm->f_name, f_name);
    create_file(fm);

    return fm;
}

void destroy_file_manager(file_manager *fm) {
    if(fm->f_name != NULL) free(fm->f_name);
    if(fm != NULL) free(fm);
}

FILE *open_file(file_manager *fm, int readonly, int binary, int overwrite) {
    if(fm->f_name == NULL) return NULL;

    FILE *fp = NULL;

    if(overwrite) fp = fopen((const char *)fm->f_name, binary ? "wb" : "w");
    else
    {
        if(readonly) fp = fopen((const char *)fm->f_name, binary ? "rb" : "r");
        else fp = fopen((const char *)fm->f_name, binary ? "rb+" : "r+");
    }

    set_file_size(fm, fp);

    return fp;
}

int close_file(file_manager *fm, FILE *fp) {
    set_file_size(fm, fp);
    return fclose(fp); //if successful, returns 0
}

int seek(file_manager *fm, long offset) {
    FILE *fp = open_file(fm, 1, 0, 0);

    fseek(fp, offset, SEEK_SET);
    return close_file(fm, fp);
}