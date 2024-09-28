#include "albatross.h"
#include "parser.h"

void parse (char buffer[BUFFER_SIZE], HttpResponseInfo* httpResInfo)
{
    char line[BUFFER_SIZE];    
    int bufferCounter = 0;
    int lineCounter = 0;

    parseLine(buffer, line, &bufferCounter);
    parseRequestLine(line, httpResInfo->method, &lineCounter, METHOD_SIZE);
    parseRequestLine(line, httpResInfo->path, &lineCounter, PATH_SIZE);
    parseRequestLine(line, httpResInfo->protocol, &lineCounter, PROTOCOL_SIZE);

    parseLine(buffer, line, &bufferCounter);
    parseLine(buffer, line, &bufferCounter);
    lineCounter = 12;
    parseConnection(line, httpResInfo, &lineCounter);

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

        if (chr == ' ' || chr == '\r' || chr == '\0')
        {
            *(httpElement + i) = '\0';
            (*lineCounter)++;
            break;
        }
            
        *(httpElement + i) = chr;
        (*lineCounter)++;
    }   
}

void parseConnection (char* line, HttpResponseInfo* httpResInfo, int* lineCounter)
{
    char chr = '\0';

    for (int i = 0; i < CONNECTION_SIZE; i++)
    {
        chr = *(line + *lineCounter);

        if (chr == ' ' || chr == '\0')
        {
            *(httpResInfo->connection + i) = '\0';
            (*lineCounter)++;
            break;
        }
            
        *(httpResInfo->connection + i) = chr;
        (*lineCounter)++;
    }
}
