//
// Created by blaise-klein on 1/30/25.
//
#include "testServer.h"
#include "copy.h"
#include "open.h"
#include "test_values.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CURRENT_TEST_COUNT 2
#define MAXMSGLEN 1024
int     generateTestArray(int (**func_array)(int, char *), int *size);
int     setupSocket(char *ip, char *port);
int     validTest_serverUserCount(int fd, char *msg);
int     maxTest_serverUserCount(int fd);
int     validTest_clientGetIp(int fd, char *msg);
int     validTest_serverStartOnline(int fd, char *msg);
int     validTest_serverStartOffline(int fd, char *msg);
int     validTest_serverStopOnline(int fd, char *msg);
int     validTest_serverStopOffline(int fd, char *msg);
ssize_t write_fully(int sockfd, const void *buf, ssize_t len, int *err);
ssize_t read_fully(int sockfd, void *buf, ssize_t len, int *err);

int runTestSuite(const char *manager_ip, const char *manager_port)
{
    int       err = 0;
    int       fd  = 0;
    in_port_t net_port;
    int (**tests)(int fd, char *msg);
    int test_count;
    net_port = parse_in_port_t(manager_port, &err);
    if(err != 0)
    {
        perror("port setup failed");
        return -1;
    }

    fd = open_network_socket_client(manager_ip, net_port, &err);
    if(err != 0 || fd == -1)
    {
        perror("socket setup failed");
        return -1;
    }

    test_count = CURRENT_TEST_COUNT;
    tests      = (int (**)(int, char *))malloc((size_t)test_count * sizeof(int (*)(int, char *)));
    if(tests == NULL)
    {
        return -1;
    }
    err = generateTestArray(tests, &test_count);
    if(err != 0)
    {
        perror("Not enough tests to load");
        free((void *)tests);
        return -1;
    }

    for(int i = 0; i < test_count; i++)
    {
        char *message = NULL;
        int   result  = 0;

        message = (char *)malloc(MAXMSGLEN);

        result = tests[i](fd, message);
        displayTestState(i, message, result);
        if(message != NULL)
        {
            free(message);
        }
    }

    free((void *)tests);
    return 0;
}

void displayTestState(int testNumber, const char *testMessage, int status)
{
    if(testMessage != NULL)
    {
        printf("Test #%d: %s\n", testNumber, testMessage);
    }
    printf("Success State: %d\n", status);
}

int generateTestArray(int (**func_array)(int, char *), int *size)
{
    int count = *size;
    int index = 0;

    if(count > 0)
    {
        func_array[index] = &validTest_serverUserCount;
        count--;
        index++;
    }

    if(count > 0)
    {
        func_array[index] = &validTest_clientGetIp;
        count--;
        index++;
    }

    if(count > 0)
    {
        func_array[index] = &validTest_serverStartOnline;
        count--;
        index++;
    }

    if(count > 0)
    {
        func_array[index] = &validTest_serverStartOffline;
        count--;
        index++;
    }

    if(count > 0)
    {
        func_array[index] = &validTest_serverStopOnline;
        count--;
        index++;
    }

    if(count > 0)
    {
        func_array[index] = &validTest_serverStopOffline;
        count--;
        index++;
    }
    *size = CURRENT_TEST_COUNT;

    if(index == 0)
    {
        return -1;
    }

    return count;
}

int validTest_serverUserCount(int fd, char *msg)
{
    int           err         = 0;
    ssize_t       result      = 0;
    const ssize_t msg_len     = 14;
    const ssize_t req_len     = 2;
    const char    s[]         = "Server user";
    const char    c[]         = "server user count sent correctly";
    uint8_t      *req_buffer  = NULL;
    uint8_t      *send_buffer = NULL;
    uint8_t      *recv_buffer = NULL;

    req_buffer = (uint8_t *)malloc((size_t)req_len);
    if(req_buffer == NULL)
    {
        return -1;
    }
    result = read_fully(fd, req_buffer, req_len, &err);
    free((void *)req_buffer);
    if(result != 0)
    {
        return -1;
    }

    send_buffer = (uint8_t *)malloc((size_t)msg_len);
    if(send_buffer == NULL)
    {
        return -1;
    }

    input_serverUserCount

        result = write_fully(fd, send_buffer, msg_len, &err);
    free(send_buffer);
    if(err != 0 || result != msg_len)
    {
        return -1;
    }

    recv_buffer = (uint8_t *)malloc(MAXMSGLEN);
    if(recv_buffer == NULL)
    {
        return -1;
    }

    result = read_fully(fd, recv_buffer, output_serverUserCount_size, &err);
    if(result < 0)
    {
        return 0;
    }

    // Checking recv_buffer for proper format
    if(output_serverUserCount)
    {
        strncpy(msg, s, strlen(s) + sizeof(char));
        free(recv_buffer);
        return 0;
    }

    free(recv_buffer);

    strncpy(msg, c, strlen(c) + sizeof(char));
    return 0;
}

int maxTest_serverUserCount(int fd)
{
    close(fd);
    return 0;
}

int validTest_serverStartOnline(int fd, char *msg)
{
    int           err         = 0;
    ssize_t       result      = 0;
    const ssize_t req_len     = 2;
    const ssize_t send_len    = 4;
    const char    s[]         = "Server start failed";
    const char    c[]         = "server start sent correctly, returning online";
    uint8_t      *req_buffer  = NULL;
    uint8_t      *send_buffer = NULL;

    req_buffer = (uint8_t *)malloc((size_t)req_len);
    if(req_buffer == NULL)
    {
        return -1;
    }
    result = read_fully(fd, req_buffer, req_len, &err);
    if(result != 0)
    {
        free((void *)req_buffer);
        return -1;
    }

    if(output_serverStart)
    {
        free((void *)req_buffer);
        strncpy(msg, s, strlen(s) + sizeof(char));
        return 0;
    }
    free((void *)req_buffer);

    send_buffer               = (uint8_t *)malloc((size_t)send_len);
    input_serverOnline result = write_fully(fd, send_buffer, send_len, &err);
    if(result != 0)
    {
        free((void *)send_buffer);
        return -1;
    }
    free((void *)send_buffer);

    strncpy(msg, c, strlen(c) + sizeof(char));
    return 0;
}

int validTest_serverStartOffline(int fd, char *msg)
{
    int           err         = 0;
    ssize_t       result      = 0;
    const ssize_t req_len     = 2;
    const ssize_t send_len    = 4;
    const char    s[]         = "Server start failed";
    const char    c[]         = "server start sent correctly, returning online";
    uint8_t      *req_buffer  = NULL;
    uint8_t      *send_buffer = NULL;

    req_buffer = (uint8_t *)malloc((size_t)req_len);
    if(req_buffer == NULL)
    {
        return -1;
    }
    result = read_fully(fd, req_buffer, req_len, &err);
    if(result != 0)
    {
        free((void *)req_buffer);
        return -1;
    }

    if(output_serverStart)
    {
        free((void *)req_buffer);
        strncpy(msg, s, strlen(s) + sizeof(char));
        return 0;
    }
    free((void *)req_buffer);

    send_buffer                = (uint8_t *)malloc((size_t)send_len);
    input_serverOffline result = write_fully(fd, send_buffer, send_len, &err);
    if(result != 0)
    {
        free((void *)send_buffer);
        return -1;
    }
    free((void *)send_buffer);

    strncpy(msg, c, strlen(c) + sizeof(char));
    return 0;
}

int validTest_serverStopOnline(int fd, char *msg)
{
    int           err         = 0;
    ssize_t       result      = 0;
    const ssize_t req_len     = 2;
    const ssize_t send_len    = 4;
    const char    s[]         = "Server stop failed";
    const char    c[]         = "server stop sent correctly";
    uint8_t      *req_buffer  = NULL;
    uint8_t      *send_buffer = NULL;

    req_buffer = (uint8_t *)malloc((size_t)req_len);
    if(req_buffer == NULL)
    {
        return -1;
    }
    result = read_fully(fd, req_buffer, req_len, &err);
    if(result != 0)
    {
        free((void *)req_buffer);
        return -1;
    }

    if(output_serverStop)
    {
        free((void *)req_buffer);
        strncpy(msg, s, strlen(s) + sizeof(char));
        return 0;
    }
    free((void *)req_buffer);

    send_buffer               = (uint8_t *)malloc((size_t)send_len);
    input_serverOnline result = write_fully(fd, send_buffer, send_len, &err);
    if(result != 0)
    {
        free((void *)send_buffer);
        return -1;
    }
    free((void *)send_buffer);

    strncpy(msg, c, strlen(c) + sizeof(char));
    return 0;
}

int validTest_serverStopOffline(int fd, char *msg)
{
    int           err         = 0;
    ssize_t       result      = 0;
    const ssize_t req_len     = 2;
    const ssize_t send_len    = 4;
    const char    s[]         = "Server stop failed";
    const char    c[]         = "server stop sent correctly";
    uint8_t      *req_buffer  = NULL;
    uint8_t      *send_buffer = NULL;

    req_buffer = (uint8_t *)malloc((size_t)req_len);
    if(req_buffer == NULL)
    {
        return -1;
    }
    result = read_fully(fd, req_buffer, req_len, &err);
    if(result != 0)
    {
        free((void *)req_buffer);
        return -1;
    }

    if(output_serverStop)
    {
        free((void *)req_buffer);
        strncpy(msg, s, strlen(s) + sizeof(char));
        return 0;
    }
    free((void *)req_buffer);

    send_buffer                = (uint8_t *)malloc((size_t)send_len);
    input_serverOffline result = write_fully(fd, send_buffer, send_len, &err);
    if(result != 0)
    {
        free((void *)send_buffer);
        return -1;
    }
    free((void *)send_buffer);

    strncpy(msg, c, strlen(c) + sizeof(char));
    return 0;
}

int validTest_clientGetIp(int fd, char *msg)
{
    int           err         = 0;
    ssize_t       result      = 0;
    const ssize_t msg_len     = 2;
    const char    s[]         = "Server user";
    const char    c[]         = "server user count sent correctly";
    uint8_t      *send_buffer = NULL;
    uint8_t      *recv_buffer = NULL;
    send_buffer               = (uint8_t *)malloc((size_t)msg_len);
    if(send_buffer == NULL)
    {
        return -1;
    }

    send_buffer[0] = 0x01;
    send_buffer[1] = 0x01;

    result = write_fully(fd, send_buffer, msg_len, &err);
    free(send_buffer);
    if(err != 0 || result != msg_len)
    {
        return -1;
    }

    recv_buffer = (uint8_t *)malloc(MAXMSGLEN);
    if(recv_buffer == NULL)
    {
        return -1;
    }

    result = read_fully(fd, recv_buffer, output_clientGetIp_size, &err);
    if(result < 0)
    {
        free(recv_buffer);
        return -1;
    }

    // Checking recv_buffer for proper format of IP address
    if(output_clientGetIp)    // Server IP 192.168.0.1
    {
        strncpy(msg, s, strlen(s) + sizeof(char));
        free(recv_buffer);
        return 0;
    }

    free(recv_buffer);

    strncpy(msg, c, strlen(c) + sizeof(char));
    return 0;
}

ssize_t read_fully(int sockfd, void *buf, ssize_t len, int *err)
{
    ssize_t total_read = 0;

    while(total_read < len)
    {
        ssize_t bytes_read;

        bytes_read = read(sockfd, (char *)buf + total_read, (size_t)(len - total_read));
        if(bytes_read == -1)
        {
            *err = -1;
            return 0;
        }

        total_read += bytes_read;
    }

    return total_read;
}

ssize_t write_fully(int sockfd, const void *buf, ssize_t len, int *err)
{
    ssize_t total_written = 0;

    while(total_written < len)
    {
        ssize_t bytes_written;

        bytes_written = write(sockfd, (const char *)buf + total_written, (size_t)(len - total_written));
        if(bytes_written == -1)
        {
            *err = -1;
            return 0;
        }

        total_written += bytes_written;
    }

    return total_written;
}
