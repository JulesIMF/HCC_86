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
#include "../inc/Parse.h"
#include "../inc/Files.h"

char const *getSourceFromMemory(char const *fileName)
{
    char *tran = nullptr;
    int fileSize = 0, nStrings = 0;
    tran = (char *)translateFileIntoRam(
        fileName,
        &fileSize,
        &nStrings);

    return tran;
}

int main(int nArgs, char const *args[])
{
    if (nArgs < 3)
    {
        errorMessage("ожидаются два файла в hccfronthcc\n");
        return 1;
    }

    StringsHolder *holder = StringsHolder::newStringsHolder();
    
    auto source = getSourceFromMemory(args[1]);
    if (source == nullptr)
    {
        errorMessage("не найден файл \"%s\"\n", args[1]);
        return 2;
    }

    Parse parse = {};
    auto parsed = parse.getParsed(source, false);

    // astDump(parsed.AST);
    // return 0;

    if(parsed.error)
        return 3;

    Tree::storeTree(args[2], parsed.AST);
}
