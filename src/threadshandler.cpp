#include "../include/threadshandler.h"

ThreadsHandler::ThreadsHandler() {
    sizeBuf = 0;
    pthread_mutex_init(&clToSer, NULL);
    pthread_cond_init(&cl, NULL);
    pthread_mutex_init(&serAllocMem, NULL);
    pthread_cond_init(&al, NULL);
    pthread_cond_init(&setBffr, NULL);
}

ThreadsHandler::~ThreadsHandler() {
    //usun obiekty
    pthread_cond_init(&setBffr, NULL);
    pthread_cond_destroy(&al);
    pthread_mutex_destroy(&serAllocMem);
    pthread_cond_destroy(&cl);
    pthread_mutex_destroy(&clToSer);
    if( buffer != NULL) delete[] buffer;
}

void ThreadsHandler::addNum(int num) {
    pthread_mutex_lock(&clToSer);
    //dodaj liczbe do listy i wyslij sygnal - zmienna cl
    cslist.push_back(num);
    pthread_cond_signal(&cl);
    pthread_mutex_unlock(&clToSer);

}

int ThreadsHandler::getNum() {
    pthread_mutex_lock(&clToSer);
    // jesli lista z numerami jest pusta:
    //czekaj (az inny watek cos doda) i zwolnij mutex na ten czas
    while(cslist.empty()) {
        pthread_cond_wait(&cl, &clToSer);
    }
    int t = cslist.front();
    cslist.pop_front();
    pthread_mutex_unlock(&clToSer);
    return t;
}

char* ThreadsHandler::getBuffer(int len) {
    pthread_mutex_lock(&serAllocMem);
    sizeBuf = len;
    //wyslij sygnal, ze mozna juz przydzielac bufor o wielkosc char[sizeBuf]
    pthread_cond_signal(&setBffr);
    //jesli buffer jest pusty czekaj, az inny watek (alokatora) przydzieli mi pamiec
    while(buffer == NULL) {
        pthread_cond_wait(&al, &serAllocMem);
    }
    char* t = buffer;
    //od razu zmieniam wartosc wskaznika buffer na null(nie usuwam danych ze sterty), aby
    // zakomunikowac, ze dane przechodza do watku serwera
    buffer = NULL;
    sizeBuf = 0;
    pthread_mutex_unlock(&serAllocMem);
    return t;
}

void ThreadsHandler::setBuffer() {
    pthread_mutex_lock(&serAllocMem);
    //czekam na sygnal, ze moge przydzielic bufor,
    //jesli sizeBuff jest ==0, w innym przypadku przydzielam pamiec
    while(sizeBuf == 0) {
        pthread_cond_wait(&setBffr, &serAllocMem);
    }
    buffer = new char[sizeBuf];
    pthread_cond_signal(&al);
    pthread_mutex_unlock(&serAllocMem);
}
