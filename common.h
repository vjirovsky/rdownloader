#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include <errno.h>
#include "curl/curl.h"  

#include <cstdlib>
#include <iostream>
#include <string>
#include "pcre/pcre.h"

#ifdef _WIN32

#include "getopt.h"
#include <direct.h>
#include <sys/time.h>
#include <conio.h>
#include <windows.h>

#define GetCurrentDir _getcwd
#else
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#define GetCurrentDir getcwd
#endif
using namespace std;
#define DEBUG 0 //! debugging mode