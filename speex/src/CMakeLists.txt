
option(BUILD_SHARED_LIBS "Build shared version libspeexdsp" ON)

list(APPEND srcs
        "buffer.c"
        "fftwrap.c"
        "filterbank.c"
        "jitter.c"
        "kiss_fft.c"
        "kiss_fftr.c"
        "mdf.c"
        "preprocess.c"
        "resample.c"
        "scal.c"
        "smallft.c"
        )

list(APPEND hdrs
        "_kiss_fft_guts.h"
        "arch.h"
        "bfin.h"
        "fftwrap.h"
        "filterbank.h"
        "fixed_arm4.h"
        "fixed_arm5e.h"
        "fixed_bfin.h"
        "fixed_debug.h"
        "fixed_generic.h"
        "kiss_fft.h"
        "kiss_fftr.h"
        "math_approx.h"
        "misc_bfin.h"
        "os_support.h"
        "pseudofloat.h"
        "resample_neon.h"
        "resample_sse.h"
        "smallft.h"
        "stack_alloc.h"
        "vorbis_psy.h"
        "../win32/config.h"
        )

list(APPEND public_hdrs
        "../include/speex/speex_buffer.h"
        "../include/speex/speex_echo.h"
        "../include/speex/speex_jitter.h"
        "../include/speex/speex_preprocess.h"
        "../include/speex/speex_resampler.h"
        "../include/speex/speexdsp_types.h"
        )

list(APPEND public_include_dirs
        "${CMAKE_CURRENT_SOURCE_DIR}/../include")

list(APPEND inc_dirs
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/../win32"
        "${public_include_dirs}")

list(APPEND definitions
        "HAVE_CONFIG_H"
        "_CRT_SECURE_NO_WARNINGS"
        #	"LIBSPEEXDSP_EXPORT"
        )

if (BUILD_SHARED_LIBS)
    set(LIBTYPE SHARED)
    #	list(APPEND definitions "LIBSPEEXDSP_DLL_EXPORT")
    #	list(APPEND public_definitions "LIBSPEEXDSP_DLL_IMPORT")
else ()
    set(LIBTYPE STATIC)
endif ()

add_library(libspeexdsp ${LIBTYPE} ${srcs} ${hdrs} ${public_hdrs})
set_target_properties(libspeexdsp PROPERTIES
        PUBLIC_HEADERS "${public_hdrs}"
        INCLUDE_DIRECTORIES "${inc_dirs}"
        COMPILE_DEFINITIONS "${definitions}"
        INTERFACE_INCLUDE_DIRECTORIES "${public_include_dirs}"
        INTERFACE_COMPILE_DEFINITIONS "${public_definitions}"
        PREFIX ""
        SOVERSION "${SPEEXSDP_LIBRARY_VERSION_MAJOR}"
        )
