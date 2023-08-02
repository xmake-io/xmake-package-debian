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
 * @file        semaphore.h
 * @ingroup     coroutine
 *
 */
#ifndef TB_COROUTINE_SEMAPHORE_H
#define TB_COROUTINE_SEMAPHORE_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tb_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * types
 */

/// the coroutine semaphore ref type
typedef __tb_typeref__(co_semaphore);

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*! init semaphore
 *
 * @param value         the initial semaphore value
 *
 * @return              the semaphore
 */
tb_co_semaphore_ref_t   tb_co_semaphore_init(tb_size_t value);

/*! exit semaphore
 *
 */
tb_void_t               tb_co_semaphore_exit(tb_co_semaphore_ref_t semaphore);

/*! post semaphore
 *
 * @param semaphore     the semaphore
 * @param post          the post semaphore value
 *
 */
tb_void_t               tb_co_semaphore_post(tb_co_semaphore_ref_t semaphore, tb_size_t post);

/*! the semaphore value
 *
 * @param semaphore     the semaphore
 *
 * @return              the semaphore value
 */
tb_size_t               tb_co_semaphore_value(tb_co_semaphore_ref_t semaphore);

/*! wait semaphore
 *
 * @param semaphore     the semaphore
 * @param timeout       the timeout
 *
 * @return              ok: 1, timeout: 0, fail: -1
 */
tb_long_t               tb_co_semaphore_wait(tb_co_semaphore_ref_t semaphore, tb_long_t timeout);

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tb_extern_c_leave__

#endif
