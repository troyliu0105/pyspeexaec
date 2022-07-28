# 简介

使用 pybind11 对 speex aec 进行简单的包装方便使用

## 安装

```shell
# 需要使用 c++ 编译器进行 c/c++ 混编 (speex 是 c 源码)
export CC=g++
python setup.py install
```

## 使用

```python
import pyspeexaec

aec = pyspeexaec.EchoCanceller(
    frame_size=160,
    filter_length=1600,
    sample_rate=16000,
    mics=1,
    speakers=1,
    use_preprocess=False
)
# rec 为近端, 单通道 int16 ndarray, shape: [N, 1]
# ref 为远端, 单通道 int16 ndarray, shape: [N, 1]
# out 为经过 aec 处理之后的音频, 单通道 int16 ndarray, shape: [N, 1]  
out = aec.process(rec, ref)
```

### C/C++ 版本的使用

具体使用方法参考 `EchoCanceller` 实现