
#include "file_manager.h"

void set_file_size(file_manager *fm) {
    FILE *fp = fopen((const char *)fm->f_name, "r");
    fseek(fp, 0L, SEEK_END);
    fm->f_size = ftell(fp);
    rewind(fp);
    fclose(fp);
}

void create_file(file_manager *fm) {
    fm->f_pointer = fopen((const char *)fm->f_name, "rb");
    if(!fm->f_pointer) fm->f_pointer = fopen((const char *)fm->f_name, "wb");
    fclose(fm->f_pointer);

    set_file_size(fm);
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

int open_file(file_manager *fm, int readonly, int binary, int overwrite) {
    if(fm->f_name == NULL) return 1;
    set_file_size(fm);

    if(overwrite) fm->f_pointer = fopen((const char *)fm->f_name, binary ? "wb" : "w");
    else
    {
        if(readonly) fm->f_pointer = fopen((const char *)fm->f_name, binary ? "rb" : "r");
        else fm->f_pointer = fopen((const char *)fm->f_name, binary ? "rb+" : "r+");
    }

    return 0;
}

int close_file(file_manager *fm) {
    set_file_size(fm);
    return fclose(fm->f_pointer); //if successful, returns 0
}

int seek(file_manager *fm, long offset) {
    if(!fm->f_pointer) return 1;

    fseek(fm->f_pointer, offset, SEEK_SET);
    return 0;
}

int seek_back(file_manager *fm, long minus) {
    if(!fm->f_pointer) return 1;
    if(minus > 0) minus *= -1;

    fseek(fm->f_pointer, minus, SEEK_CUR);
    return 0;
}

int seek_foward(file_manager *fm, long plus) {
    if(!fm->f_pointer) return 1;
    if(plus < 0) plus *= -1;

    fseek(fm->f_pointer, plus, SEEK_CUR);
    return 0;
}
