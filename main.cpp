//
// Created by Troy Liu on 2021/11/25.
//

#include "src/echo_canceller.h"
#include <fstream>

int main(int argc, char **argv) {
  if (argc != 4) {
    printf("arguments should be: 1) near pcm; 2) far pcm; 3) out pcm");
    exit(1);
  }
  const char *near = argv[1];
  const char *far = argv[2];
  const char *out_path = argv[3];

  std::ifstream near_f{near, std::ios::in | std::ios::binary};
  std::ifstream far_f{far, std::ios::in | std::ios::binary};
  std::ofstream out_f{out_path, std::ios::out | std::ios::binary};

  int frame_size = 128;
  int filter_length = 4096;
  EchoCanceller canceller{frame_size, filter_length, 16000, 1, 1, false};

  auto *near_buffer = new int16_t[frame_size];
  auto *far_buffer = new int16_t[frame_size];
  std::memset(near_buffer, 0, sizeof(int16_t) * frame_size);
  std::memset(far_buffer, 0, sizeof(int16_t) * frame_size);

  if (near_f.is_open() && far_f.is_open() && out_f.is_open()) {
    while (near_f.read(reinterpret_cast<char *>(near_buffer), sizeof(int16_t) * frame_size) &&
           far_f.read(reinterpret_cast<char *>(far_buffer), sizeof(int16_t) * frame_size)) {
      const auto *buffer = canceller.process(near_buffer, far_buffer);
      out_f.write(reinterpret_cast<const char *>(buffer), sizeof(int16_t) * frame_size);
    }
    near_f.close();
    far_f.close();
    out_f.flush();
    out_f.close();
  } else {
    printf("Open failed!");
  }
  delete[] near_buffer;
  delete[] far_buffer;
}
