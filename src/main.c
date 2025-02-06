#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <testServer.h>

int main(void)
{
    const char *ip       = "127.0.0.1";
    const char *port     = "8080";
    char       *ip_str   = NULL;
    char       *port_str = NULL;

    ip_str = (char *)malloc(strlen(ip) + sizeof(char));
    if(ip_str == NULL)
    {
        printf("malloc failed\n");
        return -1;
    }
    strcpy(ip_str, ip);
    port_str = (char *)malloc(strlen(port) + sizeof(char));
    if(port_str == NULL)
    {
        free(ip_str);
        printf("malloc failed\n");
        return -1;
    }
    strcpy(port_str, port);
    runTestSuite(ip_str, port_str);

    free(ip_str);
    free(port_str);
    return EXIT_SUCCESS;
}
