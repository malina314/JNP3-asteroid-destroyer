// This file defines some macro constants before including windows.h.
// It prevents windows.h from including some rarely used headers, which can slow
// down compilation. It also defines UNICODE macro, which is used to tell
// windows.h to use Unicode encoding.

#ifndef WINDOWS_H_H
#define WINDOWS_H_H

#define WIN32_LEAN_AND_MEAN

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

#endif // WINDOWS_H_H
