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


// Module information.
static PyMethodDef pymt19937_methods[] =
{
    {"seed32", seed32, METH_VARARGS, "Python wrapper around `mt19937_seed32`."},
    {"seed64", seed64, METH_VARARGS, "Python wrapper around `mt19937_seed64`."},
    {"rand32", rand32, METH_NOARGS, "Python wrapper around `mt19937_rand32`."},
    {"rand64", rand64, METH_NOARGS, "Python wrapper around `mt19937_rand64`."},
    {"uint32", uint32, METH_VARARGS, "Python wrapper around `mt19937_uint32`."},
    {"uint64", uint64, METH_VARARGS, "Python wrapper around `mt19937_uint64`."},
    {"real32", real32, METH_NOARGS, "Python wrapper around `mt19937_real32`."},
    {"real64", real64, METH_NOARGS, "Python wrapper around `mt19937_real64`."},
    {NULL, NULL, 0, NULL},
};
static PyModuleDef pymt19937_module =
{
    PyModuleDef_HEAD_INIT,
    "mt19937",
    "Python wrapper around MT19937.",
    -1,
    pymt19937_methods,
};


PyMODINIT_FUNC PyInit_mt19937(void)
{
    return PyModule_Create(&pymt19937_module);
}
