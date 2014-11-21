
#include "binary_file.h"

int write_bytes(file_manager *fm, char *bytes) {
    FILE *fp = open_file(fm, 0, 0, 1);
    if(!fp) return 1;
    seek(fm, 0L);

    fwrite((unsigned char *)bytes, sizeof(unsigned char), strlen(bytes)+1, fp);

    return close_file(fm, fp);
}

char *read_all_bytes(file_manager *fm) {

    FILE *fp = open_file(fm, 1, 0, 0);
    if(!fp) return NULL;
    seek(fm, 0L);

    char *buffer = (char *) malloc(sizeof(char)*(fm->f_size+1));
    int i = 0;
    unsigned char byte;
    while(!feof(fp)) {
        fread(&byte, sizeof(unsigned char), 1, fp);
        buffer[i++] = (char) byte;
    }

    buffer[i-1] = '\0';
    if(close_file(fm, fp)) return NULL;

    return buffer;
}
