#include "../include/watcher.h"

Watcher::Watcher() {
    pthread_mutex_init(&m, NULL);
}

//sprawdz czy przekazany id znajduje sie w kontenerze w klasie
bool Watcher::check(pthread_t t) {
    pthread_mutex_lock(&m);
    if(idThreads.empty()) {
        pthread_mutex_unlock(&m);
        return false;
    }
    for(int i = 0; i < idThreads.size(); ++i) {
        if(t == idThreads.at(i)) {
            pthread_mutex_unlock(&m);
            return true;
        }
    }
    pthread_mutex_unlock(&m);
    return false;
}

//zaraportuj(dodaj swoj id watku) do klasy
void Watcher::report(pthread_t t) {
    pthread_mutex_lock(&m);
    idThreads.push_back(t);
    pthread_mutex_unlock(&m);
}

//zresetuj zawartosc klasy
void Watcher::reset() {
    pthread_mutex_lock(&m);
    if(!idThreads.empty())
        idThreads.erase(idThreads.begin(), idThreads.end());
    pthread_mutex_unlock(&m);
}
