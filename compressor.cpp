#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

extern "C" {
    #include <Python.h>
}

using std::vector;
using std::string;

/**
 * The namespace for.
 */
namespace compressor {
    vector<int> z_function(string str) {
        using std::min;
        int len = static_cast<int>(str.length());
        vector<int> zRes(len);
        zRes[0] = len;
        for (int i = 1, l = 0, rMax = 0; i < len; ++i) {
            if (i <= rMax)
                zRes[i] = min(rMax - i + 1, zRes[i - l]);
            while (i + zRes[i] < len && str[zRes[i]] == str[i + zRes[i]])
                ++zRes[i];
            if (i + zRes[i] - 1 > rMax)
                l = i, rMax = i + zRes[i] - 1;
        }
        return zRes;
    }

    int getPeriod(const vector<int> &zFunc) {
        int strLen = zFunc.size();
        for (int ind = 1; ind < strLen; ++ind) {
            if (ind + zFunc.at(ind) == strLen && strLen % ind == 0) {
                return strLen / ind;
            }
        }
        return 1;
    }

    int compress(string str) {
        vector<int> res = z_function(str);
        int result = getPeriod(res);

        return result;

    }

}

/**
 * Run algorithm for list of strings.
 * Returns list of numbers.
 */
PyObject* comporess_list(PyObject *mod, PyObject *args){
    PyObject *inputList = PyTuple_GetItem(args, 0);
    PyObject *outputList = PyList_New(0);
    char* str;
    if(PyList_Check(inputList)) {
        for (size_t i = 0; i < PyList_Size(inputList); ++i) {
            PyObject *list_item = PyList_GetItem(inputList, i);
            if (!PyArg_Parse(list_item, "s", &str)) {
                Py_XDECREF(list_item);
                Py_XDECREF(inputList);
                Py_XDECREF(outputList);
                return NULL;
            }
            PyList_Append(outputList, PyLong_FromSize_t(compressor::compress(string(str))));
        }
    }
    else if(!PyArg_ParseTuple(inputList, "s", &str)){
        Py_XDECREF(inputList);
        Py_XDECREF(outputList);
        return NULL;
    }
    else {
        PyList_Append(outputList, PyLong_FromSize_t(compressor::compress(string(str))));
    }
    Py_INCREF(outputList);
    return outputList;
}

/**
 * Registring the Python module.
 */
PyMODINIT_FUNC PyInit_compressor() {
    static PyMethodDef ModuleMethods[] = {
            {"compressor", compress_list, METH_VARARGS,
                    "compressing"},
            { NULL, NULL, 0, NULL}
    };
    static PyModuleDef ModuleDef = {
            PyModuleDef_HEAD_INIT,
            "compressor",
            "solving Task 1.4. (SHAD, 2nd semester) for list of strings or for the single one.",
            -1, ModuleMethods,
            NULL, NULL, NULL, NULL
    };
    PyObject* module = PyModule_Create(&ModuleDef);
    return module;
}   