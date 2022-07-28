import sys
from pybind11.setup_helpers import Pybind11Extension, build_ext, ParallelCompile
from glob import glob
from setuptools import setup, Extension

# Optional multithreaded build
ParallelCompile("NPY_NUM_BUILD_JOBS").install()

cpp_args = []
srcs = sorted(glob("src/*.cpp") + glob("speex/src/*.c")) + ["py_module.cpp"]
define_macros = [
    # ("FIXED_POINT", ""),
    ("HAVE_CONFIG_H", ""),
    ("FLOATING_POINT", "")
]
include_dirs = ["speex/include"]
if sys.platform != "win32":
    libraries = ['stdc++']
else:
    libraries = []

ext_modules = [
    Pybind11Extension(
        "pyspeexaec",
        srcs,  # Sort source files for reproducibility
        define_macros=define_macros,
        include_dirs=include_dirs,
        language='c++',
        extra_compile_args=cpp_args,
        libraries=libraries,
        cxx_std=11,
    ),
]

setup(
    name='pyspeexaec',
    version='0.2',
    description='Python bindings of speexdsp library',
    long_description="",
    long_description_content_type='text/markdown',
    author='Troy Liu',
    author_email='troyliu0105@outlook.com',
    maintainer='Troy Liu',
    maintainer_email='troyliu0105@outlook.com',
    url='https://github.com/troyliu0105/pyspeexaec',
    # download_url='https://pypi.python.org/pypi/pyspeexaec',
    packages=['pyspeexaec'],
    ext_modules=ext_modules,
    # Currently, build_ext only provides an optional "highest supported C++
    # level" feature, but in the future it may provide more features.
    cmdclass={"build_ext": build_ext},
    license='BSD',
    keywords=['speexdsp', 'acoustic echo cancellation'],
    platforms=['Linux'],
    package_dir={
        'pyspeexaec': 'src'
    },
    python_requires=">=3.6",
)
