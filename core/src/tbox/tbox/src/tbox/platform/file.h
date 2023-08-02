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
 * @file        file.h
 * @ingroup     platform
 *
 */
#ifndef TB_PLATFORM_FILE_H
#define TB_PLATFORM_FILE_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tb_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */

/// the aligned size for direct mode
#define TB_FILE_DIRECT_ASIZE            (512)

/// the cached size for direct mode
#ifdef __tb_small__
#   define TB_FILE_DIRECT_CSIZE         (1 << 14)
#else
#   define TB_FILE_DIRECT_CSIZE         (1 << 17)
#endif

/* //////////////////////////////////////////////////////////////////////////////////////
 * types
 */

/// the file mode type
typedef enum __tb_file_mode_e
{
    TB_FILE_MODE_RO         = 1     //!< read only
,   TB_FILE_MODE_WO         = 2     //!< write only
,   TB_FILE_MODE_RW         = 4     //!< read and write
,   TB_FILE_MODE_CREAT      = 8     //!< create
,   TB_FILE_MODE_APPEND     = 16    //!< append
,   TB_FILE_MODE_TRUNC      = 32    //!< truncate
,   TB_FILE_MODE_DIRECT     = 64    //!< direct, no cache, @note data & size must be aligned by TB_FILE_DIRECT_ASIZE
,   TB_FILE_MODE_EXEC       = 128   //!< executable, only for tb_file_access, not supported when creating files, not supported on windows

}tb_file_mode_e;

/// the file seek flag
typedef enum __tb_file_seek_flag_e
{
    TB_FILE_SEEK_BEG        = 0
,   TB_FILE_SEEK_CUR        = 1
,   TB_FILE_SEEK_END        = 2

}tb_file_seek_flag_e;

/// the file copy flag
typedef enum __tb_file_copy_flag_e
{
    TB_FILE_COPY_NONE       = 0 //!< default: copy symlink as file
,   TB_FILE_COPY_LINK       = 1 //!< reserve symlink

}tb_file_copy_flag_e;

/// the file type
typedef enum __tb_file_type_e
{
    TB_FILE_TYPE_NONE       = 0
,   TB_FILE_TYPE_DIRECTORY  = 1
,   TB_FILE_TYPE_FILE       = 2
,   TB_FILE_TYPE_DOT        = 3
,   TB_FILE_TYPE_DOT2       = 4

}tb_file_type_e;

/// the file flag
typedef enum __tb_file_flag_e
{
    TB_FILE_FLAG_NONE       = 0
,   TB_FILE_FLAG_LINK       = 1 //!< is symlink?

}tb_file_flag_e;

/// the file info type
typedef struct __tb_file_info_t
{
    /// the file type
    tb_size_t               type: 16;

    /// the file flags
    tb_size_t               flags: 16;

    /// the file size
    tb_hize_t               size;

    /// the last access time
    tb_time_t               atime;

    /// the last modify time
    tb_time_t               mtime;

}tb_file_info_t;

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*! init the file
 *
 * @param path          the file path
 * @param mode          the file mode
 *
 * @return              the file
 */
tb_file_ref_t           tb_file_init(tb_char_t const* path, tb_size_t mode);

/*! exit the file
 *
 * @param file          the file
 *
 * @return              tb_true or tb_false
 */
tb_bool_t               tb_file_exit(tb_file_ref_t file);

/*! read the file data
 *
 * @param file          the file
 * @param data          the data
 * @param size          the size
 *
 * @return              the real size or -1
 */
tb_long_t               tb_file_read(tb_file_ref_t file, tb_byte_t* data, tb_size_t size);

/*! writ the file data
 *
 * @param file          the file
 * @param data          the data
 * @param size          the size
 *
 * @return              the real size or -1
 */
tb_long_t               tb_file_writ(tb_file_ref_t file, tb_byte_t const* data, tb_size_t size);

/*! pread the file data
 *
 * @param file          the file
 * @param data          the data
 * @param size          the size
 * @param offset        the offset, the file offset will not be changed
 *
 * @return              the real size or -1
 */
tb_long_t               tb_file_pread(tb_file_ref_t file, tb_byte_t* data, tb_size_t size, tb_hize_t offset);

/*! pwrit the file data
 *
 * @param file          the file
 * @param data          the data
 * @param size          the size
 * @param offset        the offset, the file offset will not be changed
 *
 * @return              the real size or -1
 */
tb_long_t               tb_file_pwrit(tb_file_ref_t file, tb_byte_t const* data, tb_size_t size, tb_hize_t offset);

/*! readv the file data
 *
 * @param file          the file
 * @param list          the iovec list
 * @param size          the iovec size
 *
 * @return              the real size or -1
 */
tb_long_t               tb_file_readv(tb_file_ref_t file, tb_iovec_t const* list, tb_size_t size);

/*! writv the file data
 *
 * @param file          the file
 * @param list          the iovec list
 * @param size          the iovec size
 *
 * @return              the real size or -1
 */
tb_long_t               tb_file_writv(tb_file_ref_t file, tb_iovec_t const* list, tb_size_t size);

/*! writf the file data
 *
 * @param file          the file
 * @param ifile         the input file
 * @param offset        the input file offset, the file offset will not be changed
 * @param size          the writed size
 *
 * @return              the real size or -1
 */
tb_hong_t               tb_file_writf(tb_file_ref_t file, tb_file_ref_t ifile, tb_hize_t offset, tb_hize_t size);

/*! preadv the file data
 *
 * @param file          the file
 * @param list          the iovec list
 * @param size          the iovec size
 * @param offset        the offset, the file offset will not be changed
 *
 * @return              the real size or -1
 */
tb_long_t               tb_file_preadv(tb_file_ref_t file, tb_iovec_t const* list, tb_size_t size, tb_hize_t offset);

/*! pwritv the file data
 *
 * @param file          the file
 * @param list          the iovec list
 * @param size          the iovec size
 * @param offset        the offset, the file offset will not be changed
 *
 * @return              the real size or -1
 */
tb_long_t               tb_file_pwritv(tb_file_ref_t file, tb_iovec_t const* list, tb_size_t size, tb_hize_t offset);

/*! seek the file offset
 *
 * @param file          the file
 * @param offset        the file offset
 * @param mode          the seek mode
 *
 * @return              the real offset or -1
 */
tb_hong_t               tb_file_seek(tb_file_ref_t file, tb_hong_t offset, tb_size_t mode);

/*! fsync the file
 *
 * @param file          the file
 */
tb_bool_t               tb_file_sync(tb_file_ref_t file);

/*! the file size
 *
 * @param file          the file
 *
 * @return              the file size
 */
tb_hize_t               tb_file_size(tb_file_ref_t file);

/*! the file offset
 *
 * @param file          the file
 *
 * @return              the file offset or -1
 */
tb_hong_t               tb_file_offset(tb_file_ref_t file);

/*! the file info for file or directory
 *
 * @param path          the file path
 * @param info          the file info
 *
 * @return              tb_true or tb_false
 */
tb_bool_t               tb_file_info(tb_char_t const* path, tb_file_info_t* info);

/*! is this file path is case sensitive?
 *
 * @param path          the file path, @note We must pass a path to the file that exists
 *
 * @return              1: case sensitive, 0: case insensitive, -1: failed
 */
tb_long_t               tb_file_fscase(tb_char_t const* path);

/*! copy the file
 *
 * @param path          the file path
 * @param dest          the dest path
 * @param flags         the copy flags, e.g. TB_FILE_COPY_LINK
 *
 * @return              tb_true or tb_false
 */
tb_bool_t               tb_file_copy(tb_char_t const* path, tb_char_t const* dest, tb_size_t flags);

/*! create the file
 *
 * @param path          the file path
 *
 * @return              tb_true or tb_false
 */
tb_bool_t               tb_file_create(tb_char_t const* path);

/*! remove the file
 *
 * @param path          the file path
 *
 * @return              tb_true or tb_false
 */
tb_bool_t               tb_file_remove(tb_char_t const* path);

/*! rename the file
 *
 * @param path          the source file path
 * @param dest          the destination file path
 *
 * @return              tb_true or tb_false
 */
tb_bool_t               tb_file_rename(tb_char_t const* path, tb_char_t const* dest);

/*! link the file
 *
 * @param path          the source file path
 * @param dest          the destination file path
 *
 * @return              tb_true or tb_false
 */
tb_bool_t               tb_file_link(tb_char_t const* path, tb_char_t const* dest);

/*! check whether the file or directory can be accessed
 *
 * @param path          the path of the file or directory
 * @param mode          the required accessing mode
 *
 * @return              tb_true or tb_false
 */
tb_bool_t               tb_file_access(tb_char_t const* path, tb_size_t mode);

/*! update the file time, it will create a new if file not found
 *
 * @param path          the file path
 * @param atime         the last access time, it will not modify this time if it's zero
 * @param mtime         the last modify time, it will not modify this time if it's zero
 *
 * @return              tb_true or tb_false
 */
tb_bool_t               tb_file_touch(tb_char_t const* path, tb_time_t atime, tb_time_t mtime);

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tb_extern_c_leave__

#endif
