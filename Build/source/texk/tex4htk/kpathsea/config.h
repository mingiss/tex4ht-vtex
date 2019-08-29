// kpathsea/config.h wrapper
// original file is included in the middle of this file
// used to add individual compiler options to all kpathsea/*.c sources in QT Creator build
// the right way should be to use an extra compiler concept:
// https://stackoverflow.com/questions/27683777/how-to-specify-compiler-flag-to-a-single-source-file-with-qmake
// current approach seems a bit dirty, though quite elegant and simpler

#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-parameter"

#define MAKE_KPSE_DLL

#include "../../kpathsea/config.h"

extern string kpathsea_expand(kpathsea kpse, const_string s);
