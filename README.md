# **Guide**

## **Startup**
This project can be compiled using the ./build.sh command as long as files.txt exists and contains the following:

    main src/main.c src/open.c include/open.h src/copy.c include/copy.h src/testServer.c include/testServer.h include/test_values.h

To run, simple run the executable at ./build/main

## **Version 2**
To update the server manager IP and port, change the ip and port strings in main.c.

To change the number of tests being run, change the CURRENT_TEST_COUNT macro value in testServer.c.

Current tests:

1. Server count and reply
2. Client get IP and reply
3. Start server and returns online
4. Start server and returns offline
5. Stop server and returns online
6. Stop server and returns offline