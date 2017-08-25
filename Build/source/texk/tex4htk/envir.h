/* --------------------------------------------
 *
 * envir.h
 *
 *  local environment definitions
 *      should be copied to the main project directory and edited to conform project prerequisites
 *
 * Changelog:
 *  2013-02-22  mp  initial creation
 *
 */


// -----------------------------------------

// #define Debug            // debug mode

// #define KP_VERBOSE       // warnings not just to .log file, to stderr as well

#define KP_CONSOLE          // console application
// #define KP_WINDOWED      // windows application; 
                            // could be defined together with KP_CONSOLE – for
                            //      console applications opening additional
                            //      dialog windows

// #define KP_CPP           // main module compiled as C++ application (exceptions can be used)

// #define KP_ALLOC_TRACE   // memory leak tracing
// #define KP_ALLOC_SAFE    // memory allocation control

// #define KP_ENCODE_LOG    // encode log file

#define DEV_EMAIL "tex-dev@vtex.lt"

#define MSVC_EXPRESS        // MSVC Express compiler used -- lack of standard libraries -- libuser32.a, for instance

// -------------------------------------
#if defined(WIN32) || defined(_WIN32)
#ifndef __WIN32__
#define __WIN32__
#endif
#endif

#ifdef _MSC_VER
// #define _X86_
#endif

#ifdef WIN32
#define HAVE_STRLWR 1
#define HAVE__GET_OSFHANDLE 1
#endif

#ifdef _MSC_VER
#define HAVE__ACCESS 1
#define HAVE__OPEN 1
#endif
