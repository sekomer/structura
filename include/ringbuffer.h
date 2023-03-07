#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <Python.h>

extern PyTypeObject RingBufferType;

typedef struct
{
    PyObject_HEAD;
    long capacity;
    long size;
    long head;
    long tail;
    PyObject **items;
} RingBuffer;

#endif /* RINGBUFFER_H */
