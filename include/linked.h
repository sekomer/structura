#ifndef LINKED_H
#define LINKED_H

#include <Python.h>

extern PyTypeObject LinkedType;

// double linked list
typedef struct _LinkedNode
{
    PyObject *data;
    struct _LinkedNode *prev;
    struct _LinkedNode *next;
} LinkedNode;

typedef struct
{
    PyObject_HEAD;
    long size;
    LinkedNode *head;
    LinkedNode *tail;
} Linked;

#endif /* LINKED_H */