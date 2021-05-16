/**********************************************************************
Copyright (c) 2020  MIPT

Module Name:
    Lexer.cpp

Abstract:
    Описывает функцию-лексер (лексический анализатор).

Author:
    JulesIMF

Last Edit:
    20.12.2020 7:53

Edit Notes:

**********************************************************************/

#ifndef CPP_LEXER
#define CPP_LEXER

#include <cstring>
#include "../common/Keywords.h"
#include "Vertex.h"
#include "Vector.h"
#include "StringsHolder.h"
#include "ErrorMessage.h"

struct Lexed
{
    Vector<Node::Vertex *> tokens;
    StringsHolder *holder;
    bool noError = true;
};

class Lexer
{
private:
    char const *source;
    CompileError error = CompileError::NO_ERROR_;
    size_t row, column;

    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------

    bool possible(char const *token);

    void checkSpace(void);

    void checkNoAlpha(void);

    void checkNoDigit(void);

    bool expected(char const *token);

    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------

#define isdef(token) bool is_##token(void);
    isdef(begin);
    isdef(end);
    isdef(expr);
    isdef(if);
    isdef(else);
    isdef(loop);
    isdef(def);
    isdef(with);
    isdef(asgn);
    isdef(dvar);
    isdef(main);
    isdef(return);
    isdef(call);
    isdef(fdelim);
    isdef(add);
    isdef(sub);
    isdef(mul);
    isdef(div);
    isdef(not);
    isdef(eq);
    isdef(neq);
    isdef(less);
    isdef(gtr);
    isdef(leq);
    isdef(geq);
    isdef(or);
    isdef(and);
    isdef(left);
    isdef(right);
    isdef(comma);
    isdef(comment);
#undef isdef

    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------

    long long getNumber(bool *isInt);

    StringsHolder::StringIter getId(Lexed *lexed);

    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------

public:
    Lexed getLexed(char const *source_);
};

void lexedDump(Lexed lexed);

#endif