#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <inttypes.h>

#include "mt19937.h"


static PyObject *
seed32(PyObject *self, PyObject *args)
{
    int long unsigned seed;
    if(!PyArg_ParseTuple(args, "k", &seed))
    {
        return NULL;
    }
    seed = PyLong_AsUnsignedLong(PyTuple_GET_ITEM(args, 0));
    if(PyErr_Occurred() != NULL || seed > UINT32_MAX)
    {
        return PyErr_Format(PyExc_ValueError, "argument 1 must be an integer in [0, %"PRIu32"]", UINT32_MAX);
    }
    return PyLong_FromUnsignedLong((int long unsigned)mt19937_seed32((uint32_t)seed, NULL));
}


static PyObject *
seed64(PyObject *self, PyObject *args)
{
    int long long unsigned seed;
    if(!PyArg_ParseTuple(args, "K", &seed))
    {
        return NULL;
    }
    seed = PyLong_AsUnsignedLongLong(PyTuple_GET_ITEM(args, 0));
    if(PyErr_Occurred() != NULL || seed > UINT64_MAX)
    {
        return PyErr_Format(PyExc_ValueError, "argument 1 must be an integer in [0, %"PRIu64"]", UINT64_MAX);
    }
    return PyLong_FromUnsignedLongLong((int long long unsigned)mt19937_seed64((uint64_t)seed, NULL));
}


static PyObject *
init32(PyObject *self, PyObject *args)
{
    return PyLong_FromUnsignedLong((int long unsigned)mt19937_init32(NULL));
}


static PyObject *
init64(PyObject *self, PyObject *args)
{
    return PyLong_FromUnsignedLongLong((int long long unsigned)mt19937_init64(NULL));
}


static PyObject *
rand32(PyObject *self, PyObject *args)
{
    return PyLong_FromUnsignedLong((int long unsigned)mt19937_rand32(NULL));
}


static PyObject *
rand64(PyObject *self, PyObject *args)
{
    return PyLong_FromUnsignedLongLong((int long long unsigned)mt19937_rand64(NULL));
}


static PyObject *
uint32(PyObject *self, PyObject *args)
{
    int long unsigned modulus;
    if(!PyArg_ParseTuple(args, "k", &modulus))
    {
        return NULL;
    }
    modulus = PyLong_AsUnsignedLong(PyTuple_GET_ITEM(args, 0));
    if(PyErr_Occurred() != NULL || modulus == 0 || modulus > UINT32_MAX)
    {
        return PyErr_Format(PyExc_ValueError, "argument 1 must be an integer in [1, %"PRIu32"]", UINT32_MAX);
    }
    return PyLong_FromUnsignedLong((int long unsigned)mt19937_uint32((uint32_t)modulus, NULL));
}


static PyObject *
uint64(PyObject *self, PyObject *args)
{
    int long long unsigned modulus;
    if(!PyArg_ParseTuple(args, "K", &modulus))
    {
        return NULL;
    }
    modulus = PyLong_AsUnsignedLongLong(PyTuple_GET_ITEM(args, 0));
    if(PyErr_Occurred() != NULL || modulus == 0 || modulus > UINT64_MAX)
    {
        return PyErr_Format(PyExc_ValueError, "argument 1 must be an integer in [1, %"PRIu64"]", UINT64_MAX);
    }
    return PyLong_FromUnsignedLongLong((int long long unsigned)mt19937_uint64((uint64_t)modulus, NULL));
}


static PyObject *
span32(PyObject *self, PyObject *args)
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
    if(err != NULL || left < INT32_MIN || left > INT32_MAX || right < INT32_MIN || right > INT32_MAX || left >= right)
    {
        return PyErr_Format(
            PyExc_ValueError,
            "argument 1 must be less than argument 2; both must be integers in [%"PRId32", %"PRId32"] "
            "and fit in the C `long` type",
            INT32_MIN, INT32_MAX
        );
    }
    return PyLong_FromLong((int long)mt19937_span32((int32_t)left, (int32_t)right, NULL));
}


static PyObject *
span64(PyObject *self, PyObject *args)
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
    if(err != NULL || left < INT64_MIN || left > INT64_MAX || right < INT64_MIN || right > INT64_MAX || left >= right)
    {
        return PyErr_Format(
            PyExc_ValueError,
            "argument 1 must be less than argument 2; both must be integers in [%"PRId64", %"PRId64"] "
            "and fit in the C `long long` type",
            INT64_MIN, INT64_MAX
        );
    }
    return PyLong_FromLongLong((int long long)mt19937_span64((int64_t)left, (int64_t)right, NULL));
}


static PyObject *
real32(PyObject *self, PyObject *args)
{
    return PyFloat_FromDouble(mt19937_real32(NULL));
}


static PyObject *
real64(PyObject *self, PyObject *args)
{
    return PyFloat_FromDouble((double)mt19937_real64(NULL));
}


static PyObject *
drop32(PyObject *self, PyObject *args)
{
    int long long count;
    if(!PyArg_ParseTuple(args, "L", &count))
    {
        return NULL;
    }
    mt19937_drop32(count, NULL);
    Py_RETURN_NONE;
}


static PyObject *
drop64(PyObject *self, PyObject *args)
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
    "seed32(seed)\n"
    "Seed 32-bit MT19937.\n\n"
    ":param seed: 32-bit number.\n\n"
    ":return: The value used for seeding (``seed``)."
);
PyDoc_STRVAR(
    seed64_doc,
    "seed64(seed)\n"
    "Seed 64-bit MT19937.\n\n"
    ":param seed: 64-bit number.\n\n"
    ":return: The value used for seeding (``seed``)."
);
PyDoc_STRVAR(
    init32_doc,
    "init32()\n"
    "Seed 32-bit MT19937 with a value generated in an unspecified manner at run-time.\n\n"
    ":return: The value used for seeding."
);
PyDoc_STRVAR(
    init64_doc,
    "init64()\n"
    "Seed 64-bit MT19937 with a value generated in an unspecified manner at run-time.\n\n"
    ":return: The value used for seeding."
);
PyDoc_STRVAR(
    rand32_doc,
    "rand32() -> int\n"
    "Generate a pseudorandom number.\n\n"
    ":return: Uniform pseudorandom 32-bit number."
);
PyDoc_STRVAR(
    rand64_doc,
    "rand64() -> int\n"
    "Generate a pseudorandom number.\n\n"
    ":return: Uniform pseudorandom 64-bit number."
);
PyDoc_STRVAR(
    uint32_doc,
    "uint32(modulus) -> int\n"
    "Generate a pseudorandom residue.\n\n"
    ":param modulus: 32-bit number. Must not be 0.\n\n"
    ":return: Uniform pseudorandom 32-bit number from 0 (inclusive) to ``modulus`` (exclusive)."
);
PyDoc_STRVAR(
    uint64_doc,
    "uint64(modulus) -> int\n"
    "Generate a pseudorandom residue.\n\n"
    ":param modulus: 64-bit number. Must not be 0.\n\n"
    ":return: Uniform pseudorandom 64-bit number from 0 (inclusive) to ``modulus`` (exclusive)."
);
PyDoc_STRVAR(
    span32_doc,
    "span32(left, right) -> int\n"
    "Generate a pseudorandom residue offset.\n\n"
    ":param left: 32-bit number.\n"
    ":param right: 32-bit number. Must be greater than ``left``.\n\n"
    ":return: Uniform pseudorandom 32-bit number from ``left`` (inclusive) to ``right`` (exclusive)."
);
PyDoc_STRVAR(
    span64_doc,
    "span64(left, right) -> int\n"
    "Generate a pseudorandom residue offset.\n\n"
    ":param left: 64-bit number.\n"
    ":param right: 64-bit number. Must be greater than ``left``.\n\n"
    ":return: Uniform pseudorandom 64-bit number from ``left`` (inclusive) to ``right`` (exclusive)."
);
PyDoc_STRVAR(
    real32_doc,
    "real32() -> float\n"
    "Generate a pseudorandom fraction.\n\n"
    ":return: Uniform pseudorandom number from 0 (inclusive) to 1 (inclusive)."
);
PyDoc_STRVAR(
    real64_doc,
    "real64() -> float\n"
    "Generate a pseudorandom fraction.\n\n"
    ":return: Uniform pseudorandom number from 0 (inclusive) to 1 (inclusive)."
);
PyDoc_STRVAR(
    drop32_doc,
    "drop32(count)\n"
    "Mutate 32-bit MT19937 by advancing its internal state. Equivalent to running ``rand32()`` ``count`` times and "
    "discarding the results.\n\n"
    ":param count: Number of steps to advance the state by. If not positive, this function has no effect."
);
PyDoc_STRVAR(
    drop64_doc,
    "drop64(count)\n"
    "Mutate 64-bit MT19937 by advancing its internal state. Equivalent to running ``rand64()`` ``count`` times and "
    "discarding the results.\n\n"
    ":param count: Number of steps to advance the state by. If not positive, this function has no effect."
);
static PyMethodDef pymt19937_methods[] =
{
    {"seed32", seed32, METH_VARARGS, seed32_doc},
    {"seed64", seed64, METH_VARARGS, seed64_doc},
    {"init32", init32, METH_NOARGS, init32_doc},
    {"init64", init64, METH_NOARGS, init64_doc},
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


PyMODINIT_FUNC
PyInit_mt19937(void)
{
    return PyModule_Create(&pymt19937_module);
}
