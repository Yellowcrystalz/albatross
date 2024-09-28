#ifndef PARSER_H
#define PARSER_H

#include "albatross.h"

void parse (char buffer[BUFFER_SIZE], HttpResponseInfo* httpResponse);
void parseLine (char* buffer, char* line, int* counter);
void parseRequestLine (char* line, char* httpElement, int* lineCounter, int parseLimit);
void parseConnection (char* line, HttpResponseInfo* parsedHttp, int* lineCounter);

#endif
