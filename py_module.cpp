//
// Created by Troy Liu on 2021/11/25.
//

#include "src/echo_canceller.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(pyspeexaec, m) {
  m.doc() = "Python Speex AEC";
  py::class_<EchoCanceller>(m, "EchoCanceller")
      .def(py::init<int, int, int, int, int>(),
           py::arg("frame_size") = 256,
           py::arg("filter_length") = 2048,
           py::arg("sample_rate") = 16000,
           py::arg("mics") = 1,
           py::arg("speakers") = 1)
      .def("process", &EchoCanceller::process, py::arg("rec"), py::arg("ref"));
}