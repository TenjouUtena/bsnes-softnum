
#include "python.hpp"

bool started = false;

static PyObject *PyInit_bsnes(void);

auto BsnesPython::init() -> void {

  PyImport_AppendInittab("bsnes", &PyInit_bsnes);
  Py_Initialize();
  PyRun_SimpleString("import sys");
  PyRun_SimpleString(
      "sys.path.append('/Users/utena/projects/bsnes_rust/bsnes/')");
  started = false;
}

auto BsnesPython::load_script(char *script_name) -> void {
  PyObject *pName = PyUnicode_DecodeFSDefault(script_name);
  script = PyImport_Import(pName);
  Py_DECREF(pName);
}

auto BsnesPython::run_frame(PyObject *script) -> void {

  PyGILState_STATE state;
  state = PyGILState_Ensure();
  PyErr_Clear();
  PyObject *pFunc = PyObject_GetAttrString(script, (char *)"update");
  PyObject *result = PyObject_CallNoArgs(pFunc);
  if (PyErr_Occurred()) {
    PyErr_Print();
  }

  PyGILState_Release(state);
  // started = false;
}

auto BsnesPython::run() -> bool {
  std::future_status status;
  if (!started) {
    started = true;
    if (t_state)
      PyEval_RestoreThread(t_state);
    t_state = PyEval_SaveThread();
    py_future = std::async(run_frame, script);
    return true;
  } else {
    switch (status = py_future.wait_for(0s); status) {
    case std::future_status::deferred:
    case std::future_status::timeout:
      break;
    case std::future_status::ready:
      std::cout << "ready!\n";
      started = false;
      break;
    }
  }
  return false;
}
auto _read_mem(uint address, uint length) -> uint* {
  uint retval[length];

  for(uint x = 0; x < length; x++)
    retval[x] = 0;

  return retval;
}
