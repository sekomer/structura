#ifndef QUEUE_H
#define QUEUE_H

#include <Python.h>

extern PyTypeObject QueueType;

typedef struct
{
    PyObject_HEAD;
    long capacity;
    long size;
    long head;
    long tail;
    PyObject **items;
} Queue;

#endif
