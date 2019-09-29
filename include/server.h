#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "../include/watcher.h"
#include "../include/threadshandler.h"
const int threadWait = 1000; //miliseconds

class Server
{
private:
    int num;
    char* buffer;
    int len;
public:
    Server();
    ~Server();
    void getNumber(ThreadsHandler* thrHandler);
    void getBuffer(ThreadsHandler* thrHandler);
    void writeToScreen();
    void freeBuffer();
private:
    void calcSizeOfNum();
};

#endif // SERVER_H
