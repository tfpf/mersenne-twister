#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <stddef.h>

#include "mt19937.c"


static PyObject *seed32(PyObject *self, PyObject *args)
{
    int long unsigned seed = 0;
    if(!PyArg_ParseTuple(args, "|k", &seed))
    {
        return NULL;
    }
    mt19937_seed32(seed, NULL);
    Py_RETURN_NONE;
}


static PyObject *seed64(PyObject *self, PyObject *args)
{
    int long long unsigned seed = 0;
    if(!PyArg_ParseTuple(args, "|K", &seed))
    {
        return NULL;
    }
    mt19937_seed64(seed, NULL);
    Py_RETURN_NONE;
}


static PyObject *rand32(PyObject *self, PyObject *args)
{
    return PyLong_FromUnsignedLong(mt19937_rand32(NULL));
}


static PyObject *rand64(PyObject *self, PyObject *args)
{
    return PyLong_FromUnsignedLongLong(mt19937_rand64(NULL));
}


static PyObject *uint32(PyObject *self, PyObject *args)
{
    int long unsigned modulus;
    if(!PyArg_ParseTuple(args, "k", &modulus))
    {
        return NULL;
    }
    if(modulus == 0)
    {
        PyErr_SetString(PyExc_RuntimeError, "argument 1 must be non-zero");
        return NULL;
    }
    return PyLong_FromUnsignedLong(mt19937_uint32(modulus, NULL));
}


static PyObject *uint64(PyObject *self, PyObject *args)
{
    int long long unsigned modulus;
    if(!PyArg_ParseTuple(args, "K", &modulus))
    {
        return NULL;
    }
    if(modulus == 0)
    {
        PyErr_SetString(PyExc_RuntimeError, "argument 1 must be non-zero");
        return NULL;
    }
    return PyLong_FromUnsignedLongLong(mt19937_uint64(modulus, NULL));
}


static PyObject *real32(PyObject *self, PyObject *args)
{
    return PyFloat_FromDouble(mt19937_real32(NULL));
}


static PyObject *real64(PyObject *self, PyObject *args)
{
    return PyFloat_FromDouble(mt19937_real64(NULL));
}


static PyObject *drop32(PyObject *self, PyObject *args)
{
    int long long unsigned count;
    if(!PyArg_ParseTuple(args, "K", &count))
    {
        return NULL;
    }
    mt19937_drop32(count, NULL);
    Py_RETURN_NONE;
}


static PyObject *drop64(PyObject *self, PyObject *args)
{
    int long long unsigned count;
    if(!PyArg_ParseTuple(args, "K", &count))
    {
        return NULL;
    }
    mt19937_drop64(count, NULL);
    Py_RETURN_NONE;
}


// Module information.
PyDoc_STRVAR(
    seed32_doc,
    "Python API for `mt19937_seed32`.\n\n"
    ":param seed: 32-bit number, optional. If this is not specified, it is the same as if it were 0."
);
PyDoc_STRVAR(
    seed64_doc,
    "Python API for `mt19937_seed64`. Seed 64-bit MT19937.\n\n"
    ":param seed: 64-bit number, optional. If this is not specified, it is the same as if it were 0."
);
PyDoc_STRVAR(
    rand32_doc,
    "Python API for `mt19937_rand32`.\n\n"
    ":return: Uniform pseudorandom 32-bit number."
);
PyDoc_STRVAR(
    rand64_doc,
    "Python API for `mt19937_rand64`.\n\n"
    ":return: Uniform pseudorandom 64-bit number."
);
PyDoc_STRVAR(
    uint32_doc,
    "Python API for `mt19937_uint32`.\n\n"
    ":param modulus: 32-bit number. Raises `RuntimeError` if this is 0.\n\n"
    ":return: Uniform pseudorandom 32-bit number from 0 (inclusive) to `modulus` (exclusive)."
);
PyDoc_STRVAR(
    uint64_doc,
    "Python API for `mt19937_uint64`.\n\n"
    ":param modulus: 64-bit number. Raises `RuntimeError` if this is 0.\n\n"
    ":return: Uniform pseudorandom 64-bit number from 0 (inclusive) to `modulus` (exclusive)."
);
PyDoc_STRVAR(
    real32_doc,
    "Python API for `mt19937_real32`.\n\n"
    ":return: Uniform pseudorandom number from 0 (inclusive) to 1 (inclusive)."
);
PyDoc_STRVAR(
    real64_doc,
    "Python API for `mt19937_real64`.\n\n"
    ":return: Uniform pseudorandom number from 0 (inclusive) to 1 (inclusive)."
);
PyDoc_STRVAR(
    drop32_doc,
    "Python API for `mt19937_drop32`.\n\n"
    ":param count: Number of steps to advance the state by."
);
PyDoc_STRVAR(
    drop64_doc,
    "Python API for `mt19937_drop64`.\n\n"
    ":param count: Number of steps to advance the state by."
);
static PyMethodDef pymt19937_methods[] =
{
    {"seed32", seed32, METH_VARARGS, seed32_doc},
    {"seed64", seed64, METH_VARARGS, seed64_doc},
    {"rand32", rand32, METH_NOARGS, rand32_doc},
    {"rand64", rand64, METH_NOARGS, rand64_doc},
    {"uint32", uint32, METH_VARARGS, uint32_doc},
    {"uint64", uint64, METH_VARARGS, uint64_doc},
    {"real32", real32, METH_NOARGS, real32_doc},
    {"real64", real64, METH_NOARGS, real64_doc},
    {"drop32", drop32, METH_VARARGS, drop32_doc},
    {"drop64", drop64, METH_VARARGS, drop64_doc},
    {NULL, NULL, 0, NULL},
};
static PyModuleDef pymt19937_module =
{
    PyModuleDef_HEAD_INIT,
    "mt19937",
    "Python API for a C implementation of MT19937",
    -1,
    pymt19937_methods,
};


PyMODINIT_FUNC PyInit_mt19937(void)
{
    return PyModule_Create(&pymt19937_module);
}
