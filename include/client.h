#ifndef CLIENT_H
#define CLIENT_H
#include <vector>
#include <pthread.h>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "../include/threadshandler.h"

//const int vecMaxSize = 100000;

class Client
{
private:
    pthread_t idThread;
    std::vector<int> randVec;
public:
    Client();
    ~Client();
    void addRandNumber(ThreadsHandler* thrHandler);
    void writeToFile();
};

#endif // CLIENT_H
