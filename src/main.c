#include <sys/socket.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>

#include "albatross.h"
#include "parser.h"
#include "responder.h"

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

    HttpResponse httpRes = {0};
    parse(buffer, &httpRes); 
    int html_fd = findFile(&httpRes);
    httpHeaderBuilder(&httpRes);

    //char* file = buffer + 5;
    //*strchr(file, ' ') = 0;

    //int opened_fd = open(file, O_RDONLY);
    sendfile(client_fd, html_fd, 0, BUFFER_SIZE);

    close(html_fd);
    close(client_fd);
    close(s);

    return 0;
}
