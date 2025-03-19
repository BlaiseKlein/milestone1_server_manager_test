//
// Created by blaise-klein on 2/5/25.
//

#ifndef TEST_VALUES_H
#define TEST_VALUES_H

#define request_serverUserCount req_buffer[0] == 0x1D && req_buffer[1] == 0x01

#define input_serverUserCount                                                                                                                                                                                                                                      \
    {                                                                                                                                                                                                                                                              \
        send_buffer[0] = 0x0A;                                                                                                                                                                                                                                     \
        send_buffer[1] = 0x01;                                                                                                                                                                                                                                     \
        send_buffer[2] = 0x30;                                                                                                                                                                                                                                     \
        send_buffer[3] = 0x04;                                                                                                                                                                                                                                     \
        send_buffer[4] = 0x02;                                                                                                                                                                                                                                     \
        send_buffer[5] = 0x02;                                                                                                                                                                                                                                     \
        send_buffer[6] = 0x00;                                                                                                                                                                                                                                     \
        send_buffer[7] = 0x0A;                                                                                                                                                                                                                                     \
        send_buffer[4] = 0x02; /*MsgCount*/                                                                                                                                                                                                                        \
        send_buffer[5] = 0x04;                                                                                                                                                                                                                                     \
        send_buffer[6] = 0x00;                                                                                                                                                                                                                                     \
        send_buffer[7] = 0x00;                                                                                                                                                                                                                                     \
        send_buffer[7] = 0x00;                                                                                                                                                                                                                                     \
        send_buffer[7] = 0x64;                                                                                                                                                                                                                                     \
    };

#define output_serverUserCount recv_buffer[0] == 0x0A && recv_buffer[1] == 0x03 && recv_buffer[2] == 0x30 && recv_buffer[3] == 0x03 && recv_buffer[4] == 0x0A && recv_buffer[5] == 0x01 && recv_buffer[6] == 0x0A

#define output_serverUserCount_size 7

// Server IP 192.168.0.1
#define output_clientGetIp                                                                                                                                                                                                                                         \
    recv_buffer[0] == 0x01 && recv_buffer[1] == 0x03 && recv_buffer[2] == 0x01 && recv_buffer[3] == 0x31 && recv_buffer[4] == 0x39 && recv_buffer[5] == 0x32 && recv_buffer[6] == 0x2E && recv_buffer[7] == 0x31 && recv_buffer[8] == 0x36 &&                      \
        recv_buffer[9] == 0x38 && recv_buffer[10] == 0x2E && recv_buffer[11] == 0x30 && recv_buffer[12] == 0x2e && recv_buffer[13] == 0x31

#define output_clientGetIp_size 14

#define output_serverStart req_buffer[0] == 0x14 && req_buffer[1] == 0x03 && req_buffer[2] == 0x00 && req_buffer[3] == 0x00

#define input_serverOnline                                                                                                                                                                                                                                         \
    {                                                                                                                                                                                                                                                              \
        send_buffer[0] = 0x0C;                                                                                                                                                                                                                                     \
        send_buffer[1] = 0x03;                                                                                                                                                                                                                                     \
        send_buffer[2] = 0x00;                                                                                                                                                                                                                                     \
        send_buffer[3] = 0x00;                                                                                                                                                                                                                                     \
    };

#define input_serverOffline                                                                                                                                                                                                                                        \
    {                                                                                                                                                                                                                                                              \
        send_buffer[0] = 0x0D;                                                                                                                                                                                                                                     \
        send_buffer[1] = 0x03;                                                                                                                                                                                                                                     \
        send_buffer[2] = 0x00;                                                                                                                                                                                                                                     \
        send_buffer[3] = 0x00;                                                                                                                                                                                                                                     \
    };

#define output_serverStop req_buffer[0] == 0x15 && req_buffer[1] == 0x03 && req_buffer[2] == 0x00 && req_buffer[3] == 0x00

#endif    // TEST_VALUES_H
