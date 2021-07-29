/*
  Copyright 2002-2004 John Plevyak, All Rights Reserved
*/
#ifndef _parse_H_
#define _parse_H_

#define NO_DPN ((D_ParseNode *)0x1)
#define DPN_TO_PN(_dpn) ((PNode *)(((char *)dpn) - (intptr_t)(&((PNode *)0)->parse_node)))
#define is_epsilon_PNode(_pn) ((_pn)->parse_node.start_loc.s == (_pn)->parse_node.end)

/* #define TRACK_PNODES 1 */

struct PNode;
struct SNode;
struct ZNode;
struct Parser;

using VecZNode = Vec(ZNode *);
using VecVecZNode = Vec(VecZNode *);
using VecSNode = Vec(SNode *);
using VecPNode = Vec(PNode *);

struct PNodeHash
{
    PNode **v;
    uint i; /* size index (power of 2) */
    uint m; /* max size (highest prime < i ** 2) */
    uint n; /* size */
    PNode *all;
};

struct SNodeHash
{
    SNode **v;
    uint i; /* size index (power of 2) */
    uint m; /* max size (highest prime < i ** 2) */
    uint n; /* size */
    SNode *all;
    SNode *last_all;
};

struct Reduction
{
    ZNode *znode;
    SNode *snode;
    D_Reduction *reduction;
    SNode *new_snode;
    int new_depth;
    Reduction *next;
};

struct Shift
{
    SNode *snode;
    Shift *next;
};

struct Parser
{
    D_Parser user;
    /* string to parse */
    char *start, *end;
    D_ParserTables *t;
    /* statistics */
    int states, pnodes, scans, shifts, reductions, compares, ambiguities;
    /* parser state */
    PNodeHash pnode_hash;
    SNodeHash snode_hash;
    Reduction *reductions_todo;
    Shift *shifts_todo;
    D_Scope *top_scope;
    SNode *accept;
    int last_syntax_error_line;
    /* memory management */
    Reduction *free_reductions;
    Shift *free_shifts;
    int live_pnodes;
    PNode *free_pnodes;
    SNode *free_snodes;
    ZNode *free_znodes;
    Vec(D_Reduction *) error_reductions;
    ShiftResult *shift_results;
    int nshift_results;
    D_Shift *code_shifts;
    int ncode_shifts;
    /* comments */
    Parser *whitespace_parser;
    /* interface support */
    void *pinterface1;
#ifdef TRACK_PNODES
    struct PNode *xall;
#endif
};

/*
  Parse Node - the 'symbol' and the constructed parse subtrees.
*/
struct PNode
{
    uint hash;
    AssocKind assoc;
    int priority;
    AssocKind op_assoc;
    int op_priority;
#ifndef USE_GC
    uint32 refcount;
#endif
    uint height; /* max tree height */
    uint8 evaluated;
    uint8 error_recovery;
    D_Reduction *reduction;
    D_Shift *shift;
    VecPNode children;
    PNode *all_next;
    PNode *bucket_next;
    PNode *ambiguities;
    PNode *latest; /* latest version of this PNode */
    char *ws_before;
    char *ws_after;
    D_Scope *initial_scope;
    void *initial_globals;
#ifdef TRACK_PNODES
    PNode *xnext;
    PNode *xprev;
#endif
    D_ParseNode parse_node; /* public fields */
};

/*
  State Node - the 'state'.
*/
struct SNode
{
    d_loc_t loc;
#ifndef USE_GC
    uint32 refcount;
#endif
    uint32 depth : 31; /* max stack depth (less loops) */
    uint32 in_error_recovery_queue : 1;
    D_State *state;
    D_Scope *initial_scope;
    void *initial_globals;
    PNode *last_pn;
    VecZNode zns;
    SNode *bucket_next;
    SNode *all_next;
};

/*
  (Z)Symbol Node - holds one of the symbols associated with a state.
*/
struct ZNode
{
    PNode *pn;
    VecSNode sns;
};
#define znode_next(_z) (*(ZNode **)&((_z)->pn))

D_ParseNode *ambiguity_count_fn(D_Parser *pp, int n, D_ParseNode **v);

#endif
