#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>

#include "../include/stack.h"

static PyObject *
Stack_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    Stack *self;

    self = (Stack *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->capacity = 0;
        self->size = 0;
        self->top = -1;
        self->items = NULL;
    }

    return (PyObject *)self;
}

static int Stack_init(Stack *self, PyObject *args)
{
    PyObject *capacity = NULL;

    // get capacity from args
    if (!PyArg_ParseTuple(args, "O", &capacity))
        return -1;

    if (!PyLong_Check(capacity))
    {
        PyErr_SetString(PyExc_TypeError, "[TypeError] Capacity must be an integer");
        return -1;
    }

    self->capacity = PyLong_AsLong(capacity);
    self->items = (PyObject **)PyMem_Malloc(self->capacity * sizeof(PyObject *));

    if (self->items == NULL)
    {
        PyErr_SetString(PyExc_MemoryError, "Out of memory");
        return -1;
    }

    return 0;
}

static void Stack_dealloc(Stack *self)
{
    Py_XDECREF(self->items);
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *Stack_push(Stack *self, PyObject *args)
{
    PyObject *item = NULL;

    if (!PyArg_ParseTuple(args, "O", &item))
        return NULL;
    Py_IncRef(item);

    if (self->top == self->capacity - 1)
    {
        PyErr_SetString(PyExc_IndexError, "Stack is full");
        return NULL;
    }

    self->top++;
    self->items[self->top] = item;
    self->size++;

    Py_RETURN_NONE;
}

static PyObject *Stack_pop(Stack *self)
{
    if (self->top == -1)
    {
        PyErr_SetString(PyExc_IndexError, "Stack is empty");
        return NULL;
    }

    PyObject *item = self->items[self->top];
    self->top--;
    self->size--;

    return item;
}

static PyObject *Stack_peek(Stack const *self)
{
    if (self->top == -1)
    {
        PyErr_SetString(PyExc_IndexError, "Stack is empty");
        return NULL;
    }

    return self->items[self->top];
}

static PyObject *Stack_is_empty(Stack const *self)
{
    if (self->top == -1)
        Py_RETURN_TRUE;

    Py_RETURN_FALSE;
}

static PyObject *Stack_is_full(Stack const *self)
{
    if (self->top == self->capacity - 1)
        Py_RETURN_TRUE;

    Py_RETURN_FALSE;
}

static PyObject *Stack_size(Stack const *self)
{
    return PyLong_FromLong(self->size);
}

static PyObject *Stack_capacity(Stack const *self)
{
    return PyLong_FromLong(self->capacity);
}

static PyMemberDef Stack_members[] = {
    {NULL},
};

static PyMethodDef Stack_methods[] = {
    {"push", (PyCFunction)Stack_push, METH_VARARGS, "Push an item to the stack"},
    {"pop", (PyCFunction)Stack_pop, METH_NOARGS, "Pop an item from the stack"},
    {"peek", (PyCFunction)Stack_peek, METH_NOARGS, "Peek the top item from the stack"},
    {"is_empty", (PyCFunction)Stack_is_empty, METH_NOARGS, "Check if the stack is empty"},
    {"is_full", (PyCFunction)Stack_is_full, METH_NOARGS, "Check if the stack is full"},
    {"size", (PyCFunction)Stack_size, METH_NOARGS, "Get the size of the stack"},
    {"capacity", (PyCFunction)Stack_capacity, METH_NOARGS, "Get the capacity of the stack"},
    {NULL},
};

PyTypeObject StackType = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "Stack",
    .tp_basicsize = sizeof(Stack),
    .tp_itemsize = 0,
    .tp_new = Stack_new,
    .tp_init = (initproc)Stack_init,
    .tp_dealloc = (destructor)Stack_dealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "Stack data structure",
    .tp_methods = Stack_methods,
    .tp_members = Stack_members,
};