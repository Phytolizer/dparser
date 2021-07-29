/*
  Copyright 2002-2006 John Plevyak, All Rights Reserved
*/

#ifndef _util_H_
#define _util_H_

#include "types.hpp"

#define INITIAL_SET_SIZE_INDEX 2

#define INITIAL_VEC_SHIFT 3
#define INITIAL_VEC_SIZE (1 << INITIAL_VEC_SHIFT)
#define INITIAL_VEC_SIZE (1 << INITIAL_VEC_SHIFT)
#define INTEGRAL_VEC_SIZE 3
#define INTEGRAL_STACK_SIZE 8

#define SET_MAX_SEQUENTIAL 5

#define IS_BIT_SET(_v, _s) ((_v)[(_s) / 8] & 1 << ((_s) % 8))
#define SET_BIT(_v, _s) (_v)[(_s) / 8] |= (1 << ((_s) % 8))

struct AbstractVec
{
    uint n;
    uint i; /* size index for use with sets */
    void **v;
    void *e[INTEGRAL_VEC_SIZE];
};
#define Vec(_x)                                                                                                        \
    struct                                                                                                             \
    {                                                                                                                  \
        uint n;                                                                                                        \
        uint i;                                                                                                        \
        _x *v;                                                                                                         \
        _x e[INTEGRAL_VEC_SIZE];                                                                                       \
    }

struct AbstractStack
{
    void **start;
    void **end;
    void **cur;
    void *initial[INTEGRAL_STACK_SIZE];
};
#define Stack(_x)                                                                                                      \
    struct                                                                                                             \
    {                                                                                                                  \
        _x *start;                                                                                                     \
        _x *end;                                                                                                       \
        _x *cur;                                                                                                       \
        _x initial[INTEGRAL_STACK_SIZE];                                                                               \
    }

struct hash_fns_t;
using hash_fn_t = uint32 (*)(void *, struct hash_fns_t *);
using cmp_fn_t = int (*)(void *, void *, struct hash_fns_t *);
struct hash_fns_t
{
    hash_fn_t hash_fn;
    cmp_fn_t cmp_fn;
    void *data[2];
};

#define vec_add(_v, _i)                                                                                                \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(_v)->v)                                                                                                  \
        {                                                                                                              \
            ((_v)->v = (_v)->e)[(_v)->n++] = (_i);                                                                     \
            break;                                                                                                     \
        }                                                                                                              \
        else if ((_v)->v == ((_v)->e))                                                                                 \
        {                                                                                                              \
            if (((_v)->n < INTEGRAL_VEC_SIZE))                                                                         \
            {                                                                                                          \
                (_v)->v[(_v)->n++] = (_i);                                                                             \
                break;                                                                                                 \
            }                                                                                                          \
        }                                                                                                              \
        else if ((_v)->n & (INITIAL_VEC_SIZE - 1))                                                                     \
        {                                                                                                              \
            (_v)->v[(_v)->n++] = (_i);                                                                                 \
            break;                                                                                                     \
        }                                                                                                              \
        vec_add_internal((_v), _i);                                                                                    \
    } while (0)
void vec_add_internal(void *v, void *elem);
int set_find(void *v, void *t);
int set_add(void *v, void *t);
int set_union(void *v, void *vv);
void *set_add_fn(void *v, void *t, hash_fns_t *fns);
void set_union_fn(void *v, void *vv, hash_fns_t *fns);
void set_to_vec(void *av);
#define vec_clear(_v)                                                                                                  \
    do                                                                                                                 \
    {                                                                                                                  \
        (_v)->n = 0;                                                                                                   \
        (_v)->v = 0;                                                                                                   \
    } while (0)
#define vec_free(_v)                                                                                                   \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((_v)->v && (_v)->v != (_v)->e)                                                                             \
            FREE((_v)->v);                                                                                             \
        vec_clear(_v);                                                                                                 \
    } while (0)

#define stack_clear(_s)                                                                                                \
    do                                                                                                                 \
    {                                                                                                                  \
        (_s)->start = (_s)->cur = (_s)->end = (_s)->initial;                                                           \
        (_s)->end += INTEGRAL_STACK_SIZE;                                                                              \
    } while (0)
#define stack_free(_s)                                                                                                 \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((_s)->start != (_s)->initial)                                                                              \
            FREE((_s)->start);                                                                                         \
        stack_clear(_s);                                                                                               \
    } while (0)
#define stack_head(_s) ((_s)->cur[-1])
#define is_stack_empty(_s) ((_s)->cur == (_s)->start)
#define stack_depth(_s) ((_s)->cur - (_s)->start)
#define stack_pop(_s) (*--((_s)->cur))
#define stack_push(_s, _x)                                                                                             \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((_s)->cur == (_s)->end)                                                                                    \
            stack_push_internal((AbstractStack *)((_s)), (void *)(uintptr_t)(_x));                                     \
        else                                                                                                           \
            (*((_s)->cur)++ = (_x));                                                                                   \
                                                                                                                       \
    } while (0)
void *stack_push_internal(AbstractStack *, void *);

int buf_read(const char *pathname, char **buf, int *len);
char *sbuf_read(const char *pathname);

#if defined(WIN32)
#define STREQ(_x, _n, _s) ((_n == sizeof(_s) - 1) && !strnicmp(_x, _s, sizeof(_s) - 1))
#else
#define STREQ(_x, _n, _s) ((_n == sizeof(_s) - 1) && !strncasecmp(_x, _s, sizeof(_s) - 1))
#endif

void d_fail(const char *str, ...);
void d_warn(const char *str, ...);
char *dup_str(const char *str, const char *end);
uint strhashl(const char *s, int len);
void d_free(void *);

char *escape_string(char *s);
char *escape_string_single_quote(char *s);

extern uint d_prime2[];
extern int d_verbose_level;
extern int d_debug_level;
extern int test_level;
extern int d_rdebug_grammar_level;

#endif
