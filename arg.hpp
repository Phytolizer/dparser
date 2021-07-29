/*
 Copyright 1994-2004 John Plevyak, All Rights Reserved
*/
#ifndef _arg_H_
#define _arg_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __alpha
#define atoll atol
#endif

/* Argument Handling
 */
struct ArgumentState;

using ArgumentFunction = void (*)(struct ArgumentState *, char *);

struct ArgumentDescription
{
    const char *name;
    char key;
    const char *description;
    const char *type;
    void *location;
    const char *env;
    ArgumentFunction pfn;
};

struct ArgumentState
{
    char **file_argument;
    int nfile_arguments;
    const char *program_name;
    ArgumentDescription *desc;
};

void usage(ArgumentState *arg_state, char *arg_unused);
void process_args(ArgumentState *arg_state, char **argv);
void free_args(ArgumentState *arg_state);

#endif
