#ifndef __ECHO_CANCELLER_H__
#define __ECHO_CANCELLER_H__

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
  /**
   * 初始化 speex 回声消除。
   * @param frame_size      帧长度
   * @param filter_length   滤波器长度
   * @param sample_rate     采样率
   * @param mics            麦克风数量
   * @param speakers        扬声器数量
   * @param use_preprocess  是否采用后处理增强
   */
  explicit EchoCanceller(int frame_size = 160, int filter_length = 1600, int sample_rate = 16000, int mics = 1,
                         int speakers = 1, bool use_preprocess = false);

  /**
   * 对 frame_size 长度的音频进行回声消除
   * @param near    近端（录音信号）
   * @param far     远端（参考信号）
   * @return
   */
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
  inline void _process(const int16_t *near, const int16_t *far);

  void *st{nullptr};
  void *den{nullptr};

  int16_t *e{nullptr};
  int frames{0};
  int mics{0};
  int speakers{0};
};

#endif // __ECHO_CANCELLER_H__