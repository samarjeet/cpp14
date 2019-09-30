#include <vector>
#include <string>
#include "linenoise.h"
#include "debugger.h"
#include <iostream>
#include <sstream>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>

void debugger::run() {
  int wait_status;
  auto options = 0;
  waitpid(m_pid, &wait_status, options);

  char *line = nullptr;
  while ((line = linenoise("minidgb> ")) != nullptr) {
    handle_command(line);
    linenoiseHistoryAdd(line);
    linenoiseFree(line);
  }
}

void debugger::handle_command(const std::string &line) {
  auto args = split(line, ' ');
  auto command = args[0];

  if (is_prefix(command, "continue")) {
    continue_execution();
  } else {
    std::cerr << "Unknown command\n";
  }
}

void debugger::continue_execution() {
  ptrace(PTRACE_CONT, m_pid, nullptr, nullptr);

  int wait_status;
  auto options = 0;
  waitpid(m_pid, &wait_status, options);
}

std::vector<std::string> debugger::split(const std::string &s, char delimiter) {
  std::vector<std::string> out{};
  std::stringstream ss ;
  ss << s ;
  std::string item;

  while (std::getline(ss, item, delimiter)) {
    out.push_back(item);
  }

  return out;
}


int main(int argc, char *argv[]) {

  if (argc < 2) {
    std::cerr << "Program name not specified\n";
    return -1;
  }

  auto prog = argv[1];

  auto pid = fork();

  if (pid == 0) {
    // We are in the child process
    // execute debugee
    ptrace(PTRACE_TRACEME, 0, nullptr, nullptr);
    execl(prog, prog, nullptr);
  }

  else if (pid >= 1) {
    // we are in the parent process
    // execute debugger
    debugger dbg{prog, pid};
    dbg.run();
  }
}
