// Natcha Jengjirapas
// Njengjir

// Useage statement
#define USAGE "usage: 53tweet [-Q] [-N LENGTH] [-P PUNC_LIST]\n"

#include <stdio.h>
#include <stdlib.h>
#include "helpers1.h"

// noFlag function runs when the user did not specify any flag and
// outputs the "tweetable" sentences, including a 
// terminating punctuation to stdout (one per line).
// statistic outputs to the stderr.
int manager(int, char**);

int run(const int, const int, const char*);
