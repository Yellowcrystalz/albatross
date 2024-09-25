#include <stdlib.h>
#include <stdio.h>

#include "albatross.h"
#include "parser.h"

void parse (char buffer[BUFFER_SIZE])
{
    HttpReqInfo parsedHttp; 

    char* line = (char *)malloc(1024 * sizeof(char));    
    int bufferCounter = 0;
    int lineCounter = 0;

    parseLine(buffer, line, &bufferCounter);
    parseRequestLine(line, parsedHttp.method, &lineCounter, METHOD_SIZE);
    parseRequestLine(line, parsedHttp.path, &lineCounter, PATH_SIZE);
    parseRequestLine(line, parsedHttp.protocol, &lineCounter, PROTOCOL_SIZE);

    parseLine(buffer, line, &bufferCounter);
    parseLine(buffer, line, &bufferCounter);
    lineCounter = 12;
    parseConnection(line, &parsedHttp, &lineCounter);

    (void)printf("Method: %s\n", parsedHttp.method);
    (void)printf("Path: %s\n", parsedHttp.path);
    (void)printf("Protocol: %s\n", parsedHttp.protocol);
    (void)printf("Connection: %s\n", parsedHttp.connection);

    free(line);
}

void parseLine (char* buffer, char* line, int* bufferCounter)
{
    char chr = '\0';
    
    for (int i = 0; i < 1023; i++)
    {
        chr = *(buffer + *bufferCounter);

        if (chr == '\0' || chr == '\n')
        {
            *(line + i) = '\0';
            (*bufferCounter)++;
            break;
        }

        *(line + i) = chr; 
        (*bufferCounter)++; 
    }
}

void parseRequestLine (char* line, char* httpElement, int* lineCounter, int parseLimit)
{
    char chr = '\0';

    for (int i = 0; i < parseLimit; i++)
    {
        chr = *(line + *lineCounter);

        if (chr == ' ' || chr == '\0')
        {
            *(httpElement + i) = '\0';
            (*lineCounter)++;
            break;
        }
            
        *(httpElement + i) = chr;
        (*lineCounter)++;
    }   
}

void parseConnection (char* line, HttpReqInfo* parsedHttp, int* lineCounter)
{
    char chr = '\0';

    for (int i = 0; i < CONNECTION_SIZE; i++)
    {
        chr = *(line + *lineCounter);

        if (chr == ' ' || chr == '\0')
        {
            *(parsedHttp->connection + i) = '\0';
            (*lineCounter)++;
            break;
        }
            
        *(parsedHttp->connection + i) = chr;
        (*lineCounter)++;
    }
}
