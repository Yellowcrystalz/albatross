#include <stdio.h>

#include "albatross.h"
#include "parser.h"

void parse (char buffer[BUFFER_SIZE], HttpResponse* httpRes)
{
    //HttpResponse httpRes; 

    char line[BUFFER_SIZE];    
    int bufferCounter = 0;
    int lineCounter = 0;

    parseLine(buffer, line, &bufferCounter);
    parseRequestLine(line, httpRes->method, &lineCounter, METHOD_SIZE);
    parseRequestLine(line, httpRes->path, &lineCounter, PATH_SIZE);
    parseRequestLine(line, httpRes->protocol, &lineCounter, PROTOCOL_SIZE);

    parseLine(buffer, line, &bufferCounter);
    parseLine(buffer, line, &bufferCounter);
    lineCounter = 12;
    parseConnection(line, httpRes, &lineCounter);

    (void)printf("Method: %s\n", httpRes->method);
    (void)printf("Path: %s\n", httpRes->path);
    (void)printf("Protocol: %s\n", httpRes->protocol);
    (void)printf("Connection: %s\n", httpRes->connection);

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

void parseConnection (char* line, HttpResponse* httpRes, int* lineCounter)
{
    char chr = '\0';

    for (int i = 0; i < CONNECTION_SIZE; i++)
    {
        chr = *(line + *lineCounter);

        if (chr == ' ' || chr == '\0')
        {
            *(httpRes->connection + i) = '\0';
            (*lineCounter)++;
            break;
        }
            
        *(httpRes->connection + i) = chr;
        (*lineCounter)++;
    }
}
