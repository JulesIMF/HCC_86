/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    TreeConverter.cpp

Abstract:    
    
Author:
    JulesIMF

Last Edit:
    13.05.2021 03:48

Edit Notes:
    
**********************************************************************/

#include <cstdio>
#include <cstring>
#include "../../inc/Tree.h"
#include "../../inc/StringsHolder.h"
#include "../../inc/Vector.h"

using Node::OperatorType;
using Node::StatementType;
using Node::Type;
using Node::Vertex;

namespace Tree
{
    int count(Vertex* vertex)
    {
        if(vertex == nullptr)
            return 0;

        return count(vertex->left) + count(vertex->right) + 1;
    }

    void storeVertex(Vertex* vertex, FILE* file, int* nProceeded)
    {
        if(vertex == nullptr)
            return;

        switch(vertex->type)
        {
        
        case Type::ArgList:
            fprintf(file, "ArgList");
            break;
        case Type::Call:
            fprintf(file, "Call %s %d", vertex->field.fnc.iter.get(), vertex->field.fnc.nArgs);
            break;
        case Type::Const:
            fprintf(file, "Const %lld %d", vertex->field.lit.value, vertex->field.lit.isInt);
            break;
        case Type::FuncDecl:
            fprintf(file, "FuncDecl %s %d", vertex->field.fnc.iter.get(), vertex->field.fnc.nArgs);
            break;
        case Type::FuncLink:
            fprintf(file, "FuncLink");
            break;
        case Type::Id:
            fprintf(file,"Id %s", vertex->field.iter.get());
            break;
        case Type::IfElse:
            fprintf(file, "IsElse");
            break;
        case Type::Main:
            fprintf(file, "Main");
            break;
        case Type::Operator:
            fprintf(file, "Operator %c", vertex->field.opType);
            break;
        case Type::Statement:
            fprintf(file, "Statement %c", vertex->field.stType);
            break;
        case Type::StmtLink:
            fprintf(file, "StmtLink %d", vertex->field.newScope);
            break;
        case Type::Var:
            fprintf(file, "Var %s", vertex->field.iter.get());
            break;
        case Type::VarType:
            fprintf(file, "VarType %s %d", vertex->field.varDecl.iter.get(), vertex->field.varDecl.nElements);
            break;
        default:
            assert("Unknown type");
        }

        (*nProceeded)++;
        fprintf(file, " %d %d\n", (vertex->left) ? (*nProceeded + 1) : 0, (vertex->right) ? (*nProceeded + 1 + count(vertex->left)) : 0);
        storeVertex(vertex->left,  file, nProceeded);
        storeVertex(vertex->right, file, nProceeded);
    }

    void storeTree(char const *fileName, Vertex* vertex)
    {
        FILE *output = fopen(fileName, "w");
        if (output == nullptr)
            return;

        int nStr = count(vertex);
        int nProceeded = 0;

        fprintf(output, "%d\n", nStr);
        storeVertex(vertex, output, &nProceeded);
        fclose(output);
    }
}