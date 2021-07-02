/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    WriteAsm86.cpp

Abstract:    
    
Author:
    JulesIMF

Last Edit:
    13.05.2021 03:48

Edit Notes:
    
**********************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "../../inc/Vertex.h"
#include "../../inc/ErrorMessage.h"
#include "../../inc/CompilationStructs.h"
#include "../../inc/WriteAsm86.h"

using Node::Vertex;
using Node::Type;
using Node::OperatorType;
using Node::StatementType;

namespace AssemblerGenerator
{
    bool isSetInstruction(Instruction instruction)
    {
        switch(instruction.type)
        {
        case InstructionType::sete:
        case InstructionType::setne:
        case InstructionType::setg:
        case InstructionType::setng:
        case InstructionType::setl:
        case InstructionType::setnl:
            return true;

        default:
            return false;
        }
    }

    void writeMnemonic(FILE* file, Instruction instruction)
    {
        static char const *mnemonics[] =
            {
                "label",
                "push",
                "pop",
                "mov",
                "syscall",
                "ret",
                "cmp",
                "jmp",
                "je",
                "jne",
                "sete",
                "setne",
                "setl",
                "setnl",
                "setg",
                "setng",
                "not",
                "or",
                "and",
                "xor",
                "idiv",
                "imul",
                "add",
                "sub",
                "test",
                "int 3",
                "call",
                "movzx",
            };

        if((size_t)instruction.type < (sizeof(mnemonics) / sizeof(mnemonics[0])))
            ;
        else
        {
            errorMessage("type == %d", (size_t)instruction.type);
            abort();
        }
        fprintf(file, "%s", mnemonics[(size_t)instruction.type]);
    }

    void writeLabelDeclaration(FILE* file, Instruction instruction)
    {
        fprintf(file, "\n%s:\n", instruction.field.labelName);
    }

    /**
     * \return true, если это вызов или переход, false иначе
    */
    bool writeLabel(FILE *file, Instruction instruction)
    {
        switch(instruction.type)
        {
        case InstructionType::call:
        case InstructionType::jmp:
        case InstructionType::je:
        case InstructionType::jne:
            fprintf(file, " %s\n", instruction.field.labelName);
            return true;

        default:
            return false;
        }
    }

    void writeOperand(FILE *file, Operand operand, bool byteRegisters = false)
    {
        static char const *regNameQ[] =
            {
                "",
                "rax",
                "rcx",
                "rdx",
                "rbx",
                "rsp",
                "rbp",
                "rsi",
                "rdi",
                "r8",
                "r9",
                "r10",
                "r11",
                "r12",
                "r13",
                "r14",
                "r15",
                "stack"};

        static char const *regNameB[] =
            {
                "",
                "al",
                "cl",
                "dl",
                "bl",
                "spl",
                "bpl",
                "sil",
                "dil",
                "r8b",
                "r9b",
                "r10b",
                "r11b",
                "r12b",
                "r13b",
                "r14b",
                "r15b",
                "stackByte"};

        char const* const* const regName = byteRegisters ? regNameB : regNameQ;

        switch(operand.type)
        {
            case OperandType::imm:
                fprintf(file, " %lld", operand.field.imm);
                return;
            
            case OperandType::reg:
                fprintf(file, " %s", regName[(int)operand.field.reg]);
                return;

            case OperandType::mem:
                fprintf(file, " [%s%+d]", regName[(int)operand.field.mem.reg], operand.field.mem.shift);
                return;

            case OperandType::none:
                return;
        }
    }

    WriteAsmError writeToAsmFile(char const *fileName, Compiled flow)
    {
        assert(fileName);
        auto file = fopen(fileName, "w");
        if(file == nullptr)
        {
            errorMessage("не удалсось открыть файл \"%s\" для генерации ассемблерного листинга", fileName);
            return WriteAsmError::FAILED_TO_OPEN;
        }

        fprintf(file,
        ".intel_syntax noprefix\n"
        ".global main\n\n");

        auto instVect = flow.instructions;

        for (int i = 0; i != instVect->size(); i++)
        {
            Instruction instruction = *instVect->at(i);
            if(instruction.type == InstructionType::label)
            {
                writeLabelDeclaration(file, instruction);
                continue;
            }

            fprintf(file, "\t");
            writeMnemonic(file, instruction);

            if(writeLabel(file, instruction))
                continue;

            int const nOperands = 2;
            for (int i = 0; i != nOperands && instruction.field.operand[i].type != OperandType::none; i++)
            {
                if(i)
                    fprintf(file, ",");
                else
                    fprintf(file, " ");
                
                writeOperand(file, instruction.field.operand[i], 
                            (instruction.type == InstructionType::movzx && i == 1) ||
                            isSetInstruction(instruction));
            }

            fprintf(file, "\n");
        }

        fclose(file);

        return WriteAsmError::NO_ERROR;
    }
}