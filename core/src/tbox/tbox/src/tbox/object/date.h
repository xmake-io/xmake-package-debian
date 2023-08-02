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
 * @file        date.h
 * @ingroup     object
 *
 */
#ifndef TB_OBJECT_DATE_H
#define TB_OBJECT_DATE_H

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

/*! init date from now
 *
 * @return          the date object
 */
tb_object_ref_t     tb_oc_date_init_from_now(tb_noarg_t);

/*! init date from time
 *
 * @param time      the date time
 *
 * @return          the date object
 */
tb_object_ref_t     tb_oc_date_init_from_time(tb_time_t time);

/*! the date time
 *
 * @param date      the date object
 *
 * @return          the date time
 */
tb_time_t           tb_oc_date_time(tb_object_ref_t date);

/*! set the date time
 *
 * @param date      the date object
 * @param time      the date time
 *
 * @return          tb_true or tb_false
 */
tb_bool_t           tb_oc_date_time_set(tb_object_ref_t date, tb_time_t time);

/*! set the date time for now
 *
 * @param date      the date object
 *
 * @return          tb_true or tb_false
 */
tb_bool_t           tb_oc_date_time_set_now(tb_object_ref_t date);

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tb_extern_c_leave__

#endif

