/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    AST.h

Abstract:    
    Модуль описывает функции парсинга и построения AST дерева программы.

Author:
    JulesIMF

Last Edit:
    20.12.2020 13:37

Edit Notes:
    
**********************************************************************/

#ifndef CPP_PARSE
#define CPP_PARSE

#include "Vertex.h"
#include "Lexer.h"

struct Parsed
{
    Node::Vertex* AST; //Хранит вершину с ошибкой в случае error != 0
    StringsHolder* holder;
    CompileError error;
};

class Parse
{
protected:
    Lexed lexed;
    size_t index= 0;
    Vector<Node::Vertex*> tokens;
    CompileError error = CompileError::NO_ERROR_;
    
    Node::Vertex* getFnc (void);
    Node::Vertex* getMain(void);
    Node::Vertex* getStmtCat
                   (void);
    Node::Vertex* getStmt(void);
    Node::Vertex* getCall(void);
    Node::Vertex* getAsgn(void);
    Node::Vertex* getLoop(void);
    Node::Vertex* getDvar(void);
    Node::Vertex* getCond(void);
    Node::Vertex* getRet (void);
    Node::Vertex* getExpr(void);
    Node::Vertex* getComp(void);
    Node::Vertex* getForm(void);
    Node::Vertex* getTerm(void);
    Node::Vertex* getPrim(void);
    Node::Vertex* getVarv(void);
    Node::Vertex* getType(void);

public:
    Parsed getParsed(char const* source, bool toDumpLexed = true);
    void deleteParser(void);
};

#endif