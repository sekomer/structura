#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>

#include "../include/linked.h"

static PyObject *
Linked_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    Linked *self;

    self = (Linked *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->size = 0;
        self->head = NULL;
        self->tail = NULL;
    }

    return (PyObject *)self;
}

static void
Linked_dealloc(Linked *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static int
Linked_init(Linked *self, PyObject *args, PyObject *kwds)
{
    return 0;
}

static PyObject *
Linked_append(Linked *self, PyObject *args)
{
    PyObject *data;
    LinkedNode *node;

    if (!PyArg_ParseTuple(args, "O", &data))
        return NULL;

    Py_IncRef(data);

    node = (LinkedNode *)PyMem_Malloc(sizeof(LinkedNode));
    node->data = data;
    node->prev = self->tail;
    node->next = NULL;

    if (self->tail != NULL)
        self->tail->next = node;
    self->tail = node;

    if (self->head == NULL)
        self->head = node;

    self->size++;

    Py_DecRef(data);
    Py_RETURN_NONE;
}

// append but at the beginning
static PyObject *
Linked_prepend(Linked *self, PyObject *args)
{
    PyObject *data;
    LinkedNode *node;

    if (!PyArg_ParseTuple(args, "O", &data))
        return NULL;

    Py_IncRef(data);

    node = (LinkedNode *)PyMem_Malloc(sizeof(LinkedNode));
    node->data = data;
    node->prev = NULL;

    if (self->head != NULL)
        self->head->prev = node;

    node->next = self->head;
    self->head = node;

    if (self->tail == NULL)
        self->tail = node;

    self->size++;

    Py_DecRef(data);
    Py_RETURN_NONE;
}

static PyObject *
Linked_pop(Linked *self, PyObject *args)
{
    PyObject *data;
    LinkedNode *node;

    if (self->size == 0)
        Py_RETURN_NONE;

    node = self->tail;
    data = node->data;

    self->tail = node->prev;
    if (self->tail != NULL)
        self->tail->next = NULL;

    PyMem_Free(node);

    self->size--;

    return data;
}

// pop first and return it
static PyObject *
Linked_popleft(Linked *self, PyObject *args)
{
    PyObject *data;
    LinkedNode *node;

    if (self->size == 0)
        Py_RETURN_NONE;

    node = self->head;
    data = node->data;

    self->head = node->next;
    if (self->head != NULL)
        self->head->prev = NULL;

    PyMem_Free(node);

    self->size--;

    return data;
}

static PyObject *
Linked_popat(Linked *self, PyObject *args)
{
    PyObject *data;
    LinkedNode *node;

    long index;
    if (!PyArg_ParseTuple(args, "l", &index))
        return NULL;

    if (index < 0 || index >= self->size)
        Py_RETURN_NONE;

    if (index == 0)
        return Linked_popleft(self, args);

    if (index == self->size - 1)
        return Linked_pop(self, args);

    node = self->head;
    for (long i = 0; i < index; i++)
        node = node->next;

    data = node->data;

    // patch the linked list
    node->prev->next = node->next;
    node->next->prev = node->prev;

    PyMem_Free(node);

    self->size--;

    return data;
}

static PyObject *
Linked_remove(Linked *self, PyObject *args)
{
    PyObject *data;
    LinkedNode *node;

    if (!PyArg_ParseTuple(args, "O", &data))
        return NULL;

    Py_IncRef(data);

    if (self->size == 0)
    {
        Py_DecRef(data);
        Py_RETURN_FALSE;
    }

    node = self->head;
    while (node != NULL)
    {
        if (PyObject_RichCompareBool(node->data, data, Py_EQ) == 1)
        {
            // patch the linked list
            if (node->prev != NULL)
                node->prev->next = node->next;
            if (node->next != NULL)
                node->next->prev = node->prev;

            /* holy blocks solves fucking bugs */
            if (node == self->head)
                self->head = node->next;
            if (node == self->tail)
                self->tail = node->prev;
            /* end_holy */

            PyMem_Free(node);

            self->size--;

            Py_DecRef(data);
            Py_RETURN_TRUE;
        }

        node = node->next;
    }

    Py_DecRef(data);
    Py_RETURN_FALSE;
}

static PyObject *
Linked_find(Linked *self, PyObject *args)
{
    PyObject *data;
    LinkedNode *node;

    if (!PyArg_ParseTuple(args, "O", &data))
        return NULL;

    Py_IncRef(data);

    node = self->head;

    long index = 0;
    while (node != NULL)
    {
        if (PyObject_RichCompareBool(node->data, data, Py_EQ) == 1)
        {
            Py_DecRef(data);
            return PyLong_FromLong(index);
        }

        node = node->next;
        index++;
    }

    Py_DecRef(data);
    Py_RETURN_NONE;
}

static PyObject *
Linked_size(Linked *self, PyObject *args)
{
    return PyLong_FromLong(self->size);
}

static PyObject *
Linked_head(Linked *self, PyObject *args)
{
    if (self->head == NULL || self->size == 0)
        Py_RETURN_NONE;

    PyObject *head = self->head->data;
    Py_IncRef(head);

    return head;
}

static PyObject *
Linked_tail(Linked *self, PyObject *args)
{
    if (self->tail == NULL || self->size == 0)
        Py_RETURN_NONE;

    PyObject *tail = self->tail->data;
    Py_IncRef(tail);

    return tail;
}

static PyMethodDef Linked_methods[] = {
    {"append", (PyCFunction)Linked_append, METH_VARARGS, "Append an item to the end of the list"},
    {"prepend", (PyCFunction)Linked_prepend, METH_VARARGS, "Append an item to the beginning of the list"},
    {"pop", (PyCFunction)Linked_pop, METH_NOARGS, "Remove and return the last item"},
    {"popleft", (PyCFunction)Linked_popleft, METH_NOARGS, "Remove and return the first item"},
    {"popat", (PyCFunction)Linked_popat, METH_VARARGS, "Delete an item at a given index"},
    {"remove", (PyCFunction)Linked_remove, METH_VARARGS, "Remove the first occurence of an item"},
    {"find", (PyCFunction)Linked_find, METH_VARARGS, "Find first occurence of an item and return its index, None otherwise"},
    {"size", (PyCFunction)Linked_size, METH_NOARGS, "Return the size of the list"},
    {"head", (PyCFunction)Linked_head, METH_NOARGS, "Return the first item"},
    {"tail", (PyCFunction)Linked_tail, METH_NOARGS, "Return the last item"},
    {NULL} /* Sentinel */
};

static PyMemberDef Linked_members[] = {
    {NULL} /* Sentinel */
};

PyTypeObject LinkedType = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "LinkedList",
    .tp_doc = "LinkedList data structure",
    .tp_basicsize = sizeof(Linked),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = Linked_new,
    .tp_init = (initproc)Linked_init,
    .tp_dealloc = (destructor)Linked_dealloc,
    .tp_members = Linked_members,
    .tp_methods = Linked_methods,
};
