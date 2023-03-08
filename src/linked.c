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

    // TODO: CHECK IF THIS IS NEEDED OR NOT
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

    // TODO: CHECK IF THIS IS NEEDED OR NOT
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

    Py_RETURN_NONE;
}

static PyObject *
Linked_pop(Linked *self, PyObject *args)
{
    PyObject *data;
    LinkedNode *node;

    if (self->size == 0)
    {
        PyErr_SetString(PyExc_IndexError, "pop from empty list");
        return NULL;
    }

    node = self->tail;
    data = node->data;

    self->tail = node->prev;
    if (self->tail != NULL)
        self->tail->next = NULL;

    PyMem_Free(node);

    self->size--;

    return data;
}

static PyObject *
Linked_pop_first(Linked *self, PyObject *args)
{
    LinkedNode *node;

    if (self->size == 0)
    {
        PyErr_SetString(PyExc_IndexError, "pop from empty list");
        return NULL;
    }

    node = self->head;

    self->head = node->next;
    if (self->head != NULL)
        self->head->prev = NULL;

    PyMem_Free(node);

    self->size--;

    Py_RETURN_NONE;
}

static PyObject *
Linked_delete_at(Linked *self, PyObject *args)
{
    PyObject *index_obj;
    LinkedNode *node;

    if (!PyArg_ParseTuple(args, "O", &index_obj))
        return NULL;

    Py_IncRef(index_obj);
    long index = PyLong_AsLong(index_obj);

    if (index < 0 || index >= self->size)
    {
        PyErr_SetString(PyExc_IndexError, "index out of range");
        return NULL;
    }

    node = self->head;

    for (long i = 0; i < index; i++)
        node = node->next;

    if (node->prev != NULL)
        node->prev->next = node->next;
    if (node->next != NULL)
        node->next->prev = node->prev;

    // PyMem_Free(node);

    self->size--;

    Py_RETURN_NONE;
}

static PyObject *
Linked_find(Linked *self, PyObject *args)
{
    PyObject *data;
    LinkedNode *node;

    if (!PyArg_ParseTuple(args, "O", &data))
        return NULL;

    // TODO: CHECK IF THIS IS NEEDED OR NOT
    Py_IncRef(data);

    node = self->head;

    long index = 0;
    while (node != NULL)
    {
        if (PyObject_RichCompareBool(node->data, data, Py_EQ) == 1)
            return PyLong_FromLong(index);

        node = node->next;
        index++;
    }

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
    if (self->head == NULL)
        Py_RETURN_NONE;

    PyObject *head = self->head->data;
    Py_IncRef(head);

    return head;
}

static PyObject *
Linked_tail(Linked *self, PyObject *args)
{
    if (self->tail == NULL)
        Py_RETURN_NONE;

    PyObject *tail = self->tail->data;
    Py_IncRef(tail);

    return tail;
}

static PyMethodDef Linked_methods[] = {
    {"append", (PyCFunction)Linked_append, METH_VARARGS, "Append an item to the end of the list"},
    {"prepend", (PyCFunction)Linked_prepend, METH_VARARGS, "Append an item to the beginning of the list"},
    {"pop", (PyCFunction)Linked_pop, METH_NOARGS, "Remove and return the last item"},
    {"pop_first", (PyCFunction)Linked_pop_first, METH_NOARGS, "Remove and return the first item"},
    {"delete_at", (PyCFunction)Linked_delete_at, METH_VARARGS, "Delete an item at a given index"},
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
