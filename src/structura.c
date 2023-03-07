#define PY_SSIZE_T_CLEAN
#include <Python.h>

extern PyTypeObject RingBufferType;

static PyObject *
method_fputs(PyObject *self, PyObject *args)
{
    char *str = NULL;
    char *filename = NULL;

    long bytes_copied = -1;

    /* Parse arguments */
    if (!PyArg_ParseTuple(args, "ss", &str, &filename))
        return NULL;

    FILE *fp = fopen(filename, "w");

    if (fp == NULL)
    {
        PyErr_SetString(PyExc_IOError, "[Structura] Could not open file");
        return NULL;
    }

    bytes_copied = fputs(str, fp);
    fclose(fp);

    return PyLong_FromLong(bytes_copied);
}

static PyMethodDef FputsMethods[] = {
    {"fputs", method_fputs, METH_VARARGS, "Python interface for fputs C library function"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef structuramodule = {
    PyModuleDef_HEAD_INIT,
    "structura",
    "Python interface for the fputs C library function",
    -1,
    FputsMethods};

PyMODINIT_FUNC PyInit_structura(void)
{
    PyObject *module = PyModule_Create(&structuramodule);

    /* Add int constant by name */
    PyModule_AddIntConstant(module, "STRUCTURA_FLAG", 1024);

    /* Add RingBuffer type */
    if (PyType_Ready(&RingBufferType) < 0)
        return NULL;

    Py_INCREF(&RingBufferType);
    PyModule_AddObject(module, "RingBuffer", (PyObject *)&RingBufferType);

        return module;
}