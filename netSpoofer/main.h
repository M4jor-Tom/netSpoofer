#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

#define IP_FETCH "/Users/benjaminscarrone/Desktop/test/ipFetch.sh"

//Temp files
#define ipTempFilePath "/Users/benjaminscarrone/Desktop/test/ips_temp"

//Pipes
#define finderPipePath "/Users/benjaminscarrone/Desktop/test/finderPipe"

//Binary files
#define finderPath "/Users/benjaminscarrone/Desktop/test/finder"

//Values
#define ipListLength 300
