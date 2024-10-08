#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "albatross.h"

void respond(HttpResponseInfo* httpResInfo, int client_fd) {

    const char *header_template = (
        "%s 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %d\r\n"
        "Connection: %s\r\n\r\n"
    );

    char filePath[PATH_SIZE];

    if(strcmp(httpResInfo->path, "/"))
        (void)strcpy(filePath, "index.html");
    else
        (void)strcpy(filePath, httpResInfo->path); 


    FILE* index_html = fopen("index.html", "r");
    (void)fseek(index_html, 0, SEEK_END);
    httpResInfo->content_length = ftell(index_html);
    (void)fseek(index_html, 0, SEEK_SET);

    int size_needed = snprintf(
        NULL,
        0,
        header_template,
        httpResInfo->protocol,
        httpResInfo->content_length,
        httpResInfo->connection
    ) + 1;

    char* http_header = (char*)malloc(size_needed);
    snprintf(
        http_header,
        size_needed,
        header_template,
        httpResInfo->protocol,
        httpResInfo->content_length,
        httpResInfo->connection
    );

    //printf("%s", http_header);

    char* html_content = (char*)malloc(httpResInfo->content_length + 1);
    fread(html_content, 1, httpResInfo->content_length, index_html);
    html_content[httpResInfo->content_length] = '\0';

    char* http_res = (char*)malloc(strlen(http_header) + httpResInfo->content_length + 1);
    strcpy(http_res, http_header);
    strcat(http_res, html_content);

    (void)send(client_fd, http_res, strlen(http_res), 0);

    free(http_header);
    free(html_content);
    free(http_res);
}
