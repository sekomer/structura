#ifndef HASHMAP_H
#define HASHMAP_H

#include <Python.h>

extern PyTypeObject HashMapType;

typedef struct _Node
{
    PyObject *key;
    PyObject *value;
    Py_uhash_t hash; // long int

    struct _Node *next;
} Node;

typedef struct
{
    PyObject_HEAD;
    long size;
    long capacity;
    double load_factor;
    Node **buckets;
    Py_uhash_t (*hash)(PyObject *);
    int (*compare)(PyObject *, PyObject *, int);
} HashMap;

#endif /* HASHMAP_H */
