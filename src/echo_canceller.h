#ifndef __ECHO_CANCELLER_H__
#define __ECHO_CANCELLER_H__

#include "speex/speex_echo.h"
#include "speex/speex_preprocess.h"
#include <cstdint>
#ifndef NO_PYBIND11
#include <pybind11/numpy.h>
#endif
#include <string>

#ifndef NO_PYBIND11
namespace py = pybind11;
#endif

class EchoCanceller {
public:
  explicit EchoCanceller(int frame_size = 160, int filter_length = 1600, int sample_rate = 16000, int mics = 1,
                         int speakers = 1, bool use_preprocess = false);

  std::string process(const std::string &near, const std::string &far);
  const int16_t *process(const int16_t *near, const int16_t *far);

#ifndef NO_PYBIND11
  py::array_t<int16_t> process(const py::array_t<int16_t, py::array::c_style | py::array::forcecast> &near,
                               const py::array_t<int16_t, py::array::c_style | py::array::forcecast> &far);
#endif

  ~EchoCanceller();

  EchoCanceller(const EchoCanceller &) = delete;
  EchoCanceller &operator=(const EchoCanceller &) = delete;

private:
  SpeexEchoState *st{nullptr};
  SpeexPreprocessState *den{nullptr};

  int16_t *e{nullptr};
  int frames{0};
  int mics{0};
  int speakers{0};
};

#endif // __ECHO_CANCELLER_H__