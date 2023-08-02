/*!The Treasure Box Library
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Copyright (C) 2009-present, TBOOX Open Source Group.
 *
 * @author      ruki
 * @file        atomic64.c
 * @ingroup     platform
 *
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "spinlock.h"
#include "atomic64.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */

// the atomic64 lock mac count
#define TB_ATOMIC64_LOCK_MAXN       (16)

/* //////////////////////////////////////////////////////////////////////////////////////
 * types
 */

// the atomic64 lock type
typedef __tb_cacheline_aligned__ struct __tb_atomic64_lock_t
{
    // the lock
    tb_spinlock_t           lock;

    // the padding
    tb_byte_t               padding[TB_L1_CACHE_BYTES];

}__tb_cacheline_aligned__ tb_atomic64_lock_t;

/* //////////////////////////////////////////////////////////////////////////////////////
 * globals
 */

// the locks
static tb_atomic64_lock_t   g_locks[TB_ATOMIC64_LOCK_MAXN] =
{
    {TB_SPINLOCK_INIT, {0}}
};

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementation
 */

static __tb_inline_force__ tb_spinlock_ref_t tb_atomic64_lock(tb_atomic64_t* a)
{
    // trace
    tb_trace1_w("using generic atomic64, maybe slower!");

    // the addr
    tb_size_t addr = (tb_size_t)a;

    // compile the hash value
    addr >>= TB_L1_CACHE_SHIFT;
    addr ^= (addr >> 8) ^ (addr >> 16);

    // the lock
    return &g_locks[addr & (TB_ATOMIC64_LOCK_MAXN - 1)].lock;
}

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementation
 */
tb_bool_t tb_atomic64_compare_and_swap_explicit_generic(tb_atomic64_t* a, tb_int64_t* p, tb_int64_t v, tb_int_t succ, tb_int_t fail)
{
    // check
    tb_assert(a && p);

    // the lock
    tb_spinlock_ref_t lock = tb_atomic64_lock(a);

    // enter
    tb_spinlock_enter(lock);

    // set value
    tb_bool_t ok = tb_false;
    tb_atomic64_t o = *a;
    if (o == *p)
    {
        *a = v;
        ok = tb_true;
    }
    else *p = o;

    // leave
    tb_spinlock_leave(lock);

    // ok?
    return ok;
}

