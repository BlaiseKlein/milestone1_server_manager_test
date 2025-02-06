//
// Created by blaise-klein on 1/30/25.
//

#ifndef TESTSERVER_H
#define TESTSERVER_H

int  runTestSuite(const char *manager_ip, const char *manager_port);
void displayTestState(int testNumber, const char *testMessage, int status);

#endif    // TESTSERVER_H
