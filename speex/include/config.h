// Microsoft version of 'inline'
#define inline __inline

// In Visual Studio, _M_IX86_FP=1 means /arch:SSE was used, likewise
// _M_IX86_FP=2 means /arch:SSE2 was used.
// Also, enable both _USE_SSE and _USE_SSE2 if we're compiling for x86-64
#if _M_IX86_FP >= 1 || defined(_M_X64)
#define _USE_SSE
#endif

#if _M_IX86_FP >= 2 || defined(_M_X64)
#define _USE_SSE2
#endif

// Visual Studio support alloca(), but it always align variables to 16-bit
// boundary, while SSE need 128-bit alignment. So we disable alloca() when
// SSE is enabled.
#ifndef _USE_SSE
#  define USE_ALLOCA
#endif

/* Default to floating point */
#ifndef FIXED_POINT
#  define FLOATING_POINT
#  define USE_SMALLFT
#else
#  define USE_KISS_FFT
#endif

#if !defined(LIBSPEEXDSP_DLL_EXPORT) && !defined(LIBSPEEXDSP_DLL_IMPORT)
#  define EXPORT
#else
#  if defined(LIBSPEEXDSP_DLL_EXPORT)
#    define EXPORT _declspec(dllexport)
#  else
#    define EXPORT _declspec(dllimport)
#  endif
#endif
