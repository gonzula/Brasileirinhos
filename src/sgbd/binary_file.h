
#ifndef _BINARYFILE_H_
#define _BINARYFILE_H_

#include "file_manager.h"

int write_bytes(file_manager *fm, char *bytes);

char *read_all_bytes(file_manager *fm);

#endif
