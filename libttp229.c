#include <Python.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* Docstrings */
static char module_docstring[] =
    "This module provides an interface for TTP229 using C.";
static char readData_docstring[] =
    "It gets data from the chip TTP229";
/* Available functions */
static PyObject *readData(PyObject *self, PyObject *args);

/* Module specification */
static PyMethodDef module_methods[] = {
    {"readData", (PyCFunction)readData, METH_VARARGS, readData_docstring},
    {NULL, NULL, 0, NULL}
};

/* Initialize the module */
PyMODINIT_FUNC initlibttp229(void)
{
    PyObject *m = Py_InitModule3("libttp229", module_methods, module_docstring);
    if (m == NULL)
        return;

}

static PyObject *readData(PyObject *self, PyObject *args)
{
    int address, quantity;
    //char *fileAdress;
    //PyObject *address, *quantity;
    //if (!PyArg_ParseTuple(args, "sii:readData", &fileAdress, &address, &quantity))
    if (!PyArg_ParseTuple(args, "ii:readData", &address, &quantity))
        return NULL;


    int file;
    char filename[40];
    //const gchar *buffer;

    //printf("Start.\n");
    sprintf(filename,"/dev/i2c-1");
    if ((file = open(filename,O_RDWR)) < 0) {
        return NULL;
    }

    if (ioctl(file,I2C_SLAVE, address) < 0) {
        return NULL;
    }

    char buf[10] = {0};
    int data;

    //char channel;

    if (read(file,buf,2) != 2) {
        /* ERROR HANDLING: i2c transaction failed */
        return NULL;
    } else {
        data = (int)(buf[0]<<8)+buf[1];
        PyObject *ret = Py_BuildValue("i", data); //d
        return ret;
    }

}

//void main(void){}