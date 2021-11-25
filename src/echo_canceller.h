#ifndef __ECHO_CANCELLER_H__
#define __ECHO_CANCELLER_H__

#include "speex/speex_echo.h"
#include <string>
#include <stdint.h>

class EchoCanceller {
public:
  explicit EchoCanceller(int frame_size = 256,
                         int filter_length = 2048,
                         int sample_rate = 16000,
                         int mics = 1,
                         int speakers = 1);

  std::string process(const std::string &near, const std::string &far);

  ~EchoCanceller();
private:
  SpeexEchoState *st;
  // SpeexPreprocessState *den;

  int16_t *e;
  int frames;
};

#endif // __ECHO_CANCELLER_H__