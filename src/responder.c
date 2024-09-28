#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

#include "albatross.h"
#include "responder.h"

int findFile(HttpResponse* httpRes)
{
    char filePath[BUFFER_SIZE] = {0};

    if(strcmp(httpRes->path, "/"))
        strcpy(filePath, "/index.html");

    int html_fd = open(filePath, O_RDONLY);

    if(html_fd < 0)
    {
        strcpy(httpRes->status, "404");
        return -1;
    }
    else
        strcpy(httpRes->status, "200");

    struct stat fileStat;
    (void)fstat(html_fd, &fileStat);
    httpRes->content = fileStat.st_size;    
    
    close(html_fd);

    return html_fd;
}

void httpHeaderBuilder(HttpResponse* httpRes)
{
    if(strcmp(httpRes->status, "200")) 
        printf("%s\n", httpRes->status);
    else if(strcmp(httpRes->status, "404"))
        printf("%s\n", httpRes->status);
}
