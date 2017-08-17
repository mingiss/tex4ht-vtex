/* --------------------------------------------
 *
 * envir.h
 *
 *    local environment definitions
 *
 * 2013-02-22  mp  initial creation
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


// -------------------------------------
#ifdef _MSC_VER
#ifdef _WIN32
#define __WIN32__
#endif
#endif

