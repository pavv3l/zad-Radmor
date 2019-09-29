#ifndef ALLOCATORBUFFER_H
#define ALLOCATORBUFFER_H


class AllocatorBuffer
{
private:
    char* buff;
    int size;
public:
    AllocatorBuffer();
    ~AllocatorBuffer();
    void setBuffer();
};

#endif // ALLOCATORBUFFER_H
