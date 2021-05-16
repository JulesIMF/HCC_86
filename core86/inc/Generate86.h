/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    Generate86.h

Abstract:    
    
Author:
    JulesIMF

Last Edit:
    13.05.2021 03:48

Edit Notes:
    
**********************************************************************/

#ifndef CPP_GENERATE
#define CPP_GENERATE
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include "Vertex.h"
#include "VarTable.h"
#include "Lexer.h"
#include "CompilationStructs.h"

void constConvolution(Node::Vertex* vertex);

/*-----------------------------------------------------------*/
/*------------------------определения------------------------*/
/*-----------------------------------------------------------*/


bool isUnary(Node::Vertex* vertex);

struct Generator
{
public:
    struct Function
    {
        int stackFrame;
        int nArgs;
    };

protected:
    VarTable varTable;
    Table<Function>
        fncTable;
    StackImitate stackImit;

    CompileError error;
    StringsHolder *holder;
    StringsHolder::StringIter *currentFnc;
    Node::Vertex *errorVertex = nullptr;
    Compiled flow;
    int shift;
    int currentNArgs;
    int currentNVars;
    bool isInMain;

    void generate(Node::Vertex *vertex);

    void insertStd(void);

public:
    Compiled compile(Node::Vertex *ast, StringsHolder *holder_, bool debug = false);

protected:
    //------------------------------------------------------
    //----------------------STATEMENTS----------------------
    //------------------------------------------------------

    void genCallArgList(Node::Vertex *vertex);

    void genCall(Node::Vertex *vertex);

    void genRet(Node::Vertex *vertex);

    void genIf(Node::Vertex *vertex);

    void genLoop(Node::Vertex *vertex);

    void genAsgn(Node::Vertex *vertex);

    void genDvar(Node::Vertex *vertex);

    //------------------------------------------------------
    //---------------------!!STATEMENTS---------------------
    //------------------------------------------------------

    bool genOperator(Node::Vertex *vertex);

    bool genConst(Node::Vertex *vertex);

    bool genVarv(Node::Vertex *vertex);

    bool genExpr(Node::Vertex *vertex);

    //-----------------------------------------------------------------------------------------

    void genMain(Node::Vertex *vertex);

    void genFuncLink(Node::Vertex *vertex);

    void genFuncDecl(Node::Vertex *vertex);

    void genArgList(Node::Vertex *vertex);

    void genStmtLink(Node::Vertex *vertex);

    void genStatement(Node::Vertex *vertex);
};

#endif