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
 * @file        page.h
 * @ingroup     platform
 *
 */
#ifndef TB_PLATFORM_PAGE_H
#define TB_PLATFORM_PAGE_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tb_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*! init page
 *
 * @note
 * need support to be called repeatly
 *
 * @return              tb_true or tb_false
 */
tb_bool_t               tb_page_init(tb_noarg_t);

/*! exit page
 *
 */
tb_void_t               tb_page_exit(tb_noarg_t);

/*! get page size
 *
 * @return              the page size
 */
tb_size_t               tb_page_size(tb_noarg_t);

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tb_extern_c_leave__

#endif
