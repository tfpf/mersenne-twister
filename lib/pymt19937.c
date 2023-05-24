#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "mt19937.c"


static PyObject *seed32(PyObject *self, PyObject *args)
{
    int long unsigned seed;
    if(!PyArg_ParseTuple(args, "k", &seed))
    {
        return NULL;
    }
    seed = PyLong_AsUnsignedLong(PyTuple_GET_ITEM(args, 0));
    if(PyErr_Occurred() || seed > 4294967295UL)
    {
        PyErr_SetString(PyExc_ValueError, "argument 1 must be an integer in the range [0, 4294967295]");
        return NULL;
    }
    mt19937_seed32((uint32_t)seed, NULL);
    Py_RETURN_NONE;
}


static PyObject *seed64(PyObject *self, PyObject *args)
{
    int long long unsigned seed;
    if(!PyArg_ParseTuple(args, "K", &seed))
    {
        return NULL;
    }
    seed = PyLong_AsUnsignedLongLong(PyTuple_GET_ITEM(args, 0));
    if(PyErr_Occurred() || seed > 18446744073709551615ULL)
    {
        PyErr_SetString(PyExc_ValueError, "argument 1 must be an integer in the range [0, 18446744073709551615]");
        return NULL;
    }
    mt19937_seed64((uint64_t)seed, NULL);
    Py_RETURN_NONE;
}


static PyObject *rand32(PyObject *self, PyObject *args)
{
    return PyLong_FromUnsignedLong((int long unsigned)mt19937_rand32(NULL));
}


static PyObject *rand64(PyObject *self, PyObject *args)
{
    return PyLong_FromUnsignedLongLong((int long long unsigned)mt19937_rand64(NULL));
}


static PyObject *uint32(PyObject *self, PyObject *args)
{
    int long unsigned modulus;
    if(!PyArg_ParseTuple(args, "k", &modulus))
    {
        return NULL;
    }
    modulus = PyLong_AsUnsignedLong(PyTuple_GET_ITEM(args, 0));
    if(PyErr_Occurred() || modulus == 0 || modulus > 4294967295UL)
    {
        PyErr_SetString(PyExc_ValueError, "argument 1 must be an integer in the range [1, 4294967295]");
        return NULL;
    }
    return PyLong_FromUnsignedLong((int long unsigned)mt19937_uint32((uint32_t)modulus, NULL));
}


static PyObject *uint64(PyObject *self, PyObject *args)
{
    int long long unsigned modulus;
    if(!PyArg_ParseTuple(args, "K", &modulus))
    {
        return NULL;
    }
    modulus = PyLong_AsUnsignedLongLong(PyTuple_GET_ITEM(args, 0));
    if(PyErr_Occurred() || modulus == 0 || modulus > 18446744073709551615ULL)
    {
        PyErr_SetString(PyExc_ValueError, "argument 1 must be an integer in the range [1, 18446744073709551615]");
        return NULL;
    }
    return PyLong_FromUnsignedLongLong((int long long unsigned)mt19937_uint64((uint64_t)modulus, NULL));
}


static PyObject *span32(PyObject *self, PyObject *args)
{
    int long left, right;
    PyObject *err = NULL;
    if(!PyArg_ParseTuple(args, "ll", &left, &right))
    {
        err = PyErr_Occurred();
        if(!PyErr_GivenExceptionMatches(err, PyExc_OverflowError))
        {
            return NULL;
        }
    }
    if(err != NULL
    || left < -2147483647L - 1 || left > 2147483647L
    || right < -2147483647L - 1 || right > 2147483647L
    || left >= right)
    {
        PyErr_SetString(
            PyExc_ValueError,
            "arguments 1 and 2 must be integers in the range [-2147483648, 2147483647]; "
            "argument 1 must be less than argument 2");
        return NULL;
    }
    return PyLong_FromLong((int long)mt19937_span32((int32_t)left, (int32_t)right, NULL));
}


static PyObject *span64(PyObject *self, PyObject *args)
{
    int long long left, right;
    PyObject *err = NULL;
    if(!PyArg_ParseTuple(args, "LL", &left, &right))
    {
        err = PyErr_Occurred();
        if(!PyErr_GivenExceptionMatches(err, PyExc_OverflowError))
        {
            return NULL;
        }
    }
    if(err != NULL
    || left < -9223372036854775807LL - 1 || left > 9223372036854775807LL
    || right < -9223372036854775807LL - 1 || right > 9223372036854775807LL
    || left >= right)
    {
        PyErr_SetString(
            PyExc_ValueError,
            "arguments 1 and 2 must be integers in the range [-9223372036854775808, 9223372036854775807]; "
            "argument 1 must be less than argument 2");
        return NULL;
    }
    return PyLong_FromLongLong((int long long)mt19937_span64((int64_t)left, (int64_t)right, NULL));
}


static PyObject *real32(PyObject *self, PyObject *args)
{
    return PyFloat_FromDouble(mt19937_real32(NULL));
}


static PyObject *real64(PyObject *self, PyObject *args)
{
    return PyFloat_FromDouble((double)mt19937_real64(NULL));
}


static PyObject *drop32(PyObject *self, PyObject *args)
{
    int long long count;
    if(!PyArg_ParseTuple(args, "L", &count))
    {
        return NULL;
    }
    mt19937_drop32(count, NULL);
    Py_RETURN_NONE;
}


static PyObject *drop64(PyObject *self, PyObject *args)
{
    int long long count;
    if(!PyArg_ParseTuple(args, "L", &count))
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
    ":param seed: 32-bit number. If this is 0, it will be seeded with the sum of the Unix time and the process ID."
);
PyDoc_STRVAR(
    seed64_doc,
    "Python API for `mt19937_seed64`.\n\n"
    ":param seed: 64-bit number. If this is 0, it will be seeded with the sum of the Unix time and the process ID."
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
    ":param modulus: 32-bit number. Must not be 0.\n\n"
    ":return: Uniform pseudorandom 32-bit number from 0 (inclusive) to `modulus` (exclusive)."
);
PyDoc_STRVAR(
    uint64_doc,
    "Python API for `mt19937_uint64`.\n\n"
    ":param modulus: 64-bit number. Must not be 0.\n\n"
    ":return: Uniform pseudorandom 64-bit number from 0 (inclusive) to `modulus` (exclusive)."
);
PyDoc_STRVAR(
    span32_doc,
    "Python API for `mt19937_span32`.\n\n"
    ":param left: 32-bit number.\n"
    ":param right: 32-bit number. Must be greater than `left`.\n\n"
    ":return: Uniform pseudorandom 32-bit number from `left` (inclusive) to `right` (exclusive)."
);
PyDoc_STRVAR(
    span64_doc,
    "Python API for `mt19937_span64`.\n\n"
    ":param left: 64-bit number.\n"
    ":param right: 64-bit number. Must be greater than `left`.\n\n"
    ":return: Uniform pseudorandom 64-bit number from `left` (inclusive) to `right` (exclusive)."
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
    {"span32", span32, METH_VARARGS, span32_doc},
    {"span64", span64, METH_VARARGS, span64_doc},
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
    "Python API for a C implementation of MT19937 "
    "(see https://github.com/tfpf/mersenne-twister/blob/main/doc for the full documentation)",
    -1,
    pymt19937_methods,
};


PyMODINIT_FUNC PyInit_mt19937(void)
{
    return PyModule_Create(&pymt19937_module);
}
