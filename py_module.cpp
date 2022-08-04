//
// Created by Troy Liu on 2021/11/25.
//

#include "src/echo_canceller.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(pyspeexaec, m) {
  m.doc() = "Python Speex AEC";
  py::class_<EchoCanceller>(m, "EchoCanceller")
      .def(py::init<int, int, int, int, int, bool>(), py::arg("frame_size") = 160, py::arg("filter_length") = 1600,
           py::arg("sample_rate") = 16000, py::arg("mics") = 1, py::arg("speakers") = 1,
           py::arg("use_preprocess") = false)
      .def("process",
           static_cast<std::string (EchoCanceller::*)(const std::string &near, const std::string &far)>(
               &EchoCanceller::process),
           py::arg("rec"), py::arg("ref"))
      .def("process",
           static_cast<py::array_t<int16_t> (EchoCanceller::*)(
               const py::array_t<int16_t, py::array::c_style | py::array::forcecast> &,
               const py::array_t<int16_t, py::array::c_style | py::array::forcecast> &)>(&EchoCanceller::process),
           py::arg("rec"), py::arg("ref"), py::return_value_policy::move);
}