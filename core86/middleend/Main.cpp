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
#include "../inc/Vertex.h"
#include "../inc/ErrorMessage.h"

void constConvolution(Node::Vertex *vertex);

int main(int nArgs, char const *args[])
{
    if (nArgs < 3)
    {
        errorMessage("ожидаются два файла в hccmiddle\n");
        return 1;
    }

    StringsHolder *holder = StringsHolder::newStringsHolder();
    auto ast = Tree::loadTree(args[1], holder);
    if (ast == nullptr)
    {
        errorMessage("не найден файл \"%s\"\n", args[1]);
        return 2;
    }

    constConvolution(ast);

    Tree::storeTree(args[2], ast);

    StringsHolder::deleteStringsHolder(holder);
}
