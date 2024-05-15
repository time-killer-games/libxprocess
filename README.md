----------------------------------------------------------------------

# xProcess

Cross-Platform Process Information and Process Execution for GameMaker

----------------------------------------------------------------------

```real ProcessExecute(string command);```

Execute a process from the specified command line string. Execution will be synchronous. The return value is the process index of the process executed by this function. The process index represents the child process ID of the process executed. In single-threaded programs, you will not be able to read process information from the returned child process ID other than from the standard output file descriptor's associated string, which can be read using the `ExecutedProcessReadFromStandardOutput()` function. All other process information will not be held in memory after the process execution has completed and is no longer running, thus the blocking nature of this function will prevent such information to be read. To read process information from executed children processes, it is generally better to use multi-threading, or call `ProcessExecuteAsync()` instead; doing so will also allow running multiple applications instances at once, without blocking the current thread.

----------------------------------------------------------------------

```real ProcessExecuteAsync(string command);```

Execute a process from the specified command line string. Execution will be asynchronous. The return value is the process index of the process executed by this function. The process index represents the child process ID of the process executed.

----------------------------------------------------------------------

```real CompletionStatusFromExecutedProcess(real procIndex);```

Check the completion status of whether the given process index has completed execution. If execution of a process index failed for any reason, the completion status returns `true` to indicate completion has been met. Pass the return value of a function call to `ProcessExecute()` or `ProcessExecuteAsync()` to this function for the process index argument. In single-threaded programs, `ProcessExecute()` will always return of a completion status of `true`, due to it blocking the current thread.

----------------------------------------------------------------------

```real ExecutedProcessWriteToStandardInput(real procIndex, string input);```

Write to the standard input file descriptor of the given process index, with the desired input string. This allows inter-process communication, (IPC), from the current process to its children processes executed from this library. This is typically only useful if the child process indicated by the process index argument is able to somehow read the string sent from the parent process and respond to the string read with some form of outcome. Pass the return value of a function call to `ProcessExecute()` or `ProcessExecuteAsync()` to this function for the process index argument. In single-threaded programs, calling `ExecutedProcessWriteToStandardInput()`, while using the value returned from `ProcessExecute()`, passed as the process index argument, is redundant; the call to `ProcessExecute()` will block the current thread, meaning any attempt to write to the standard input file descriptor won't happen until after the child process has already ended. If the current process is not the parent process, but is the child instead, you may call `CurrentProcessReadFromStandardInput()` to read the string sent to the child by a call to `ExecutedProcessWriteToStandardInput()` from the parent. After every call to `ProcessExecute()` and `ProcessExecuteAsync()`, when you are completely done writing to the standard input file descriptor of the associated process index with calls to `ExecutedProcessWriteToStandardInput()`, always call `FreeExecutedProcessStandardInput()` on the same process index.

----------------------------------------------------------------------

```string CurrentProcessReadFromStandardInput();```

Return the entire string held in the standard input file descriptor for the current process. If the parent process of the current one is also using this library, it may write to the standard input file desciptor of the current process a given string for the input argument of the `ExecutedProcessWriteToStandardInput()` function, which the current process may use a call to `CurrentProcessReadFromStandardInput()` to read that string sent from the parent.

----------------------------------------------------------------------

```string ExecutedProcessReadFromStandardOutput(real procIndex);```

By default, this function will return the entire string held in the standard output file descriptor for a child process of the given process index. This allows inter-process communication, (IPC), to the current process from its children processes executed from this library. To set a limit on the number of bytes this string can contain, call the `SetBufferLimitForStandardOutput()` function, and pass the amount of bytes for the limit argument. A buffer limit of zero will be treated as no limit to be applied. This is useful for preventing buffer overflow, (which results in a crash), for child processes that print a lot of bytes to the standard output file descriptor. After every call to `ProcessExecute()` and `ProcessExecuteAsync()`, when you are completely done reading from the standard outut file descriptor of the associated process index with calls to `ExecutedProcessReadFromStandardOutput()`, always call `FreeExecutedProcessStandardOutput()` on the same process index. Unlike `FreeExecutedProcessStandardInput()`, only call `FreeExecutedProcessStandardOutput()` after the child process of the specficied process index has completed its execution and is no longer running. You may use GameMaker's built-in `show_debug_message()` function to write to the standard output file desciptor of the current process, which if the current process was executed from another application using this library, the parent may call `ExecutedProcessReadFromStandardOutput()` to read the entire debug output string sent from the child's call to `show_debug_message()`; otherwise, `ExecutedProcessReadFromStandardOutput()` does not serve much purpose. You need the child to write output in order for the parent to have something to read and respond to in some way. Since GameMaker prints a lot of output on its own, you will need some means to parse the substring written by you with `show_debug_message` that is meant for reading by the parent process.

----------------------------------------------------------------------

```real SetBufferLimitForStandardOutput(real limit);```

Set a byte limit on the string held universally by the standard output file desciptors of all children processes executed by this library. Pass the desired number of bytes to limit the string buffer to in the limit argument, in order to prevent buffer overflow. Buffer overflow can cause your program to crash and only happens when too many bytes are being held in memory for your program to be able to continue running. There is no buffer limit by default. When a buffer limit is set, to remove it afterwards, set the limit argument to zero, and no more limit will be applied.

----------------------------------------------------------------------

```real FreeExecutedProcessStandardInput(real procIndex);```

Free memory from the standard input file desciptor's associated string of the given child process in the process index argument. Must be called after every call to `ProcessExecute()` and `ProcessExecuteAsync()`, once for each call, with their return values passed as the process index argument. Do not call this function until after you are completely done writing to the standard input file descriptor string with calls to `ExecutedProcessWriteToStandardInput()` with the appropriate child process passed to the process index argument. Failing to call this function will cause a memory leak which will eventually crash your program.

----------------------------------------------------------------------

```real FreeExecutedProcessStandardOutput(real procIndex);```

Free memory from the standard output file desciptor's associated string of the given child process in the process index argument. Must be called after every call to `ProcessExecute()` and `ProcessExecuteAsync()`, once for each call, with their return values passed as the process index argument. Do not call this function until after you are completely done reading from the standard output file descriptor string with calls to `ExecutedProcessReadFromStandardOutput()` with the appropriate child process passed to the process index argument. Unlike the `FreeExecutedProcessStandardInput()` function, it's also needed to not call this function until the child process referenced in the process index argument has completed its execution and is no longer running. Failing to call this function will cause a memory leak which will eventually crash your program.

----------------------------------------------------------------------

```real ProcIdFromSelf();```

Return the ID of the current process.

----------------------------------------------------------------------

```real ParentProcIdFromSelf();```

Return the ID of the current process's parent process.

----------------------------------------------------------------------

```real ParentProcIdFromProcId(real procId);```

Return the ID of the parent process of the given child process in the process ID argument.

----------------------------------------------------------------------

```real ProcIdExists(real procId);```

Return whether the process of the given ID exists in the current user session. Search is linear.

----------------------------------------------------------------------

```real ProcIdSuspend(real procId);```

Send a suspend signal to the process of the given ID. Will pause execution of that process.

----------------------------------------------------------------------

```real ProcIdResume(real procId);```

Send a resume signal to the process of the given ID. Will unpause a previous paused execution of that process.

----------------------------------------------------------------------

```real ProcIdKill(real procId);```

Send a terminate signal to the process of the given ID. The process will be forced to close and stop running. Use with caution.

----------------------------------------------------------------------

```string ExecutableFromSelf();```

Return the absolute path to the current process's executable filename.

----------------------------------------------------------------------

```string ExeFromProcId(real procId);```

Return the absolute path to the executable filename of the given process ID.

----------------------------------------------------------------------

```string CwdFromProcId(real procId);```

Return the absolute path to the current working directory of the given process ID.

----------------------------------------------------------------------

```real ProcInfoFromProcId(real procId);```

Return a process information handle of all process information from the given process ID. This is the same as calling `ProcInfoFromProcIdEx(procId, KINFO_EXEP | KINFO_CWDP | KINFO_PPID | KINFO_CPID | KINFO_ARGV | KINFO_ENVV | KINFO_OWID)`, however calling `ProcInfoFromProcIdEx()` with less flags, (and only using the flags for the process information you need to retrieve), produces way less overhead. See `ProcInfoFromProcIdEx()` for more details. Always free the process information handle when you are done with reading process information from it using the `FreeProcInfo()` function.

----------------------------------------------------------------------

```real ProcInfoFromProcIdEx(real procId, real kInfoFlags);```

Returns a process information handle based on the specified flags, from the given process ID. The possible flags are `KINFO_EXEP`, `KINFO_CWDP`, `KINFO_PPID`, `KINFO_CPID`, `KINFO_ARGV`, `KINFO_ENVV`, and `KINFO_OWID`. `KINFO_EXEP` is for retrieving the executable path from the specified process ID. `KINFO_CWDP` is for retrieving the current working directory path. `KINFO_PPID` is for getting the associated parent process ID. `KINFO_CPID` will give you a vector of child process ID's. `KINFO_ARGV` will give a vector of command line arguments associated with the process ID argument. `KINFO_ENVV` will give a vector of environment variables held in memory for the process ID. `KINFO_OWID` is a vector of owned window ID's associated with the process. Always free the process information handle when you are done with reading process information from it using the `FreeProcInfo()` function.

----------------------------------------------------------------------

```real FreeProcInfo(real procInfo);```

Free a process information handle. Always free a handle returned by `ProcInfoFromProcId()` and `ProcInfoFromProcIdEx()` when you are done reading process information using calls to those functions. Otherwise, you will have a memory leak which will eventually crash your program.

----------------------------------------------------------------------

```real ProcListCreate();```

Return a process list handle. Pass this handle to the `ProcessId()`, `ProcessIdLength()` and `FreeProcessLength()` functions. Internally it records a snapshot of all process ID's running on the current user session. You may use calls to `ProcessId()` in a for-loop to save record of those process ID's, and end the loop when the index of the loop reaches the length returned by `ProcessIdLength()`. When you are done recording the process ID values you need, call `FreeProcList()` while passing the process list handle to the argument; doing so will prevent a memory leak.

----------------------------------------------------------------------

```real ProcessId(real procList, real i);```

Returns the process ID from the specified process list handle of the given index.

----------------------------------------------------------------------

```real ProcessIdLength(real procList);```

Returns the length, (or amount), of how many process ID's are being held in the specified process list handle.

----------------------------------------------------------------------

```real FreeProcList(real procList);```

Free the specified process list handle from memory. Do this whenever you no longer need to retrieve process ID's from a list. Otherwise, your program will eventually crash.

----------------------------------------------------------------------

```string ExecutableImageFilePath(real procInfo);```

Return the absolute path to the executable filename found in the specified process information handle, (expects the `KINFO_EXEP` flag).

----------------------------------------------------------------------

```string CurrentWorkingDirectory(real procInfo);```

Return the absolute path to the current working directory found in the specified process information handle, (expects the `KINFO_CWDP` flag).

----------------------------------------------------------------------

```real ParentProcessId(real procInfo);```

Return the parent process ID found in the specified process information handle, (expects the `KINFO_PPID` flag).

----------------------------------------------------------------------

```real ChildProcessId(real procInfo, real i);```

Return the child process ID at the current index found in the specified process information handle, (expects the `KINFO_CPID` flag). To get the number of child process ID's in the process information handle, call `ChildProcessIdLength()`.

----------------------------------------------------------------------

```real ChildProcessIdLength(real procInfo);```

Return the length, (or amount), of child processes stored in the specified process information handle, (expects the `KINFO_CPID` flag).

----------------------------------------------------------------------

```string CommandLine(real procInfo, real i);```

Return the command line argument at the current index found in the specified process information handle, (expects the `KINFO_ARGV` flag). To get the number of command line arguments in the process information handle, call `CommandLineLength()`.

----------------------------------------------------------------------

```real CommandLineLength(real procInfo);```

Return the length, (or amount), of command line arguments stored in the specified process information handle, (expects the `KINFO_ARGV` flag).

----------------------------------------------------------------------

```string Environment(real procInfo, real i);```

Return the environment variables at the current index found in the specified process information handle, (expects the `KINFO_ENVV` flag). To get the number of environment variables in the process information handle, call `EnvironmentLength()`.

----------------------------------------------------------------------

```real EnvironmentLength(real procInfo);```

Return the length, (or amount), of environment variables stored in the specified process information handle, (expects the `KINFO_ENVV` flag).

----------------------------------------------------------------------

```string DirectoryGetCurrentWorking();```

Return the current working directory for the current process.

----------------------------------------------------------------------

```real DirectorySetCurrentWorking(string dname);```

Set the current working directory for the current process.

----------------------------------------------------------------------

```string EnvironmentGetVariable(string name);```

Get the environment variable's value from the given variable name, for the current process.

----------------------------------------------------------------------

```real EnvironmentGetVariableExists(string name);```

Get whether an environment variable exists based on the given variable name, for the current process.

----------------------------------------------------------------------

```real EnvironmentSetVariable(string name, string value);```

Set the environment variable from the given variable name to the specified value, for the current process.

----------------------------------------------------------------------

```real EnvironmentUnsetVariable(string name);```

Unset, (remove), the environment variable completely based on the given variable name, for the current process.

----------------------------------------------------------------------

```string DirectoryGetTemporaryPath();```

Get the temporary directory for the current process, (internally based on environment variables for the current process).

----------------------------------------------------------------------

```string OwnedWindowId(real procInfo, real i);```

Return the owned window ID at the current index found in the specified process information handle, (expects the `KINFO_OWID` flag). To get the number of owned window ID's in the process information handle, call `OwnedWindowIdLength()`.

----------------------------------------------------------------------

```real OwnedWindowIdLength(real procInfo);```

Return the length, (or amount), of owned window ID's stored in the specified process information handle, (expects the `KINFO_OWID` flag).

----------------------------------------------------------------------

```real WindowIdExists(string winId);```

Return whether the window of the given ID exists in the current user session. Search is linear.

----------------------------------------------------------------------

```real WindowIdSuspend(string winId);```

Send a suspend signal to the process which owns a window of the given window ID. Will pause execution of that process.

----------------------------------------------------------------------

```real WindowIdResume(string winId);```

Send a resume signal to the process which owns a window of the given window ID. Will unpause a previous paused execution of that process.

----------------------------------------------------------------------

```real WindowIdKill(string winId);```

Send a terminate signal to the process which owns a window of the given window ID. The process will be forced to close and stop running. Use with caution.

----------------------------------------------------------------------

```string WindowIdFromNativeWindow(ptr window);```

Retrieves from the given window pointer the associated global window ID, (typically, you pass `window_handle()` as the argument on GameMaker's end). The window ID on Windows and Linux is the same thing as the window handle or pointer, except it is converted to a 64-bit integer and then wrapped in a string. On macOS, the integer wrapped in the string is not the window handle or pointer converted to a 64-bit integer, instead, it is the global `CGWindowID` window number associated with the underlying `NSWindow *` pointer. An `NSWindow *` is only valid for the current process, where as a `CGWindowID` window number is global and valid for any application to access in the current user session. This is done for consistency with the other window ID functions in this library, which are also `CGWindowID` window numbers wrapped in strings.

----------------------------------------------------------------------
