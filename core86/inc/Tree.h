/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    Tree.h

Abstract:    
    
Author:
    JulesIMF

Last Edit:
    13.05.2021 03:48

Edit Notes:
    
**********************************************************************/

#ifndef CPP_TREECONVERTER
#define CPP_TREECONVERTER
#include "Vertex.h"
#include "StringsHolder.h"

namespace Tree
{
    Node::Vertex* loadTree(char const*, StringsHolder* holder);
    void storeTree(char const *, Node::Vertex*);
}

#endif //!#ifndef CPP_TREECONVERTER