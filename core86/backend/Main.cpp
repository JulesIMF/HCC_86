/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    Main.cpp

Abstract:    
    
Author:
    JulesIMF

Last Edit:
    13.05.2021 03:48

Edit Notes:
    
**********************************************************************/

#include <cstdio>
#include "../inc/Tree.h"
#include "../inc/AstDump.h"
#include "../inc/Generate86.h"
#include "../inc/WriteAsm86.h"
#include "../inc/Translate86.h"
#include "../inc/ErrorMessage.h"

int main(int nArgs, char const* args[])
{
    if (nArgs < 3)
    {
        errorMessage("ожидаются два файла в hccback86\n");
        return 1;
    }

    StringsHolder *holder = StringsHolder::newStringsHolder();
    auto ast = Tree::loadTree(args[1], holder);
    if (ast == nullptr)
    {
        errorMessage("не найден файл \"%s\"\n", args[1]);
        return 2;
    }

    Generator generator = {};
    auto compiled = generator.compile(ast, holder);
    
    if(compiled.error)
    {
        StringsHolder::deleteStringsHolder(holder);
        return 3;
    }

    if (nArgs > 3)
    {
        AssemblerGenerator::writeToAsmFile(args[2], compiled);
        return 0;
    }

    Translator tranlator = {};
    tranlator.translate(args[2], compiled.instructions, holder);
    StringsHolder::deleteStringsHolder(holder);
}

