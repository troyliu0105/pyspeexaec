#ifndef __ECHO_CANCELLER_H__
#define __ECHO_CANCELLER_H__

#include "speex/speex_echo.h"
#include "speex/speex_preprocess.h"
#include <cstdint>
#include <pybind11/numpy.h>
#include <string>

namespace py = pybind11;
using DType = int16_t;

class EchoCanceller {
public:
  explicit EchoCanceller(int frame_size = 160, int filter_length = 1600, int sample_rate = 16000, int mics = 1,
                         int speakers = 1, bool use_preprocess = false);

  std::string process(const std::string &near, const std::string &far);
  py::array_t<DType> process(const py::array_t<DType, py::array::c_style | py::array::forcecast> &near,
                             const py::array_t<DType, py::array::c_style | py::array::forcecast> &far);

  ~EchoCanceller();

private:
  SpeexEchoState *st{nullptr};
  SpeexPreprocessState *den{nullptr};

  DType *e{nullptr};
  int frames{0};
  int mics{0};
  int speakers{0};
};

#endif // __ECHO_CANCELLER_H__