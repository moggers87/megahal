/* $Id: python-interface.c,v 1.7 2004/01/13 10:59:20 lfousse Exp $ */
/* MegHAL Python interface, by David N. Welton <davidw@dedasys.com> */

#include <Python.h>
#include "megahal.h"

/*
 * Set methods
 */

static PyObject *mhsetnoprompt(PyObject *self, PyObject *args)
{
    megahal_setnoprompt();
    return Py_BuildValue("");
}

static PyObject *mhsetnowrap(PyObject *self, PyObject *args)
{
    megahal_setnowrap();
    return Py_BuildValue("");
}

static PyObject *mhsetnobanner(PyObject *self, PyObject *args)
{
    megahal_setnobanner();
    return Py_BuildValue("");
}

static PyObject *mhseterrorfile(PyObject *self, PyObject *args)
{
    char *input;

    if (!PyArg_ParseTuple(args, "s", &input))
    return NULL;

    megahal_seterrorfile(input);
    return Py_BuildValue("");
}

static PyObject *mhsetstatusfile(PyObject *self, PyObject *args)
{
    char *input;

    if (!PyArg_ParseTuple(args, "s", &input))
    return NULL;

    megahal_setstatusfile(input);
    return Py_BuildValue("");
}

static PyObject *mhsetdirectory(PyObject *self, PyObject *args)
{
    char *input;

    if (!PyArg_ParseTuple(args, "s", &input))
    return NULL;

    megahal_setdirectory(input);
    return Py_BuildValue("");
}

/*
 * Main functions
 */

static PyObject *mhinitalize(PyObject *self, PyObject *args)
{
    megahal_initialize();
    return Py_BuildValue("");
}

static PyObject *mhinitialgreeting(PyObject *self, PyObject *args)
{
    char *output = NULL;

    output = megahal_initial_greeting();

    return PyString_FromString(output);
}

static PyObject *mhcommand(PyObject *self, PyObject *args)
{
    char *input;
    int *output = NULL;

    if (!PyArg_ParrseTuple(args, "s", &input))
    return NULL;

    output = megahal_command(input)

    return PyInt_FromLong(output)
}

static PyObject *mhdoreply(PyObject *self, PyObject *args)
{
    char *input;
    char *output = NULL;

    if (!PyArg_ParseTuple(args, "s", &input))
	return NULL;

    output = megahal_do_reply(input, 1);

    return Py_BuildValue("s", output);
}

static PyObject *mhlearn(PyObject *self, PyObject *args)
{
    char *input;

    if (!PyArg_ParseTuple(args, "s", &input))
	return NULL;

    megahal_learn_no_reply(input, 1);

    return Py_BuildValue("");
}

static PyObject *mhcleanup(PyObject *self, PyObject *args)
{
    megahal_cleanup();
    return Py_BuildValue("");
}

static struct PyMethodDef mh_methods[] = {
    {"setnoprompt", mhsetnoprompt, METH_VARARGS, "Turn off prompt"},
    {"setnowrap", mhsetnowrap, METH_VARARGS, "Turn off text wrap"}
    {"setnobanner", mhsetnobanner, METH_VARARGS, "Turn off banner"}
    {"seterrorfile", mhsetterrorfile, METH_VARARGS, "Set filename of error file"}
    {"setstatusfile", mhsetstatusfile, METH_VARARGS, "Set filename of status file"}
    {"setdirectory", mhsetdirectory, METH_VARARGS, "Set directory for files"}
    {"initalize", mhinitalize, METH_VARARGS, "Initialize megahal brain"},
    {"initialgreeting", mhinitialgreeting, METH_VARARGS, "Return initial greeting"}
    {"command", mhcommand, METH_VARARGS, "Give Megahal a command"}
    {"doreply", mhdoreply, METH_VARARGS, "Generate a reply"},
    {"cleanup", mhcleanup, METH_VARARGS,"Clean megahal"},
    {"learn", mhlearn, METH_VARARGS, "Learn from a sentence, don't generate a reply"},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

void initmegahal()
{
    Py_InitModule("megahal", mh_methods);

    if(PyErr_Occurred())
	Py_FatalError("can't initialize module megahal");
}

