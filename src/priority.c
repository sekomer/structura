#define PY_SSIZE_T_CLEAN

#include "Python.h"
#include "structmember.h"
#include "../include/priority.h"

static PyObject *
PriorityQueue_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PriorityQueue *self;
    self = (PriorityQueue *)type->tp_alloc(type, 0);

    if (self != NULL)
    {
        self->size = 0;
        self->head = NULL;
        self->tail = NULL;
    }

    return (PyObject *)self;
}

static int
PriorityQueue_init(PriorityQueue *self, PyObject *args, PyObject *kwds)
{
    return 0;
}

static void
PriorityQueue_dealloc(PriorityQueue *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *
PriorityQueue_push(PriorityQueue *self, PyObject *args)
{
    PyObject *item;
    PyObject *priority;

    if (!PyArg_ParseTuple(args, "OO", &item, &priority))
        return NULL;

    Py_IncRef(item);
    Py_IncRef(priority);

    PriorityNode *node = PyMem_Malloc(sizeof(PriorityNode));

    node->next = NULL;
    node->prev = NULL;
    node->value = item;
    node->priority = priority;

    if (self->size == 0)
    {
        self->head = node;
        self->tail = node;
    }
    else
    {
        PriorityNode *current = self->head;
        PriorityNode *prev = NULL;

        while (current != NULL)
        {
            // if priority is less than current node's priority insert before and break
            if (PyObject_RichCompareBool(priority, current->priority, Py_LT) == 1)
            {
                if (prev == NULL)
                {
                    node->next = current;
                    current->prev = node;
                    self->head = node;
                }
                else
                {
                    node->next = current;
                    node->prev = prev;
                    prev->next = node;
                    current->prev = node;
                }

                break;
            }

            // if error occurred
            if (PyErr_Occurred())
            {
                PyMem_Free(node);
                Py_DecRef(item);
                Py_DecRef(priority);

                PyErr_SetString(PyExc_TypeError, "cannot compare different types!");
                return NULL;
            }

            prev = current;
            current = current->next;
        }

        if (current == NULL)
        {
            self->tail->next = node;
            node->prev = self->tail;
            self->tail = node;
        }
    }

    self->size++;

    Py_RETURN_NONE;
}

static PyObject *
PriorityQueue_pop(PriorityQueue *self, PyObject *args)
{
    if (self->size == 0)
    {
        PyErr_SetString(PyExc_IndexError, "pop from empty priority queue");
        return NULL;
    }

    PriorityNode *node = self->head;

    if (self->size == 1)
    {
        self->head = NULL;
        self->tail = NULL;
    }
    else
    {
        self->head = node->next;
        self->head->prev = NULL;
    }

    self->size--;

    PyObject *item = node->value;
    PyObject *priority = node->priority;

    PyMem_Free(node);

    return Py_BuildValue("OO", item, priority);
}

static PyObject *
PriorityQueue_peek(PriorityQueue *self, PyObject *args)
{
    if (self->size == 0)
    {
        PyErr_SetString(PyExc_IndexError, "peek from empty priority queue");
        return NULL;
    }

    Py_IncRef(self->head->value);
    Py_IncRef(self->head->priority);

    return Py_BuildValue("OO", self->head->value, self->head->priority);
}

static PyObject *
PriorityQueue_clear(PriorityQueue *self, PyObject *args)
{
    PriorityNode *next;
    PriorityNode *current = self->head;

    while (current != NULL)
    {
        next = current->next;

        Py_DecRef(current->priority);
        Py_DecRef(current->value);
        PyMem_Free(current);

        current = next;
    }

    self->size = 0;

    Py_RETURN_NONE;
}

static PyObject *
PriorityQueue_size(PriorityQueue *self, PyObject *args)
{
    return PyLong_FromLong(self->size);
}

static PyObject *
PriorityQueue_is_empty(PriorityQueue *self, PyObject *args)
{
    return PyBool_FromLong(self->size == 0);
}

static PyMemberDef PriorityQueue_members[] = {
    {NULL} /* Sentinel */
};

static PyGetSetDef PriorityQueue_getsetters[] = {
    {"size", (getter)PriorityQueue_size, NULL, "size of the priority queue", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef PriorityQueue_methods[] = {
    {"push", (PyCFunction)PriorityQueue_push, METH_VARARGS, "Push an item into the priority queue"},
    {"pop", (PyCFunction)PriorityQueue_pop, METH_NOARGS, "Pop an item from the priority queue"},
    {"peek", (PyCFunction)PriorityQueue_peek, METH_NOARGS, "Peek an item from the priority queue"},
    {"clear", (PyCFunction)PriorityQueue_clear, METH_NOARGS, "Clear the priority queue"},
    {"is_empty", (PyCFunction)PriorityQueue_is_empty, METH_NOARGS, "Check if the priority queue is empty"},
    {NULL} /* Sentinel */
};

PyTypeObject PriorityQueueType = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "PriorityQueue",
    .tp_doc = "Priority queue data structure",
    .tp_basicsize = sizeof(PriorityQueue),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PriorityQueue_new,
    .tp_init = (initproc)PriorityQueue_init,
    .tp_dealloc = (destructor)PriorityQueue_dealloc,
    .tp_members = PriorityQueue_members,
    .tp_getset = PriorityQueue_getsetters,
    .tp_methods = PriorityQueue_methods,
};