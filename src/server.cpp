#include "../include/server.h"

extern Watcher watch;

Server::Server() {
    num = 0;
    len = 0;
    buffer = NULL;
}

Server::~Server() {
    if(buffer != NULL)
        delete[] buffer;
}

void Server::getNumber(ThreadsHandler* thrHandler) {
    //pobierz wylosowany w innym watku numer
    num = thrHandler->getNum();
    //oblicz ile cyfr ma liczba
    calcSizeOfNum();
}

void Server::getBuffer(ThreadsHandler* thrHandler) {
    //pobierz adres zalokowanej pamieci
    buffer = thrHandler->getBuffer(len +1);
    sprintf(buffer, "%d", num);
}

void Server::writeToScreen() {
    //celowo nie daje kolejnego mutexu do obslugi strumieni
    std::cout << buffer << "\n";
    //jesli num z zakresu <> nie rob nic
    while(num < 1001) { // (num < 1001 && num > -1) jesli zmienna num moglaby byc rowniez ujemna
        sleep(1);
        // funkcja w main.cpp co 2 sekundy resetuje watcher. Jesli w tym czasie program nie doda
        // do klasy watcher swojego id kod w instrukcja warunkowa if przerwie petle
        if(!watch.check(pthread_self())) break;
    }
}

void Server::freeBuffer() {
    //wyczysc i zwolnij pamiec
    if ( buffer != NULL)
        delete[] buffer;
    buffer = NULL;
}

void Server::calcSizeOfNum() {
    len = 0;
    if(num<10) {
        len = 1;
        return;
    }
        // (num<10 && mum > -10) jesli zmienna num moglaby byc rowniez ujemna
    int temp = num;
    while(temp) {
        temp /= 10;
        ++len;
    }
}
