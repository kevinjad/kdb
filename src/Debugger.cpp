//
// Created by kevin on 03-04-2022.
//

#include "Debugger.h"

void Debugger::run(){
    int wait_status;
    auto options = 0;
    waitpid(pid, &wait_status, options);

    char* line = nullptr;
    while((line = linenoise("kdb> ")) != nullptr) {
        handle_command(line);
        linenoiseHistoryAdd(line);
        linenoiseFree(line);
    }
}

void Debugger::handle_command(const std::string& line){
    auto vCmd = split(line, ' ');
    std::string s = vCmd[0];
    if(isCommand(s, "continue")){
        continue_exec();
    }
    else if(isCommand(s, "break")){
        std::string address = vCmd[1];
        set_breakpoint_at_address(std::stol(address, 0, 16));
    }
    else{
        std::cerr << "Unknown Command\n";
    }
}

void Debugger::continue_exec(){
    ptrace(PTRACE_CONT, pid, NULL, NULL);

    int wait_status;
    auto options=0;
    waitpid(pid, &wait_status, options);
}

bool Debugger::isCommand(const std::string& s, const std::string& ss){
    if(s.length() != ss.length()) return false;
    return std::equal(s.begin(), s.end(), ss.begin());
}

std::vector<std::string> Debugger::split(const std::string& line, char delimiter){
    std::stringstream ss{line};
    std::vector<std::string> out{};
    std::string temp;
    while(std::getline(ss,temp,delimiter)){
        out.push_back(temp);
    }
    return out;
}

void Debugger::set_breakpoint_at_address(std::intptr_t addr) {
    std::cout << "Setting break point at address 0x" << std::hex << addr << std::endl;
    Breakpoint breakpoint(pid, addr);
    breakpoint.enable();
    this->breakpoints[addr] = breakpoint;
}

Debugger::Debugger(std::string program_name, pid_t  pid){
    this->program_name = program_name;
    this->pid = pid;
}