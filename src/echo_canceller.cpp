#include "speex/speex_echo.h"
#include "speex/speex_preprocess.h"
#include <cstdint>
#include <iostream>

#include "echo_canceller.h"

EchoCanceller::EchoCanceller(int frame_size, int filter_length, int sample_rate, int mics, int speakers,
                             bool use_preprocess) {
  st = speex_echo_state_init_mc(frame_size, filter_length, mics, speakers);
  speex_echo_ctl(static_cast<SpeexEchoState *>(st), SPEEX_ECHO_SET_SAMPLING_RATE, &sample_rate);

  if (use_preprocess) {
    den = speex_preprocess_state_init(frame_size, sample_rate);
    speex_preprocess_ctl(static_cast<SpeexPreprocessState *>(den), SPEEX_PREPROCESS_SET_ECHO_STATE,
                         static_cast<SpeexEchoState *>(st));
  }

  frames = frame_size * mics;
  this->mics = mics;
  this->speakers = speakers;
  e = new int16_t[frames];
}

EchoCanceller::~EchoCanceller() {
  speex_echo_state_destroy(static_cast<SpeexEchoState *>(st));
  if (den) {
    speex_preprocess_state_destroy(static_cast<SpeexPreprocessState *>(den));
  }
  delete[] e;
}

std::string EchoCanceller::process(const std::string &near, const std::string &far) {
  const auto *y = reinterpret_cast<const int16_t *>(near.data());
  const auto *x = reinterpret_cast<const int16_t *>(far.data());

  this->_process(y, x);

  return {reinterpret_cast<const char *>(e), frames * sizeof(int16_t)};
}

const int16_t *EchoCanceller::process(const int16_t *near, const int16_t *far) {
  this->_process(near, far);
  return e;
}

#ifndef NO_PYBIND11
py::array_t<int16_t>
EchoCanceller::process(const py::array_t<int16_t, py::array::c_style | py::array::forcecast> &near,
                       const py::array_t<int16_t, py::array::c_style | py::array::forcecast> &far) {

  const int16_t *y = reinterpret_cast<const int16_t *>(near.request(false).ptr);
  const int16_t *x = reinterpret_cast<const int16_t *>(far.request(false).ptr);
  this->_process(y, x);
  py::array_t<int16_t> out(frames);
  std::memcpy(out.request(true).ptr, e, frames * sizeof(int16_t));
  out.reshape({this->frames / mics, mics});
  return out;
}
#endif

void EchoCanceller::_process(const int16_t *near, const int16_t *far) {
  // e = y - filter(x)
  speex_echo_cancellation(static_cast<SpeexEchoState *>(st), near, far, e);

  if (den) {
    speex_preprocess_run(static_cast<SpeexPreprocessState *>(den), e);
  }
}