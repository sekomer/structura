#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include <structmember.h>
#include "../include/hashmap.h"

// define error number returned from the hash function
const Py_uhash_t HASH_ERROR = (Py_uhash_t)-1;

Py_uhash_t PyObject_Unsigned_Hash(PyObject *obj)
{
    Py_hash_t hash = PyObject_Hash(obj);
    if (hash == -1)
        return HASH_ERROR;

    return (Py_uhash_t)hash;
}

static PyObject *
HashMap_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    HashMap *self;
    self = (HashMap *)type->tp_alloc(type, 0);

    if (self != NULL)
    {
        self->size = 0;
        self->capacity = 0;
        self->load_factor = 0.0;
        self->buckets = NULL;
        self->hash = NULL;
        self->compare = NULL;
    }

    return (PyObject *)self;
}

static int
HashMap_init(HashMap *self, PyObject *args, PyObject *kwds)
{
    long capacity = 16;
    double load_factor = 0.75;
    static char *kwlist[] = {"capacity", "load_factor", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|ld", kwlist, &capacity, &load_factor))
        return -1;

    if (capacity <= 0)
    {
        PyErr_SetString(PyExc_ValueError, "Initial capacity must be greater than 0");
        return -1;
    }

    if (load_factor <= 0.0 || load_factor >= 1.0)
    {
        PyErr_SetString(PyExc_ValueError, "Load factor must be greater than 0 and less than 1");
        return -1;
    }

    self->capacity = capacity;
    self->load_factor = load_factor;

    self->buckets = (Node **)PyMem_Malloc(self->capacity * sizeof(Node *));

    for (int i = 0; i < self->capacity; i++)
        self->buckets[i] = NULL;

    self->hash = &PyObject_Unsigned_Hash;
    self->compare = &PyObject_RichCompareBool;

    return 0;
}

static void
HashMap_dealloc(HashMap *self)
{
    for (int i = 0; i < self->capacity; i++)
    {
        Node *current = self->buckets[i];
        while (current != NULL)
        {
            Node *next = current->next;
            Py_DecRef(current->key);
            Py_DecRef(current->value);
            PyMem_Free(current);
            current = next;
        }
    }

    PyMem_Free(self->buckets);
    Py_TYPE(self)->tp_free((PyObject *)self);
}

void HashMap_resize(HashMap *self)
{
    // get the new capacity
    long new_capacity = self->capacity * 2;

    // create a new array of buckets
    Node **new_buckets = (Node **)PyMem_Malloc(new_capacity * sizeof(Node *));

    // initialize the new buckets
    for (int i = 0; i < new_capacity; i++)
        new_buckets[i] = NULL;

    // rehash the key-value pairs
    for (int i = 0; i < self->capacity; i++)
    {
        Node *current = self->buckets[i];
        while (current != NULL)
        {
            // get the index of the new bucket
            long index = current->hash % new_capacity;

            // get the new bucket
            Node *new_bucket = new_buckets[index];

            // create a new node
            Node *node = (Node *)PyMem_Malloc(sizeof(Node));
            node->key = current->key;
            node->value = current->value;
            node->hash = current->hash;
            node->next = new_bucket;

            // update the new bucket
            new_buckets[index] = node;

            // move to the next node
            current = current->next;
        }
    }

    // free the old buckets
    PyMem_Free(self->buckets);

    // update the hashmap
    self->buckets = new_buckets;
    self->capacity = new_capacity;
}

// add a new key-value pair to the hashmap
static PyObject *
HashMap_put(HashMap *self, PyObject *args)
{
    PyObject *key;
    PyObject *value;

    if (!PyArg_ParseTuple(args, "OO", &key, &value))
        return NULL;

    Py_uhash_t hash = self->hash(key);
    if (hash == HASH_ERROR)
    {
        PyErr_SetString(PyExc_TypeError, "Key is not hashable\n"
                                         "Hashable types are: int, float, str, tuple, frozenset, "
                                         "type, NoneType, bool, bytes, bytearray, memoryview, range,"
                                         "slice, complex, set, frozenset, dict, array, datetime, enum,"
                                         "and any user-defined class that implements __hash__ and __eq__");
        return NULL;
    }

    size_t index = hash % self->capacity;

    // get the bucket
    Node *bucket = self->buckets[index];

    // check if the key already exists
    Node *current = bucket;
    while (current != NULL)
    {
        if (self->compare(current->key, key, Py_EQ))
        {
            // key already exists, update the value
            Py_DecRef(current->value);
            current->value = value;
            Py_IncRef(value);
            Py_RETURN_NONE;
        }

        current = current->next;
    }

    // key does not exist, create a new node
    Node *node = (Node *)PyMem_Malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->hash = hash;
    node->next = bucket;

    // increment the size
    self->size++;

    // update the bucket
    self->buckets[index] = node;

    // increment the reference count of the key and value
    Py_IncRef(key);
    Py_IncRef(value);

    // resize the hashmap if the load factor is exceeded
    if ((double)self->size / (double)self->capacity > self->load_factor)
        HashMap_resize(self);

    Py_RETURN_NONE;
}

static PyObject *
HashMap_remove(HashMap *self, PyObject *args)
{
    PyObject *key;

    if (!PyArg_ParseTuple(args, "O", &key))
        return NULL;

    Py_uhash_t hash = self->hash(key);
    if (hash == HASH_ERROR)
    {
        PyErr_SetString(PyExc_TypeError, "Key is not hashable\n"
                                         "Hashable types are: int, float, str, tuple, frozenset, "
                                         "type, NoneType, bool, bytes, bytearray, memoryview, range,"
                                         "slice, complex, set, frozenset, dict, array, datetime, enum,"
                                         "and any user-defined class that implements __hash__ and __eq__");
        return NULL;
    }

    size_t index = hash % self->capacity;

    // get the bucket
    Node *bucket = self->buckets[index];

    // check if the key already exists
    Node *current = bucket;
    Node *previous = NULL;
    while (current != NULL)
    {
        if (self->compare(current->key, key, Py_EQ))
        {
            // key already exists, remove the node
            if (previous == NULL)
                self->buckets[index] = current->next;
            else
                previous->next = current->next;

            // decrement the size
            self->size--;

            // decrement the reference count of the key and value
            Py_DecRef(current->key);
            Py_DecRef(current->value);

            // free the memory
            PyMem_Free(current);

            Py_RETURN_NONE;
        }

        previous = current;
        current = current->next;
    }

    // key does not exist, raise an exception
    PyErr_SetString(PyExc_KeyError, "Key does not exist");
    return NULL;
}

static PyObject *
HashMap_get(HashMap *self, PyObject *args)
{
    PyObject *key;

    if (!PyArg_ParseTuple(args, "O", &key))
        return NULL;

    Py_uhash_t hash = self->hash(key);
    size_t index = hash % self->capacity;

    // get the bucket
    Node *bucket = self->buckets[index];

    // check if the key already exists
    Node *current = bucket;
    while (current != NULL)
    {
        if (self->compare(current->key, key, Py_EQ))
        {
            // key already exists, return the value
            Py_IncRef(current->value);
            return current->value;
        }

        current = current->next;
    }

    // key does not exist, raise an exception
    PyErr_SetString(PyExc_KeyError, "Key does not exist");
    return NULL;
}

static PyObject *
HashMap_size(HashMap *self)
{
    return PyLong_FromLong(self->size);
}

static PyObject *
HashMap_capacity(HashMap *self)
{
    return PyLong_FromLong(self->capacity);
}

static PyObject *
HashMap_load_factor(HashMap *self)
{
    return PyFloat_FromDouble(self->load_factor);
}

static PyObject *
HashMap_keys(HashMap *self)
{
    PyObject *keys = PyList_New(0);

    for (int i = 0; i < self->capacity; i++)
    {
        Node *current = self->buckets[i];
        while (current != NULL)
        {
            PyList_Append(keys, current->key);
            current = current->next;
        }
    }

    return keys;
}

static PyGetSetDef HashMap_getsetters[] = {
    {"size", (getter)HashMap_size, NULL, "Size of the hashmap", NULL},
    {"capacity", (getter)HashMap_capacity, NULL, "Capacity of the hashmap", NULL},
    {"load_factor", (getter)HashMap_load_factor, NULL, "Load factor of the hashmap", NULL},
    {NULL} /* Sentinel */
};

static PyMemberDef HashMap_members[] = {
    {NULL} /* Sentinel */
};

static PyMethodDef HashMap_methods[] = {
    {"get", (PyCFunction)HashMap_get, METH_VARARGS, "Get the value of a key"},
    {"remove", (PyCFunction)HashMap_remove, METH_VARARGS, "Remove a key-value pair"},
    {"put", (PyCFunction)HashMap_put, METH_VARARGS, "Put a key-value pair"},
    {"keys", (PyCFunction)HashMap_keys, METH_NOARGS, "Get all the keys"},
    {NULL} /* Sentinel */
};

PyTypeObject HashMapType = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "HashMap",
    .tp_doc = "HashMap data structure",
    .tp_basicsize = sizeof(HashMap),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = HashMap_new,
    .tp_init = (initproc)HashMap_init,
    .tp_dealloc = (destructor)HashMap_dealloc,
    .tp_members = HashMap_members,
    .tp_methods = HashMap_methods,
    .tp_getset = HashMap_getsetters,
};
