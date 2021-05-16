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

#include <algorithm>
#include "../inc/List.h"
#include "../inc/CompilationStructs.h"

Register StackImitate::getNext(void)
{
    return registers[std::min(pointer, 11)];
}

Register StackImitate::getCurrent(void)
{
    if (!pointer)
        return Register::none;

    if (pointer >= 11)
        return Register::stack;

    return registers[pointer - 1];
}

Register StackImitate::getPrev(void)
{
    if (pointer < 2)
        return Register::none;

    if (pointer >= 12)
        return Register::stack;

    return registers[pointer - 2];
}

void StackImitate::push(void)
{
    pointer++;
}

void StackImitate::pop(void)
{
    assert(pointer);
    pointer--;
}

void Instruction::zeroAll(void)
{
    type = InstructionType::label;
    field.operand[0] = field.operand[1] = {OperandType::none, Register::none};
}
