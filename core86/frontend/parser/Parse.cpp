/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    AST.h

Abstract:    
    Модуль реализует функции парсинга и построения AST дерева программы.

Author:
    JulesIMF

Last Edit:
    20.12.2020 13:37

Edit Notes:
    
**********************************************************************/

#include "../../inc/Lexer.h"
#include "../../inc/Parse.h"

//---------------------DEFINES---------------------
#define VERTEX(type)    Vertex::newVertex(Type::type)
#define THIS            (*(tokens.at(index)))
#define TYPE            (THIS->type)
#define FIELD           (THIS->field)
#define CTYPE(tp, err)  if (!error && THIS->type != Type::tp) { error = CompileError::err; return nullptr; }
#define CSIZE           if (index >= tokens.size()) return nullptr;
#define CROSS_EXPECT    if (TYPE != Type::Delimiter || THIS->field.delimiter != '|') { error = CompileError::EXPECTED_CROSS; return nullptr; }
#define OPTYPE(type)    (TYPE == Type::Operator && FIELD.opType == OperatorType::type)

using namespace Node;



void Parse::deleteParser(void)
{
    tokens.deInit();
}


Parsed Parse::getParsed(char const* source, bool toDumpLexed)
{
    Lexer  lexer;
    Parsed parsed;
    lexed  = lexer.getLexed(source);
    tokens = lexed.tokens;

    if(toDumpLexed) 
        lexedDump(lexed);

    error  = lexed.noError ? NO_ERROR_ : PROCEEDED_ERROR;

    auto   funcLink = VERTEX(FuncLink);

    /*
    *   FNC+
    */
    while (index < tokens.size() && TYPE == Type::FuncDecl && !error)
    {
        auto oldFuncLink = funcLink;
        auto fnc         = getFnc();
        funcLink         = Vertex::newVertex(Type::FuncLink, 0, 0, oldFuncLink, fnc);
    }

    /*
    *   MAIN
    */
    if (!error && TYPE == Type::Main)
    {
        auto main       = THIS;
        index++;
        /*
        *   STMT
        */
        main->right      = getStmt();
        main->left       = funcLink;
        funcLink         = main;
    }

    else
        if(!error) error = CompileError::EXPECTED_MAIN;

    /*
    *   '\0'
    */

    if (!error && TYPE != Type::PgmEnd) error = CompileError::UNEXPECTED_END;

    //Обработка ошибок начинается, когда все остальные отказываются что-то делать
    if (error > CompileError::PROCEEDED_ERROR)
    {
        errorMessage("P%d %s на месте %d:%d во время разбора, индекс == %d\n", error, errorToStr(error), THIS->row, THIS->column, index);
        parsed.error = error;
        parsed.AST = THIS;
        return parsed;
    }

    parsed.error  = error;
    parsed.holder = lexed.holder;
    parsed.AST = funcLink;
    return parsed;
}


Vertex* Parse::getFnc(void)
{
    /*
    *   _def
    */

    //assert("Expected funcDecl", (TYPE == Type::FuncDecl));
    auto argList = THIS; argList->type = Type::ArgList;
    index++;
    /*
    *   ID
    */

    CTYPE(Id, EXPECTED_ID);
    FIELD.fnc.iter   = FIELD.iter;
    TYPE             = Type::FuncDecl;
    auto fnc         = THIS;
    size_t nArgs     = 0;
    index++;

    if (TYPE == Type::With)
    {
        /*
        * _with
        */
        Vertex::deleteVertex(argList);
        TYPE          = Type::ArgList;
        argList       = THIS;
        index++;

        /*
        *   ID
        */
        nArgs++;
        CTYPE(Id, EXPECTED_ID);
        argList->right = THIS;
        index++;

        //{',' ID}*
        while (!error && TYPE == Type::Delimiter && FIELD.delimiter == ',')
        {
            nArgs++;
            auto oldList   = argList;
            argList        = THIS;
            argList->type  = Type::ArgList;
            index++;
            CTYPE(Id, EXPECTED_ID);
            argList->left  = oldList;
            argList->right = THIS;
            index++;
        }    

        fnc->left = argList;
    }

    /*
    *   STMT_CAT
    */

    auto stmt = getStmtCat();
    if (stmt == nullptr)
    {
        if(!error) error = CompileError::EXPECTED_STMT_CAT;
        return nullptr;
    }
    
    
    fnc->right             = stmt;
    fnc->field.fnc.nArgs   = nArgs;
    return fnc;
}


Vertex* Parse::getMain(void)
{
    /*
    *   _main
    */
    CTYPE(Main, EXPECTED_MAIN);
    index++;

    /*
    *   STMT
    */
    return getStmt();
}


Vertex* Parse::getStmtCat(void)
{
    /*
    *   _begin
    */
    if (TYPE == Type::Delimiter && FIELD.delimiter == '{')
    {
        auto vertex  = THIS;
        index++;
        vertex->type = Type::StmtLink;
        Vertex* stmt = nullptr;

        /*
        *   {STMT}*
        */
        while ((stmt = getStmt()) && !error)
        {
            auto oldVertex = vertex;
            vertex = VERTEX(StmtLink);
            vertex->left   = oldVertex;
            vertex->right  = stmt;
        }

        /*
        *   _end
        */
        if (!(TYPE == Type::Delimiter && FIELD.delimiter == '}'))
        {
            if(!error) error = CompileError::EXPECTED_END;
            return nullptr;
        }
        index++;
        vertex->field.newScope = true;
        return vertex;
    }

    else
        return nullptr;
}


Vertex* Parse::getStmt(void)
{
    /*
    * STMT_CAT
    */
    auto stmt = getStmtCat();
    if (stmt)
        return stmt;

    /*
    *   _expr
    */
    if (TYPE != Type::StmtBegin) return nullptr;
    Vertex::deleteVertex(THIS);
    index++;

    /*
    *   {_break | _cont | CALL | LOOP | DVAR | COND | RET | ASGN}
    */

    stmt = getCall();    if (stmt) 
    { 
        stmt->type          = Type::Statement; 
        auto id             = VERTEX(Id);
        id->field.iter      = stmt->field.iter;
        stmt->field.stType  = StatementType::Call; 
        stmt->right         = id;
        return stmt; 
    }

    if(TYPE == Type::Statement && FIELD.stType == StatementType::Break ||
       TYPE == Type::Statement && FIELD.stType == StatementType::Cont)
    {
        auto expr = THIS;
        index++;
        return expr;
    }

    stmt = getLoop();    if (stmt) return stmt; if (error) return nullptr;
    stmt = getDvar();    if (stmt) return stmt; if (error) return nullptr;
    stmt = getCond();    if (stmt) return stmt; if (error) return nullptr;
    stmt = getRet ();    if (stmt) return stmt; if (error) return nullptr;
    stmt = getAsgn();    if (stmt) return stmt; if (error) return nullptr;
    
    error = CompileError::EXPECTED_STMT;
    return nullptr;
}


Vertex* Parse::getCall(void)
{
    /*
    *   _call
    */
    if (TYPE != Type::Call)
        return nullptr;

    Vertex::deleteVertex(THIS);
    index++;

    /*
    *   ID
    */
    CTYPE(Id, EXPECTED_ID);
    auto fncCall   = THIS;
    fncCall->type  = Type::Call;
    fncCall->field.fnc.iter
                   = fncCall->field.iter;
    index++;

    /*
    *   _delim
    */
    CROSS_EXPECT;
    auto argList = THIS; TYPE = Type::ArgList;
    index++;
    int nArgs = 0;



    
    if ( !(TYPE == Type::Delimiter && FIELD.delimiter == '|') )
    {
        /*
        *   EXPR
        */
        auto expr = getExpr();
        nArgs++;
        if (expr == nullptr)
        {
            if(!error) error = CompileError::EXPECTED_EXPR;
            return nullptr;
        }

        argList->right = expr;

        /*
        *   ','
        */
        while (TYPE == Type::Delimiter && FIELD.delimiter == ',')
        {
            nArgs++;
            auto oldList  = argList;
            argList = THIS; argList->type = Type::ArgList;
            index++;
            argList->left = oldList;
            /*
            *   EXPR
            */
            auto expr = getExpr();
            if (expr == nullptr)
            {
                if(!error) error = CompileError::EXPECTED_EXPR;
                return nullptr;
            }
            argList->right = expr;
        }
    }

    /*
    *   _delim
    */
    CROSS_EXPECT;
    Vertex::deleteVertex(THIS);
    index++;

    fncCall->left = argList;
    fncCall->field.fnc.nArgs = nArgs;


    ///*
    //*   STMT
    //*/

    //auto stmt = getStmt();
    //if (stmt == nullptr)
    //{
    //    error = CompileError::EXPECTED_STMT;
    //    return nullptr;
    //}
    //fncCall->right = stmt;

    return fncCall;
}


Vertex* Parse::getAsgn(void)
{
    if (index + 1 >= tokens.size())
        return nullptr;

    auto oldIndex = index;

    /*
    *   VARV
    */
    auto varv   = getVarv();
    if (error || varv == nullptr)
        return nullptr;

    /*
    *   _asgn
    */

    // VARV _asgn EXPR
    if (TYPE != Type::Statement ||
        FIELD.stType != StatementType::Asgn)
    {
        index = oldIndex;
        return nullptr;
    }
        
    auto asgn   = THIS;
    index++;

    /*
    *   EXPR
    */

    auto expr   = getExpr();

    if (error)  return nullptr;

    if (expr == nullptr)
    {
        error = CompileError::EXPECTED_EXPR;
        return nullptr;
    }

    asgn->left  = varv;
    asgn->right = expr;

    return asgn;
}


Vertex* Parse::getLoop(void)
{
    /*
    *   _loop
    */
    if (TYPE != Type::Statement || FIELD.stType != StatementType::Loop)
        return nullptr;

    auto loop = THIS;
    index++;

    /*
    *   '++'
    */
    CROSS_EXPECT;
    Vertex::deleteVertex(THIS);
    index++;

    /*
    *   EXPR
    */

    auto expr = getExpr();
    if (error) return nullptr;

    if (expr == nullptr)
    {
        error = CompileError::EXPECTED_EXPR;
        return nullptr;
    }

    /*
    *   '++'
    */
    CROSS_EXPECT;
    Vertex::deleteVertex(THIS);
    index++;


    /*
    *   STMT
    */
    auto stmt   = getStmt();
    if (error) return nullptr;

    if (expr == nullptr)
    {
        error = CompileError::EXPECTED_STMT;
        return nullptr;
    }

    loop->left  = expr;
    loop->right = stmt;

    return loop;
}


Vertex* Parse::getDvar(void)
{
    if (index + 2 >= tokens.size())
        return nullptr;

    if((*tokens.at(index+1))->type         != Type::Statement      || 
       (*tokens.at(index+1))->field.stType != StatementType::Dvar)
        return nullptr;

    /*
    *   ID
    */

    CTYPE(Id, EXPECTED_ID);
    auto id   = THIS;
    index++;

    /*
    *   _dvar
    */

    auto dvar = THIS;
    index++;

    /*
    *   TYPE
    */
    auto type = getType();
    if(type == nullptr)
    {
        error = CompileError::EXPECTED_TYPE;
        return nullptr;
    }

    dvar->left  = id;
    dvar->right = type;

    return dvar;
}


Vertex* Parse::getCond(void)
{
    if (THIS->type != Type::Statement || FIELD.stType != StatementType::Cond)
        return nullptr;

    /*
    *   _if
    */
    auto cond = THIS;
    index++;

    /*
    *   '++'
    */
    CROSS_EXPECT;
    Vertex::deleteVertex(THIS);
    index++;

    /*
    *   EXPR
    */
    auto expr     = getExpr();
    cond->left    = expr;
    if (error) return nullptr;

    /*
    *   '++'
    */
    CROSS_EXPECT;
    auto if_else  = THIS;
    if_else->type = Type::IfElse;
    index++;

    /*
    *   STMT
    */
    auto stmt     = getStmt();
    if (error)    return nullptr;
    if (stmt == nullptr)
    {
        error     = CompileError::EXPECTED_STMT;
        return    nullptr;
    }
    if_else->left = stmt;

    Vertex* Else  = nullptr;

    /*
    *   _else
    */
    if (TYPE == Type::Statement && FIELD.stType == StatementType::Else)
    {
        Vertex::deleteVertex(THIS); index++;

        /*
        *   STMT
        */
        Else = getStmt();
        if (error) return nullptr;
    }

    if_else->right = Else;
    cond->right    = if_else;
    return cond;
}


Vertex* Parse::getRet(void)
{
    if (TYPE != Type::Statement || FIELD.stType != StatementType::Ret) return nullptr;
    /*
    *   _ret
    */
    auto ret  = THIS;
    index++;
    
    /*
    *   EXPR
    */

    auto expr = getExpr();
    if (error) return nullptr;
    if (expr == nullptr)
    {
        error = CompileError::EXPECTED_EXPR;
        return nullptr;
    }
    
    ret->left = expr;

    return ret;
}


Vertex* Parse::getExpr(void)
{
    /*
    *   COMP
    */

    auto expr = getComp();

    /*
    *   [_and | _or]
    */
    while (OPTYPE(Or) || OPTYPE(And))
    {
        auto newExpr   = THIS; index++;

        /*
        *   COMP
        */
        auto comp      = getComp(); if(error) return nullptr;
        newExpr->left  = expr;
        newExpr->right = comp;
        expr           = newExpr;
    }

    return expr;
}


Vertex* Parse::getComp(void)
{
    /*
    *   FORM
    */
    auto comp = getForm();
    if (OPTYPE(Eq) || OPTYPE(Neq) || OPTYPE(Leq) || OPTYPE(Geq) || OPTYPE(Less) || OPTYPE(Gtr))
    {
        /*
        *   [_eq | _neq | _leq | _geq | _less | _gtr]
        */
        auto newComp = THIS; index++;

        /*
        *   FORM
        */
        auto form = getForm(); if (error) return nullptr;
        newComp->left   = comp;
        newComp->right  = form;
        comp            = newComp;
    }

    return comp;
}


Vertex* Parse::getForm(void)
{
    /*
    *   TERM
    */

    auto form = getTerm();

    /*
    *   [_add | _sub]
    */
    while (OPTYPE(Add) || OPTYPE(Sub))
    {
        auto newForm   = THIS; index++;

        /*
        *   TERM
        */
        auto term      = getTerm(); if(error) return nullptr;
        newForm->left  = form;
        newForm->right = term;
        form           = newForm;
    }

    return form;
}


Vertex* Parse::getTerm(void)
{
    /*
    *   PRIM
    */

    auto term = getPrim();

    /*
    *   [_mul | _div]
    */
    while (OPTYPE(Mul) || OPTYPE(Div))
    {
        auto newTerm   = THIS; index++;

        /*
        *   PRIM
        */
        auto prim      = getPrim(); if(error) return nullptr;
        newTerm->left  = term;
        newTerm->right = prim;
        term           = newTerm;
    }

    return term;
}


Vertex* Parse::getPrim()
{
    /*
    *   ['!' '-']
    */
    if (OPTYPE(Sub) || OPTYPE(Not))
    {
        auto unary   = THIS;
        index++;

        auto zero    = Vertex::newVertex(Type::Const); zero->field.lit = { 0, /*isInt = */ true };

        /*
        *   PRIM
        */
        auto prim    = getPrim(); if (error) { Vertex::deleteVertex(zero); return nullptr; }

        unary->left  = zero;
        unary->right = prim;
        return unary;
    }

    /*
    *   CALL
    */
    {
        auto call    = getCall();
        if (call)    return call;
    }

    /*
    *   '('
    */
    if (TYPE == Type::Delimiter && THIS->field.delimiter == '(')
    {
        Vertex::deleteVertex(THIS);
        index++;

        /*
        *   EXPR
        */

        auto expr = getExpr();

        /*
        *   ')'
        */
        if (!(TYPE == Type::Delimiter && THIS->field.delimiter == ')'))
        {
            if(!error) error = CompileError::EXPECTED_BRACKET;
            return nullptr;
        }

        Vertex::deleteVertex(THIS); index++;
        return expr;
    }


    /*
    *   NUMB
    */
    if (TYPE == Type::Const)
    {
        auto numb = THIS;
        index++;
        return numb;
    }

    /*
    *   VARV
    */
    auto varv   = getVarv();
    if(varv != nullptr)
        return varv;

    if(!error) error = CompileError::EXPECTED_PRIM;
    return nullptr;
}


Vertex* Parse::getVarv()
{
    // ID | ID '[' EXPR ']'
    if(TYPE != Type::Id)
        return nullptr;

    /*
    *   ID
    */
    auto id = THIS;
    index++;

    id->type = Type::Var;

    // '[' EXPR ']'

    /*
    *   '['
    */
    if(TYPE == Type::Delimiter && THIS->field.delimiter == '[')
    {
        index++;

        /*
        *   EXPR
        */
        auto expr = getExpr();
        if(expr == nullptr)
        {
            if(!error)
                error = CompileError::EXPECTED_EXPR;

            return nullptr;
        }

        /*
        *   ']'
        */
        if (!(TYPE == Type::Delimiter && THIS->field.delimiter == ']') )
        {
            error = CompileError::EXPECTED_RIGHTS;
            return nullptr;
        }

        else
        {
            index++;

            id->left = expr;
        }
    }

    return id;
}


Vertex* Parse::getType()
{
    // ID | ID '[' EXPR ']'
    if (TYPE != Type::Id)
        return nullptr;

    /*
    *   ID
    */
    auto id = THIS;
    index++;

    id->type                    = Type::VarType;
    id->field.varDecl.iter      = id->field.iter;
    id->field.varDecl.nElements = 0;

    // '[' NUMB ']'

    /*
    *   '['
    */
    if (TYPE == Type::Delimiter && THIS->field.delimiter == '[')
    {
        index++;

        CTYPE(Const, EXPECTED_CONST);
        id->field.varDecl.nElements = FIELD.lit.value;
        index++;

        /*
        *   ']'
        */
        if (!(TYPE == Type::Delimiter && THIS->field.delimiter == ']'))
        {
            error = CompileError::EXPECTED_RIGHTS;
            return nullptr;
        }

        index++;
    }

    return id;
}