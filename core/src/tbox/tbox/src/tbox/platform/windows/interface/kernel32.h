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
 * @file        kernel32.h
 *
 */
#ifndef TB_PLATFORM_WINDOWS_INTERFACE_KERNEL32_H
#define TB_PLATFORM_WINDOWS_INTERFACE_KERNEL32_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */
#ifndef FILE_SKIP_COMPLETION_PORT_ON_SUCCESS
#   define FILE_SKIP_COMPLETION_PORT_ON_SUCCESS   (0x1)
#endif

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tb_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * types
 */

// the OVERLAPPED_ENTRY type
typedef struct _tb_OVERLAPPED_ENTRY_t
{
    ULONG_PTR    lpCompletionKey;
    LPOVERLAPPED lpOverlapped;
    ULONG_PTR    Internal;
    DWORD        dwNumberOfBytesTransferred;

}tb_OVERLAPPED_ENTRY_t, *tb_LPOVERLAPPED_ENTRY_t;

// the GetQueuedCompletionStatusEx func type
typedef BOOL (WINAPI* tb_kernel32_GetQueuedCompletionStatusEx_t)(
    HANDLE CompletionPort,
    tb_LPOVERLAPPED_ENTRY_t lpCompletionPortEntries,
    ULONG ulCount,
    PULONG ulNumEntriesRemoved,
    DWORD dwMilliseconds,
    BOOL fAlertable);

// the CancelIoEx func type
typedef BOOL (WINAPI* tb_kernel32_CancelIoEx_t)(HANDLE hFile, LPOVERLAPPED lpOverlapped);

// the RtlCaptureStackBackTrace func type
typedef USHORT (WINAPI* tb_kernel32_RtlCaptureStackBackTrace_t)(
    ULONG FramesToSkip,
    ULONG FramesToCapture,
    PVOID *BackTrace,
    PULONG BackTraceHash);

// the GetFileSizeEx func type
typedef BOOL (WINAPI* tb_kernel32_GetFileSizeEx_t)(HANDLE hFile, PLARGE_INTEGER lpFileSize);

// the GetEnvironmentVariableW func type
typedef DWORD (WINAPI* tb_kernel32_GetEnvironmentVariableW_t)(LPCWSTR lpName, LPWSTR lpBuffer, DWORD nSize);

// the SetEnvironmentVariableW func type
typedef BOOL (WINAPI* tb_kernel32_SetEnvironmentVariableW_t)(LPCWSTR lpName, LPCWSTR lpValue);

// the CreateProcessW func type
typedef BOOL (WINAPI* tb_kernel32_CreateProcessW_t)(
    LPCWSTR lpApplicationName,
    LPCWSTR lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    BOOL bInheritHandles,
    DWORD dwCreationFlags,
    LPVOID lpEnvironment,
    LPCWSTR lpCurrentDirectory,
    LPSTARTUPINFO lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation);

// the WaitForMultipleObjects func type
typedef DWORD (WINAPI* tb_kernel32_WaitForMultipleObjects_t)(
    DWORD  nCount,
    const HANDLE* lpHandles,
    BOOL bWaitAll,
    DWORD dwMilliseconds);

// the GetExitCodeProcess func type
typedef BOOL (WINAPI* tb_kernel32_GetExitCodeProcess_t)(HANDLE hProcess, LPDWORD lpExitCode);

// the TerminateProcess func type
typedef BOOL (WINAPI* tb_kernel32_TerminateProcess_t)(HANDLE hProcess, UINT uExitCode);

// the SuspendThread func type
typedef DWORD (WINAPI* tb_kernel32_SuspendThread_t)(HANDLE hThread);

// the ResumeThread func type
typedef DWORD (WINAPI* tb_kernel32_ResumeThread_t)(HANDLE hThread);

// the GetEnvironmentStringsW func type
typedef LPWCH (WINAPI* tb_kernel32_GetEnvironmentStringsW_t)(tb_void_t);

// the FreeEnvironmentStringsW func type
typedef DWORD (WINAPI* tb_kernel32_FreeEnvironmentStringsW_t)(
    LPWCH lpszEnvironmentBlock);

// the SetHandleInformation func type
typedef BOOL (WINAPI* tb_kernel32_SetHandleInformation_t)(
    HANDLE hObject,
    DWORD dwMask,
    DWORD dwFlags);

// the SetFileCompletionNotificationModes func type
typedef BOOL (WINAPI* tb_kernel32_SetFileCompletionNotificationModes_t)(
    HANDLE FileHandle,
    UCHAR Flags);

// the CreateSymbolicLinkW func type
typedef BOOLEAN (WINAPI* tb_kernel32_CreateSymbolicLinkW_t)(
    LPCWSTR lpSymlinkFileName,
    LPCWSTR lpTargetFileName,
    DWORD dwFlags);

// the CreateJobObjectW func type
typedef HANDLE (WINAPI* tb_kernel32_CreateJobObjectW_t)(LPSECURITY_ATTRIBUTES lpJobAttributes, LPCWSTR lpName);

// the TerminateJobObject func type
typedef BOOL (WINAPI* tb_kernel32_TerminateJobObject_t)(
    HANDLE hJob,
    UINT uExitCode);

// the AssignProcessToJobObject func type
typedef BOOL (WINAPI* tb_kernel32_AssignProcessToJobObject_t)(
    HANDLE hJob,
    HANDLE hProcess);

// the SetInformationJobObject func type
typedef BOOL (WINAPI* tb_kernel32_SetInformationJobObject_t)(
    HANDLE hJob,
    JOBOBJECTINFOCLASS JobObjectInformationClass,
    LPVOID lpJobObjectInformation,
    DWORD cbJobObjectInformationLength);

// the GetActiveProcessorCount func type
typedef DWORD (WINAPI* tb_kernel32_GetActiveProcessorCount_t)(WORD GroupNumber);

// the InitializeProcThreadAttributeList func type
typedef BOOL (WINAPI* tb_kernel32_InitializeProcThreadAttributeList_t)(
    LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList,
    DWORD dwAttributeCount,
    DWORD dwFlags,
    PSIZE_T lpSize);

// the UpdateProcThreadAttribute func type
typedef BOOL (WINAPI* tb_kernel32_UpdateProcThreadAttribute_t)(
    LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList,
    DWORD dwFlags,
    DWORD_PTR Attribute,
    PVOID lpValue,
    SIZE_T cbSize,
    PVOID lpPreviousValue,
    PSIZE_T lpReturnSize);

// the DeleteProcThreadAttributeList func type
typedef void (WINAPI* tb_kernel32_DeleteProcThreadAttributeList_t)(
    LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList);

// the GetLogicalProcessorInformationEx func type
#if defined(TB_COMPILER_IS_MSVC) && TB_COMPILER_VERSION_BT(16, 0)
typedef BOOL (WINAPI* tb_kernel32_GetLogicalProcessorInformationEx_t)(
    LOGICAL_PROCESSOR_RELATIONSHIP RelationshipType,
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX Buffer,
    PDWORD ReturnedLength);
#endif

// the kernel32 interfaces type
typedef struct __tb_kernel32_t
{
    // CaptureStackBackTrace
    tb_kernel32_RtlCaptureStackBackTrace_t              RtlCaptureStackBackTrace;

    // GetFileSizeEx
    tb_kernel32_GetFileSizeEx_t                         GetFileSizeEx;

    // CancelIoEx
    tb_kernel32_CancelIoEx_t                            CancelIoEx;

    // GetQueuedCompletionStatusEx
    tb_kernel32_GetQueuedCompletionStatusEx_t           GetQueuedCompletionStatusEx;

    // GetEnvironmentVariableW
    tb_kernel32_GetEnvironmentVariableW_t               GetEnvironmentVariableW;

    // SetEnvironmentVariableW
    tb_kernel32_SetEnvironmentVariableW_t               SetEnvironmentVariableW;

    // CreateProcessW
    tb_kernel32_CreateProcessW_t                        CreateProcessW;

    // WaitForMultipleObjects
    tb_kernel32_WaitForMultipleObjects_t                WaitForMultipleObjects;

    // GetExitCodeProcess
    tb_kernel32_GetExitCodeProcess_t                    GetExitCodeProcess;

    // TerminateProcess
    tb_kernel32_TerminateProcess_t                      TerminateProcess;

    // SuspendThread
    tb_kernel32_SuspendThread_t                         SuspendThread;

    // ResumeThread
    tb_kernel32_ResumeThread_t                          ResumeThread;

    // GetEnvironmentStringsW
    tb_kernel32_GetEnvironmentStringsW_t                GetEnvironmentStringsW;

    // FreeEnvironmentStringsW
    tb_kernel32_FreeEnvironmentStringsW_t               FreeEnvironmentStringsW;

    // SetHandleInformation
    tb_kernel32_SetHandleInformation_t                  SetHandleInformation;

    // SetFileCompletionNotificationModes
    tb_kernel32_SetFileCompletionNotificationModes_t    SetFileCompletionNotificationModes;

    // CreateSymbolicLinkW
    tb_kernel32_CreateSymbolicLinkW_t                   CreateSymbolicLinkW;

    // CreateJobObjectW
    tb_kernel32_CreateJobObjectW_t                      CreateJobObjectW;

    // TerminateJobObject
    tb_kernel32_TerminateJobObject_t                    TerminateJobObject;

    // AssignProcessToJobObject
    tb_kernel32_AssignProcessToJobObject_t              AssignProcessToJobObject;

    // SetInformationJobObject
    tb_kernel32_SetInformationJobObject_t               SetInformationJobObject;

    // GetActiveProcessorCount
    tb_kernel32_GetActiveProcessorCount_t               GetActiveProcessorCount;

    // InitializeProcThreadAttributeList
    tb_kernel32_InitializeProcThreadAttributeList_t     InitializeProcThreadAttributeList;

    // UpdateProcThreadAttribute
    tb_kernel32_UpdateProcThreadAttribute_t             UpdateProcThreadAttribute;

    // DeleteProcThreadAttributeList
    tb_kernel32_DeleteProcThreadAttributeList_t         DeleteProcThreadAttributeList;

    // GetLogicalProcessorInformationEx
#if defined(TB_COMPILER_IS_MSVC) && TB_COMPILER_VERSION_BT(16, 0)
    tb_kernel32_GetLogicalProcessorInformationEx_t      GetLogicalProcessorInformationEx;
#endif

}tb_kernel32_t, *tb_kernel32_ref_t;

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/* the kernel32 interfaces
 *
 * @return          the kernel32 interfaces pointer
 */
tb_kernel32_ref_t   tb_kernel32(tb_noarg_t);

/* has SetFileCompletionNotificationModes?
 *
 * Verifies that SetFileCompletionNotificationModes Windows API is present on the system
 * and is safe to use.
 *
 * We can uses the SetFileCompletionNotificationModes Windows API to skip calling GetQueuedCompletionStatus
 * if an IO operation completes synchronously.
 *
 * There is a known bug where SetFileCompletionNotificationModes crashes on some systems
 * (see https://support.microsoft.com/kb/2568167 for details).
 *
 * It's not safe to skip completion notifications for UDP:
 * https://blogs.technet.com/b/winserverperformance/archive/2008/06/26/designing-applications-for-high-performance-part-iii.aspx
 *
 * So we can only use it to skip tcp completion notifications.
 *
 * @return          tb_true or tb_false
 */
tb_bool_t           tb_kernel32_has_SetFileCompletionNotificationModes();

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tb_extern_c_leave__


#endif
