#include "parser.h"

/*
* This function is used to compare to strings to see if they match
*/
static int string_compare(const char *json, jsmntok_t *tok, const char *s) {
	if ((int)strlen(s) == tok->end - tok->start && strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}

/*
* This function is used to check if a token from the parser is a JSMN_STRING Object
*/
static int json_string_check(const char *json, jsmntok_t *tok, const char *s) {
	if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start && strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}

parsed_data json_parser(char *JSON_STRING) {
	// Default result initialization
	parsed_data result;

	// Parser Initialization
	jsmn_parser parser;
	jsmntok_t tokens[200];
	jsmn_init(&parser);

	// Parse JSON
	int tokens_used = 0;
	tokens_used = jsmn_parse(&parser, JSON_STRING, strlen(JSON_STRING), tokens, 200);

	// Check if parsing failed
	if (tokens_used < 0) {
		printf("Failed to parse JSON: %d\n", tokens_used);
		result.errType = no_data;
		result.parsed_status = error;
		return result;
	}

	// Check if top object is a JSMN Object 
	if (tokens_used < 1 || tokens[0].type != JSMN_OBJECT) {
		printf("Object expected\n");
		result.errType = parsing_error;
		result.parsed_status = error;
		return result;
	}

	int loop_counter = 0;
	char title[200];
	char value[200];
	for (loop_counter = 1; loop_counter < tokens_used; loop_counter++) {
		if (json_string_check(JSON_STRING, &tokens[loop_counter], "title") == 0) {
			if (string_compare(JSON_STRING, &tokens[loop_counter + 1], "title") == -1 && string_compare(JSON_STRING, &tokens[loop_counter + 1], "value") == -1) {
				int loc = 0;
				int title_length = tokens[loop_counter + 1].end - tokens[loop_counter + 1].start;

				for (loc = 0; loc < title_length; loc++) {
					title[loc] = JSON_STRING[tokens[loop_counter + 1].start + loc];
				}
				title[loc] = '\0';
				result.parsed_title = title;
				loop_counter++;
			}
			else {
				result.errType = missing_field;
				result.parsed_status = error;
				return result;
			}
		}
		else if (json_string_check(JSON_STRING, &tokens[loop_counter], "value") == 0) {
			if (string_compare(JSON_STRING, &tokens[loop_counter + 1], "title") == -1 && string_compare(JSON_STRING, &tokens[loop_counter + 1], "value") == -1) {
				int loc = 0;
				int value_length = tokens[loop_counter + 1].end - tokens[loop_counter + 1].start;

				for (loc = 0; loc < value_length; loc++) {
					value[loc] = JSON_STRING[tokens[loop_counter + 1].start + loc];
				}
				value[loc] = '\0';
				result.parsed_value = value;
				loop_counter++;
			}
			else {
				result.errType = missing_field;
				result.parsed_status = error;
				return result;
			}
		}
	}

	result.parsed_status = instruction_parsed;
	result.errType = no_error;
	return result;
}

/*
void main() {
	char *JSON_STRING = "{\"Title\" : \"Color\", \"Value\" : \"Purple\"}";
	parsed_data result = json_parser(JSON_STRING);
	if (result.parsed_status == instruction_parsed && result.errType == no_error) {
		printf("Title: %s\n", result.parsed_title);
		printf("Value: %s\n", result.parsed_value);
	}
	else {
		if (result.errType == no_data) {
			printf("Error: No Data\n");
		}
		else if (result.errType == missing_field) {
			printf("Error: Missing Field\n");
		}
		else if (result.errType == parsing_error) {
			printf("Error: Parsing Error\n");
		}
	}
	getchar();
}*/