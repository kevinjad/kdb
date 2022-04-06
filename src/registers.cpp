//
// Created by kevin on 05-04-2022.
//

#include <sys/ptrace.h>
#include <sys/user.h>
#include "registers.h"


std::unordered_map<reg, int> getRegToIndexMap(){
    if(!regToIndexMapInitialized){
        int i = 0;
        for(const reg_descriptor r : g_register_descriptors){
            regToIndex[r.r] = i;
            i++;
        }
        regToIndexMapInitialized = true;
        return regToIndex;
    } else{
        return regToIndex;
    }
}

std::unordered_map<int, reg> getDwarfToRegMap(){
    if(!regToDwarfMapInitialized){
        for(const reg_descriptor r : g_register_descriptors){
            dwarfToReg[r.dwarf_r] = r.r;
        }
        regToDwarfMapInitialized = true;
        return dwarfToReg;
    } else{
        return dwarfToReg;
    }
}

uint64_t get_register_value(pid_t pid, reg r) {
    user_regs_struct regs;
    ptrace(PTRACE_GETREGS, pid, nullptr, &regs);
    return *(reinterpret_cast<uint64_t*>(&regs) + getRegToIndexMap()[r]);
}

void set_register_value(pid_t pid, reg r, uint64_t val){
    user_regs_struct regs;
    ptrace(PTRACE_GETREGS, pid, nullptr, &regs);
    *(reinterpret_cast<uint64_t*>(&regs) + getRegToIndexMap()[r]) = val;
    ptrace(PTRACE_SETREGS, pid, NULL, &regs);
}

uint64_t get_register_value_from_dwarf_number(pid_t pid, int dwarf_number){
    if(dwarfToReg.find(dwarf_number) == dwarfToReg.end()){
        throw std::out_of_range{"Unknown dwarf register"};
    }
    return get_register_value(pid, dwarfToReg[dwarf_number]);
}