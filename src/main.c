#include <sys/socket.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "albatross.h"
#include "parser.h"

int main(void)
{

    int s = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = 
    {
        AF_INET,
        0x901f,
        {0},
        {0} 
    };

    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        (void)printf("Error: could not bind\n");
        return -1;
    }

    printf("http://127.0.0.1:8080\n");

    listen(s, 10);

    int client_fd = accept(s, 0, 0);
    char buffer[BUFFER_SIZE] = {0};
    recv(client_fd, buffer, BUFFER_SIZE, 0);
    //(void)printf("%s\n", buffer);

    HttpResponseInfo httpResInfo = {0};
    parse(buffer, &httpResInfo); 

    //(void)printf("Method: %s\n", httpResInfo.method);
    //(void)printf("Path: %s\n", httpResInfo.path);
    //(void)printf("Protocol: %s\n", httpResInfo.protocol);
    //(void)printf("Connection: %s\n", httpResInfo.connection);

    const char *header_template = (
        "%s 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %d\r\n"
        "Connection: %s\r\n\r\n"
    );

    char filePath[PATH_SIZE];

    if(strcmp(httpResInfo.path, "/"))
        strcpy(filePath, "index.html");
    else
        strcpy(filePath, httpResInfo.path); 


    FILE* index_html = fopen("index.html", "r");
    fseek(index_html, 0, SEEK_END);
    httpResInfo.content_length = ftell(index_html);
    fseek(index_html, 0, SEEK_SET);

    int size_needed = snprintf(
        NULL,
        0,
        header_template,
        httpResInfo.protocol,
        httpResInfo.content_length,
        httpResInfo.connection
    ) + 1;

    char* http_header = (char*)malloc(size_needed);
    snprintf(
        http_header,
        size_needed,
        header_template,
        httpResInfo.protocol,
        httpResInfo.content_length,
        httpResInfo.connection
    );

    printf("%s", http_header);

    char* html_content = (char*)malloc(httpResInfo.content_length + 1);
    fread(html_content, 1, httpResInfo.content_length, index_html);
    html_content[httpResInfo.content_length] = '\0';

    char* http_res = (char*)malloc(strlen(http_header) + httpResInfo.content_length + 1);
    strcpy(http_res, http_header);
    strcat(http_res, html_content);

    send(client_fd, http_res, strlen(http_res), 0);

    free(http_header);
    free(html_content);
    free(http_res);

    //close(html_fd);
    close(client_fd);
    close(s);

    return 0;
}
