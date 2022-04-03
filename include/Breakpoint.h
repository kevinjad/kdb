//
// Created by kevin on 03-04-2022.
//

#ifndef KDB_BREAKPOINT_H
#define KDB_BREAKPOINT_H


#include <cstdlib>
#include <cstdint>

class Breakpoint {
private:
    pid_t pid;
    std::intptr_t addr;
    bool isEnabled;
    uint8_t instructionBackup;
public:
    Breakpoint(pid_t pid, std::intptr_t addr);
    void enable();
    void disable();
    std::intptr_t getAddr();

    Breakpoint();
};


#endif //KDB_BREAKPOINT_H
