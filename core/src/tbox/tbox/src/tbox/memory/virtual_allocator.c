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
 * @file        virtual_allocator.c
 *
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * trace
 */
#define TB_TRACE_MODULE_NAME            "virtual_allocator"
#define TB_TRACE_MODULE_DEBUG           (0)

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "virtual_allocator.h"
#include "../utils/utils.h"
#include "../platform/platform.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * private implementation
 */
static tb_pointer_t tb_virtual_allocator_malloc(tb_allocator_ref_t allocator, tb_size_t size __tb_debug_decl__)
{
    // trace
    tb_trace_d("vmalloc(%lu) at %s(): %lu, %s", size, func_, line_, file_);

    // malloc it
    return tb_virtual_memory_malloc(size);
}
static tb_pointer_t tb_virtual_allocator_ralloc(tb_allocator_ref_t allocator, tb_pointer_t data, tb_size_t size __tb_debug_decl__)
{
    // trace
    tb_trace_d("vralloc(%p, %lu) at %s(): %lu, %s", data, size, func_, line_, file_);

    // ralloc it
    return tb_virtual_memory_ralloc(data, size);
}
static tb_bool_t tb_virtual_allocator_free(tb_allocator_ref_t allocator, tb_pointer_t data __tb_debug_decl__)
{
    // trace
    tb_trace_d("vfree(%p) at %s(): %lu, %s", data, func_, line_, file_);

    // free it
    return tb_virtual_memory_free(data);
}
static tb_bool_t tb_virtual_allocator_instance_init(tb_handle_t instance, tb_cpointer_t priv)
{
    // check
    tb_allocator_ref_t allocator = (tb_allocator_ref_t)instance;
    tb_check_return_val(allocator, tb_false);

    // init allocator
    allocator->type         = TB_ALLOCATOR_TYPE_VIRTUAL;
    allocator->flag         = TB_ALLOCATOR_FLAG_NOLOCK;
    allocator->malloc       = tb_virtual_allocator_malloc;
    allocator->ralloc       = tb_virtual_allocator_ralloc;
    allocator->free         = tb_virtual_allocator_free;
#ifdef __tb_debug__
    allocator->dump         = tb_null;
    allocator->have         = tb_null;
#endif

    // ok
    return tb_true;
}

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementation
 */
tb_allocator_ref_t tb_virtual_allocator()
{
    // init
    static tb_atomic32_t    s_inited = 0;
    static tb_allocator_t   s_allocator = {0};

    // init the static instance
    tb_singleton_static_init(&s_inited, &s_allocator, tb_virtual_allocator_instance_init, tb_null);

    // ok
    return &s_allocator;
}

