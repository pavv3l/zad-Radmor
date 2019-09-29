#ifndef THREADSHANDLER_H
#define THREADSHANDLER_H
#include <pthread.h>
#include <list>

class ThreadsHandler
{
private:
    //zmienna warunkowa dla zapytan serwer-klient
    pthread_mutex_t clToSer;
    pthread_cond_t cl;
    std::list<int> cslist;
    //zmienna warunkowa dla zapytan serwer - alokuj pamiec
    pthread_mutex_t serAllocMem;
    pthread_cond_t al;
    pthread_cond_t setBffr;
    char* buffer;
    int sizeBuf;

public:
    ThreadsHandler();
    ~ThreadsHandler();
    void addNum(int num);
    int getNum();
    char* getBuffer(int len);
    void setBuffer();
};

#endif // THREADSHANDLER_H
