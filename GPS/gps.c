#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
//#include "types.h"
#include "gps.h"



static int GetComma(int num,char* str);
static void UTC2BTC(date_time *GPS);
static double get_double_number(char *s);

