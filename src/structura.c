#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include <structmember.h>

extern PyTypeObject StackType;
extern PyTypeObject QueueType;
extern PyTypeObject LinkedType;
extern PyTypeObject HashMapType;
extern PyTypeObject RingBufferType;
extern PyTypeObject PriorityQueueType;

static PyObject *
magic(PyObject *self, PyObject *args)
{
    return Py_BuildValue("i", 0x7f454c46);
}

const char mithril[] = "\nIn the land of Python, where libraries thrive,\n"
                       "There lies a function that will revive.\n"
                       "It returns the magic of Middle-earth lore,\n"
                       "The ELF that you seek is at the core.\n";

static PyMethodDef StructuraMethods[] = {
    {"__magic", magic, METH_VARARGS, mithril},
    {NULL, NULL, 0, NULL},
};

static struct PyModuleDef structuramodule = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "structura",
    .m_doc = "Python interface for the structura.",
    .m_size = -1,
    .m_methods = StructuraMethods,
};

PyMODINIT_FUNC PyInit_structura(void)
{
    PyObject *module = PyModule_Create(&structuramodule);

    /* add version */
    PyModule_AddStringConstant(module, "__version__", "0.3.0");

    /* add docstring */
    PyModule_AddStringConstant(module, "__doc__", "Python interface for the structura.");

    /* Add int constant by name */
    PyModule_AddIntConstant(module, "__ANSWER", 42);

    /* Add RingBuffer type */
    if (PyType_Ready(&RingBufferType) < 0)
        return NULL;

    Py_INCREF(&RingBufferType);
    PyModule_AddObject(module, "RingBuffer", (PyObject *)&RingBufferType);

    /* Add Stack type */
    if (PyType_Ready(&StackType) < 0)
        return NULL;

    Py_INCREF(&StackType);
    PyModule_AddObject(module, "Stack", (PyObject *)&StackType);

    /* Add LinkedList type */
    if (PyType_Ready(&LinkedType) < 0)
        return NULL;

    Py_INCREF(&LinkedType);
    PyModule_AddObject(module, "LinkedList", (PyObject *)&LinkedType);

    /* Add Queue type */
    if (PyType_Ready(&QueueType) < 0)
        return NULL;

    Py_INCREF(&QueueType);
    PyModule_AddObject(module, "Queue", (PyObject *)&QueueType);

    /* Add HashMap type */
    if (PyType_Ready(&HashMapType) < 0)
        return NULL;

    Py_INCREF(&HashMapType);
    PyModule_AddObject(module, "HashMap", (PyObject *)&HashMapType);

    /* Add PriorityQueue type */
    if (PyType_Ready(&PriorityQueueType) < 0)
        return NULL;

    Py_INCREF(&PriorityQueueType);
    PyModule_AddObject(module, "PriorityQueue", (PyObject *)&PriorityQueueType);

    return module;
}