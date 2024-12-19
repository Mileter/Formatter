#include <iostream>
#include <functional>
#include <unordered_map>
#include <map>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>
#include <utility>

#include <cstdio>
#include <cstring>
#include <cstdarg>

#include "kern/kern.h"

#define F_BUILD_TYPE "ALPHA"
#define F_BUILD_VER  "0.1.0.1"

// error codes
// haha
#define ERR_OK 0
#define ERR_UNKNOWN_CMD 5
// files
#define ERR_FILEIO_DENIED 10
// args
#define ERR_IMPROPER_ARGS 30

template < typename F, typename T, std::size_t N > decltype(auto) apply(F f,
																		T(&t)
																		[N]);
