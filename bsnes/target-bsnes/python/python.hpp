#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <chrono>
#include <cstddef>
#include <future>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

struct BsnesPython {
  std::future<void> py_future;

  PyObject *script;
  PyThreadState *t_state = nullptr;

  BsnesPython() {}
  auto init() -> void;
  auto load_script(char *script_name) -> void;
  static auto run_frame(PyObject *script) -> void;
  auto run() -> bool;
  ~BsnesPython() { Py_FinalizeEx(); }
};

auto _read_mem(uint address, uint length) -> uint *;

static PyObject *read_mem(PyObject *self, PyObject *args) { return Py_None; }

static PyMethodDef PyMethods[] = {
    {"read_mem", read_mem, METH_VARARGS,
     "Return the number of arguments received by the process."},
    {NULL, NULL, 0, NULL}};

static PyModuleDef PyModule = {PyModuleDef_HEAD_INIT,
                               "bsnes",
                               NULL,
                               -1,
                               PyMethods,
                               NULL,
                               NULL,
                               NULL,
                               NULL};

static PyObject *PyInit_bsnes(void) { return PyModule_Create(&PyModule); }
