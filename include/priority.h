#ifndef PRIORITY_H
#define PRIORITY_H

#include <Python.h>

extern PyTypeObject PriorityQueueType;

typedef struct _Node
{
    PyObject *value;
    PyObject *priority;

    struct _Node *next;
    struct _Node *prev;
} PriorityNode;

typedef struct
{
    PyObject_HEAD;
    long size;
    PriorityNode *head;
    PriorityNode *tail;
} PriorityQueue;

#endif /* PRIORITY_H */
