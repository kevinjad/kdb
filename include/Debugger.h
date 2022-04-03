//
// Created by kevin on 03-04-2022.
//

#ifndef KDB_DEBUGGER_H
#define KDB_DEBUGGER_H

#include <iostream>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <linenoise.h>
#include <vector>
#include <unordered_map>
#include <sstream>
#include "Breakpoint.h"

class Debugger{
private:
    std::string program_name;
    pid_t pid;

    std::unordered_map<std::intptr_t, Breakpoint> breakpoints;
public:
    Debugger(std::string program_name, pid_t  pid);

    std::vector<std::string> split(const std::string& line, char delimiter);

    bool isCommand(const std::string& s, const std::string& ss);

    void continue_exec();

    void handle_command(const std::string& line);

    void run();

    void set_breakpoint_at_address(std::intptr_t addr);
};


#endif //KDB_DEBUGGER_H
