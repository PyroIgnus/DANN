#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"

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

int process_config_line(char *line)
{
	// Ignore comments.
	if (line[0] == CONFIG_COMMENT_CHAR || strncmp(line,"\n",1)==0)
		return 0;

	// Extract config parameter name and value.
	char name[100];
	char value[50];
	int items = sscanf(line, "%s %s\n", name, value);

	// Line wasn't as expected.
	if (items != 2)
		return 1;

	// Process this line.
	if (strcmp(name, "CUE_SEED") == 0) {
        CUE_SEED = atoi(value);
	} else if (strcmp(name, "MAX_AXON_LENGTH") == 0) {
        MAX_AXON_LENGTH = atoi(value);
	} else if (strcmp(name, "MAX_SYNAPSES") == 0) {
        MAX_SYNAPSES = atoi(value);
	} else if (strcmp(name, "MAX_WEIGHT") == 0) {
        MAX_WEIGHT = atoi(value);
	} else if (strcmp(name, "MAX_CUE") == 0) {
        MAX_CUE = atoi(value);
	}
	else if (strcmp(name, "SEARCH_RADIUS") == 0) {
        SEARCH_RADIUS = atoi(value);
	}
	else if (strcmp(name, "ACTION_POTENTIAL") == 0) {
        ACTION_POTENTIAL = atoi(value);
	}
	else if (strcmp(name, "THRESHOLD") == 0) {
        THRESHOLD = atoi(value);
	}
	else if (strcmp(name, "INITIAL_SYNAPSE_WEIGHT") == 0) {
        INITIAL_SYNAPSE_WEIGHT = atoi(value);
	}
	else if (strcmp(name, "CUE_CHANGE") == 0) {
        CUE_CHANGE = (float)atof(value);
	}
	else if (strcmp(name, "WEIGHT_CHANGE") == 0) {
        WEIGHT_CHANGE = (float)atof(value);
	}
	else {
		// Ignore unknown config parameters.
	}

	return 0;
}

/**
 * @brief Reads the config file to compare the values later on
 * @return If successful, return 0 if found, -1 if not found
 */
int read_config(char *config_file)
{
	int error_occurred = 0;

	// Open file for reading.
	FILE *file = fopen(config_file, "r");
	if (file == NULL)
		error_occurred = 1;

	// Process the config file.
	while (!error_occurred && !feof(file)) {
		// Read a line from the file.
		char line[150];
		char *l = fgets(line, sizeof line, file);

		// Process the line.
		if (l == line)
			error_occurred = process_config_line(line);
		else if (!feof(file))
			error_occurred = 1;
	}

	return error_occurred ? -1 : 0;
}
