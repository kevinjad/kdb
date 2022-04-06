//
// Created by kevin on 02-04-2022.
//

#include <iostream>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sstream>
#include <sys/personality.h>

#include "Debugger.h"

int main(int argc, char** argsv){
    if(argc < 2){
        std::cerr << "Program name is missing." << std::endl;
        return -1;
    }
    auto prog = argsv[1];
    auto pid = fork();
    if(pid == 0){
        // execute the program
        personality(ADDR_NO_RANDOMIZE);
        ptrace(PTRACE_TRACEME, 0, nullptr, nullptr);
        execl(prog, prog, nullptr);
    } else if(pid >= 1){
        // debugger code
        Debugger debugger(prog, pid);
        debugger.run();
    }
    return 0;
}

