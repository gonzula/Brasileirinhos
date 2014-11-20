
#include "binary_file.h"

int write_bytes(file_manager *fm, char *bytes) {
	if(open_file(fm, 0, 1, 1)) return 1;
	seek(fm, 0L);

	fwrite((unsigned char *)bytes, sizeof(unsigned char), strlen(bytes)+1, fm->f_pointer);

	if(close_file(fm)) return 1;

	return 0;
}

char *read_all_bytes(file_manager *fm) {

	if(open_file(fm, 1, 1, 0)) return NULL;
	seek(fm, 0L);

	char *buffer = (char *) malloc(sizeof(char)*(fm->f_size));
	int i = 0;
	unsigned char byte;
	do {
		fread(&byte, sizeof(unsigned char), 1, fm->f_pointer);
		buffer[i++] = (char) byte;
	} while(byte != '\0');

	if(close_file(fm)) return NULL;

	return buffer;
}
