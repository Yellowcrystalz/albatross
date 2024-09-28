#ifndef PARSER_H
#define PARSER_H

#include "albatross.h"

void parse (char buffer[BUFFER_SIZE], HttpResponse* httpResponse);
void parseLine (char* buffer, char* line, int* counter);
void parseRequestLine (char* line, char* httpElement, int* lineCounter, int parseLimit);
void parseConnection (char* line, HttpResponse* parsedHttp, int* lineCounter);

#endif
