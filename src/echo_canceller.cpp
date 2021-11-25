#include <cstdint>
#include <iostream>

#include "echo_canceller.h"

EchoCanceller::EchoCanceller(int frame_size, int filter_length, int sample_rate, int mics, int speakers,
                             bool use_preprocess) {
  st = speex_echo_state_init_mc(frame_size, filter_length, mics, speakers);
  speex_echo_ctl(st, SPEEX_ECHO_SET_SAMPLING_RATE, &sample_rate);

  if (use_preprocess) {
    den = speex_preprocess_state_init(frame_size, sample_rate);
    speex_preprocess_ctl(den, SPEEX_PREPROCESS_SET_ECHO_STATE, st);
  }

  frames = frame_size * mics;
  this->mics = mics;
  this->speakers = speakers;
  e = new DType[frames];
}

EchoCanceller::~EchoCanceller() {
  speex_echo_state_destroy(st);
  if (den) {
    speex_preprocess_state_destroy(den);
  }
  delete e;
}

std::string EchoCanceller::process(const std::string &near, const std::string &far) {
  const auto *y = (const DType *)(near.data());
  const auto *x = (const DType *)(far.data());

  // e = y - filter(x)
  speex_echo_cancellation(st, y, x, e);

  if (den) {
    speex_preprocess_run(den, e);
  }

  return {(const char *)e, frames * sizeof(DType)};
}

py::array_t<DType> EchoCanceller::process(const py::array_t<DType, py::array::c_style | py::array::forcecast> &near,
                                          const py::array_t<DType, py::array::c_style | py::array::forcecast> &far) {

  const DType *y = static_cast<const DType *>(near.request(false).ptr);
  const DType *x = static_cast<const DType *>(far.request(false).ptr);
  // e = y - filter(x)
  speex_echo_cancellation(st, y, x, e);

  if (den) {
    speex_preprocess_run(den, e);
  }
  py::array_t<DType> out(frames);
  std::memcpy(out.request(true).ptr, e, frames * sizeof(DType));
  return out;
}