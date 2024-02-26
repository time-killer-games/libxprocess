/*

 MIT License
 
 Copyright © 2021-2022 Samuel Venable
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
*/

#include <cstdint>

#include "gamemaker.hpp"

// execute process from the shell, return process id
double ProcessExecute(char *command) {
  return xprocess::process_execute(command);
}

// execute process from the shell async, return process id
double ProcessExecuteAsync(char *command) {
  return xprocess::process_execute_async(command);
}

//  get whether executed process has quit based on process id
double CompletionStatusFromExecutedProcess(double procIndex) {
  return xprocess::completion_status_from_executed_process((PROCID)procIndex);
}

// write to executed process standard input file descriptor based on process id
double ExecutedProcessWriteToStandardInput(double procIndex, char *input) {
  return (double)xprocess::executed_process_write_to_standard_input((PROCID)procIndex, input);
}

// read from current process standard input file descriptor
char *CurrentProcessReadFromStandardInput() {
  return (char *)xprocess::current_process_read_from_standard_input();
}

// read from executed process standard output file descriptor based on process id
char *ExecutedProcessReadFromStandardOutput(double procIndex) {
  return (char *)xprocess::executed_process_read_from_standard_output((PROCID)procIndex);
}

// set buffer limit for all standard output file descriptors
double SetBufferLimitForStandardOutput(double limit) {
  xprocess::set_buffer_limit_for_standard_output((long long)limit); return 0;
}

// free executed process standard input string based on process id
double FreeExecutedProcessStandardInput(double procIndex) {
  return xprocess::free_executed_process_standard_input((PROCID)procIndex);
}

// free executed process standard ouptut string based on process id
double FreeExecutedProcessStandardOutput(double procIndex) {
  return xprocess::free_executed_process_standard_output((PROCID)procIndex);
}

// get process id from self
double ProcIdFromSelf() {
  return xprocess::proc_id_from_self();
}

// get parent process id from self
double ParentProcIdFromSelf() {
  return xprocess::parent_proc_id_from_self();
}

// get parent process id from process id
double ParentProcIdFromProcId(double procId) {
  return xprocess::parent_proc_id_from_proc_id((PROCID)procId);
}

// get whether process exists based on process id
double ProcIdExists(double procId) {
  return xprocess::proc_id_exists((PROCID)procId);
}

// suspend process based on process id, return whether succeeded
double ProcIdSuspend(double procId) {
  return xprocess::proc_id_suspend((PROCID)procId);
}

// resume process based on process id, return whether succeeded
double ProcIdResume(double procId) {
  return xprocess::proc_id_resume((PROCID)procId);
}

// kill process based on process id, return whether succeeded
double ProcIdKill(double procId) {
  return xprocess::proc_id_kill((PROCID)procId);
}

// get executable image file path from self
char *ExecutableFromSelf() {
  return (char *)xprocess::executable_from_self();
}

// get executable image file path from process id
char *ExeFromProcId(double procId) {
  return (char *)xprocess::exe_from_proc_id((PROCID)procId);
}

// get current working directory from process id
char *CwdFromProcId(double procId) {
  return (char *)xprocess::cwd_from_proc_id((PROCID)procId);
}

// get process info from process id
double ProcInfoFromProcId(double procId) {
  return xprocess::proc_info_from_proc_id((PROCID)procId);
}

// get specific process info from process id
double ProcInfoFromProcIdEx(double procId, double kInfoFlags) {
  return xprocess::proc_info_from_proc_id_ex((PROCID)procId, (KINFOFLAGS)kInfoFlags);
}

// free process info data from memory
double FreeProcInfo(double procInfo) {
  xprocess::free_proc_info((PROCINFO)procInfo); return 0;
}

// create a list of all process id's
double ProcListCreate() {
  return xprocess::proc_list_create();
}

// get process id from process list at index
double ProcessId(double procList, double i) {
  return xprocess::process_id((PROCLIST)procList, (int)i);
}

// get amount of process id's in process list
double ProcessIdLength(double procList) {
  return xprocess::process_id_length((PROCLIST)procList);
}

// free list of process id's from memory
double FreeProcList(double procList) {
  xprocess::free_proc_list((PROCLIST)procList); return 0;
}

// get executable image file path from process info data
char *ExecutableImageFilePath(double procInfo) {
  return xprocess::executable_image_file_path((PROCINFO)procInfo);
}

// get current working directory ffrom process info data
char *CurrentWorkingDirectory(double procInfo) {
  return xprocess::current_working_directory((PROCINFO)procInfo);
}

// get parent processs id from process info data
double ParentProcessId(double procInfo) {
  return xprocess::parent_process_id((PROCINFO)procInfo);
}

// get child process id from process info data at index
double ChildProcessId(double procInfo, double i) {
  return xprocess::child_process_id((PROCINFO)procInfo, (int)i);
}

// get amount of child processes from process info data
double ChildProcessIdLength(double procInfo) {
  return xprocess::child_process_id_length((PROCINFO)procInfo);
}

// get command line argument from process info data at index
char *CommandLine(double procInfo, double i) {
  return xprocess::commandline((PROCINFO)procInfo, (int)i);
}

// get amount of command line arguments from process info data
double CommandLineLength(double procInfo) {
  return xprocess::commandline_length((PROCINFO)procInfo);
}

// get environment variable (NAME=VALUE) from process info at index
char *Environment(double procInfo, double i) {
  return xprocess::environment((PROCINFO)procInfo, (int)i);
}

// get amount of anvironment variables from process info at index
double EnvironmentLength(double procInfo) {
  return xprocess::environment_length((PROCINFO)procInfo);
}

// get current working directory
char *DirectoryGetCurrentWorking() {
  return (char *)xprocess::directory_get_current_working();
}

// set current working directory based on a given dname
double DirectorySetCurrentWorking(char *dname) {
  return xprocess::directory_set_current_working(dname);
}

// get the environment variable of the given name
char *EnvironmentGetVariable(char *name) {
  return (char *)xprocess::environment_get_variable(name);
}

// get whether the environment variable of the given name exists
double EnvironmentGetVariableExists(char *name) {
  return xprocess::environment_get_variable_exists(name);
}

// set the environment variable with the given name and value
double EnvironmentSetVariable(char *name, char *value) {
  return xprocess::environment_set_variable(name, value);
}

// unset the environment variable with the given name
double EnvironmentUnsetVariable(char *name) {
  return xprocess::environment_unset_variable(name);
}

// get temporary directory path
char *DirectoryGetTemporaryPath() {
  return (char *)xprocess::directory_get_temporary_path();
}

#if defined(PROCESS_GUIWINDOW_IMPL)
// get owned window id string from process info at index
char *OwnedWindowId(double procInfo, double i) {
  return xprocess::owned_window_id((PROCINFO)procInfo, (int)i);
}

// get amount of owned window id's from process info at index
double OwnedWindowIdLength(double procInfo) {
  return xprocess::owned_window_id_length((PROCINFO)procInfo);
}

// get whether a process exists based on one of its window id's
double WindowIdExists(char *winId) {
  return xprocess::window_id_exists((WINDOWID)winId);
}

// suspend process based on one of its window id's, return whether succeeded
double WindowIdSuspend(char *winId) {
  return xprocess::window_id_suspend((WINDOWID)winId);
}

// resume process based on one of its window id's, return whether succeeded
double WindowIdResume(char *winId) {
  return xprocess::window_id_resume((WINDOWID)winId);
}

// kill a process based on one of its window id's, return whether succeeded
double WindowIdKill(char *winId) {
  return xprocess::window_id_kill((WINDOWID)winId);
}

// return a window id from native window handle
char *WindowIdFromNativeWindow(void *window) {
  return xprocess::window_id_from_native_window((WINDOW)(uintptr_t)window);
}
#endif
