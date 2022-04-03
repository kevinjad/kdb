//
// Created by kevin on 03-04-2022.
//

#include <sys/ptrace.h>
#include "Breakpoint.h"

Breakpoint::Breakpoint(pid_t pid, std::intptr_t addr) {
    this->pid = pid;
    this->addr = addr;
    this->isEnabled=false;
    this->instructionBackup = 0;
}

void Breakpoint::enable() {
    auto data = ptrace(PTRACE_PEEKDATA, pid, addr, NULL);
    this->instructionBackup = static_cast<uint8_t>(data&0xff);
    uint64_t int3 = 0xcc;
    uint64_t modData = ((data & 0x00) | int3);
    ptrace(PTRACE_POKEDATA, pid, addr, modData);
    this->isEnabled = true;
}

void Breakpoint::disable() {
    auto data = ptrace(PTRACE_PEEKDATA, pid, addr, NULL);
    uint64_t originalData = ((data & 0x00) | instructionBackup);
    ptrace(PTRACE_POKEDATA, pid, addr, originalData);
    this->isEnabled = false;
}

std::intptr_t Breakpoint::getAddr() {
    return this->addr;
}

Breakpoint::Breakpoint() {

}
