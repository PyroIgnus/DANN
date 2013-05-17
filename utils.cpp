#include "utils.h"
#include <stdio.h>

/**
 * @brief helper funtion used to print
 * @return void
 */
void logger(FILE *file, char *message)
{
    if (LOGGING) {
        fprintf(file,"%s",message);
        fflush(file);
    }
}
