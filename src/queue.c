#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include "structmember.h"
#include "../include/queue.h"

static PyObject *
Queue_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    Queue *self;

    self = (Queue *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->capacity = 0;
        self->size = 0;
        self->head = 0;
        self->tail = 0;
        self->items = NULL;
    }

    return (PyObject *)self;
}

static int
Queue_init(Queue *self, PyObject *args, PyObject *kwds)
{
    long capacity;
    static char *kwlist[] = {"capacity", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "l", kwlist, &capacity))
        return -1;

    if (capacity <= 0)
    {
        PyErr_SetString(PyExc_ValueError, "capacity must be greater than 0");
        return -1;
    }

    self->capacity = capacity;
    self->items = (PyObject **)PyMem_Malloc(self->capacity * sizeof(PyObject *));

    if (self->items == NULL)
    {
        PyErr_SetString(PyExc_MemoryError, "unable to allocate memory");
        return -1;
    }

    return 0;
}

static void
Queue_dealloc(Queue *self)
{
    Py_XDECREF(self->items);
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *
Queue_is_empty(Queue *self)
{
    if (self->size == 0)
        Py_RETURN_TRUE;

    Py_RETURN_FALSE;
}

static PyObject *
Queue_is_full(Queue *self)
{
    if (self->size == self->capacity)
        Py_RETURN_TRUE;

    Py_RETURN_FALSE;
}

static PyObject *
Queue_enqueue(Queue *self, PyObject *args)
{
    PyObject *item;

    if (!PyArg_ParseTuple(args, "O", &item))
        return NULL;

    if (self->size == self->capacity)
    {
        PyErr_SetString(PyExc_IndexError, "queue is full");
        return NULL;
    }

    Py_IncRef(item);

    self->items[self->tail] = item;
    self->tail = (self->tail + 1) % self->capacity;
    self->size++;

    Py_RETURN_NONE;
}

static PyObject *
Queue_dequeue(Queue *self)
{
    PyObject *item;

    if (self->size == 0)
    {
        PyErr_SetString(PyExc_IndexError, "queue is empty");
        return NULL;
    }

    item = self->items[self->head];
    self->head = (self->head + 1) % self->capacity;
    self->size--;

    return item;
}

static PyObject *
Queue_peek(Queue *self)
{
    PyObject *item;

    if (self->size == 0)
    {
        PyErr_SetString(PyExc_IndexError, "queue is empty");
        return NULL;
    }

    item = self->items[self->head];
    Py_IncRef(item);

    return item;
}

static PyObject *
Queue_clear(Queue *self)
{
    // empty the queue
    while (self->size > 0)
    {
        PyObject *item = self->items[self->head];
        Py_DecRef(item);
        self->head = (self->head + 1) % self->capacity;
        self->size--;
    }

    Py_RETURN_NONE;
}

static PyObject *
Queue_size(Queue *self)
{
    return PyLong_FromLong(self->size);
}

static PyObject *
Queue_capacity(Queue *self)
{
    return PyLong_FromLong(self->capacity);
}

static PyMemberDef Queue_members[] = {
    {NULL}, /* Sentinel */
};

static PyMethodDef Queue_methods[] = {
    {"is_empty", (PyCFunction)Queue_is_empty, METH_NOARGS, "Check if the queue is empty"},
    {"is_full", (PyCFunction)Queue_is_full, METH_NOARGS, "Check if the queue is full"},
    {"enqueue", (PyCFunction)Queue_enqueue, METH_VARARGS, "Add an item to the queue"},
    {"dequeue", (PyCFunction)Queue_dequeue, METH_NOARGS, "Remove an item from the queue"},
    {"peek", (PyCFunction)Queue_peek, METH_NOARGS, "Return the item at the front of the queue"},
    {"clear", (PyCFunction)Queue_clear, METH_NOARGS, "Clear the queue"},
    {NULL} /* Sentinel */
};

static PyGetSetDef Queue_getsetters[] = {
    {"size", (getter)Queue_size, NULL, "Size of the queue", NULL},
    {"capacity", (getter)Queue_capacity, NULL, "Capacity of the queue", NULL},
    {NULL} /* Sentinel */
};

PyTypeObject QueueType = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "Queue",
    .tp_doc = "Queue data structure",
    .tp_basicsize = sizeof(Queue),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = Queue_new,
    .tp_init = (initproc)Queue_init,
    .tp_dealloc = (destructor)Queue_dealloc,
    .tp_members = Queue_members,
    .tp_methods = Queue_methods,
    .tp_getset = Queue_getsetters,
};
