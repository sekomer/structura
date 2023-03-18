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

    Py_RETURN_NONE;
}

static PyObject *
Linked_insert(Linked *self, PyObject *args)
{
    PyObject *data;
    LinkedNode *node;
    LinkedNode *current;

    long index;
    if (!PyArg_ParseTuple(args, "lO", &index, &data))
        return NULL;

    if (index < 0 || index > self->size)
    {
        PyErr_SetString(PyExc_IndexError, "index out of range");
        return NULL;
    }

    if (index == 0)
        return Linked_prepend(self, args);

    if (index == self->size)
        return Linked_append(self, args);

    Py_IncRef(data);

    node = (LinkedNode *)PyMem_Malloc(sizeof(LinkedNode));
    node->data = data;

    current = self->head;
    while (index--)
        current = current->next;

    node->prev = current->prev;
    node->next = current;

    current->prev->next = node;
    current->prev = node;

    self->size++;

    Py_RETURN_NONE;
}

static PyObject *
Linked_bulk_append(Linked *self, PyObject *args)
{
    PyObject *data;
    LinkedNode **node;

    if (!PyArg_ParseTuple(args, "O", &data))
        return NULL;

    if (!PySequence_Check(data))
    {
        PyErr_SetString(PyExc_TypeError, "data must be a sequence");
        return NULL;
    }

    Py_ssize_t SEQ_BEG = 0;
    Py_ssize_t SEQ_LEN = PySequence_Size(data);

    // allocate memory for all nodes
    node = (LinkedNode **)PyMem_Malloc(sizeof(LinkedNode *) * SEQ_LEN);
    if (node == NULL)
    {
        PyErr_SetString(PyExc_MemoryError, "failed to allocate memory");
        return NULL;
    }

    // initialize all nodes
    for (long i = SEQ_BEG; i < SEQ_LEN; i++)
    {
        node[i] = (LinkedNode *)PyMem_Malloc(sizeof(LinkedNode));
        node[i]->data = PySequence_GetItem(data, i);
        Py_IncRef(node[i]->data);

        node[i]->prev = NULL;
        node[i]->next = NULL;
    }

    // fix the linked list
    if (self->tail != NULL)
        self->tail->next = node[SEQ_BEG];

    node[SEQ_BEG]->prev = self->tail;

    for (long i = SEQ_BEG; i < SEQ_LEN - 1; i++)
    {
        node[i]->next = node[i + 1];
        node[i + 1]->prev = node[i];
    }

    self->tail = node[SEQ_LEN - 1];

    if (self->head == NULL)
        self->head = node[SEQ_BEG];

    self->size += SEQ_LEN;

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

// pop first and return it
static PyObject *
Linked_popleft(Linked *self, PyObject *args)
{
    PyObject *data;
    LinkedNode *node;

    if (self->size == 0)
    {
        PyErr_SetString(PyExc_IndexError, "pop from empty list");
        return NULL;
    }

    node = self->head;
    data = node->data;
    Py_IncRef(data);

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
    {
        PyErr_SetString(PyExc_IndexError, "index out of range");
        return NULL;
    }

    if (index == 0)
        return Linked_popleft(self, args);

    if (index == self->size - 1)
        return Linked_pop(self, args);

    node = self->head;
    for (long i = 0; i < index; i++)
        node = node->next;

    data = node->data;
    Py_IncRef(data);

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
    PyObject *ret;
    PyObject *rmv;
    LinkedNode *node;

    if (!PyArg_ParseTuple(args, "O", &rmv))
        return NULL;

    if (self->size == 0)
    {
        PyErr_SetString(PyExc_IndexError, "remove from empty list");
        return NULL;
    }

    node = self->head;
    while (node != NULL)
    {
        if (PyObject_RichCompareBool(node->data, rmv, Py_EQ) == 1)
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

            ret = node->data;
            Py_IncRef(ret);

            PyMem_Free(node);
            self->size--;

            return ret;
        }

        node = node->next;
    }

    // raise value not found in list
    PyErr_SetString(PyExc_ValueError, "value not found in list");
    return NULL;
}

static PyObject *
Linked_get(Linked *self, PyObject *args)
{
    PyObject *data;
    LinkedNode *node;

    long index;
    if (!PyArg_ParseTuple(args, "l", &index))
        return NULL;

    if (index < 0 || index >= self->size)
    {
        PyErr_SetString(PyExc_IndexError, "index out of range");
        return NULL;
    }

    node = self->head;
    while (index--)
        node = node->next;

    data = node->data;
    Py_IncRef(data);

    return data;
}

static PyObject *
Linked_set(Linked *self, PyObject *args)
{
    PyObject *data;
    LinkedNode *node;

    long index;
    if (!PyArg_ParseTuple(args, "lO", &index, &data))
        return NULL;

    if (index < 0 || index >= self->size)
    {
        PyErr_SetString(PyExc_IndexError, "index out of range");
        return NULL;
    }

    node = self->head;
    while (index--)
        node = node->next;

    Py_IncRef(data);
    Py_DecRef(node->data);
    node->data = data;

    Py_RETURN_NONE;
}

static PyObject *
Linked_find(Linked *self, PyObject *args)
{
    PyObject *data;
    LinkedNode *node;

    if (!PyArg_ParseTuple(args, "O", &data))
        return NULL;

    node = self->head;

    long index = 0;
    while (node != NULL)
    {
        if (PyObject_RichCompareBool(node->data, data, Py_EQ) == 1)
            return PyLong_FromLong(index);

        node = node->next;
        index++;
    }

    // return -1 if not found
    return PyLong_FromLong(-1);
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
    {
        PyErr_SetString(PyExc_IndexError, "empty list does not have a head");
        return NULL;
    }

    PyObject *head = self->head->data;
    Py_IncRef(head);

    return head;
}

static PyObject *
Linked_tail(Linked *self, PyObject *args)
{
    if (self->tail == NULL || self->size == 0)
    {
        PyErr_SetString(PyExc_IndexError, "empty list does not have a tail");
        return NULL;
    }

    PyObject *tail = self->tail->data;
    Py_IncRef(tail);

    return tail;
}

static PyObject *
Linked_is_empty(Linked *self, PyObject *args)
{
    if (self->size == 0)
        Py_RETURN_TRUE;

    Py_RETURN_FALSE;
}

static PyObject *
Linked_clear(Linked *self, PyObject *args)
{
    LinkedNode *node = self->head;
    LinkedNode *next;

    while (node != NULL)
    {
        next = node->next;
        Py_DecRef(node->data);
        PyMem_Free(node);
        node = next;
    }

    self->head = NULL;
    self->tail = NULL;
    self->size = 0;

    Py_RETURN_NONE;
}

static PyMethodDef Linked_methods[] = {
    {"append", (PyCFunction)Linked_append, METH_VARARGS, "Append an item to the end of the list"},
    {"prepend", (PyCFunction)Linked_prepend, METH_VARARGS, "Append an item to the beginning of the list"},
    {"insert", (PyCFunction)Linked_insert, METH_VARARGS, "Insert an item at a given index"},
    {"bulk_append", (PyCFunction)Linked_bulk_append, METH_VARARGS, "Append multiple items to the end of the list"},
    {"pop", (PyCFunction)Linked_pop, METH_NOARGS, "Remove and return the last item"},
    {"popat", (PyCFunction)Linked_popat, METH_VARARGS, "Delete an item at a given index and return it"},
    {"popleft", (PyCFunction)Linked_popleft, METH_NOARGS, "Remove and return the first item"},
    {"remove", (PyCFunction)Linked_remove, METH_VARARGS, "Remove the first occurence of an item and return it, raise ValueError if not found"},
    {"get", (PyCFunction)Linked_get, METH_VARARGS, "Get an item at a given index"},
    {"set", (PyCFunction)Linked_set, METH_VARARGS, "Set an item at a given index"},
    {"find", (PyCFunction)Linked_find, METH_VARARGS, "Find first occurence of an item and return its index, -1 otherwise"},
    {"head", (PyCFunction)Linked_head, METH_NOARGS, "Return the first item"},
    {"tail", (PyCFunction)Linked_tail, METH_NOARGS, "Return the last item"},
    {"is_empty", (PyCFunction)Linked_is_empty, METH_NOARGS, "Return True if the list is empty, False otherwise"},
    {"clear", (PyCFunction)Linked_clear, METH_NOARGS, "Clear the list"},
    {NULL} /* Sentinel */
};

static PyGetSetDef Linked_getsetters[] = {
    {"size", (getter)Linked_size, NULL, "Size of the list", NULL},
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
    .tp_getset = Linked_getsetters,
};
