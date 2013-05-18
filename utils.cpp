#include "utils.h"
#include <stdio.h>

/**
 * @brief helper function used to print
 * @return void
 */
void logger(FILE *file, char *message)
{
    if (LOGGING) {
        fprintf(file,"%s",message);
        fflush(file);
    }
}
