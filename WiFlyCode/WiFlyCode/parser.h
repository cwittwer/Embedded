#pragma once
/*
*********************************************************************************************
The parser uses jsmn to parse a json object into a structure that contains information
necessary for the PIC32 boards to effectively communicate with the server.

JSMN Link: https://github.com/zserge/jsmn
*********************************************************************************************
*/

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include "jsmn.h"

// This enum is used to indicate if the parsing was successful or if an error occured.
typedef enum {
	instruction_parsed = 5, error = 6
} status;

// This enum is used to indicate the type of error that occured, if any.
typedef enum {
	no_data = 7, missing_field = 8, parsing_error = 9, no_error=10
} error_type;

/*
* parsed_data is a struct that is returned by the parsing function which contains 
* information that the server sent to the PIC32 board.
*/
typedef struct {
	status parsed_status;
	char * parsed_title;
	char * parsed_value;
	error_type errType;
}parsed_data;

/*
* This function parses the json object and returns information in a format useful to the PIC32 board.
*/
parsed_data json_parser(char *jsonData);