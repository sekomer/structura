#ifndef STACK_H
#define STACK_H

#include <Python.h>

extern PyTypeObject StackType;

typedef struct
{
    PyObject_HEAD;
    long top;
    long size;
    long capacity;
    PyObject **items;
} Stack;

#endif /* STACK_H */
