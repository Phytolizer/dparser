/*
  Copyright 2002-2004 John Plevyak, All Rights Reserved
*/

#ifndef _scan_H_
#define _scan_H_

#include "gram.hpp"

typedef struct ShiftResult
{
    struct SNode *snode;
    D_Shift *shift;
    d_loc_t loc;
} ShiftResult;

int scan_buffer(d_loc_t *loc, D_State *st, ShiftResult *result);

#endif
