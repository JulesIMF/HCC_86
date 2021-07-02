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
#include "../../inc/Files.h"

using Node::Vertex;
using Node::StatementType;
using Node::Type;
using Node::OperatorType;

namespace Tree
{
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