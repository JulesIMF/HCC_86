/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    Compilation Structs.h

Abstract:    
    
Author:
    JulesIMF

Last Edit:
    13.05.2021 03:48

Edit Notes:
    
**********************************************************************/

#ifndef CPP_COMPILATION_STRUCTS
#define CPP_COMPILATION_STRUCTS
#include <algorithm>
#include "../common/Keywords.h"
#include "Vector.h"

enum class InstructionType
{
    label,
    push,
    pop,
    mov,
    syscall,
    ret,
    cmp,
    jmp,
    je,
    jne,
    sete,
    setne,
    setl,
    setnl,
    setg,
    setng,
    not_,
    or_,
    and_,
    xor_,
    idiv,
    imul,
    add,
    sub,
    test,
    int_,
    call,
    movzx,
    lea,
};

enum class OperandType
{
    none,
    reg,
    imm,
    mem
};

enum class Register
{
    none,
    rax,
    rcx,
    rdx,
    rbx,
    rsp,
    rbp,
    rsi,
    rdi,
    r8,
    r9,
    r10,
    r11,
    r12,
    r13,
    r14,
    r15,
    stack
};

class StackImitate
{
public:
    // rax, rdx, rdi всегда свободны
    // rsp, rbp имеют спец. назначение
    // остальные образуют стек

    Register const registers[12] =
        {
            Register::rbx,
            Register::rcx,
            Register::rsi,
            Register::r8,
            Register::r9,
            Register::r10,
            Register::r11,
            Register::r12,
            Register::r13,
            Register::r14,
            Register::r15,
            Register::stack};

    int pointer = 0; // указывает на СВОБОДНОЕ место

    Register getNext(void);

    Register getCurrent(void);

    Register getPrev(void);

    void push(void);  

    void pop(void);
};


struct Memory
{
    Register reg;
    int      shift;
};

struct Operand
{
    OperandType type;

    union OperandField
    {
        Memory      mem;
        Register    reg;
        long long   imm;
    } field; 
};

struct Instruction
{
    InstructionType type;
    union
    {
        Operand operand[2];
        char labelName[32];        
    } field;  

    int shift;

    void zeroAll(void);
};

struct Compiled
{
    Vector<Instruction>* instructions;
    CompileError error;
};


#endif