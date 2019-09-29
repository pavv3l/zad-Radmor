#ifndef WATCHER_H
#define WATCHER_H
#include <vector>
#include <pthread.h>

class Watcher
{
private:
    std::vector<pthread_t> idThreads;
    pthread_mutex_t m;
public:
    Watcher();
    bool check(pthread_t t);
    void report(pthread_t t);
    void reset();
};

#endif // WATCHER_H
