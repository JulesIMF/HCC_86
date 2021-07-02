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
#include "../inc/Tree.h"
#include "../inc/StringsHolder.h"
#include "../inc/Vector.h"

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

    Vertex* loadTree(char const* fileName, StringsHolder* holder)
    {
        int fileSize = 0, nStrings = 0;
        FILE* input = fopen(fileName, "r");

        if(input == nullptr)
            return nullptr;

        int nStr = 0;
        Vector<Vertex *> vertexes;
        vertexes.init();

        fscanf(input, "%d", &nStr);

        for(int i = 0; i != nStr + 1; i++)
            vertexes.pushBack(Vertex::newVertex(Type::FuncLink));

        for(int i = 1; i != nStr + 1; i++)
        {
            char type[100];
            char buf[100];

            fscanf(input, "%s", type);
            
#define VERTEX (*vertexes.at(i))

            if (!strcmp(type, "FuncLink"))
            {
                VERTEX->type = Type::FuncLink;
            }

            if (!strcmp(type, "ArgList"))
            {
                VERTEX->type = Type::ArgList;
            }

            if (!strcmp(type, "Main"))
            {
                VERTEX->type = Type::Main;
            }

            if(!strcmp(type, "Call"))
            {
                VERTEX->type = Type::Call;
                int nArgs = 0;
                fscanf(input, "%s %d", buf, &nArgs);
                VERTEX->field.fnc.iter = holder->insert(buf);
                VERTEX->field.fnc.nArgs = nArgs;
            }

            if (!strcmp(type, "IfElse"))
            {
                VERTEX->type = Type::IfElse;
            }

            if(!strcmp(type, "FuncDecl"))
            {
                VERTEX->type = Type::FuncDecl;
                int nArgs = 0;
                fscanf(input, "%s %d", buf, &nArgs);
                VERTEX->field.fnc.iter = holder->insert(buf);
                VERTEX->field.fnc.nArgs = nArgs;
            }

            if (!strcmp(type, "VarType"))
            {
                VERTEX->type = Type::FuncDecl;
                int nElements = 0;
                fscanf(input, "%s %d", buf, &nElements);
                VERTEX->field.varDecl.iter = holder->insert(buf);
                VERTEX->field.varDecl.nElements = nElements;
            }

            if (!strcmp(type, "StmtLink"))
            {
                int newScope = 0;
                fscanf(input, "%d", &newScope);
                VERTEX->type = Type::StmtLink;
                VERTEX->field.newScope = newScope;
            }

            if (!strcmp(type, "Id"))
            {
                fscanf(input, "%s", buf);
                VERTEX->type = Type::Id;
                VERTEX->field.iter = holder->insert(buf);
            }

            if (!strcmp(type, "Var"))
            {
                fscanf(input, "%s", buf);
                VERTEX->type = Type::Var;
                VERTEX->field.iter = holder->insert(buf);
            }

            if (!strcmp(type, "Const"))
            {
                long long val = 0;
                VERTEX->type = Type::Const;
                fscanf(input, "%d %d", &val, &VERTEX->field.lit.isInt);
                VERTEX->field.lit.value = val;
            }

            if(!strcmp(type, "Statement"))
            {
                fscanf(input, "%s", &buf);
                VERTEX->type = Type::Statement;
                VERTEX->field.stType = (StatementType)*buf;
            }

            if (!strcmp(type, "Operator"))
            {
                fscanf(input, "%s", &buf);;
                VERTEX->type = Type::Operator;
                VERTEX->field.opType = (OperatorType)*buf;
            }

            int left = 0, right = 0;
            fscanf(input, "%d %d", &left, &right);
            VERTEX->left  = left  ? *vertexes.at(left)  : nullptr;
            VERTEX->right = right ? *vertexes.at(right) : nullptr;
        }

        auto ret = *vertexes.at(1);
        
        return ret;
    }
}