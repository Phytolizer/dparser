/*
  Copyright 2002-2004 John Plevyak, All Rights Reserved
*/
#ifndef _dparse_tables_H_
#define _dparse_tables_H_

#define SCANNER_BLOCKS_POW2 2
#define SCANNER_BLOCKS (1 << SCANNER_BLOCKS_POW2)
#define SCANNER_BLOCK_SHIFT (8 - SCANNER_BLOCKS_POW2)
#define SCANNER_BLOCK_MASK ((1 << SCANNER_BLOCK_SHIFT) - 1)
#define SCANNER_BLOCK_SIZE (256 / SCANNER_BLOCKS)

struct D_Parser;
struct D_ShiftTable;

#define D_PN(_x, _o) ((D_ParseNode *)((char *)(_x) + _o))

struct d_loc_t
{
    char *s;
    const char *pathname;
    char *ws;
    int col, line;
};

using D_WhiteSpaceFn = void (*)(struct D_Parser *p, d_loc_t *loc, void **p_globals);
using D_ScanCode = int (*)(d_loc_t *loc, unsigned short *symbol, int *term_priority, unsigned char *op_assoc,
                           int *op_priority);
using D_ReductionCode = int (*)(void *new_ps, void **children, int n_children, int pn_offset, struct D_Parser *parser);

struct D_Reduction
{
    unsigned short nelements;
    unsigned short symbol;
    D_ReductionCode speculative_code;
    D_ReductionCode final_code;
    unsigned short op_assoc;
    unsigned short rule_assoc;
    int op_priority;
    int rule_priority;
    int action_index;
    int npass_code;
    D_ReductionCode *pass_code;
};

struct D_RightEpsilonHint
{
    unsigned short depth;
    unsigned short preceeding_state;
    D_Reduction *reduction;
};

struct D_ErrorRecoveryHint
{
    unsigned short depth;
    unsigned short symbol;
    const char *string;
};

struct D_Shift
{
    unsigned short symbol;
    unsigned char shift_kind;
    unsigned char op_assoc;
    int op_priority;
    int term_priority;
    int action_index;
    D_ReductionCode speculative_code;
};

struct SB_uint8
{
    D_Shift **shift;
    unsigned char *scanner_block[SCANNER_BLOCKS];
};

struct SB_uint16
{
    D_Shift **shift;
    unsigned short *scanner_block[SCANNER_BLOCKS];
};

struct SB_uint32
{
    D_Shift **shift;
    unsigned int *scanner_block[SCANNER_BLOCKS];
};

struct SB_trans_uint8
{
    unsigned char *scanner_block[SCANNER_BLOCKS];
};

struct SB_trans_uint16
{
    unsigned short *scanner_block[SCANNER_BLOCKS];
};

struct SB_trans_uint32
{
    unsigned int *scanner_block[SCANNER_BLOCKS];
};

#define D_SCAN_ALL 0
#define D_SCAN_LONGEST 1
#define D_SCAN_MIXED 2
#define D_SCAN_TRAILING 3
#define D_SCAN_RESERVED 4
#define D_SCAN_DEFAULT D_SCAN_ALL

struct D_State
{
    unsigned char *goto_valid;
    int goto_table_offset;
    struct
    {
        unsigned int n;
        D_Reduction **v;
    } reductions;
    struct
    {
        unsigned int n;
        D_RightEpsilonHint *v;
    } right_epsilon_hints;
    struct
    {
        unsigned int n;
        D_ErrorRecoveryHint *v;
    } error_recovery_hints;
    int shifts;
    D_ScanCode scanner_code;
    void *scanner_table;
    unsigned char scanner_size;
    unsigned char accept;
    unsigned char scan_kind;
    void *transition_table;
    D_Shift ***accepts_diff;
    int reduces_to;
};

#define D_SHIFTS_CODE ((D_Shift **)-1)

#define D_SYMBOL_NTERM 1
#define D_SYMBOL_INTERNAL 2
#define D_SYMBOL_EBNF 3
#define D_SYMBOL_STRING 4
#define D_SYMBOL_REGEX 5
#define D_SYMBOL_CODE 6
#define D_SYMBOL_TOKEN 7
struct D_Symbol
{
    unsigned int kind;
    const char *name;
    int name_len;
    int start_symbol;
};

#define D_PASS_PRE_ORDER 0x0001
#define D_PASS_POST_ORDER 0x0002
#define D_PASS_MANUAL 0x0004
#define D_PASS_FOR_ALL 0x0008
#define D_PASS_FOR_UNDEFINED 0x0010
struct D_Pass
{
    char *name;
    unsigned int name_len;
    unsigned int kind;
    unsigned int index;
};

struct D_ParserTables
{
    unsigned int nstates;
    D_State *state;
    unsigned short *goto_table;
    unsigned int whitespace_state;
    unsigned int nsymbols;
    D_Symbol *symbols;
    D_WhiteSpaceFn default_white_space;
    unsigned int npasses;
    D_Pass *passes;
    unsigned int save_parse_tree;
};

void parse_whitespace(D_Parser *p, d_loc_t *loc, void **p_globals);

#endif
