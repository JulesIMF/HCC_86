/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    AstDump.h

Abstract:    
    Модуль, генерирующий изображение AST дерева    
Author:
    JulesIMF

Last Edit:
    20.12.2020 2:27

Edit Notes:
    
**********************************************************************/

#ifndef CPP_ASTDUMP
#define CPP_ASTDUMP

#include <cstdlib>
#include <cassert>
#include <cstdio>
#include "Vertex.h"

static void astDump(Node::Vertex* astTree);

#endif