#include "../include/client.h"

Client::Client() {
    // zapisz id watku
    idThread = pthread_self();
}

Client::~Client() {
    writeToFile();
}

void Client::addRandNumber(ThreadsHandler* thrHandler) {
    //wylosuj liczbe, zapisz do kontenera i wyslij do uchwytu thrHandler
    randVec.push_back(rand());
    thrHandler->addNum(randVec.back());
    //dopisywanie do pliku po przekroczeniu ustalonego rozmiaru(vacMAxSize) kontenera
    //if(randVec.size() > vecMaxSize) {
        //writeToFile();
    //    randVec.erase(randVec.begin(), randVec.end());
    //    randVec.clear() - cpp11
    //}

}
void Client::writeToFile() {
    //zapisz do pliku log wylosowane liczby
    //problemy z funkcja itoa, uzylem innego sposobu, mozna bylo uzyc rowniez std::string std::to_string(int) z cpp11
    std::stringstream sstr;
    sstr << idThread;
    std::string str = sstr.str();
    std::string filName = "Thread " + str + ".log";
    std::ofstream clientLog;
    clientLog.open(filName.c_str(), std::ios::out | std::ios::app); // dopisywanie do pliku
    for(int i = 0; i < randVec.size(); ++i) {
        clientLog << randVec.at(i) << "\n";
    }
    clientLog.close();
}
