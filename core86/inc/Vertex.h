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
        VarType,
        Call,
        Delimiter,
        With,
        PgmEnd,
        In,
        Out,
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
        In      = 'I',
        Out     = 'O',
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
        Cont    = 'U',
        Break   = 'B',
    };

    struct VarDeclaration
    {
        StringsHolder::StringIter
            iter;

        // Ноль, если не массив
        long long nElements;
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

        int          nArgs;
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
            VarDeclaration  varDecl;
            char            delimiter;
        } 
        field;

        static Vertex* newVertex(
            Type    type, 
            size_t  row     = 0, 
            size_t  column  = 0, 
            Vertex* left    = nullptr, 
            Vertex* right   = nullptr);

        static void    deleteVertex(Vertex* vertex);
    };
}

#endif