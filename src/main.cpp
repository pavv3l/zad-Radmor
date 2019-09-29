#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <signal.h>
#include "../include/client.h"
#include "../include/server.h"
#include "../include/threadshandler.h"
#include "../include/watcher.h"

Watcher watch;
const int waitClient = 1; //sekundy
const int waitWatcher = 2; //sekundy
const int Thr = 7; // liczba watkow
bool run = true;

void* client(void* thrHand);
void* server(void* thrHand);
void* allocMem(void* thrHand);
void* watchdog(void* thrHand);
void sigHand(int sig);

int main(int argc, char** argv) {
    signal(SIGINT, sigHand);
    std::srand(time(NULL));
    ThreadsHandler thrHandler;
    pthread_t threads[Thr];
    pthread_create(&threads[0], NULL, client, (void*) &thrHandler);
    pthread_create(&threads[1], NULL, client, (void*) &thrHandler);
    pthread_create(&threads[2], NULL, client, (void*) &thrHandler);
    pthread_create(&threads[3], NULL, server, (void*) &thrHandler);
    pthread_create(&threads[4], NULL, server, (void*) &thrHandler);
    pthread_create(&threads[5], NULL, allocMem, (void*) &thrHandler);
    pthread_create(&threads[6], NULL, watchdog, (void*) &thrHandler);

    for (int i = 0; i < Thr; ++i) {
        pthread_join(threads[i], NULL);
    }
    getchar();
    exit(0);
}

void* client(void* thrHand) {
    ThreadsHandler* thr = (ThreadsHandler*) thrHand;
    Client cl;
    while(run) {
        cl.addRandNumber(thr);
        //czekaj 1s
        sleep(waitClient);
    }
    return 0;
}

void* server(void* thrHand) {
    ThreadsHandler* thr = (ThreadsHandler*) thrHand;
    Server srv;
    while(run) {
        watch.report(pthread_self());
        srv.getNumber(thr);
        srv.getBuffer(thr);
        srv.writeToScreen();
        srv.freeBuffer();
    }
    return 0;
}

void* allocMem(void* thrHand) {
    ThreadsHandler* thr = (ThreadsHandler*) thrHand;
    while(run) {
        thr->setBuffer();
    }
    return 0;
}

void* watchdog(void* thrHand) {
    ThreadsHandler* thr = (ThreadsHandler*) thrHand;
    while(run) {
        //co $waitWatcher sekund zresetuj watcher
        watch.reset();
        //sleep(waitWatcher);
    }
}

void sigHand(int sig) {
    std::cout << "Catch sigint\n";
    //ustaw run na false i zakoncz watki
    run = false;
    //w cpp 11 napisalbym
    //       include <chrono>
    //       include <thread>
    //       std::this_thread::sleep_for(std::chrono::milliseconds(100))
    sleep(1);
    exit(1);
}
