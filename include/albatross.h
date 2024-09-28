#ifndef ALBATROSS_H
#define ALBATROSS_H

#define BUFFER_SIZE     8192
#define METHOD_SIZE     8
#define PATH_SIZE       1024
#define PROTOCOL_SIZE   16
#define CONNECTION_SIZE 16
#define STATUS_SIZE 4

typedef struct HttpResponse
{
    char method[METHOD_SIZE];
    char path[PATH_SIZE];
    char protocol[PROTOCOL_SIZE]; 
    char connection[CONNECTION_SIZE];
    char status[STATUS_SIZE];
    long content;
} HttpResponse;

#endif // !ALBATROSS_H
