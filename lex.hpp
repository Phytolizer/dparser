/*
  Copyright 2002-2004 John Plevyak, All Rights Reserved
*/

#ifndef _lex_H_
#define _lex_H_

/* #define LIVE_DIFF_IN_TRANSITIONS */

struct Grammar;

struct ScanStateTransition
{
    uint index;
    VecAction live_diff;
    VecAction accepts_diff;
};

struct ScanState
{
    uint index;
    ScanState *chars[256];
    VecAction accepts;
    VecAction live;
    ScanStateTransition *transition[256];
};

void build_scanners(Grammar *g);

#endif
