/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    Vertex.h

Abstract:    
    
Author:
    JulesIMF

Last Edit:
    17.12.2020 19:53

Edit Notes:
    
**********************************************************************/

#ifndef CPP_VERTEX
#define CPP_VERTEX
#include "StringsHolder.h"
#include <cstddef>

namespace Node
{
    enum class Type
    {
        Id,
        Operator,
        Const,
        FuncLink,
        StmtLink,
        ArgList,
        Statement,
        StmtBegin,
        Main,
        FuncDecl,
        Var,
        Call,
        Delimiter,
        With,
        PgmEnd,
        IfElse,
    };


    enum class OperatorType
    {
        Add     = '+',
        Sub     = '-',
        Mul     = '*',
        Div     = '/',
        Not     = '!',
        Eq      = '=',
        Neq     = '~',
        Less    = '<',
        Gtr     = '>',
        Leq     = '(',
        Geq     = ')',
        Or      = '|',
        And     = '&',
    };

    enum class StatementType
    {
        Call    = 'C',
        Asgn    = 'A',
        Loop    = 'L',
        Dvar    = 'D',
        Cond    = 'I',
        Else    = 'E',
        Ret     = 'R',
    };

    struct stConst
    {
        long long value;
        bool      isInt;
    };

    struct stFnc
    {
        StringsHolder::StringIter
            iter;

        size_t          nArgs;
    };

    struct Vertex
    {
        Vertex *left, *right;
        size_t row, column;
        Type type;

        union
        {
            StringsHolder::StringIter 
                            iter;
            bool            newScope = false;
            OperatorType    opType;
            stConst         lit;
            stFnc           fnc;
            StatementType   stType;
            char            delimiter;
        } 
        field;

        static Vertex* newVertex(
            Type    type, 
            size_t  row = 0, 
            size_t  column = 0, 
            Vertex* left = nullptr, 
            Vertex* right = nullptr);

        static void    deleteVertex(Vertex* vertex);
    };
}

#endif