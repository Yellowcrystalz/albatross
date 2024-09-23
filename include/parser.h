#ifndef PARSER_H
#define PARSER_H

#include "albatross.h"

#define METHOD_SIZE     8
#define PATH_SIZE       1024
#define PROTOCOL_SIZE   16
#define CONNECTION_SIZE 16

typedef struct HttpReqInfo
{
    char method[METHOD_SIZE];
    char path[PATH_SIZE];
    char protocol[PROTOCOL_SIZE]; 
    char connection[CONNECTION_SIZE];
} HttpReqInfo;

void parse (char buffer[BUFFER_SIZE]);
void parseLine (char* buffer, char* line, int* counter);
void parseMethod (char* line, HttpReqInfo* parsedHttp, int* lineCounter);
void parsePath (char* line, HttpReqInfo* parsedHttp, int* lineCounter);
void parseProtocol (char* line, HttpReqInfo* parsedHttp, int* lineCounter);
void parseConnection (char* line, HttpReqInfo* parsedHttp, int* lineCounter);

#endif

