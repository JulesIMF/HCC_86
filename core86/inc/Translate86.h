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
#ifndef CPP_TRANSLATE
#define CPP_TRANSLATE
#include "CompilationStructs.h"
#include "Vector.h"
#include "Table.h"

class Translator
{
protected:
    Vector<Instruction> *flow;
    Table<int> labelTable;
    StringsHolder *holder;

    int pointer;
    char *buffer;
    int bufferSize;

    void emitInt(int a);

    void emit(char a);

    template <typename... Args>
    void emit(char a, Args... b);

    void pushLabels(void);

    void translateCode(void);

    void writeStd(void);

    int translateTriple(Instruction instruction, char memregOpcode, char immOpcode = 0, char immBase = 0, char regmemOpcode = 0);

    int translatePushPop(Instruction instruction, char opcode);

    int translateSet(Instruction instruction, char opcode);

    int translateBranch(Instruction instruction, char opcode, bool isConditional = false);

    int translateImul(Instruction instruction);

    int translateIdiv(Instruction instruction);

    int translateMovzx(Instruction instruction);

    int translateInstruction(Instruction instruction);

public:
    void translate(char const *fileName, Vector<Instruction> *flow_, StringsHolder *holder_);
};

#endif