#include "../include/allocatorbuffer.h"

AllocatorBuffer::AllocatorBuffer() {

}

AllocatorBuffer::~AllocatorBuffer() {
    if(buff != NULL) delete[] buff;
}

void setBuffer();
